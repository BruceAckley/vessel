#include <vector>
#include <string>


struct Note {
    std::string name;  // "C", "F#", "Ab"
    int octave;        // 4, 5, 6

    Note(std::string n, int o)
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

struct Chord {
    std::string name;           // The display name of the chord
    std::string root;           // The root note of the chord, like "C"
    std::string chordType;      // The type of the chord, like "major" or "minor"
    std::vector<Note> notes;    // The notes that make up the chord
    std::vector<int> midi;      // The notes that make up the chord as midi
    std::string scale;          // The scale, like "Major"
    std::vector<std::string> connections;   // The recommended transitions from the chord
    std::string function;       // The chord function, like "tonic"

    Chord(std::string r, std::string type, std::vector<Note> n)
        : root(r), chordType(type), notes(n) {
            midi = asMidi();
        }

    std::vector<int> asMidi() {
        for (const auto& note : notes) {
            int midiNote = note.asMidi();
            midi.push_back(midiNote);
        }
    }
};
