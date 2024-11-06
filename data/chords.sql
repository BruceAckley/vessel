INSERT INTO chords 
(function, mood, region, intervals, outbound, map_mode) VALUES
    -- Basic Diatonic, Tonic
    ('I', 'major', 'tonic', '0,4,7', '', 'basic_diatonic'), 
    ('I-', 'minor', 'tonic', '0,3,7', '', 'basic_diatonic'), 
    ('bIII', 'major', 'tonic', '0,4,7', '', 'basic_diatonic'), 
    ('VI-7b5', 'half_diminished', 'tonic', '0,3,6,10', '', 'basic_diatonic'), 
    ('VI-', 'minor', 'tonic', '0,3,7', '', 'basic_diatonic'), 
    -- Basic Diatonic, Subdominant
    ('IV', 'major', 'subdominant', '0,4,7', '', 'basic_diatonic'), 
    ('II-', 'minor', 'subdominant', '0,3,7', '', 'basic_diatonic'), 
    ('IV-', 'minor', 'subdominant', '0,3,7', '', 'basic_diatonic'), 
    ('II-7b5', 'half_diminished', 'subdominant', '0,3,6,10', '', 'basic_diatonic'), 
    ('bVI', 'major', 'subdominant', '0,4,7', '', 'basic_diatonic'), 
    -- Basic Diatonic, Dominant
    ('bVII', 'major', 'dominant', '0,4,7', '', 'basic_diatonic'), 
    ('V', 'major_and_minor', 'dominant', '0,4,7', '', 'basic_diatonic'), 
    ('VII-dim', 'diminished', 'dominant', '0,3,6,9', '', 'basic_diatonic'), 
    ('VII-7b5', 'half_diminished', 'dominant', '0,3,6,10', '', 'basic_diatonic');
