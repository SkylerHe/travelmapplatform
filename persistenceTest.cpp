#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <crow.h>
#include <doctest.h>
#include "profiles.h"
#include "destinations.h"
#include "media.h"
#include "notes.h"
#include "photos.h"
#include "persistence.h"

using namespace std;
using namespace crow;


// Declare the maps globally
map<int, Profiles> profilesMap;
map<int, Destinations> destinationsMap;
map<int, Media> mediaMap; 
map<int, Notes> notesMap;
map<int, Photos> photosMap;



// Media
TEST_CASE("Media: Saving to a file and loading from a file.") 
{
    // Load a resources to read.
    mediaMap[1] = Media{json::load(R"({"id":1, "isPublic": false, "mediaType":"Portrait"})")};
    mediaMap[2] = Media{json::load(R"({"id":2, "isPublic": true, "mediaType":"Screenshot"})")};
    

    // Perform the action
    saveToFile<Media>(mediaMap, "persistenceTest.json");
    map<int, Media> mediaMapLoaded = loadFromFile<Media>("persistenceTest.json");

    // Check the results
    CHECK(mediaMap.size() == mediaMapLoaded.size()); // Ensure saved and loaded map are the same size.
    CHECK(mediaMap.at(1).getId() == mediaMapLoaded.at(1).getId()); // Validate the resource content
    CHECK(mediaMap.at(1).getIsPublic() == mediaMapLoaded.at(1).getIsPublic()); // Validate the resource content
    CHECK(mediaMap.at(1).getMediaType() == mediaMapLoaded.at(1).getMediaType()); // Validate the resource content
    CHECK(mediaMap.size() == mediaMapLoaded.size()); // Ensure saved and loaded map are the same size.
    CHECK(mediaMap.at(2).getId() == mediaMapLoaded.at(2).getId()); // Validate the resource content
    CHECK(mediaMap.at(2).getIsPublic() == mediaMapLoaded.at(2).getIsPublic()); // Validate the resource content
    CHECK(mediaMap.at(2).getMediaType() == mediaMapLoaded.at(2).getMediaType()); // Validate the resource content
}


// Destinations
TEST_CASE("Destinations: Saving to a file and loading from a file.") 
{
    // Load a resources to read.
    destinationsMap[1] = Destinations{json::load(R"({"id":1, "destination":"China", "hasMedia":true, "media":[{"id":1}]})")};
    destinationsMap[2] = Destinations{json::load(R"({"id":2, "destination":"USA", "hasMedia":true, "media":[{"id":2}]})")};
    
    // Perform the action
    saveToFile<Destinations>(destinationsMap, "persistenceTest.json");
    map<int, Destinations> destinationsMapLoaded = loadFromFile<Destinations>("persistenceTest.json");

    // Check the results
    CHECK(destinationsMap.size() == destinationsMapLoaded.size()); // Ensure saved and loaded map are the same size.
    CHECK(destinationsMap.at(1).getId() == destinationsMapLoaded.at(1).getId()); // Validate the resource content
    CHECK(destinationsMap.at(1).getDestination() == destinationsMapLoaded.at(1).getDestination()); // Validate the resource content
    CHECK(destinationsMap.at(1).getHasMedia() == destinationsMapLoaded.at(1).getHasMedia()); // Validate the resource content
    vector<Media> media1 = destinationsMap.at(1).getMedia();
    vector<Media> media_check1 = destinationsMap.at(1).getMedia();
   
    for (size_t i = 0; i < media1.size(); ++i)
    {
        CHECK(media1[i].getId() == media_check1[i].getId());
    }

    CHECK(destinationsMap.size() == destinationsMapLoaded.size()); // Ensure saved and loaded map are the same size.
    CHECK(destinationsMap.at(2).getId() == destinationsMapLoaded.at(2).getId()); // Validate the resource content
    CHECK(destinationsMap.at(2).getDestination() == destinationsMapLoaded.at(2).getDestination()); // Validate the resource content
    CHECK(destinationsMap.at(2).getHasMedia() == destinationsMapLoaded.at(2).getHasMedia()); // Validate the resource content
    vector<Media> media2 = destinationsMap.at(2).getMedia();
    vector<Media> media_check2 = destinationsMapLoaded.at(2).getMedia();   
    for (size_t i = 0; i < media2.size(); ++i)
    {
        CHECK(media2[i].getId() == media_check2[i].getId());
    }
}

