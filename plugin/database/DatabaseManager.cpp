#include <fstream> 
#include "Vessel/DatabaseManager.h"
#include <juce_core/juce_core.h>
#include "Vessel/Chord.h"

// SQLite column indices for the "chords" table
enum ChordColumns {
    ID = 0,
    FUNCTION,
    NOTES_REL_C3,
    SCALE,
    REGION
};

const int CHORD_COUNT = 7;

const char* dropChordsTable = "DROP TABLE chords;";

const char* createChordsTable = "CREATE TABLE IF NOT EXISTS chords ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "function TEXT NOT NULL,"
                    "notes_rel_c3 TEXT NOT NULL,"
                    "scale TEXT NOT NULL,"
                    "region TEXT NOT NULL"
                    ");";

DatabaseManager::DatabaseManager() {}

DatabaseManager::~DatabaseManager() {
    if (db) {
        sqlite3_close(db);
    }
}

void DatabaseManager::connect() {
    // Connect to db
    juce::File dbFile = juce::File::getSpecialLocation(juce::File::userApplicationDataDirectory).getChildFile("chords.db");
    int resultCode = sqlite3_open(dbFile.getFullPathName().toRawUTF8(), &db);
    if (resultCode) {
        auto message = sqlite3_errmsg(db);
        sqlite3_close(db);
        std::cerr << "Error opening database: " << message << std::endl;
    } else {
        std::cout << "Opened database successfully!" << std::endl;
    }

    char* errMsg = nullptr;
    if (sqlite3_exec(db, createChordsTable, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Error creating table: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

void DatabaseManager::runMigrations() {
    int currentChordCount = getCurrentChordCount();

    if (currentChordCount != CHORD_COUNT) {
        char* errMsg = nullptr;
        if (sqlite3_exec(db, dropChordsTable, nullptr, nullptr, &errMsg) != SQLITE_OK) {
            std::cerr << "Error dropping table: " << errMsg << std::endl;
            sqlite3_free(errMsg);
        }

        if (sqlite3_exec(db, createChordsTable, nullptr, nullptr, &errMsg) != SQLITE_OK) {
            std::cerr << "Error recreating table: " << errMsg << std::endl;
            sqlite3_free(errMsg);
        }

        applyMigrations();
    }
}

int DatabaseManager::getCurrentChordCount() {
    int count = 0;
    const char* sql = "SELECT count(*) FROM chords;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            count = sqlite3_column_int(stmt, 0);
        }
        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
    }

    return count;
}

void DatabaseManager::applyMigrations() {
    juce::File dataDir(DATA_DIR);
    if (!dataDir.exists() || !dataDir.isDirectory()) {
        std::cerr << "Data directory does not exist or is not a directory: " << DATA_DIR << std::endl;
        return;
    }

    juce::Array<juce::File> migrationFiles = dataDir.findChildFiles(juce::File::findFiles, false, "*.sql");
    for (const auto& file : migrationFiles) {
        juce::String sql = file.loadFileAsString();
        char* errMsg = nullptr;
        if (sqlite3_exec(db, sql.toRawUTF8(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
            std::cerr << "Error applying migration from file " << file.getFileName() << ": " << errMsg << std::endl;
            sqlite3_free(errMsg);
        }
    }
}

// This function pulls all chord data from the database matching the specified "map_mode"
std::vector<Chord> DatabaseManager::getChords(const juce::String& scale) {
    std::vector<Chord> chords;
    juce::String sql = "SELECT * FROM chords WHERE scale = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.toRawUTF8(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
        return chords;
    }

    sqlite3_bind_text(stmt, 1, scale.toRawUTF8(), -1, SQLITE_STATIC);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, ChordColumns::ID);
        juce::String function = juce::String((const char*)sqlite3_column_text(stmt, ChordColumns::FUNCTION));
        juce::String notes_rel_c3 = juce::String((const char*)sqlite3_column_text(stmt, ChordColumns::NOTES_REL_C3));
        juce::String scale = juce::String((const char*)sqlite3_column_text(stmt, ChordColumns::SCALE));
        juce::String region = juce::String((const char*)sqlite3_column_text(stmt, ChordColumns::REGION));

        Chord chord(function, notes_rel_c3, scale, region);
        juce::String tonalCenter = "E";
        chords.push_back(chord);
    }

    sqlite3_finalize(stmt);
    return chords;
}
