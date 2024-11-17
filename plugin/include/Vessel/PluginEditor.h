#pragma once

#include "PluginProcessor.h"
#include <juce_gui_extra/juce_gui_extra.h>

namespace audio_plugin
{
  class AudioPluginAudioProcessorEditor : public juce::AudioProcessorEditor
  {
  public:
    explicit AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor &);
    ~AudioPluginAudioProcessorEditor() override;

    void resized() override;

  private:
    using Resource = juce::WebBrowserComponent::Resource;
    std::optional<Resource> getResource(const juce::String &url);
    AudioPluginAudioProcessor &processorRef;
    const juce::String localDevServerAddress;

    juce::WebBrowserComponent webComponent{juce::WebBrowserComponent::Options{}
                                       .withBackend(juce::WebBrowserComponent::Options::Backend::webview2)
                                       .withWinWebView2Options(juce::WebBrowserComponent::Options::WinWebView2{}
                                                                   .withUserDataFolder(juce::File::getSpecialLocation(juce::File::SpecialLocationType::tempDirectory)))
                                       .withNativeIntegrationEnabled()
                                       .withNativeFunction("sayHello", [](auto &var, auto complete)
                                                           { complete("Hello " + var[0].toString()); })
                                       .withResourceProvider([this](const auto &url)
                                                             { return getResource(url); },
                                                             juce::URL{localDevServerAddress}.getOrigin())};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioPluginAudioProcessorEditor)
  };

} // namespace audio_plugin
