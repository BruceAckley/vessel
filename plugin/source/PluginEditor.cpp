#include "Vessel/PluginEditor.h"
#include "Vessel/PluginProcessor.h"

namespace audio_plugin
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

        enum class AssertAssetExists
        {
            no,
            yes
        };

        inline juce::File getExamplesDirectory() noexcept
        {
#ifdef PIP_JUCE_EXAMPLES_DIRECTORY
            MemoryOutputStream mo;

            auto success = Base64::convertFromBase64(mo, JUCE_STRINGIFY(PIP_JUCE_EXAMPLES_DIRECTORY));
            ignoreUnused(success);
            jassert(success);

            return mo.toString();
#elif defined PIP_JUCE_EXAMPLES_DIRECTORY_STRING
            return File{CharPointer_UTF8{PIP_JUCE_EXAMPLES_DIRECTORY_STRING}};
#else
            auto currentFile = juce::File::getSpecialLocation(juce::File::SpecialLocationType::currentApplicationFile);
            auto exampleDir = currentFile.getParentDirectory().getChildFile("examples");

            if (exampleDir.exists())
                return exampleDir;

            // keep track of the number of parent directories so we don't go on endlessly
            for (int numTries = 0; numTries < 15; ++numTries)
            {
                if (currentFile.getFileName() == "examples")
                    return currentFile;

                const auto sibling = currentFile.getSiblingFile("examples");

                if (sibling.exists())
                    return sibling;

                currentFile = currentFile.getParentDirectory();
            }

            return currentFile;
#endif
        }

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

    AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(
        AudioPluginAudioProcessor &p)
        : AudioProcessorEditor(&p), processorRef(p)
    {
        juce::ignoreUnused(processorRef);
        addAndMakeVisible(webComponent);

        webComponent.goToURL(webComponent.getResourceProviderRoot());
        setResizable(true, true);
        setSize(800, 600);
    }

    AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor() {}

    void AudioPluginAudioProcessorEditor::resized()
    {
        webComponent.setBounds(getLocalBounds());
    }

#if JUCE_ANDROID
    // The localhost is available on this address to the emulator
    const juce::String localDevServerAddress = "http://10.0.2.2:3000/";
#else
    const juce::String localDevServerAddress = "http://localhost:3000/";
#endif

    auto AudioPluginAudioProcessorEditor::getResource(const juce::String &url) -> std::optional<Resource>
    {
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
} // namespace audio_plugin
