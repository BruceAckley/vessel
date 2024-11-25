#include "Vessel/PluginEditor.h"
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_events/juce_events.h>
#include <optional>
#include <ranges>
#include "Vessel/PluginProcessor.h"
#include "juce_core/juce_core.h"
#include "juce_graphics/juce_graphics.h"
#include "juce_gui_extra/juce_gui_extra.h"
#include "Vessel/ParameterIDs.h"

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
                      // allowedOriginIn parameter is necessary to
                      // retrieve resources from the C++ backend even if
                      // on live server
                      juce::URL{LOCAL_DEV_SERVER_ADDRESS}.getOrigin())
                  .withInitialisationData("vendor", JUCE_COMPANY_NAME)
                  .withInitialisationData("pluginName", JUCE_PRODUCT_NAME)
                  .withInitialisationData("pluginVersion", JUCE_PRODUCT_VERSION)
                  .withUserScript("console.log(\"C++ backend here: This is run "
                                  "before any other loading happens\");")
                  .withEventListener(
                      "exampleJavaScriptEvent",
                      [this](juce::var objectFromFrontend)
                      {
                          labelUpdatedFromJavaScript.setText(
                              "example JavaScript event occurred with value " +
                                  objectFromFrontend.getProperty("emittedCount", 0)
                                      .toString(),
                              juce::dontSendNotification);
                      })
                  .withOptionsFrom(webTonalCenterRelay)},
          webTonalCenterComboBoxAttachment{
              *processorRef.state.getParameter(id::TONAL_CENTER.getParamID()),
              webTonalCenterRelay, nullptr}
    {
        addAndMakeVisible(webView);
        webView.goToURL(juce::WebBrowserComponent::getResourceProviderRoot());

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
        webView.setBounds(getLocalBounds());
    }

    auto AudioPluginAudioProcessorEditor::getResource(const juce::String &url) const
        -> std::optional<Resource>
    {
        std::cout << "ResourceProvider called with " << url << std::endl;

        static const auto resourceFilesRoot =
            juce::File::getSpecialLocation(
                juce::File::SpecialLocationType::currentApplicationFile)
                .getParentDirectory()
                .getParentDirectory()
                .getChildFile("public");

        [[maybe_unused]] static auto printRootOnce = []
        {
            std::cout << "Resource files root is "
                      << resourceFilesRoot.getFullPathName() << std::endl;
            return true;
        }();

        const auto resourceToRetrieve =
            url == "/" ? "index.html" : url.fromFirstOccurrenceOf("/", false, false);

        const auto resource =
            resourceFilesRoot.getChildFile(resourceToRetrieve).createInputStream();
        if (resource)
        {
            const auto extension =
                resourceToRetrieve.fromLastOccurrenceOf(".", false, false);
            return Resource{streamToVector(*resource), getMimeForExtension(extension)};
        }

        return std::nullopt;
    }
} // namespace vessel
