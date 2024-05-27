#include "notes.h"

using namespace std;
using namespace crow;


Notes::Notes(json::rvalue readValueJson)  
{
    updateFromJson(readValueJson);
}


// Convert to JSON
json::wvalue Notes::convertToJson() 
{
    // Convert the base Media part
    json::wvalue writeJson = Media::convertToJson();

    // Add Notes-specific details
    writeJson["wordCounts"] = wordCounts;
    writeJson["notesCategory"] = notesCategory;

    return writeJson;
}

// Update from JSON
void Notes::updateFromJson(json::rvalue readValueJson) 
{
    // Update the base Media part
    Media::updateFromJson(readValueJson); 

    // Update Notes-specific details
    wordCounts = readValueJson["wordCounts"].i();
    notesCategory = readValueJson["notesCategory"].s();

}