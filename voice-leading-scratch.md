POSSIBLE MVP:

Your plugin sounds like an excellent tool for composers and musicians wanting to explore tonal harmony with intelligent chord suggestions and voice-leading assistance. For a Minimum Viable Product (MVP), we’ll want to prioritize the core functionality, a clear UI, and responsive controls. Here’s a breakdown of the features and controls needed:

### 1. **Core Functionalities**  
   - **Chord Identification**:
     - **MIDI Input Analysis**: Detects and identifies chords from incoming MIDI data.
     - **Chord Display**: Displays detected chord names on the interface (e.g., Cmaj7, Gm9).
   
   - **Chord Suggestion / Progression Exploration**:
     - **MIDI Output**: Allows the user to send suggested chords as MIDI output to the DAW.
     - **Progression Suggestion**: Provides possible chord progressions based on current chords, e.g., diatonic options, secondary dominants, or modal interchange.

   - **Chord Modification for Voice Leading**:
     - **Voice Leading and Passing Note Recommendations**: Analyzes chord transitions and suggests alterations for smoother voice leading, such as neighboring or passing tones.

### 2. **UI Controls and Parameters**
   - **Chord Detection Display**:
     - Display the current chord detected from MIDI input, with labels like chord root, quality (major, minor, diminished, etc.), and extensions (7, 9, 13).
   
   - **Progression Exploration Controls**:
     - **Chord Suggestions Panel**: Show suggestions for chords to follow the current one. Options to accept, modify, or replace a chord in a progression.
     - **Preview Button**: Play or preview a suggested chord or progression before committing to it.
   
   - **Voice Leading & Modifications Panel**:
     - **Smooth Transitions Toggle**: Turns on/off suggestions for smooth voice-leading.
     - **Passing Note Toggle**: Adds suggestions for possible passing notes between chords.
     - **Adjustment Parameters**: Sliders or knobs to control the complexity and range of the voice-leading and passing note modifications.
   
   - **Additional Controls**:
     - **Key & Scale Selector**: Let users set a key and scale to influence chord suggestions.
     - **MIDI In/Out Selectors**: Manage routing of MIDI input and output to and from the plugin.
     - **Mode Selector (Analyze/Suggest/Modify)**: Switch between analyzing chords, suggesting new ones, or modifying an existing progression.

### 3. **Additional Considerations for MVP**
   - **Real-Time Performance**: Ensure that chord detection and suggestions are responsive.
   - **MIDI Mapping and DAW Integration**: Smoothly connect to DAW tracks, allowing MIDI data flow for a seamless experience.
   - **Visual Feedback**: Display an easily readable chord map or guide for users to visualize harmonic relationships.

Would you like to dive into specifics on any of these components? Or explore potential UI/UX wireframes for the plugin?


---


The approach *Mapping Tonal Harmony Pro* uses—visualizing harmonic relationships in a circular map where chord functions are grouped by their roles and relative positions—is built on well-established music theory concepts. This type of visualization can be found in various theoretical resources and has been used historically in different forms, so the basic idea isn’t proprietary. However, the specific design and implementation by MDecks, including particular layouts, graphics, and user interface details, would be protected by copyright.

You can definitely create a similar chord map that’s inspired by functional harmony and tonal relationships, as long as it has unique visual and structural elements. Here are some ways to create a distinct, intuitive chord map:

1. **Functional Rings**: Use concentric circles or distinct zones to represent different harmonic functions (tonic, subdominant, dominant), with each ring containing the chords in that category. This differs from MDecks' design but still captures functional relationships.

2. **Radial Progressions**: Chords could radiate out from the center according to their relative distance from the tonic or key center, with chords more likely to resolve inwards toward the center. This would allow users to visualize both key changes and tonal distance.

3. **Color-Coded Paths and Arrows**: Use unique color coding and arrows to suggest typical chord transitions and pathways for voice leading without replicating their visual styling. Paths could adjust dynamically based on the current chord or key.

4. **Interactive Modes and Highlighting**: Create a dynamic interaction where hovering or clicking on a chord highlights its likely progressions or resolutions, showing different options for major/minor key modulations. This interactivity adds unique functionality without directly copying any specific layout.

5. **Chord Clusters for Diatonic and Non-Diatonic Options**: Separate clusters for diatonic chords in the selected key, with additional clusters or spokes for borrowed chords, secondary dominants, or substitutions that help in modulating to other keys.

6. **Rotational Animation**: To add uniqueness, the entire map could rotate to reorient the tonic or current key chord at the top or center, making it clear how other chords relate to the "home" chord. 

By combining these elements, you can create a fresh, functional chord map that is distinct from *Mapping Tonal Harmony Pro* but equally intuitive and rich for tonal exploration.



---


To determine which notes make up a specific chord like **A♭7♯11**, you can follow these steps. This example breaks down the intervals typically used to build chords and can be applied to any chord type once you’ve set up a structure for each chord in your database.

### Step 1: **Understand the Basic Chord Structure**

The chord **A♭7♯11** is an **A♭ dominant seventh** chord with an added **♯11** (sharp eleventh). Here’s a breakdown of its components:

1. **Root**: **A♭**
2. **Major third**: **C** (4 semitones above the root)
3. **Perfect fifth**: **E♭** (7 semitones above the root)
4. **Minor seventh**: **G♭** (10 semitones above the root)
5. **Sharp eleventh**: **D** (an augmented fourth above the root, which is 6 semitones plus an octave, or 18 semitones)

### Step 2: **Translate Chord Symbols to Intervals**

