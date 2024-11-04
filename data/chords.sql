INSERT INTO chords_c3 
(name_c3, function, mood, region, root_c3, intervals, outbound, map_mode) VALUES 
-- Basic Diatonic, Tonic
('C', 'I', 'major', 'tonic', 'C3', '[0, 4, 7]', '[]', 'basic_diatonic'), 
('Cm', 'I-', 'minor', 'tonic', 'C3', '[0, 3, 7]', '[]', 'basic_diatonic'), 
('Eb', 'bIII', 'major', 'tonic', 'Eb3', '[0, 4, 7]', '[]', 'basic_diatonic'), 
('Am7b5', 'VI-7b5', 'half_diminished', 'tonic', 'A3', '[0, 3, 6, 10]', '[]', 'basic_diatonic'), 
('Am', 'VI-', 'minor', 'tonic', 'A3', '[0, 3, 7]', '[]', 'basic_diatonic'), 
-- Basic Diatonic, Subdominant
('F', 'IV', 'major', 'subdominant', 'F3', '[0, 4, 7]', '[]', 'basic_diatonic'), 
('Dm', 'II-', 'minor', 'subdominant', 'D3', '[0, 3, 7]', '[]', 'basic_diatonic'), 
('Fm', 'IV-', 'minor', 'subdominant', 'F3', '[0, 3, 7]', '[]', 'basic_diatonic'), 
('Dm7b5', 'II-7b5', 'half_diminished', 'subdominant', 'D3', '[0, 3, 6, 10]', '[]', 'basic_diatonic'), 
('Ab', 'bVI', 'major', 'subdominant', 'Ab3', '[0, 4, 7]', '[]', 'basic_diatonic'), 
-- Basic Diatonic, Dominant
('Bb', 'bVII', 'major', 'dominant', 'Bb3', '[0, 4, 7]', '[]', 'basic_diatonic'), 
('G', 'V', 'major_and_minor', 'dominant', 'G3', '[0, 4, 7]', '[]', 'basic_diatonic'), 
('Bdim', 'VII-dim', 'diminished', 'dominant', 'B3', '[0, 3, 6, 9]', '[]', 'basic_diatonic'), 
('Bm7b5', 'VII-7b5', 'half_diminished', 'dominant', 'B3', '[0, 3, 6, 10]', '[]', 'basic_diatonic');
