#include <sqlite3.h>
#include <juce_core/juce_core.h>
#include <memory>
#include "Chord.h"

class DatabaseManager {
public:
    DatabaseManager(const juce::String& databasePath);
    ~DatabaseManager();

    void connect();
    void runMigrations();
    std::vector<Chord> getChords(const juce::String& map_mode);

private:
    sqlite3* db;

    int getCurrentMigrationRevision();
    int getLatestMigrationRevision();
    void applyMigrations(int currentRevision, int latestRevision);
};
