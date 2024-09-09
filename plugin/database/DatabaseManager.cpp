#include "Vessel/sqlite3.h"
#include "Vessel/DatabaseManager.h"
#include <juce_core/juce_core.h>

namespace audio_plugin {
DatabaseManager::~DatabaseManager() {}

void DatabaseManager::connect() {
    juce::File dbFile = juce::File::getSpecialLocation(juce::File::tempDirectory).getChildFile("chords.db");

    int resultCode = sqlite3_open(dbFile.getFullPathName().toRawUTF8(), &db);

    if (resultCode) {
        auto message = sqlite3_errmsg(db);
        sqlite3_close(db);
    } else {
        std::cout << "Opened database successfully!" << std::endl;
    }
}
}  // namespace audio_plugin
