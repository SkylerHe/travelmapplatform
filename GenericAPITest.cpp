#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <crow.h>
#include <doctest.h>
#include "profiles.h"
#include "destinations.h"
#include "media.h"
#include "notes.h"
#include "photos.h"
#include "GenericAPI.h"
#include <vector>


using namespace std;
using namespace crow;

map<int, Profiles> profilesMap;
map<int, Destinations> destinationsMap;
map<int, Media> mediaMap;
map<int, Photos> photosMap;
map<int, Notes> notesMap;

// Media
TEST_CASE("Creating a new Media resource") 
{
    // Setup resource map to be empty before the test
    GenericAPI<Media>::resourceMap.clear();

    // Setup request object
    request req;
    req.body = R"({"mediaType":"Photos","id":1,"isPublic":false})"; 

    // Perform the action
    response res = GenericAPI<Media>::createResource(req);

    // Check the results
    CHECK(res.code == 201); // Check that the response code is 201 Created
    CHECK(res.body == req.body); // Validate the reponse body
    CHECK(GenericAPI<Media>::resourceMap.size() == 1); // Ensure the resource was added to the map
    CHECK(GenericAPI<Media>::resourceMap.at(1).getId() == 1); // Validate the resource content
    CHECK(GenericAPI<Media>::resourceMap.at(1).getIsPublic() == false); // Validate the resource content
    CHECK(GenericAPI<Media>::resourceMap.at(1).getMediaType() == "Photos"); // Validate the resource content

}

TEST_CASE("Reading a Media resource") 
{
    // Load a resource to read.
    mediaMap[1] = Media{json::load(R"({"id":1, "isPublic": false, "mediaType":"Photos"})")};

    // Setup resource map to be empty before the test
    GenericAPI<Media>::resourceMap = mediaMap;

    // Perform the action
    response res = GenericAPI<Media>::readResource(1);

    // Check the results
    CHECK(res.code == 200); // Check that the response code is 200 Ok
    CHECK(res.body == mediaMap[1].convertToJson().dump()); // Validate the reponse body
    CHECK(GenericAPI<Media>::resourceMap.size() == 1); // Ensure that no resources were added or removed from the map
}

TEST_CASE("Reading all Media resources") 
{
    // Load resources to read.
    mediaMap[1] = Media{json::load(R"({"mediaType":"Notes", "id":1, "isPublic": false})")};
    mediaMap[2] = Media{json::load(R"({"mediaType":"Photos", "id":2, "isPublic": true})")};
    mediaMap[3] = Media{json::load(R"({"mediaType":"Notes", "id":3, "isPublic": false})")};
    mediaMap[4] = Media{json::load(R"({"mediaType":"Photos", "id":4, "isPublic": true})")};


    // Setup resource map to be empty before the test
    GenericAPI<Media>::resourceMap = mediaMap;

    // Perform the action
    response res = GenericAPI<Media>::readAllResources();

    // Create the expected reponse body
    string expectedResponseBody = R"([{"mediaType":"Notes","isPublic":false,"id":1},{"id":2,"isPublic":true,"mediaType":"Photos"},{"mediaType":"Notes","id":3,"isPublic":false},{"mediaType":"Photos","id":4,"isPublic":true}])";

    // Check the results
    CHECK(res.code == 200); // Check that the response code is 200 Ok
    CHECK(res.body == expectedResponseBody); // Validate the reponse body
    CHECK(GenericAPI<Media>::resourceMap.size() == 4); // Ensure that no resources were added or removed from the map
}


TEST_CASE("Updating a Media resource") 
{
    // Load resources to update.
    mediaMap[1] = Media{json::load(R"({"id":1, "isPublic": false, "mediaType":"Notes"})")};
    mediaMap[2] = Media{json::load(R"({"id":2, "isPublic": true, "mediaType":"Photos"})")};
    mediaMap[3] = Media{json::load(R"({"id":3, "isPublic": false, "mediaType":"Notes"})")};
    mediaMap[4] = Media{json::load(R"({"id":4, "isPublic": true, "mediaType":"Photos"})")};



    // Setup resource map to be empty before the test
    GenericAPI<Media>::resourceMap = mediaMap;

    // Setup request object
    request req;
    req.body = R"({"mediaType":"Photos","id":5,"isPublic":false})"; 

    // Setup a response object
    response res;

    // Perform the action
    GenericAPI<Media>::updateResource(req, res, 1);

    // Check the results
    CHECK(res.code == 200); // Check that the response code is 200 Ok
    CHECK(res.body == req.body); // Validate the reponse body
    CHECK(GenericAPI<Media>::resourceMap.size() == 4); // Ensure the resource was added to the map
    CHECK(GenericAPI<Media>::resourceMap.at(1).getId() == 5); // Validate the resource content
    CHECK(GenericAPI<Media>::resourceMap.at(1).getIsPublic() == false); // Validate the resource content
    CHECK(GenericAPI<Media>::resourceMap.at(1).getMediaType() == "Photos"); // Validate the resource content
}


