#include "Chord.h"
#include <map>


enum MapMode {
    simple_traditional,
    simple_jazz,
    advanced_traditional,
    advanced_jazz
};

static const std::map<MapMode, std::vector<Chord>> chordMap = {
    {MapMode::simple_traditional, {
        {}
    }}
};
