#include <fstream>
#include "Vessel/DatabaseManager.h"
#include <juce_core/juce_core.h>
#include "Vessel/Chord.h"

enum ChordColumns
{
    ID = 0,
    FUNCTION,
    MOOD,
    REGION,
    INTERVALS,
    CADENCE,
    MAP_MODE
};

// Commands
const char *dropChordsTable = "DROP TABLE chords;";
const char *createChordsTable = "CREATE TABLE IF NOT EXISTS chords ("
                                "id INTEGER PRIMARY KEY, "
                                "name TEXT, "      // Name of the chord, e.g., "I", "bIII", "VI-7b5"
                                "function TEXT, "  // Harmonic function, e.g., "tonic", "subdominant", "dominant"
                                "mood TEXT, "      // Mood of the chord, e.g., "major", "minor", "half_diminished", "diminished"
                                "region TEXT, "    // Functional region, e.g., "tonic", "subdominant", "dominant"
                                "intervals TEXT, " // Intervals from the root, as a comma-separated string "0,4,7"
                                "cadence TEXT, "   // Contains IDs of chords that could come after in cadence
                                "map_mode TEXT "   // Mode of the map, e.g., "basic_diatonic"
                                ");";

DatabaseManager::DatabaseManager() {}

DatabaseManager::~DatabaseManager()
{
    if (db)
    {
        sqlite3_close(db);
    }
}

void DatabaseManager::openDatabaseConnection(sqlite3 **db, const juce::File &dbFile)
{
    int resultCode = sqlite3_open(dbFile.getFullPathName().toRawUTF8(), db);
    if (resultCode)
    {
        auto message = sqlite3_errmsg(*db);

        sqlite3_close(*db);

        std::cerr << "Error opening database: " << message << std::endl;
    }
    else
    {
        std::cout << "The database connected successfully" << std::endl;
    }
}

void DatabaseManager::executeSQL(const char *sql, sqlite3 *db)
{
    char *errMsg = nullptr;
    if (sqlite3_exec(db, sql, nullptr, nullptr, &errMsg) != SQLITE_OK)
    {
        std::cerr << "Error executing SQL: " << errMsg << std::endl;

        sqlite3_free(errMsg);
    }
}

int DatabaseManager::getCurrentChordCount()
{
    int count = 0;
    const char *sql = "SELECT count(*) FROM chords;";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK)
    {
        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            count = sqlite3_column_int(stmt, 0);
        }

        sqlite3_finalize(stmt);
    }
    else
    {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
    }

    return count;
}

void DatabaseManager::connect()
{
    // TODO: There is likely a better place to store the application data
    juce::File dbFile = juce::File::getSpecialLocation(juce::File::userApplicationDataDirectory).getChildFile("chords.db");

    openDatabaseConnection(&db, dbFile);
    executeSQL(createChordsTable, db);
}

void DatabaseManager::runMigrations()
{
    int currentChordCount = getCurrentChordCount();

    if (currentChordCount == 0)
    {
        applyMigrations();
    }
}

void DatabaseManager::applyMigrations()
{
    juce::File dataDir(DATA_DIR);

    if (!dataDir.exists() || !dataDir.isDirectory())
    {
        std::cerr << "Data directory does not exist or is not a directory: " << DATA_DIR << std::endl;

        return;
    }

    juce::Array<juce::File> migrationFiles = dataDir.findChildFiles(juce::File::findFiles, false, "*.sql");

    for (const auto &file : migrationFiles)
    {
        juce::String sql = file.loadFileAsString();

        executeSQL(sql.toRawUTF8(), db);
    }
}

/**
 * @brief Retrieves all chord data from the database matching the specified "map_mode".
 *
 * This function executes a SQL query to select all chords from the database
 * where the map_mode matches the provided parameter. The results are stored
 * in a vector of Chord objects.
 *
 * @param map_mode The map mode to filter chords by.
 * @return A vector of Chord objects matching the specified map mode.
 */
std::vector<Chord> DatabaseManager::getChords(const juce::String &map_mode)
{
    std::vector<Chord> chords;
    juce::String sql = "SELECT * FROM chords WHERE map_mode = ?;";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql.toRawUTF8(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;

        return chords;
    }

    sqlite3_bind_text(stmt, 1, map_mode.toRawUTF8(), -1, SQLITE_STATIC);

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        juce::String function = juce::String((const char *)sqlite3_column_text(stmt, ChordColumns::FUNCTION));
        juce::String mood = juce::String((const char *)sqlite3_column_text(stmt, ChordColumns::MOOD));
        juce::String region = juce::String((const char *)sqlite3_column_text(stmt, ChordColumns::REGION));
        juce::String intervals = juce::String((const char *)sqlite3_column_text(stmt, ChordColumns::INTERVALS));

        Chord chord(function, mood, region, intervals);

        chords.push_back(chord);
    }

    sqlite3_finalize(stmt);

    return chords;
}