TEST_CASE("Deleting a Media resource") 
{
    // Load a resources to update.
    mediaMap[1] = Media{json::load(R"({"id":1, "isPublic": false, "mediaType":"Notes"})")};
    mediaMap[2] = Media{json::load(R"({"id":2, "isPublic": true, "mediaType":"Photos"})")};
    mediaMap[3] = Media{json::load(R"({"id":3, "isPublic": false, "mediaType":"Notes"})")};
    mediaMap[4] = Media{json::load(R"({"id":4, "isPublic": true, "mediaType":"Photos"})")};

    // Setup resource map to be empty before the test
    GenericAPI<Media>::resourceMap = mediaMap;

    // Perform the action
    response res = GenericAPI<Media>::deleteResource(4);

    // Check the results
    CHECK(res.code == 204); // Check that the response code is 204 No Content
    CHECK(res.body == ""); // Validate the reponse body
    CHECK(GenericAPI<Media>::resourceMap.size() == 3); // Ensure one resource was removed from the map
}

// Destinations
TEST_CASE("Creating a new Destinations resource") 
{
    // Setup resource map to be empty before the test
    GenericAPI<Destinations>::resourceMap.clear();

    // Setup request object
    request req;
    req.body = R"({"media":[{"id":1}],"hasMedia":true,"id":1,"destination":"China"})"; 

    // Perform the action
    response res = GenericAPI<Destinations>::createResource(req);

    // Check the results
    CHECK(res.code == 201); // Check that the response code is 201 Created
    CHECK(res.body == req.body); // Validate the reponse body
    CHECK(GenericAPI<Destinations>::resourceMap.size() == 1); // Ensure the resource was added to the map
    CHECK(GenericAPI<Destinations>::resourceMap.at(1).getId() == 1); // Validate the resource content
    CHECK(GenericAPI<Destinations>::resourceMap.at(1).getDestination() == "China"); // Validate the resource content
    CHECK(GenericAPI<Destinations>::resourceMap.at(1).getHasMedia() == true); // Validate the resource content
    vector<Media> media = GenericAPI<Destinations>::resourceMap.at(1).getMedia();
    for (const auto& media : media)
    {
        CHECK(media.getId() == 1); // Validate the resource content
    }
    
}

TEST_CASE("Reading a Destinations resource") 
{
    // Load a resource to read.
    destinationsMap[1] = Destinations{json::load(R"({"id":1,"destination":"China", "hasMedia":true, "media":[{"id":1}]})")};

    // Setup resource map to be empty before the test
    GenericAPI<Destinations>::resourceMap = destinationsMap;

    // Perform the action
    response res = GenericAPI<Destinations>::readResource(1);

    // Check the results
    CHECK(res.code == 200); // Check that the response code is 200 Ok
    CHECK(res.body == destinationsMap[1].convertToJson().dump()); // Validate the reponse body
    CHECK(GenericAPI<Destinations>::resourceMap.size() == 1); // Ensure that no resources were added or removed from the map
}

