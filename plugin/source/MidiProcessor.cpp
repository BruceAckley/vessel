#include "Vessel/MidiProcessor.h"

void MidiProcessor::setChords(const std::vector<Chord> &chordData)
{
    int keyboardDefaultNote = 60;
    for (const auto &chord : chordData)
    {
        chords[keyboardDefaultNote] = chord;
        keyboardDefaultNote++;
    }
}

void MidiProcessor::process(juce::MidiBuffer &midiMessages)
{
    juce::MidiBuffer processedMidi;
    for (const auto metadata : midiMessages)
    {
        auto message = metadata.getMessage();

        if (message.isNoteOnOrOff())
        {
            int midiNote = message.getNoteNumber();
            auto it = chords.find(midiNote);

            if (it != chords.end())
            {
                Chord chord = it->second;
                chord.setTonalCenter(tonalCenter);
                std::vector<int> notes = chord.getMidiNotes();

                for (int note : notes)
                {
                    if (message.isNoteOn())
                    {
                        juce::MidiMessage noteOnMessage = juce::MidiMessage::noteOn(message.getChannel(), note, message.getVelocity());
                        processedMidi.addEvent(noteOnMessage, metadata.samplePosition);
                    }
                    else if (message.isNoteOff())
                    {
                        juce::MidiMessage noteOffMessage = juce::MidiMessage::noteOff(message.getChannel(), note);
                        processedMidi.addEvent(noteOffMessage, metadata.samplePosition);
                    }
                }
            }
        }
    }

    midiMessages.swapWith(processedMidi);
}
