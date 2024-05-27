#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <crow.h>
#include <doctest.h>
#include <string>
#include "media.h"

using namespace std;  
using namespace crow;  



TEST_CASE("Testing Media Class") 
{
    // Testing Media constructor
    SUBCASE("Testing the Media Constructor") 
    {
        // Create a new Media class from json.
        Media testMedia(json::load(R"({"mediaType":"Photos","isPublic": false, "id":1})"));

        // Check that the constructor properly loaded the values.
        CHECK(testMedia.getId() == 1);
        CHECK(testMedia.getMediaType() == "Photos");
        CHECK(testMedia.getIsPublic() == false);
    }

    // Testing convertToJson method
    SUBCASE("Testing the convertToJson Method") 
    {
        // Create a new Media class from json.
        Media testMedia(json::load(R"({"mediaType":"Photos","isPublic": false, "id":1})"));

        // Convert the Media class to json using the convertToJson method.
        json::wvalue jsonOutput = testMedia.convertToJson();

        // Convert back to a json read value for testing.
        json::rvalue jsonReadValue = json::load(jsonOutput.dump());

        // Check the values.
        CHECK(jsonReadValue["id"].i() == 1);
        CHECK(jsonReadValue["mediaType"].s() == "Photos");
        CHECK(jsonReadValue["isPublic"].b() == false);
    }

    // Testing updateFromJson method
    SUBCASE("Testing updateFromJson Method") 
    {
        // Create a new Media class from json.
        Media testMedia(json::load(R"({"mediaType":"Photos","isPublic": false, "id":1})"));

        // Create the update json.
        json::rvalue updateJson = json::load(R"({"mediaType":"Notes","isPublic": true, "id":1})");

        // Update the Media with the updateFromJson method. 
        testMedia.updateFromJson(updateJson);

        // Check the updated values.
        CHECK(testMedia.getId() == 1);
        CHECK(testMedia.getMediaType() == "Notes");
        CHECK(testMedia.getIsPublic() == true);
    }
}