TEST_CASE("Reading all Destinations resources") 
{
    // Load resources to read.
    destinationsMap[1] = Destinations{json::load(R"({"id":1,"destination":"China", "hasMedia":true, "media":[{"id":1}]})")};
    destinationsMap[2] = Destinations{json::load(R"({"id":2,"destination":"USA", "hasMedia":false, "media":[{"id":2}]})")};
    destinationsMap[3] = Destinations{json::load(R"({"id":3,"destination":"Korea", "hasMedia":true, "media":[{"id":3}]})")};
    destinationsMap[4] = Destinations{json::load(R"({"id":4,"destination":"Russia", "hasMedia":false, "media":[{"id":4}]})")};


    // Setup resource map to be empty before the test
    GenericAPI<Destinations>::resourceMap = destinationsMap;

    // Perform the action
    response res = GenericAPI<Destinations>::readAllResources();

    // Create the expected reponse body
    string expectedResponseBody = R"([{"media":[{"id":1}],"hasMedia":true,"id":1,"destination":"China"},{"destination":"USA","id":2,"hasMedia":false,"media":[{"id":2}]},{"media":[{"id":3}],"hasMedia":true,"id":3,"destination":"Korea"},{"media":[{"id":4}],"hasMedia":false,"id":4,"destination":"Russia"}])";

    // Check the results
    CHECK(res.code == 200); // Check that the response code is 200 Ok
    CHECK(res.body == expectedResponseBody); // Validate the reponse body
    CHECK(GenericAPI<Destinations>::resourceMap.size() == 4); // Ensure that no resources were added or removed from the map
}


TEST_CASE("Updating a Destinations resource") 
{
    // Load resources to update.
    destinationsMap[1] = Destinations{json::load(R"({"id":1,"destination":"China", "hasMedia":true, "media":[{"id":1}]})")};
    destinationsMap[2] = Destinations{json::load(R"({"id":2,"destination":"USA", "hasMedia":false, "media":[{"id":2}]})")};
    destinationsMap[3] = Destinations{json::load(R"({"id":3,"destination":"Korea", "hasMedia":true, "media":[{"id":3}]})")};
    destinationsMap[4] = Destinations{json::load(R"({"id":4,"destination":"Russia", "hasMedia":false, "media":[{"id":4}]})")};



    // Setup resource map to be empty before the test
    GenericAPI<Destinations>::resourceMap = destinationsMap;

    // Setup request object
    request req;
    req.body = R"({"media":[{"id":4}],"hasMedia":false,"id":4,"destination":"India"})"; 

    // Setup a response object
    response res;

    // Perform the action
    GenericAPI<Destinations>::updateResource(req, res, 4);

    // Check the results
    CHECK(res.code == 200); // Check that the response code is 200 Ok
    CHECK(res.body == req.body); // Validate the reponse body
    CHECK(GenericAPI<Destinations>::resourceMap.size() == 4); // Ensure no resource was added or removed from the map
    CHECK(GenericAPI<Destinations>::resourceMap.at(4).getId() == 4); // Validate the resource content
    CHECK(GenericAPI<Destinations>::resourceMap.at(4).getDestination() == "India"); // Validate the resource content
    CHECK(GenericAPI<Destinations>::resourceMap.at(4).getHasMedia() == false); // Validate the resource content
    vector<Media> media = GenericAPI<Destinations>::resourceMap.at(4).getMedia();
    for (const auto& media : media)
    {
        CHECK(media.getId() == 4); // Validate the resource content
    }
}


TEST_CASE("Deleting a Destinations resource") 
{
    // Load a resources to update.
    destinationsMap[1] = Destinations{json::load(R"({"id":1,"destination":"China", "hasMedia":true, "media":[{"id":5}]})")};
    destinationsMap[2] = Destinations{json::load(R"({"id":2,"destination":"USA", "hasMedia":false, "media":[{"id":6}]})")};
    destinationsMap[3] = Destinations{json::load(R"({"id":3,"destination":"Korea", "hasMedia":true, "media":[{"id":7}]})")};
    destinationsMap[4] = Destinations{json::load(R"({"id":4,"destination":"Russia", "hasMedia":false, "media":[{"id":8}]})")};
    // Setup resource map to be empty before the test
    GenericAPI<Destinations>::resourceMap = destinationsMap;

    // Perform the action
    response res = GenericAPI<Destinations>::deleteResource(4);

    // Check the results
    CHECK(res.code == 204); // Check that the response code is 204 No Content
    CHECK(res.body == ""); // Validate the reponse body
    CHECK(GenericAPI<Destinations>::resourceMap.size() == 3); // Ensure one resource was removed from the map
}

