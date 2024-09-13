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
            juce::MidiBuffer processedMidi;
            for (const auto metadata : midiMessages) {
                auto message = metadata.getMessage();
                
                // DEBUG
                auto event = getEventString (message);
                auto timeStamp = message.getTimeStamp();
                auto channel = message.getChannel();
                auto data = getDataString (message);
                
                if (message.isNoteOnOrOff()) {
                    // Map the MIDI input to chords
                    // Example: Replace the note with a chord's note
                    for (const auto& chord : chords) {
                        if (message.getNoteNumber() == someCondition) { // Define your condition
                            // Modify the MIDI message based on the chord
                            // Example: Change the note number to the chord's root note
                            message.setNoteNumber(chord.notes[0].asMidi());
                        }
                    }
                }
                processedMidi.addEvent(message, metadata.samplePosition);
            }
            midiMessages.swapWith(processedMidi);
        }
};
