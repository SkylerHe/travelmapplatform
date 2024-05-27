#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <crow.h>
#include <doctest.h>
#include <string>
#include "profiles.h"

using namespace std;  
using namespace crow;  



TEST_CASE("Testing Profiles Class") 
{
    // Testing Profiles constructor
    SUBCASE("Testing the Profiles Constructor") 
    {
        // Create a new Profiles class from json.
        Profiles testProfiles(json::load(R"({"id":1,"gender":"F", "age":20})"));

        // Check that the constructor properly loaded the values.
        CHECK(testProfiles.getId() == 1);
        CHECK(testProfiles.getGender() == "F");
        CHECK(testProfiles.getAge() == 20);
    }

    // Testing convertToJson method
    SUBCASE("Testing the convertToJson Method") 
    {
        // Create a new Profiles class from json.
        Profiles testProfiles(json::load(R"({"id":1,"gender":"F", "age":20})"));

        // Convert the Profile class to json using the convertToJson method.
        json::wvalue jsonOutput = testProfiles.convertToJson();

        // Convert back to a json read value for testing.
        json::rvalue jsonReadValue = json::load(jsonOutput.dump());

        // Check the values.
        CHECK(jsonReadValue["id"].i() == 1);
        CHECK(jsonReadValue["gender"].s() == "F");
        CHECK(jsonReadValue["age"].i() == 20);
    }

    // Testing updateFromJson method
    SUBCASE("Testing updateFromJson Method") 
    {
        // Create a new Profiles class from json.
        Profiles testProfiles(json::load(R"({"id":1,"gender":"F", "age":20})"));

        // Create the update json.
        json::rvalue updateJson = json::load(R"({"id":2, "gender":"M", "age":21})");

        // Update the Profiles with the updateFromJson method. 
        testProfiles.updateFromJson(updateJson);

        // Check the updated values.
        CHECK(testProfiles.getId() == 2);
        CHECK(testProfiles.getGender() == "M");
        CHECK(testProfiles.getAge() == 21);
    }
}