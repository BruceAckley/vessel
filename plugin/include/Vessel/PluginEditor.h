#pragma once

#include "PluginProcessor.h"
#include "juce_gui_basics/juce_gui_basics.h"
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_extra/juce_gui_extra.h>

namespace vessel
{

  class AudioPluginAudioProcessorEditor : public juce::AudioProcessorEditor
  {
  public:
    explicit AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor &);
    ~AudioPluginAudioProcessorEditor() override;

    void resized() override;

  private:
    using Resource = juce::WebBrowserComponent::Resource;

    std::optional<Resource> getResource(const juce::String &url) const;

    void nativeFunction(
        const juce::Array<juce::var> &args,
        juce::WebBrowserComponent::NativeFunctionCompletion completion);

    juce::TextButton runJavaScriptButton{"Run some JavaScript"};
    juce::TextButton emitJavaScriptEventButton{"Emit JavaScript event"};
    juce::Label labelUpdatedFromJavaScript{"label",
                                           "To be updated from JavaScript"};

    AudioPluginAudioProcessor &processorRef;

    juce::Label tonalCenterLabel{"tonal center label", "Tonal Center"};
    juce::ComboBox tonalCenterComboBox{"tonal center combo box"};
    juce::ComboBoxParameterAttachment tonalCenterComboBoxAttachment;

    // Web*Relay class instances must be initialized before the
    // WebBrowserComponent because the WebBrowserComponent calls their methods in
    // its constructor.
    juce::WebComboBoxRelay webTonalCenterRelay;

    juce::WebBrowserComponent webView;

    // Web*ParameterAttachment class instances must be initialized after
    // the WebBrowserComponent because they interact with it
    // transitively through Web*Relay class instances.
    juce::WebComboBoxParameterAttachment webTonalCenterComboBoxAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioPluginAudioProcessorEditor)
  };

} // namespace vessel