// Profiles
TEST_CASE("Profiles: Saving to a file and loading from a file.") 
{
    // Load a resources to read.
    profilesMap[1] = Profiles{json::load(R"({"id":1,"gender":"F", "age":20, "destinations":[{"id":1}]})")};
    profilesMap[2] = Profiles{json::load(R"({"id":2,"gender":"M", "age":21, "destinations":[{"id":2}]})")};
    // Perform the action
    saveToFile<Profiles>(profilesMap, "persistenceTest.json");
    map<int, Profiles> profilesMapLoaded = loadFromFile<Profiles>("persistenceTest.json");
    // Check the results
    
    // Check if keys exist in the loaded map before accessing
    CHECK(profilesMapLoaded.find(1) != profilesMapLoaded.end());
    CHECK(profilesMapLoaded.find(2) != profilesMapLoaded.end());

    CHECK(profilesMapLoaded.find(1) != profilesMapLoaded.end());
    CHECK(profilesMapLoaded.find(2) != profilesMapLoaded.end());
    CHECK(profilesMap.size() == profilesMapLoaded.size()); // Ensure saved and loaded map are the same size.
    CHECK(profilesMap.at(1).getId() == profilesMapLoaded.at(1).getId()); // Validate the resource content
    CHECK(profilesMap.at(1).getGender() == profilesMapLoaded.at(1).getGender()); // Validate the resource content
    CHECK(profilesMap.at(1).getAge() == profilesMapLoaded.at(1).getAge()); // Validate the resource content
    //CHECK(profilesMap.at(1).getDestinations() == profilesMapLoaded.at(1).getDestinations()); // Validate the resource content
    vector<Destinations> destinations1 = profilesMap.at(1).getDestinations();
    vector<Destinations> destinations_check1 = profilesMapLoaded.at(1).getDestinations();
    for (size_t i = 0; i < destinations1.size(); i++)
    {
       CHECK(destinations1[i].getId() == destinations_check1[i].getId());
    }
    CHECK(profilesMap.size() == profilesMapLoaded.size()); // Ensure saved and loaded map are the same size.
    CHECK(profilesMap.at(2).getId() == profilesMapLoaded.at(2).getId()); // Validate the resource content
    CHECK(profilesMap.at(2).getGender() == profilesMapLoaded.at(2).getGender()); // Validate the resource content
    CHECK(profilesMap.at(2).getAge() == profilesMapLoaded.at(2).getAge()); // Validate the resource content
    vector<Destinations> destinations2 = profilesMap.at(2).getDestinations();
    vector<Destinations> destinations_check2 = profilesMapLoaded.at(2).getDestinations();   
    for (size_t i = 0; i < destinations2.size(); ++i)
    {
        CHECK(destinations2[i].getId() == destinations_check2[i].getId());
    }


}