// Profiles
TEST_CASE("Creating a new Profiles resource") 
{
    // Setup resource map to be empty before the test
    GenericAPI<Profiles>::resourceMap.clear();

    // Setup request object
    request req;
    req.body = R"({"destinations":[{"id":1}],"age":20,"id":1,"gender":"F"})"; 

    // Perform the action
    response res = GenericAPI<Profiles>::createResource(req);

    // Check the results
    CHECK(res.code == 201); // Check that the response code is 201 Created
    CHECK(res.body == req.body); // Validate the reponse body
    CHECK(GenericAPI<Profiles>::resourceMap.size() == 1); // Ensure the resource was added to the map
    CHECK(GenericAPI<Profiles>::resourceMap.at(1).getId() == 1); // Validate the resource content
    CHECK(GenericAPI<Profiles>::resourceMap.at(1).getGender() == "F"); // Validate the resource content
    CHECK(GenericAPI<Profiles>::resourceMap.at(1).getAge() == 20); // Validate the resource content
    vector<Destinations> destinations = GenericAPI<Profiles>::resourceMap.at(1).getDestinations();
    for (const auto& destination : destinations)
    {
        CHECK(destination.getId() == 1); // Validate the resource content
    }
    
}

TEST_CASE("Reading a Profiles resource") 
{
    // Load a resource to read.
    profilesMap[1] = Profiles{json::load(R"({"id":1,"gender":"F","age":20,"destinations":[{"id":4}]})")};

    // Setup resource map to be empty before the test
    GenericAPI<Profiles>::resourceMap = profilesMap;

    // Perform the action
    response res = GenericAPI<Profiles>::readResource(1);

    // Check the results
    CHECK(res.code == 200); // Check that the response code is 200 Ok
    CHECK(res.body == profilesMap[1].convertToJson().dump()); // Validate the reponse body
    CHECK(GenericAPI<Profiles>::resourceMap.size() == 1); // Ensure that no resources were added or removed from the map
}

TEST_CASE("Reading all Profiles resources") 
{
    // Load resources to read.
    profilesMap[1] = Profiles{json::load(R"({"id":1,"gender":"F", "age":20, "destinations":[{"id":4}]})")};
    profilesMap[2] = Profiles{json::load(R"({"id":2,"gender":"M", "age":21, "destinations":[{"id":5}]})")};
    profilesMap[3] = Profiles{json::load(R"({"id":3,"gender":"F", "age":22, "destinations":[{"id":6}]})")};
    profilesMap[4] = Profiles{json::load(R"({"id":4,"gender":"M", "age":23, "destinations":[{"id":7}]})")};


    // Setup resource map to be empty before the test
    GenericAPI<Profiles>::resourceMap = profilesMap;

    // Perform the action
    response res = GenericAPI<Profiles>::readAllResources();

    // Create the expected reponse body
    string expectedResponseBody = R"([{"destinations":[{"id":4}],"age":20,"id":1,"gender":"F"},{"gender":"M","id":2,"age":21},{"age":22,"id":3,"gender":"F"},{"age":23,"id":4,"gender":"M"}])";

    // Check the results
    CHECK(res.code == 200); // Check that the response code is 200 Ok
    CHECK(res.body == expectedResponseBody); // Validate the reponse body
    CHECK(GenericAPI<Profiles>::resourceMap.size() == 4); // Ensure that no resources were added or removed from the map
}


TEST_CASE("Updating a Profiles resource") 
{
    // Load resources to update.
    profilesMap[1] = Profiles{json::load(R"({"id":1,"gender":"F", "age":20, "destinations":[{"id":4}]})")};
    profilesMap[2] = Profiles{json::load(R"({"id":2,"gender":"M", "age":21, "destinations":[{"id":5}]})")};
    profilesMap[3] = Profiles{json::load(R"({"id":3,"gender":"F", "age":22, "destinations":[{"id":6}]})")};
    profilesMap[4] = Profiles{json::load(R"({"id":4,"gender":"M", "age":23, "destinations":[{"id":7}]})")};


    // Setup resource map to be empty before the test
    GenericAPI<Profiles>::resourceMap = profilesMap;

    // Setup request object
    request req;
    req.body = R"({"destinations":[{"id":4}],"age":19,"id":1,"gender":"F"})"; 

    // Setup a response object
    response res;

    // Perform the action
    GenericAPI<Profiles>::updateResource(req, res, 1);

    // Check the results
    CHECK(res.code == 200); // Check that the response code is 200 Ok
    CHECK(res.body == req.body); // Validate the reponse body
    CHECK(GenericAPI<Profiles>::resourceMap.size() == 4); // Ensure no resource was added or removed from the map
    CHECK(GenericAPI<Profiles>::resourceMap.at(1).getId() == 1); // Validate the resource content
    CHECK(GenericAPI<Profiles>::resourceMap.at(1).getGender() == "F"); // Validate the resource content
    CHECK(GenericAPI<Profiles>::resourceMap.at(1).getAge() == 19); // Validate the resource content
    vector<Destinations> destinations = GenericAPI<Profiles>::resourceMap.at(1).getDestinations();
    for (const auto& destination : destinations)
    {
        CHECK(destination.getId() == 4); // Validate the resource content
    }
}


