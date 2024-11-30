#include <Vessel/Chord.h>
#include <gtest/gtest.h>

namespace vessel_test
{
    TEST(Chord, BasicChord)
    {
        Chord c3{"I", "major", "tonic", "0,4,7", 0};
        c3.setTonalCenter(0, 3);                         // C3
        std::vector<int> expectedC3Notes = {48, 52, 55}; // C3, E3, G3
        Chord c4{"I", "major", "tonic", "0,4,7", 0};
        c4.setTonalCenter(0, 4);                         // C4
        std::vector<int> expectedC4Notes = {60, 64, 67}; // C4, E4, G4

        ASSERT_EQ(c3.transposedNotes, expectedC3Notes);
        ASSERT_EQ(c4.transposedNotes, expectedC4Notes);
    }

    TEST(Chord, MinorChord)
    {
        Chord c3Minor{"I-", "minor", "tonic", "0,3,7", 0};
        c3Minor.setTonalCenter(0, 3);                    // C3
        std::vector<int> expectedC3Notes = {48, 51, 55}; // C3, Eb3, G3
        Chord c4Minor{"I-", "minor", "tonic", "0,3,7", 0};
        c4Minor.setTonalCenter(0, 4);                    // C4
        std::vector<int> expectedC4Notes = {60, 63, 67}; // C4, Eb4, G4

        ASSERT_EQ(c3Minor.transposedNotes, expectedC3Notes);
        ASSERT_EQ(c4Minor.transposedNotes, expectedC4Notes);
    }

    TEST(Chord, bVIIChord)
    {
        Chord dbVII{"bVII", "minor", "dominant", "0,4,7", 10};
        dbVII.setTonalCenter(0, 3);                         // C3
        std::vector<int> expecteddbVIINotes = {58, 62, 65}; // C3, Eb3, G3

        ASSERT_EQ(dbVII.transposedNotes, expecteddbVIINotes);
    }
} // namespace vessel_test