// Notes
TEST_CASE("Notes: Saving to a file and loading from a file.") 
{
    // Load a resources to read.
    notesMap[1] = Notes{json::load(R"({"id":1, "isPublic":false, "mediaType":"Notes", "wordCounts":100, "notesCategory":"Dairy"})")};
    notesMap[2] = Notes{json::load(R"({"id":2, "isPublic":true, "mediaType":"Notes", "wordCounts":300, "notesCategory":"Outlines"})")};
    

    // Perform the action
    saveToFile<Notes>(notesMap, "persistenceTest.json");
    map<int, Notes> notesMapLoaded = loadFromFile<Notes>("persistenceTest.json");

    // Check the results
    CHECK(notesMap.size() == notesMapLoaded.size()); // Ensure saved and loaded map are the same size.
    CHECK(notesMap.at(1).getId() == notesMapLoaded.at(1).getId()); // Validate the resource content
    CHECK(notesMap.at(1).getIsPublic() == notesMapLoaded.at(1).getIsPublic()); // Validate the resource content
    CHECK(notesMap.at(1).getMediaType() == notesMapLoaded.at(1).getMediaType()); // Validate the resource content
    CHECK(notesMap.at(1).getWordCounts() == notesMapLoaded.at(1).getWordCounts()); // Validate the resource content
    CHECK(notesMap.at(1).getNotesCategory() == notesMapLoaded.at(1).getNotesCategory()); // Validate the resource content
    CHECK(notesMap.size() == notesMapLoaded.size()); // Ensure saved and loaded map are the same size.
    CHECK(notesMap.at(2).getId() == notesMapLoaded.at(2).getId()); // Validate the resource content
    CHECK(notesMap.at(2).getIsPublic() == notesMapLoaded.at(2).getIsPublic()); // Validate the resource content
    CHECK(notesMap.at(2).getMediaType() == notesMapLoaded.at(2).getMediaType()); // Validate the resource content
    CHECK(notesMap.at(2).getWordCounts() == notesMapLoaded.at(2).getWordCounts()); // Validate the resource content
    CHECK(notesMap.at(2).getNotesCategory() == notesMapLoaded.at(2).getNotesCategory()); // Validate the resource content
}


// Photos
TEST_CASE("Photos: Saving to a file and loading from a file.") 
{
    // Load a resources to read.
    photosMap[1] = Photos{json::load(R"({"id":1, "isPublic":false, "mediaType":"Photos", "photosSize":1.5, "photosCategory":"Self-Portrait"})")};
    photosMap[2] = Photos{json::load(R"({"id":2, "isPublic":true, "mediaType":"Photos", "photosSize":2.5, "photosCategory":"Screenshot"})")};
    

    // Perform the action
    saveToFile<Photos>(photosMap, "persistenceTest.json");
    map<int, Photos>photosMapLoaded = loadFromFile<Photos>("persistenceTest.json");

    // Check the results
    CHECK(photosMap.size() == photosMapLoaded.size()); // Ensure saved and loaded map are the same size.
    CHECK(photosMap.at(1).getId() == photosMapLoaded.at(1).getId()); // Validate the resource content
    CHECK(photosMap.at(1).getIsPublic() == photosMapLoaded.at(1).getIsPublic()); // Validate the resource content
    CHECK(photosMap.at(1).getMediaType() == photosMapLoaded.at(1).getMediaType()); // Validate the resource content
    CHECK(photosMap.at(1).getPhotosSize() == photosMapLoaded.at(1).getPhotosSize()); // Validate the resource content
    CHECK(photosMap.at(1).getPhotosCategory() == photosMapLoaded.at(1).getPhotosCategory()); // Validate the resource content
    CHECK(photosMap.size() == photosMapLoaded.size()); // Ensure saved and loaded map are the same size.
    CHECK(photosMap.at(2).getId() == photosMapLoaded.at(2).getId()); // Validate the resource content
    CHECK(photosMap.at(2).getIsPublic() == photosMapLoaded.at(2).getIsPublic()); // Validate the resource content
    CHECK(photosMap.at(2).getMediaType() == photosMapLoaded.at(2).getMediaType()); // Validate the resource content
    CHECK(photosMap.at(2).getPhotosSize() == photosMapLoaded.at(2).getPhotosSize()); // Validate the resource content
    CHECK(photosMap.at(2).getPhotosCategory() == photosMapLoaded.at(2).getPhotosCategory()); // Validate the resource content
}