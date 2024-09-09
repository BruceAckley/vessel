#include <sqlite3.h>
#include <juce_core/juce_core.h>
#include <memory>

class DatabaseManager {
    public:
        DatabaseManager(const juce::String& databasePath);
        ~DatabaseManager();

        void connect();

    private:
        sqlite3* db;
};
