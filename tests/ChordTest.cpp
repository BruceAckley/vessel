#include <Vessel/Chord.h>
#include <gtest/gtest.h>

namespace vessel_test {
    TEST(Chord, Constructor) {
        Chord chord{"foo", "bar", "baz", "1,2,3"};
    }
}  // namespace vessel_test
