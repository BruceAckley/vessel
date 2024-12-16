#include "Vessel/MidiProcessor.h"

const int OCTAVE = 3;

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
                chord.setTonalCenter(tonalCenter, OCTAVE);

                for (int note : chord.transposedNotes)
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

void MidiProcessor::setTonalCenter(int t)
{
    this->tonalCenter = t;
}

// TODO: Parse time signature meta-event, this will be useful for things
// like passing tones
// Example:
// // Get the current position and tempo information from the host
// AudioPlayHead* playHead = getPlayHead();
// if (playHead != nullptr)
// {
//     // Get the current time signature
//     int numerator = playHead->getTimeSignatureNumerator();
//     int denominator = playHead->getTimeSignatureDenominator();

//     // Use the time signature data as needed
//     DBG("Time signature: " << numerator << "/" << denominator);
// }
