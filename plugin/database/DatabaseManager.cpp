#include "Vessel/DatabaseManager.h"
#include <juce_core/juce_core.h>
#include "Vessel/Chord.h"

// Define an enum for the column indices
enum ChordColumns {
    ID = 0,
    NAME,
    ROOT,
    CHORD_TYPE,
    NOTES,
    MIDI,
    SCALE,
    CONNECTIONS,
    FUNCTION
};

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

// This function runs migrations from SQL files that exist in plugin/config/migrations
void DatabaseManager::runMigrations() {
    juce::File migrationsDir = juce::File::getCurrentWorkingDirectory().getChildFile("plugin/config/migrations");
    if (!migrationsDir.isDirectory()) {
        std::cerr << "Migrations directory does not exist!" << std::endl;
        return;
    }

    for (auto& file : migrationsDir.findChildFiles(juce::File::findFiles, false, "*.sql")) {
        juce::String sql = file.loadFileAsString();
        char* errorMessage = nullptr;

        int resultCode = sqlite3_exec(db, sql.toRawUTF8(), nullptr, nullptr, &errorMessage);
        if (resultCode != SQLITE_OK) {
            std::cerr << "Error executing SQL from file " << file.getFileName() << ": " << errorMessage << std::endl;
            sqlite3_free(errorMessage);
        } else {
            std::cout << "Executed migration from file " << file.getFileName() << " successfully!" << std::endl;
        }
    }
}

// This function pulls all chord data from the database matching the specified "map_mode"
std::vector<Chord> DatabaseManager::getChords(const juce::String& map_mode) {
    std::vector<Chord> chords;
    juce::String sql = "SELECT * FROM chords WHERE map_mode = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.toRawUTF8(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
        return chords;
    }

    sqlite3_bind_text(stmt, 1, map_mode.toRawUTF8(), -1, SQLITE_STATIC);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, ChordColumns::ID);
        juce::String name = juce::String(reinterpret_cast<const char*>(sqlite3_column_text(stmt, ChordColumns::NAME)));
        juce::String root = juce::String(reinterpret_cast<const char*>(sqlite3_column_text(stmt, ChordColumns::ROOT)));
        juce::String chordType = juce::String(reinterpret_cast<const char*>(sqlite3_column_text(stmt, ChordColumns::CHORD_TYPE)));
        juce::String scale = juce::String(reinterpret_cast<const char*>(sqlite3_column_text(stmt, ChordColumns::SCALE)));
        juce::String function = juce::String(reinterpret_cast<const char*>(sqlite3_column_text(stmt, ChordColumns::FUNCTION)));

        Chord chord(id, name, root, chordType, scale, function);
        chords.push_back(chord);
    }

    sqlite3_finalize(stmt);
    return chords;
}
