#include <sqlite3.h>
#include <juce_core/juce_core.h>
#include <memory>
#include "Chord.h"

class DatabaseManager {
public:
    DatabaseManager();
    ~DatabaseManager();

    void connect();
    void runMigrations();
    std::vector<Chord> getChords(const juce::String& map_mode);

private:
    sqlite3* db;

    int getCurrentChordCount();
    void applyMigrations();
    void DatabaseManager::executeSQL(const char* sql, sqlite3* db);
    void openDatabaseConnection(sqlite3** db, const juce::File& dbFile);
};
