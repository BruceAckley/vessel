INSERT INTO Chords (name, map_mode, scale, function, midi, notes, connections)
VALUES (
    'I',
    'simple_traditional',
    'Major',
    'Tonic',
    '[60, 64, 67]',                 -- MIDI notes as a JSON array
    '["C", "E", "G"]',              -- Notes as a JSON array (example)
    '["region_subdominant", "region_dominant"]'  -- Connections as a JSON array
);
