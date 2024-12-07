#pragma once

/*
* Chord Management
*
* - Maintain a mapping of MIDI keys to chords
* - Allows the dock to modify the MIDI output behavior
* - Provides functions to Add, Update, Remove, and Reorder chords
*/

class ChordManager {
    public:
        void assignChordToMidiKey(int midiKey, const Chord& chord);
        void removeChordFromMidiKey(int midiKey);
        Chord getChordForMidiKey(int midiKey);
    
    private:
        std::map<int, Chord> midiKeyChordMap;
};