TEST_CASE("Deleting a Profiles resource") 
{
    // Load a resources to update.
    profilesMap[1] = Profiles{json::load(R"({"id":1,"gender":"F", "age":20, "destinations":[{"id":4}]})")};
    profilesMap[2] = Profiles{json::load(R"({"id":2,"gender":"M", "age":21, "destinations":[{"id":5}]})")};
    profilesMap[3] = Profiles{json::load(R"({"id":3,"gender":"F", "age":22, "destinations":[{"id":6}]})")};
    profilesMap[4] = Profiles{json::load(R"({"id":4,"gender":"M", "age":23, "destinations":[{"id":7}]})")};

    // Setup resource map to be empty before the test
    GenericAPI<Profiles>::resourceMap = profilesMap;

    // Perform the action
    response res = GenericAPI<Profiles>::deleteResource(4);

    // Check the results
    CHECK(res.code == 204); // Check that the response code is 204 No Content
    CHECK(res.body == ""); // Validate the reponse body
    CHECK(GenericAPI<Profiles>::resourceMap.size() == 3); // Ensure one resource was removed from the map
}





// Photos
TEST_CASE("Creating a new Photos resource") 
{
    // Setup resource map to be empty before the test
    GenericAPI<Photos>::resourceMap.clear();

    // Setup request object
    request req;
    req.body = R"({"mediaType":"Photos","photosCategory":"Screenshot","id":1,"photosSize":1.5,"isPublic":false})"; 

    // Perform the action
    response res = GenericAPI<Photos>::createResource(req);

    // Check the results
    CHECK(res.code == 201); // Check that the response code is 201 Created
    CHECK(res.body == req.body); // Validate the reponse body
    CHECK(GenericAPI<Photos>::resourceMap.size() == 1); // Ensure the resource was added to the map
    CHECK(GenericAPI<Photos>::resourceMap.at(1).getId() == 1); // Validate the resource content
    CHECK(GenericAPI<Photos>::resourceMap.at(1).getIsPublic() == false); // Validate the resource content
    CHECK(GenericAPI<Photos>::resourceMap.at(1).getMediaType() == "Photos"); // Validate the resource content
    CHECK(GenericAPI<Photos>::resourceMap.at(1).getPhotosSize() == 1.5); // Validate the resource content
    CHECK(GenericAPI<Photos>::resourceMap.at(1).getPhotosCategory() == "Screenshot"); // Validate the resource content

}

TEST_CASE("Reading a Photos resource") 
{
    // Load a resource to read.
    photosMap[1] = Photos{json::load(R"({"photosSize":1.5, "photosCategory":"Screenshot", "mediaType":"Photos", "isPublic":false, "id":1})")};

    // Setup resource map to be empty before the test
    GenericAPI<Photos>::resourceMap = photosMap;

    // Perform the action
    response res = GenericAPI<Photos>::readResource(1);

    // Check the results
    CHECK(res.code == 200); // Check that the response code is 200 Ok
    CHECK(res.body == photosMap[1].convertToJson().dump()); // Validate the reponse body
    CHECK(GenericAPI<Photos>::resourceMap.size() == 1); // Ensure that no resources were added or removed from the map
}

TEST_CASE("Reading all Photos resources") 
{
    // Load resources to read.
    photosMap[1] = Photos{json::load(R"({"photosSize":1.5, "photosCategory":"Screenshot", "mediaType":"Photos", "isPublic":false, "id":1})")};
    photosMap[2] = Photos{json::load(R"({"photosSize":3, "photosCategory":"Screenshot", "mediaType":"Photos", "isPublic":true, "id":2})")};
    

    // Setup resource map to be empty before the test
    GenericAPI<Photos>::resourceMap = photosMap;

    // Perform the action
    response res = GenericAPI<Photos>::readAllResources();

    // Create the expected reponse body
    string expectedResponseBody = R"([{"isPublic":false,"photosSize":1.5,"id":1,"photosCategory":"Screenshot","mediaType":"Photos"},{"mediaType":"Photos","photosCategory":"Screenshot","id":2,"photosSize":3.0,"isPublic":true}])";

    // Check the results
    CHECK(res.code == 200); // Check that the response code is 200 Ok
    CHECK(res.body == expectedResponseBody); // Validate the reponse body
    CHECK(GenericAPI<Photos>::resourceMap.size() == 2); // Ensure that no resources were added or removed from the map
}


