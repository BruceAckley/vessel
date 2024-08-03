#pragma once


class MidiProcessor
{
    public:
        static juce::String getEventString (const juce::MidiMessage& m)
        {
            if (m.isNoteOn())           return "Note on";
            if (m.isNoteOff())          return "Note off";
            if (m.isProgramChange())    return "Program change";
            if (m.isPitchWheel())       return "Pitch wheel";
            if (m.isAftertouch())       return "Aftertouch";
            if (m.isChannelPressure())  return "Channel pressure";
            if (m.isAllNotesOff())      return "All notes off";
            if (m.isAllSoundOff())      return "All sound off";
            if (m.isMetaEvent())        return "Meta event";

            if (m.isController())
            {
                const auto* name = juce::MidiMessage::getControllerName (m.getControllerNumber());
                return "Controller " + (name == nullptr ? juce::String (m.getControllerNumber()) : juce::String (name));
            }

            return juce::String::toHexString (m.getRawData(), m.getRawDataSize());
        }

        static juce::String getDataString (const juce::MidiMessage& m)
        {
            if (m.isNoteOn())           return juce::MidiMessage::getMidiNoteName (m.getNoteNumber(), true, true, 3) + " Velocity " + juce::String (m.getVelocity());
            if (m.isNoteOff())          return juce::MidiMessage::getMidiNoteName (m.getNoteNumber(), true, true, 3) + " Velocity " + juce::String (m.getVelocity());
            if (m.isProgramChange())    return juce::String (m.getProgramChangeNumber());
            if (m.isPitchWheel())       return juce::String (m.getPitchWheelValue());
            if (m.isAftertouch())       return juce::MidiMessage::getMidiNoteName (m.getNoteNumber(), true, true, 3) +  ": " + juce::String (m.getAfterTouchValue());
            if (m.isChannelPressure())  return juce::String (m.getChannelPressureValue());
            if (m.isController())       return juce::String (m.getControllerValue());

            return {};
        }

        void process(juce::MidiBuffer& midiMessages)
        {
            for (const auto metadata : midiMessages)
            {
                auto midi = metadata.getMessage();
                auto event = getEventString (midi);
                auto timeStamp = midi.getTimeStamp();
                auto channel = midi.getChannel();
                auto data = getDataString (midi);
            }
        }
};

// Left off at 19:50  here: https://www.youtube.com/watch?v=tgf6J8foCiw

// TODO: Chord model
// - When user hits a note, what happens? The note is mapped to a chord and that chord is output as MIDI.
// - Black keys are fifths, like Nopia (double check how that was presented)
//      - Chord being played is displayed in plugin
//      - Notes making up the chord being played are displayed
//      - Dissonance level is shown (based on tonic, subdominant, or dominant)
//      - Recommended next chords (based on connections) are shown, along with the key on the keyboard to use for that chord
