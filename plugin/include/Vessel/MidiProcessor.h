#pragma once

#include "Chord.h"


class MidiProcessor
{
    public:
        void process(juce::MidiBuffer& midiMessages);
        void setChords(const std::vector<Chord>& chordData);

    private:
        std::unordered_map<int, Chord> chords;
        juce::String tonalCenter = "C";
};