TEST_CASE("Updating a Photos resource") 
{
    // Load resources to update.
    photosMap[1] = Photos{json::load(R"({"photosSize":1.5, "photosCategory":"Screenshot", "mediaType":"Photos", "isPublic":false, "id":1})")};
    photosMap[2] = Photos{json::load(R"({"photosSize":3, "photosCategory":"Screenshot", "mediaType":"Photos", "isPublic":true, "id":2})")};



    // Setup resource map to be empty before the test
    GenericAPI<Photos>::resourceMap = photosMap;

    // Setup request object
    request req;
    req.body = R"({"mediaType":"Photos","photosCategory":"Screenshot","id":1,"photosSize":1.8,"isPublic":true})"; 

    // Setup a response object
    response res;

    // Perform the action
    GenericAPI<Photos>::updateResource(req, res, 1);

    // Check the results
    CHECK(res.code == 200); // Check that the response code is 200 Ok
    CHECK(res.body == req.body); // Validate the reponse body
    CHECK(GenericAPI<Photos>::resourceMap.size() == 2); // Ensure the resource was added to the map
    CHECK(GenericAPI<Photos>::resourceMap.at(1).getId() == 1); // Validate the resource content
    CHECK(GenericAPI<Photos>::resourceMap.at(1).getIsPublic() == true); // Validate the resource content
    CHECK(GenericAPI<Photos>::resourceMap.at(1).getMediaType() == "Photos"); // Validate the resource content
    CHECK(GenericAPI<Photos>::resourceMap.at(1).getPhotosSize() == 1.8); // Validate the resource content
    CHECK(GenericAPI<Photos>::resourceMap.at(1).getPhotosCategory() == "Screenshot"); // Validate the resource content

}


TEST_CASE("Deleting a Photos resource") 
{
    // Load a resources to update.
    photosMap[1] = Photos{json::load(R"({"photosSize":1.5, "photosCategory":"Screenshot", "mediaType":"Photos", "isPublic":false, "id":1})")};
    photosMap[2] = Photos{json::load(R"({"photosSize":3, "photosCategory":"Screenshot", "mediaType":"Photos", "isPublic":true, "id":2})")};


    // Setup resource map to be empty before the test
    GenericAPI<Photos>::resourceMap = photosMap;

    // Perform the action
    response res = GenericAPI<Photos>::deleteResource(2);

    // Check the results
    CHECK(res.code == 204); // Check that the response code is 204 No Content
    CHECK(res.body == ""); // Validate the reponse body
    CHECK(GenericAPI<Photos>::resourceMap.size() == 1); // Ensure one resource was removed from the map
}



// Notes
TEST_CASE("Creating a new Notes resource") 
{
    // Setup resource map to be empty before the test
    GenericAPI<Notes>::resourceMap.clear();

    // Setup request object
    request req;
    req.body = R"({"notesCategory":"Dairy","wordCounts":100,"mediaType":"Notes","id":1,"isPublic":false})"; 

    // Perform the action
    response res = GenericAPI<Notes>::createResource(req);

    // Check the results
    CHECK(res.code == 201); // Check that the response code is 201 Created
    CHECK(res.body == req.body); // Validate the reponse body
    CHECK(GenericAPI<Notes>::resourceMap.size() == 1); // Ensure the resource was added to the map
    CHECK(GenericAPI<Notes>::resourceMap.at(1).getId() == 1); // Validate the resource content
    CHECK(GenericAPI<Notes>::resourceMap.at(1).getIsPublic() == false); // Validate the resource content
    CHECK(GenericAPI<Notes>::resourceMap.at(1).getMediaType() == "Notes"); // Validate the resource content
    CHECK(GenericAPI<Notes>::resourceMap.at(1).getWordCounts() == 100); // Validate the resource content
    CHECK(GenericAPI<Notes>::resourceMap.at(1).getNotesCategory() == "Dairy"); // Validate the resource content


}

