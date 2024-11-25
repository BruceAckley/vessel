#include "Vessel/Chord.h"


const std::map<juce::String, int> Chord::chordNameToMidi = {
    {"C", 0}, {"C#", 1}, {"D", 2}, {"D#", 3}, {"E", 4}, {"F", 5},
    {"F#", 6}, {"G", 7}, {"G#", 8}, {"A", 9}, {"A#", 10}, {"B", 11}
};

const std::map<juce::String, int> Chord::functionToMidiOffset = {
    // Tonic family (based on scale degrees)
    {"I", 0},    // Tonic
    {"bIII", 3}, // Flat third
    {"III", 4},  // Major third
    {"VI", 9},   // Major sixth
    {"VI-", 9},  // Minor sixth
    
    // Subdominant family
    {"II", 2},    // Major second
    {"II-", 2},   // Minor second
    {"IV", 5},    // Perfect fourth
    {"IV-", 5},   // Minor fourth
    {"bVI", 8},   // Flat sixth
    
    // Dominant family
    {"V", 7},     // Perfect fifth
    {"bVII", 10}, // Flat seventh
    {"VII", 11},  // Major seventh
    {"VII-", 11}  // Minor seventh
};

void Chord::setTonalCenter(int tonalCenter, int octave) {
    auto midiNoteForFunction = getMidiNoteFromFunction(function, tonalCenter);
    rootMidiNote = ((octave + 1) * 12) + tonalCenter + midiNoteForFunction;

    transposeIntervals();
}

std::vector<int> Chord::getMidiNotes() const {
    return transposedNotes;
}

void Chord::parseIntervals(const juce::String& intervalsCSV) {
    juce::StringArray intervalStrings;

    intervalStrings.addTokens(intervalsCSV, ",", "");

    for (const auto& interval : intervalStrings) {
        intervalPattern.push_back(interval.getIntValue());
    }
}

void Chord::transposeIntervals() {
    transposedNotes.clear();

    for (int interval : intervalPattern) {
        transposedNotes.push_back(rootMidiNote + interval);
    }
}

int Chord::getMidiNoteFromFunction(const juce::String& f, int t) {
    auto offset = functionToMidiOffset.find(f);
    if (offset != functionToMidiOffset.end()) {
        return t + offset->second;
    }
    return -1; // Invalid function
}
