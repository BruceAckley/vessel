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
    void executeSQL(const char* sql, sqlite3* db_pointer);
    void openDatabaseConnection(sqlite3** db_pointer, const juce::File& dbFile);
};
