#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <crow.h>
#include <doctest.h>
#include <string>
#include "photos.h"

using namespace std;  
using namespace crow;  



TEST_CASE("Testing Photos Class") 
{
    // Testing Photos constructor
    SUBCASE("Testing the Photos Constructor") 
    {
        // Create a new Photos class from json.
        Photos testPhotos(json::load(R"({"photosSize":1.5, "photosCategory":"Screenshot", "mediaType":"Photos", "isPublic":false, "id":7})"));

        // Check that the constructor properly loaded the values.
        CHECK(testPhotos.getId() == 7);
        CHECK(testPhotos.getPhotosSize() == 1.5);
        CHECK(testPhotos.getPhotosCategory() == "Screenshot");
        CHECK(testPhotos.getMediaType() == "Photos");
        CHECK(testPhotos.getIsPublic() == false);
    }

    // Testing convertToJson method
    SUBCASE("Testing the convertToJson Method") 
    {
        // Create a new Photos class from json.
        Photos testPhotos(json::load(R"({"photosSize":1.5, "photosCategory":"Screenshot", "mediaType":"Photos", "isPublic":false, "id":7})"));

        // Convert the Photos class to json using the convertToJson method.
        json::wvalue jsonOutput = testPhotos.convertToJson();

        // Convert back to a json read value for testing.
        json::rvalue jsonReadValue = json::load(jsonOutput.dump());

        // Check the values.
        CHECK(jsonReadValue["id"].i() == 7);
        CHECK(jsonReadValue["isPublic"].b() == false);
        CHECK(jsonReadValue["mediaType"].s() == "Photos");
        CHECK(jsonReadValue["photosCategory"].s() == "Screenshot");
        CHECK(jsonReadValue["photosSize"].i() == 1.5);
    }

    // Testing updateFromJson method
    SUBCASE("Testing updateFromJson Method") 
    {
        // Create a new Photos class from json.
        Photos testPhotos(json::load(R"({"photosSize":1.5, "photosCategory":"Screenshot", "mediaType":"Photos", "isPublic":false, "id":7})"));

        // Create the update json.
        json::rvalue updateJson = json::load(R"({"photosSize":2.5, "photosCategory":"Portrait", "mediaType":"Photos", "isPublic":true, "id":8})");

        // Update the GePhotosnre with the updateFromJson method. 
        testPhotos.updateFromJson(updateJson);

        // Check the values.
        CHECK(testPhotos.getId() == 8);
        CHECK(testPhotos.getPhotosSize() == 2.5);
        CHECK(testPhotos.getPhotosCategory() == "Portrait");
        CHECK(testPhotos.getMediaType() == "Photos");
        CHECK(testPhotos.getIsPublic() == true);
    }
}