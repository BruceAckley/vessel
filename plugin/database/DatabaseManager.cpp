#include <fstream> 
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


DatabaseManager::~DatabaseManager() {
    if (db) {
        sqlite3_close(db);
    }
}

void DatabaseManager::connect() {
    juce::File dbFile = juce::File::getSpecialLocation(juce::File::userApplicationDataDirectory).getChildFile("chords.db");

    int resultCode = sqlite3_open(dbFile.getFullPathName().toRawUTF8(), &db);

    if (resultCode) {
        auto message = sqlite3_errmsg(db);
        sqlite3_close(db);
        std::cerr << "Error opening database: " << message << std::endl;
    } else {
        std::cout << "Opened database successfully!" << std::endl;
        runMigrations();
    }
}

void DatabaseManager::runMigrations() {
    int currentRevision = getCurrentMigrationRevision();
    int latestRevision = getLatestMigrationRevision();

    if (currentRevision < latestRevision) {
        applyMigrations(currentRevision, latestRevision);
    }
}

int DatabaseManager::getCurrentMigrationRevision() {
    int revision = 0;
    const char* sql = "SELECT revision FROM migrations ORDER BY revision DESC LIMIT 1;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            revision = sqlite3_column_int(stmt, 0);
        }
        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
    }

    return revision;
}

int DatabaseManager::getLatestMigrationRevision() {
    int latestRevision = 0;
    juce::File migrationsDir = juce::File::getSpecialLocation(juce::File::currentApplicationFile).getChildFile("plugin/config/migrations");

    for (juce::DirectoryIterator iter(migrationsDir, false, "*.sql"); iter.next();) {
        juce::File file = iter.getFile();
        int revision = file.getFileNameWithoutExtension().getIntValue();
        if (revision > latestRevision) {
            latestRevision = revision;
        }
    }

    return latestRevision;
}

void DatabaseManager::applyMigrations(int currentRevision, int latestRevision) {
    juce::File migrationsDir = juce::File::getSpecialLocation(juce::File::currentApplicationFile).getChildFile("plugin/config/migrations");

    for (juce::DirectoryIterator iter(migrationsDir, false, "*.sql"); iter.next();) {
        juce::File file = iter.getFile();
        int revision = file.getFileNameWithoutExtension().getIntValue();

        if (revision > currentRevision && revision <= latestRevision) {
            std::ifstream migrationFile(file.getFullPathName().toStdString());
            std::string sql((std::istreambuf_iterator<char>(migrationFile)), std::istreambuf_iterator<char>());

            char* errMsg = nullptr;
            if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
                std::cerr << "Error applying migration " << revision << ": " << errMsg << std::endl;
                sqlite3_free(errMsg);
            } else {
                std::cout << "Applied migration " << revision << " successfully!" << std::endl;
            }
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
