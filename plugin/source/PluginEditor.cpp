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
    } // namespace

    AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(
        AudioPluginAudioProcessor &p)
        : AudioProcessorEditor(&p), processorRef(p),
          webView(juce::WebBrowserComponent::Options{}
                      .withResourceProvider([this](const auto &url)
                            { return getResource(url); }
                      )
                      .withNativeIntegrationEnabled()
        )
    {
        juce::ignoreUnused(processorRef);
        addAndMakeVisible(webView);

        webView.goToURL(webView.getResourceProviderRoot());
        setResizable(true, true);
        setSize(800, 600);
    }

    AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor() {}

    void AudioPluginAudioProcessorEditor::resized()
    {
        webView.setBounds(getLocalBounds());
    }

    auto AudioPluginAudioProcessorEditor::getResource(const juce::String &url) const -> std::optional<Resource>
    {
        static const auto resourceFileRoot = juce::File{R"(/Users/bruceackley/projects/vessel/plugin/ui/public)"};
        const auto resourceToRetrieve = url == "/" ? "index.html" : url.fromFirstOccurrenceOf("/", false, false);
        const auto resource = resourceFileRoot.getChildFile(resourceToRetrieve).createInputStream();

        if (resource)
        {
            const auto extension = resourceToRetrieve.fromLastOccurrenceOf(".", false, false);
            return Resource{streamToVector(*resource), getMimeForExtension(extension)}; 
        }

        return std::nullopt;
    }
} // namespace audio_plugin
