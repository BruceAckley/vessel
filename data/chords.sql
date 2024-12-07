INSERT INTO chords 
(function, mood, region, intervals, root_note_offset, cadence, map_mode) VALUES
    -- Basic Diatonic, Tonic
    ('I', 'major', 'tonic', '0,4,7', 0, '', 'basic_diatonic_contemporary'), 
    ('I-', 'minor', 'tonic', '0,3,7', 0, '', 'basic_diatonic_contemporary'), 
    ('bIII', 'major', 'tonic', '0,4,7', 3, '', 'basic_diatonic_contemporary'), 
    ('VI-7b5', 'half_diminished', 'tonic', '0,3,6,10', 9, '', 'basic_diatonic_contemporary'), 
    ('VI-', 'minor', 'tonic', '0,3,7', 9, '', 'basic_diatonic_contemporary'), 
    -- Basic Diatonic, Subdominant
    ('IV', 'major', 'subdominant', '0,4,7', 5, '', 'basic_diatonic_contemporary'), 
    ('II-', 'minor', 'subdominant', '0,3,7', 2, '', 'basic_diatonic_contemporary'), 
    ('IV-', 'minor', 'subdominant', '0,3,7', 5, '', 'basic_diatonic_contemporary'), 
    ('II-7b5', 'half_diminished', 'subdominant', '0,3,6,10', 2, '', 'basic_diatonic_contemporary'), 
    ('bVI', 'major', 'subdominant', '0,4,7', 8, '', 'basic_diatonic_contemporary'), 
    -- Basic Diatonic, Dominant
    ('bVII', 'major', 'dominant', '0,4,7', 10, '', 'basic_diatonic_contemporary'), 
    ('V', 'major_and_minor', 'dominant', '0,4,7', 7, '', 'basic_diatonic_contemporary'), 
    ('VII-dim', 'diminished', 'dominant', '0,3,6,9', 11, '', 'basic_diatonic_contemporary'), 
    ('VII-7b5', 'half_diminished', 'dominant', '0,3,6,10', 11, '', 'basic_diatonic_contemporary');
