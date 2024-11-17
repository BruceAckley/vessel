# Chords Database Schema Documentation

This document provides an overview of the chords table schema used in the project.

## Table: 

**chords**

The chords table stores information about the combinations of notes available to the midi processor, including their function, mood, region, intervals, cadence, and map mode. The user interface allows for filtering of the chords based on their attributes, refining the set of chords visualized for the user.

### Columns

- **function**: The harmonic function of the chord (e.g., "I", "bIII", "VI-7b5"). The project functions on the principle of tonal harmony, and the harmonic function defines the chord's roman numeral function notation. This is irrespective of the key, or in tonal harmony, the tonal center.
- **mood**: The mood of the chord (e.g., "major", "minor", "half_diminished", "diminished"). The mood will be used by the visualizer to position the chord relative to other chords with the same mood in the map.
- **region**: The functional region of the chord (e.g., "tonic", "subdominant", "dominant"). In functional tonal harmony, the function determines the family of chords and how cadences can be added to chord progressions. The region is further used by the visualizer to determine the position of the chords and add dissonance information.
- **intervals**: The intervals that make up the chord, represented as a comma-separated list of semitone values (e.g., "0,4,7"). The application will use this information to build the proper chord in the current key.
- **cadence**: The cadence information associated with the chord (TODO: currently empty in the provided data). 
- **map_mode**: The map mode categorizing the chord (e.g., "basic_diatonic_contemporary"). This is the attrbute the project will use to filter the chords to add to the map visualizer.

### Sample Data

The following are examples of chord entries in the chords table:

#### Basic Diatonic, Tonic
- **I**: major, tonic, 0,4,7, , basic_diatonic_contemporary
- **I-**: minor, tonic, 0,3,7, , basic_diatonic_contemporary
- **bIII**: major, tonic, 0,4,7, , basic_diatonic_contemporary
- **VI-7b5**: half_diminished, tonic, 0,3,6,10, , basic_diatonic_contemporary
- **VI-**: minor, tonic, 0,3,7, , basic_diatonic_contemporary

#### Basic Diatonic, Subdominant
- **IV**: major, subdominant, 0,4,7, , basic_diatonic_contemporary
- **II-**: minor, subdominant, 0,3,7, , basic_diatonic_contemporary
- **IV-**: minor, subdominant, 0,3,7, , basic_diatonic_contemporary
- **II-7b5**: half_diminished, subdominant, 0,3,6,10, , basic_diatonic_contemporary
- **bVI**: major, subdominant, 0,4,7, , basic_diatonic_contemporary

#### Basic Diatonic, Dominant
- **bVII**: major, dominant, 0,4,7, , basic_diatonic_contemporary
- **V**: major_and_minor, dominant, 0,4,7, , basic_diatonic_contemporary
- **VII-dim**: diminished, dominant, 0,3,6,9, , basic_diatonic_contemporary
- **VII-7b5**: half_diminished, dominant, 0,3,6,10, , basic_diatonic_contemporary

### Notes

- The `cadence` column is currently empty for all entries in the provided data.
- The map_mode column categorizes the chords into different modes, such as "basic_diatonic_contemporary".

This schema allows for the organization and retrieval of chord data based on their harmonic function, mood, region, and other characteristics.
