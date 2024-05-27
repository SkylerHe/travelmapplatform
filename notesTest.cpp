#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <crow.h>
#include <doctest.h>
#include <string>
#include "notes.h"

using namespace std;  
using namespace crow;  



TEST_CASE("Testing Notes Class") 
{
    // Testing Notes constructor
    SUBCASE("Testing the Notes Constructor") 
    {
        // Create a new Notes class from json.
        Notes testNotes(json::load(R"({"wordCounts":100,"notesCategory":"Dairy", "mediaType":"Notes","isPublic": false, "id":4})"));

        // Check that the constructor properly loaded the values.
        CHECK(testNotes.getId() == 4);
        CHECK(testNotes.getWordCounts() == 100);
        CHECK(testNotes.getNotesCategory() == "Dairy");
        CHECK(testNotes.getMediaType() == "Notes");
        CHECK(testNotes.getIsPublic() == false);
    }

    // Testing convertToJson method
    SUBCASE("Testing the convertToJson Method") 
    {
        // Create a new Notes class from json.
        Notes testNotes(json::load(R"({"wordCounts":100,"notesCategory":"Dairy", "mediaType":"Notes","isPublic": false, "id":4})"));
                                        

        // Convert the Notes class to json using the convertToJson method.
        json::wvalue jsonOutput = testNotes.convertToJson();

        // Convert back to a json read value for testing.
        json::rvalue jsonReadValue = json::load(jsonOutput.dump());

        // Check the values.
        CHECK(jsonReadValue["id"].i() == 4);
        CHECK(jsonReadValue["wordCounts"].i() == 100);
        CHECK(jsonReadValue["notesCategory"].s() == "Dairy");
        CHECK(jsonReadValue["mediaType"].s() == "Notes");
        CHECK(jsonReadValue["isPublic"].b() == false);

    }

    // Testing updateFromJson method
    SUBCASE("Testing updateFromJson Method") 
    {
        // Create a new Notes class from json.
        Notes testNotes(json::load(R"({"wordCounts":100,"notesCategory":"Dairy", "mediaType":"Notes", "isPublic": false, "id":4})"));
                                        

        // Create the update json.
        json::rvalue updateJson = json::load(R"({"wordCounts":200,"notesCategory":"Description", "mediaType":"Notes", "isPublic": true, "id":5})");
                                        

        // Update the Notes with the updateFromJson method. 
        testNotes.updateFromJson(updateJson);

        // Check the updated values.
        CHECK(testNotes.getId() == 5);
        CHECK(testNotes.getWordCounts() == 200);
        CHECK(testNotes.getNotesCategory() == "Description");
        CHECK(testNotes.getMediaType() == "Notes");
        CHECK(testNotes.getIsPublic() == true);
    }
}