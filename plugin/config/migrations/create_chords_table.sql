CREATE TABLE IF NOT EXISTS Chords (
    id INTEGER PRIMARY KEY AUTOINCREMENT,      -- Unique identifier for the chord
    name TEXT NOT NULL,                        -- The display name of the chord
    map_mode TEXT,                             -- The map mode (e.g., "simple_traditional")
    scale TEXT,                                -- The scale (e.g., "Major")
    function TEXT,                             -- The chord function (e.g., "Tonic")
    root TEXT,                                 -- The root note of the chord (e.g., "C")
    chordType TEXT,                            -- The chord type (e.g., "major" or "minor")
    midi TEXT,                                 -- MIDI notes as a serialized JSON array or string
    notes TEXT,                                -- Chord notes as a serialized JSON array or string
    connections TEXT                           -- Recommended chord transitions as a serialized JSON array or string
);
