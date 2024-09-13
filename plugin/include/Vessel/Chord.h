#ifndef CHORD_H
#define CHORD_H

#include <vector>
#include <string>
#include <map>
#include <stdexcept>

class Note {
public:
    std::string name;  // "C", "F#", "Ab"
    int octave;        // 4, 5, 6

    Note(const std::string& n, int o)
        : name(n), octave(o) {}

    int asMidi() const {
        static const std::map<std::string, int> noteToMidi = {
            {"C", 0}, {"C#", 1}, {"Db", 1}, {"D", 2}, {"D#", 3}, {"Eb", 3}, {"E", 4}, {"F", 5},
            {"F#", 6}, {"Gb", 6}, {"G", 7}, {"G#", 8}, {"Ab", 8}, {"A", 9}, {"A#", 10}, {"Bb", 10}, {"B", 11}
        };

        auto it = noteToMidi.find(name);

        if (it != noteToMidi.end()) {
            return it->second + (octave + 1) * 12;
        } else {
            throw std::invalid_argument("Invalid note name");
        }
    }
};

class Chord {
public:
    int id;                     // The unique identifier for the chord
    juce::String name;           // The display name of the chord
    juce::String root;           // The root note of the chord, like "C"
    juce::String chordType;      // The type of the chord, like "major" or "minor"
    std::vector<Note> notes;    // The notes that make up the chord
    std::vector<int> midi;      // The notes that make up the chord as midi
    juce::String scale;          // The scale, like "Major"
    std::vector<juce::String> connections;   // The recommended transitions from the chord
    juce::String function;       // The chord function, like "tonic"

    Chord(int id, const juce::String& name, const juce::String& root, const juce::String& chordType, const juce::String& scale, const juce::String& function)
        : id(id), name(name), root(root), chordType(chordType), scale(scale), function(function) {
            midi = asMidi();
        }

    std::vector<int> asMidi() {
        std::vector<int> midiNotes;
        for (const auto& note : notes) {
            int midiNote = note.asMidi();
            midiNotes.push_back(midiNote);
        }
        return midiNotes;
    }
};

#endif // CHORD_H
