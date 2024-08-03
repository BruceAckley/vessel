#include <juce_core/juce_core.h>
#include <iostream>

class Chord
{
public:
    Chord(const juce::String& name, const juce::Array<int>& notes)
        : chordName(name), midiNotes(notes)
    {
    }

    const juce::String& getName() const { return chordName; }
    const juce::Array<int>& getNotes() const { return midiNotes; }

private:
    juce::String chordName;
    juce::Array<int> midiNotes;
};

juce::Array<Chord> loadChordsFromJson(const juce::File& jsonFile)
{
    juce::Array<Chord> chords;

    if (!jsonFile.existsAsFile())
    {
        juce::Logger::writeToLog("JSON file does not exist.");
        return chords;
    }

    juce::var parsedJson = juce::JSON::parse(jsonFile);

    if (parsedJson.isVoid())
    {
        juce::Logger::writeToLog("Failed to parse JSON.");
        return chords;
    }

    auto* jsonArray = parsedJson.getProperty("chords", juce::var()).getArray();

    if (jsonArray == nullptr)
    {
        juce::Logger::writeToLog("Invalid JSON format.");
        return chords;
    }

    for (auto& jsonValue : *jsonArray)
    {
        auto jsonObject = jsonValue.getDynamicObject();
        if (jsonObject == nullptr) continue;

        juce::String chordName = jsonObject->getProperty("name").toString();
        juce::Array<int> midiNotes;
        auto notesVar = jsonObject->getProperty("notes");

        if (auto* notesArray = notesVar.getArray())
        {
            for (auto& note : *notesArray)
            {
                midiNotes.add(static_cast<int>(note));
            }
        }

        chords.add(Chord(chordName, midiNotes));
    }

    return chords;
}

void printChords(const juce::Array<Chord>& chords)
{
    for (const auto& chord : chords)
    {
        std::cout << "Chord: " << chord.getName() << " Notes: ";
        for (const auto note : chord.getNotes())
        {
            std::cout << note << " ";
        }
        std::cout << std::endl;
    }
}