TEST_CASE("Reading a Notes resource") 
{
    // Load a resource to read.
    notesMap[1] = Notes{json::load(R"({"wordCounts":100, "notesCategory":"Dairy", "mediaType":"Notes", "isPublic":false, "id":1})")};

    // Setup resource map to be empty before the test
    GenericAPI<Notes>::resourceMap = notesMap;

    // Perform the action
    response res = GenericAPI<Notes>::readResource(1);

    // Check the results
    CHECK(res.code == 200); // Check that the response code is 200 Ok
    CHECK(res.body == notesMap[1].convertToJson().dump()); // Validate the reponse body
    CHECK(GenericAPI<Notes>::resourceMap.size() == 1); // Ensure that no resources were added or removed from the map
}

TEST_CASE("Reading all Notes resources") 
{
    // Load resources to read.
    notesMap[1] = Notes{json::load(R"({"wordCounts":100, "notesCategory":"Dairy", "mediaType":"Notes", "isPublic":false, "id":1})")};
    notesMap[2] = Notes{json::load(R"({"wordCounts":200, "notesCategory":"Dairy", "mediaType":"Notes", "isPublic":true, "id":2})")};
    

    // Setup resource map to be empty before the test
    GenericAPI<Notes>::resourceMap = notesMap;

    // Perform the action
    response res = GenericAPI<Notes>::readAllResources();

    // Create the expected reponse body
    string expectedResponseBody = R"([{"isPublic":false,"id":1,"mediaType":"Notes","wordCounts":100,"notesCategory":"Dairy"},{"notesCategory":"Dairy","wordCounts":200,"mediaType":"Notes","id":2,"isPublic":true}])";

    // Check the results
    CHECK(res.code == 200); // Check that the response code is 200 Ok
    CHECK(res.body == expectedResponseBody); // Validate the reponse body
    CHECK(GenericAPI<Notes>::resourceMap.size() == 2); // Ensure that no resources were added or removed from the map
}


TEST_CASE("Updating a Notes resource") 
{
    // Load resources to update.
    notesMap[1] = Notes{json::load(R"({"wordCounts":100, "notesCategory":"Dairy", "mediaType":"Notes", "isPublic":false, "id":1})")};
    notesMap[2] = Notes{json::load(R"({"wordCounts":200, "notesCategory":"Dairy", "mediaType":"Notes", "isPublic":true, "id":2})")};
    
    // Setup resource map to be empty before the test
    GenericAPI<Notes>::resourceMap = notesMap;

    // Setup request object
    request req;
    req.body = R"({"notesCategory":"Dairy","wordCounts":99,"mediaType":"Notes","id":1,"isPublic":false})"; 

    // Setup a response object
    response res;

    // Perform the action
    GenericAPI<Notes>::updateResource(req, res, 1);

    // Check the results
    CHECK(res.code == 200); // Check that the response code is 200 Ok
    CHECK(res.body == req.body); // Validate the reponse body
    CHECK(GenericAPI<Notes>::resourceMap.size() == 2); // Ensure the resource was added to the map
    CHECK(GenericAPI<Notes>::resourceMap.at(1).getId() == 1); // Validate the resource content
    CHECK(GenericAPI<Notes>::resourceMap.at(1).getIsPublic() == false); // Validate the resource content
    CHECK(GenericAPI<Notes>::resourceMap.at(1).getMediaType() == "Notes"); // Validate the resource content
    CHECK(GenericAPI<Notes>::resourceMap.at(1).getWordCounts() == 99); // Validate the resource content
    CHECK(GenericAPI<Notes>::resourceMap.at(1).getNotesCategory() == "Dairy"); // Validate the resource content


}


TEST_CASE("Deleting a Notes resource") 
{
    // Load a resources to update.
    notesMap[1] = Notes{json::load(R"({"wordCounts":100, "notesCategory":"Dairy", "mediaType":"Notes", "isPublic":false, "id":1})")};
    notesMap[2] = Notes{json::load(R"({"wordCounts":200, "notesCategory":"Dairy", "mediaType":"Notes", "isPublic":true, "id":2})")};
    


    // Setup resource map to be empty before the test
    GenericAPI<Notes>::resourceMap = notesMap;

    // Perform the action
    response res = GenericAPI<Notes>::deleteResource(2);

    // Check the results
    CHECK(res.code == 204); // Check that the response code is 204 No Content
    CHECK(res.body == ""); // Validate the reponse body
    CHECK(GenericAPI<Notes>::resourceMap.size() == 1); // Ensure one resource was removed from the map
}

