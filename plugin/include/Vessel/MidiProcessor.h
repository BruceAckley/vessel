#pragma once

#include "Chord.h"


class MidiProcessor
{
    public:
        juce::String TONAL_CENTER = "C";
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

        void load_dbg_info(juce::MidiMessage message) {
            auto event = getEventString (message);
            auto timeStamp = message.getTimeStamp();
            auto channel = message.getChannel();
            auto data = getDataString (message);
        }

        void process(juce::MidiBuffer& midiMessages)
        {
            juce::MidiBuffer processedMidi;
            for (const auto metadata : midiMessages) {
                auto message = metadata.getMessage();

                load_dbg_info(message);

                if (message.isNoteOnOrOff()) {
                    int midiNote = message.getNoteNumber();
                    auto it = chords.find(midiNote);

                    if (it != chords.end()) {
                        Chord chord = it->second;
                        chord.setTonalCenter(TONAL_CENTER);
                        std::vector<int> notes = chord.getMidiNotes();
                        for (int note : notes) {
                            if (message.isNoteOn()) {
                                juce::MidiMessage noteOnMessage = juce::MidiMessage::noteOn(message.getChannel(), note, message.getVelocity());
                                processedMidi.addEvent(noteOnMessage, metadata.samplePosition);
                            } else if (message.isNoteOff()) {
                                juce::MidiMessage noteOffMessage = juce::MidiMessage::noteOff(message.getChannel(), note);
                                processedMidi.addEvent(noteOffMessage, metadata.samplePosition);
                            }
                        }
                    }
                }
            }

            midiMessages.swapWith(processedMidi);
        }

        void setChords(const std::vector<Chord>& chordData) {
            int keyboardDefaultNote = 60;
            for (const auto& chord : chordData) {
                chords[keyboardDefaultNote] = chord;
                keyboardDefaultNote++;
            }
        }

    private:
        std::unordered_map<int, Chord> chords;
};