For consistency and flexibility, store each chord type as intervals relative to the root in your static database. The intervals for **A♭7♯11** would be:

- **0** (root)
- **4** (major third)
- **7** (perfect fifth)
- **10** (minor seventh)
- **18** (sharp eleventh)

### Step 3: **Calculate Notes Based on the Root**

If you’re analyzing **A♭7♯11**:
1. Start with the **A♭** root note (MIDI number or pitch class).
2. Apply the intervals to find each note:
   - **A♭** + 0 semitones = **A♭**
   - **A♭** + 4 semitones = **C**
   - **A♭** + 7 semitones = **E♭**
   - **A♭** + 10 semitones = **G♭**
   - **A♭** + 18 semitones (sharp eleventh) = **D** (which is 6 semitones above the fifth but adjusted to the next octave).

### Step 4: **Transposition for Any Root Note**

Once this chord structure is stored in intervals, you can transpose it to any root by adding the root’s pitch class to each interval. For example, if you want **C7♯11**:
- Root note: **C** (typically 0 as the starting note in a C-major scale).
- Add each interval: **0, 4, 7, 10, and 18**.
- This would yield: **C, E, G, B♭, and F♯** for the **C7♯11** chord.

### Summary for **A♭7♯11**:
- **A♭, C, E♭, G♭, and D**.

This method will let you determine chord notes for any chord type on your map by simply changing the root note and applying the stored interval patterns, which is ideal for efficient chord transposition in a plugin.


----


Creating an algorithm for smooth voice leading involves adjusting the notes of each chord to minimize the motion between successive notes in a progression. Here’s a step-by-step approach to designing an algorithm that prioritizes minimal movement, common tones, and optimal positioning for smooth transitions:

### 1. **Define the Rules for Voice Leading**
   - **Minimize Motion**: Each note should move by the smallest possible interval (ideally within a semitone or a whole step).
   - **Preserve Common Tones**: Retain notes that are shared between chords to avoid unnecessary movement.
   - **Close Positioning**: Use chord inversions and voicings that position the chord tones as close to each other as possible.
   - **Consider Optimal Range**: Ensure that each voice stays within a natural range for smoothness and coherence (e.g., avoid large octave jumps).
   - **Leading Tone Resolution**: In traditional harmony, resolve leading tones (e.g., the 7th in dominant chords) stepwise up or down.

### 2. **Set Up Your Chord Structure**
   - Define each chord as a list of intervals from the root.
   - For example, a C major chord could be represented as `[0, 4, 7]` (C, E, G), while a G7 chord could be `[0, 4, 7, 10]` (G, B, D, F).
   - Store chords with their respective pitches in MIDI numbers or pitch classes for easier transposition.

### 3. **Write the Voice Leading Algorithm**
   
Here’s a basic algorithm for smooth voice leading between two chords, `Chord1` and `Chord2`:

```cpp
#include <vector>
#include <cmath>
#include <algorithm>

// Function to find the closest note in the target chord for each note in the current chord
std::vector<int> smoothVoiceLeading(const std::vector<int>& chord1, const std::vector<int>& chord2) {
    // Resulting chord with voice-leading adjustments
    std::vector<int> voicedChord;

    for (int note : chord1) {
        // Find the closest note in chord2 to the current note
        int closestNote = chord2[0];
        int minDistance = std::abs(note - chord2[0]);

        for (int targetNote : chord2) {
            int distance = std::abs(note - targetNote);
            if (distance < minDistance) {
                minDistance = distance;
                closestNote = targetNote;
            }
        }

        // Add the closest note to the voiced chord
        voicedChord.push_back(closestNote);
    }

    return voicedChord;
}
```

### Explanation of the Algorithm
1. **Iterate Through Each Note in `Chord1`**: For each note in `Chord1`, find the closest possible pitch in `Chord2`.
2. **Determine the Minimal Movement**: For each note in `Chord1`, calculate the distance to each note in `Chord2` and select the closest note.
3. **Build the Voiced Chord**: Store the closest notes from `Chord2` in a new `voicedChord` list. This list represents the target chord with voice leading applied.

### 4. **Optimize for Common Tones**
   - If you find any common tones between `Chord1` and `Chord2`, retain those without movement. This can be done by checking if a `note` in `Chord1` also exists in `Chord2` and directly copying it over.

### 5. **Enhance the Algorithm with Inversion Selection (Optional)**
   - To reduce motion further, consider chord inversions that bring chord tones closer together. You could test different inversions of `Chord2` and pick the one that minimizes the total distance to `Chord1`.

### 6. **Add Leading Tone Rules (Optional)**
   - For a more classical voice leading, apply a special rule for leading tones (e.g., in dominant chords). If `Chord1` is a dominant seventh, resolve its seventh stepwise down in `Chord2`.

### Example Usage
For a progression from `C` (C, E, G) to `G7` (G, B, D, F), the algorithm will attempt to keep:
- **C** moving to the closest tone (possibly to **B**).
- **E** moving minimally (perhaps to **D**).
- **G** staying in place if possible (as both chords share G).

### Optimizations
To improve further:
- **Weight the distances**: Prefer common tones and close semitone movements over larger movements.
- **Experiment with inversions and voicings**: Calculate the cost of different voicings and choose the one with minimal total movement.

This algorithm will provide a flexible framework for achieving smooth voice leading in your plugin! Adjusting parameters (e.g., voice range constraints, weighting of common tones) allows you to fine-tune the voice leading to different styles, such as jazz or classical.