#include "Vessel/Chord.h"

// Define noteMap here
const std::map<juce::String, int> Chord::noteMap = {
    {"C", 0}, {"C#", 1}, {"D", 2}, {"D#", 3}, {"E", 4}, {"F", 5},
    {"F#", 6}, {"G", 7}, {"G#", 8}, {"A", 9}, {"A#", 10}, {"B", 11}
};

void Chord::setTonalCenter(const juce::String& tonalCenter, int octave)
{
    if (noteMap.find(tonalCenter) == noteMap.end())
        throw std::invalid_argument("Invalid tonal center");

    rootMidiNote = (octave + 1) * 12 + noteMap.at(tonalCenter);
    transposeIntervals();
}

std::vector<int> Chord::getMidiNotes() const
{
    return transposedNotes;
}

void Chord::parseIntervals(const juce::String& intervalsCSV)
{
    juce::StringArray intervalStrings;
    intervalStrings.addTokens(intervalsCSV, ",", "");
    for (const auto& interval : intervalStrings)
    {
        intervalPattern.push_back(interval.getIntValue());
    }
}

void Chord::transposeIntervals()
{
    transposedNotes.clear();
    for (int interval : intervalPattern)
    {
        transposedNotes.push_back(rootMidiNote + interval);
    }
}
