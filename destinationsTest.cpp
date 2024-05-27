#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <crow.h>
#include <doctest.h>
#include <string>
#include "destinations.h"

using namespace std;  
using namespace crow;  



TEST_CASE("Testing Destinations Class") 
{
    // Testing Destinations constructor
    SUBCASE("Testing the Destinations Constructor") 
    {
        // Create a new Destinations class from json.
        Destinations testDestinations(json::load(R"({"id":1, "destination":"China", "hasMedia":true, "media":[{"id":1}]})"));

        // Check that the constructor properly loaded the values.
        CHECK(testDestinations.getId() == 1);
        CHECK(testDestinations.getDestination() == "China");
        CHECK(testDestinations.getHasMedia() == true);
        for (const auto& mediaItem : testDestinations.getMedia())
        {
            CHECK(mediaItem.getId() == 1);
        }
        
    }

    // Testing convertToJson method
    SUBCASE("Testing the convertToJson Method") 
    {
        // Create a new Destinations class from json.
        Destinations testDestinations(json::load(R"({"id":1, "destination":"China", "hasMedia":true, "media":[{"id":1}]})"));

        // Convert the Destinations class to json using the convertToJson method.
        json::wvalue jsonOutput = testDestinations.convertToJson();

        // Convert back to a json read value for testing.
        json::rvalue jsonReadValue = json::load(jsonOutput.dump());

        // Check the values.
        CHECK(jsonReadValue["id"].i() == 1);
        CHECK(jsonReadValue["destination"].s() == "China");
        CHECK(jsonReadValue["hasMedia"].b() == true);
        const auto& mediaArray = jsonReadValue["media"];
        for (size_t i = 0; i < mediaArray.size(); ++i)
        {
            // Accessing each media item using indexing
            const auto& mediaItem = mediaArray[i];
            CHECK(mediaItem["id"].i() == 1);
        }
    }

    // Testing updateFromJson method
    SUBCASE("Testing updateFromJson Method") 
    {
        // Create a new Destinations class from json.
        Destinations testDestinations(json::load(R"({"id":1, "destination":"China", "hasMedia":true, "media":[{"id":1}]})"));

        // Create the update json.
        json::rvalue updateJson = json::load(R"({"id":2, "destination":"USA", "hasMedia":true, "media":[{"id":2}]})");

        // Update the Destinations with the updateFromJson method. 
        testDestinations.updateFromJson(updateJson);

        // Check the updated values.
        CHECK(testDestinations.getId() == 2);
        CHECK(testDestinations.getDestination() == "USA");
        CHECK(testDestinations.getHasMedia() == true);
        for (const auto& mediaItem : testDestinations.getMedia())
        {
            CHECK(mediaItem.getId() == 2);
        }
    }
}