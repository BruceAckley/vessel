#include "Vessel/PluginEditor.h"
#include "Vessel/PluginProcessor.h"
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_events/juce_events.h>
#include <optional>
#include <ranges>
#include "juce_core/juce_core.h"
#include "juce_graphics/juce_graphics.h"
#include "juce_gui_extra/juce_gui_extra.h"

using juce::ParameterID;

namespace vessel
{
    namespace
    {

        std::vector<std::byte> streamToVector(juce::InputStream &stream)
        {
            // Workaround to make ssize_t work cross-platform.
            using namespace juce;
            const auto sizeInBytes = static_cast<size_t>(stream.getTotalLength());
            std::vector<std::byte> result(sizeInBytes);
            stream.setPosition(0);
            [[maybe_unused]] const auto bytesRead =
                stream.read(result.data(), result.size());
            jassert(bytesRead == static_cast<ssize_t>(sizeInBytes));
            return result;
        }

        static const char *getMimeForExtension(const juce::String &extension)
        {
            static const std::unordered_map<juce::String, const char *> mimeMap = {
                {{"htm"}, "text/html"},
                {{"html"}, "text/html"},
                {{"txt"}, "text/plain"},
                {{"jpg"}, "image/jpeg"},
                {{"jpeg"}, "image/jpeg"},
                {{"svg"}, "image/svg+xml"},
                {{"ico"}, "image/vnd.microsoft.icon"},
                {{"json"}, "application/json"},
                {{"png"}, "image/png"},
                {{"css"}, "text/css"},
                {{"map"}, "application/json"},
                {{"js"}, "text/javascript"},
                {{"woff2"}, "font/woff2"}};

            if (const auto it = mimeMap.find(extension.toLowerCase());
                it != mimeMap.end())
                return it->second;

            jassertfalse;
            return "";
        }

        constexpr auto LOCAL_DEV_SERVER_ADDRESS = "http://127.0.0.1:8080";

        enum class AssertAssetExists
        {
            no,
            yes
        };

        static juce::String getExtension(juce::String filename)
        {
            return filename.fromLastOccurrenceOf(".", false, false);
        }

        inline std::unique_ptr<juce::InputStream> createAssetInputStream(const char *resourcePath,
                                                                         [[maybe_unused]] AssertAssetExists assertExists = AssertAssetExists::yes)
        {
#if JUCE_ANDROID
            ZipFile apkZip(juce::File::getSpecialLocation(juce::File::invokedExecutableFile));
            const auto fileIndex = apkZip.getIndexOfFileName("assets/" + String(resourcePath));

            if (fileIndex == -1)
            {
                jassert(assertExists == AssertAssetExists::no);
                return {};
            }

            return std::unique_ptr<juce::InputStream>(apkZip.createStreamForEntry(fileIndex));
#else
#if JUCE_IOS
            auto assetsDir = juce::File::getSpecialLocation(juce::File::currentExecutableFile)
                                 .getParentDirectory()
                                 .getChildFile("Assets");
#elif JUCE_MAC
            // auto assetsDir = juce::File::getSpecialLocation(juce::File::currentExecutableFile)
            //                      .getParentDirectory()
            //                      .getParentDirectory()
            //                      .getChildFile("ui")
            //                      .getChildFile("Assets");

            static const auto assetsDir = juce::File{R"(/Users/bruceackley/projects/vessel/plugin/ui/Assets)"};
#else
            auto assetsDir = getExamplesDirectory().getChildFile("Assets");
#endif

            auto resourceFile = assetsDir.getChildFile(resourcePath);

            if (!resourceFile.existsAsFile())
            {
                jassert(assertExists == AssertAssetExists::no);
                return {};
            }

            return resourceFile.createInputStream();
#endif
        }

        static juce::ZipFile *getZipFile()
        {
            static auto stream = createAssetInputStream("webviewplugin-gui_1.0.0.zip", AssertAssetExists::no);

            if (stream == nullptr)
                return nullptr;

            static juce::ZipFile f{stream.get(), false};
            return &f;
        }
    } // namespace

    AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor &p)
        : AudioProcessorEditor(&p),
          processorRef(p),
          tonalCenterComboBoxAttachment{
              *processorRef.state.getParameter(id::TONAL_CENTER.getParamID()),
              tonalCenterComboBox, nullptr},
          webTonalCenterRelay{"tonalCenterComboBox"},
          webView{
              juce::WebBrowserComponent::Options{}
                  .withBackend(
                      juce::WebBrowserComponent::Options::Backend::webview2)
                  .withWinWebView2Options(
                      juce::WebBrowserComponent::Options::WinWebView2{}
                          .withBackgroundColour(juce::Colours::black)
                          .withUserDataFolder(juce::File::getSpecialLocation(
                              juce::File::SpecialLocationType::tempDirectory)))
                  .withNativeIntegrationEnabled()
                  .withResourceProvider(
                      [this](const auto &url)
                      { return getResource(url); },
                      juce::URL{LOCAL_DEV_SERVER_ADDRESS}.getOrigin())
                  .withInitialisationData("vendor", JUCE_COMPANY_NAME)
                  .withInitialisationData("pluginName", JUCE_PRODUCT_NAME)
                  .withInitialisationData("pluginVersion", JUCE_PRODUCT_VERSION)
                  .withOptionsFrom(webTonalCenterRelay)},
          webTonalCenterComboBoxAttachment{
              *processorRef.state.getParameter(id::TONAL_CENTER.getParamID()),
              webTonalCenterRelay, nullptr}
    {
        addAndMakeVisible(webView);
        webView.goToURL(juce::WebBrowserComponent::getResourceProviderRoot());

        // This can be used for hot reloading
        // webView.goToURL(LOCAL_DEV_SERVER_ADDRESS);

        addAndMakeVisible(tonalCenterLabel);

        const auto tonalCenterParameter =
            dynamic_cast<juce::AudioParameterChoice *>(
                processorRef.state.getParameter(id::TONAL_CENTER.getParamID()));
        tonalCenterComboBox.addItemList(tonalCenterParameter->choices, 1);
        tonalCenterComboBox.setSelectedItemIndex(
            tonalCenterParameter->getIndex(), juce::dontSendNotification);
        addAndMakeVisible(tonalCenterComboBox);

        setResizable(true, true);
        setSize(800, 600);
    }

    AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor() {}

    void AudioPluginAudioProcessorEditor::resized()
    {
        auto bounds = getBounds();
        tonalCenterLabel.setBounds(bounds.removeFromTop(50).reduced(5));
        tonalCenterComboBox.setBounds(bounds.removeFromTop(50).reduced(5));
    }

    auto AudioPluginAudioProcessorEditor::getResource(const juce::String &url) -> std::optional<Resource>
    {
        // TODO:
        // X Revert to zip file loading
        // X Fix the midiprocessor mapping of tonal center to a midi note (this was actually right)
        // - Fix parameter IDs import
        // - Build
        // - Finish menu component

        // CODE FROM WOLF SOUND TUTORIAL:
        // static const auto resourceFilesRoot =
        //     juce::File::getSpecialLocation(
        //         juce::File::SpecialLocationType::currentApplicationFile)
        //         .getParentDirectory()
        //         .getParentDirectory()
        //         .getChildFile("public");

        // const auto resourceToRetrieve =
        //     url == "/" ? "index.html" : url.fromFirstOccurrenceOf("/", false, false);

        // const auto resource =
        //     resourceFilesRoot.getChildFile(resourceToRetrieve).createInputStream();

        // if (resource) {
        //     const auto extension =
        //         resourceToRetrieve.fromLastOccurrenceOf(".", false, false);
        //     return Resource(streamToVector(*resource), getMimeForExtension(extension));
        // }

        // return std::nullopt;

        // EXISTING CODE THAT GRABS THE REACT BUILD:
        const auto urlToRetrive = url == "/" ? juce::String{"index.html"}
                                             : url.fromFirstOccurrenceOf("/", false, false);

        if (auto *archive = getZipFile())
        {
            if (auto *entry = archive->getEntry(urlToRetrive))
            {
                auto stream = rawToUniquePtr(archive->createStreamForEntry(*entry));
                auto v = streamToVector(*stream);
                auto mime = getMimeForExtension(getExtension(entry->filename).toLowerCase());
                return juce::WebBrowserComponent::Resource{std::move(v),
                                                           std::move(mime)};
            }
        }

        if (urlToRetrive == "index.html")
        {
            auto fallbackIndexHtml = createAssetInputStream("webviewplugin-gui-fallback.html");
            return juce::WebBrowserComponent::Resource{streamToVector(*fallbackIndexHtml),
                                                       juce::String{"text/html"}};
        }

        return std::nullopt;
    }
} // namespace vessel
