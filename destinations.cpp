#include "destinations.h"



using namespace std;
using namespace crow;

extern map<int, Media> mediaMap;


Destinations::Destinations(json::rvalue readValueJson)  
{
    updateFromJson(readValueJson);
}


// Convert to JSON
json::wvalue Destinations::convertToJson() 
{
    // Convert the base Destinations part
    //json::wvalue writeJson = Destinations::convertToJson();

    // Add Destinations-specific details
    json::wvalue writeJson;
    writeJson["id"] = id;
    writeJson["destination"] = destination;
    writeJson["hasMedia"] = hasMedia;
    //writeJson["linkToCoverMedia"] = linkToCoverMedia;
    // Convert destinations to json (Save only the ids)
    int index = 0;
    for (Media media : media) 
    {
        writeJson["media"][index]["id"] = media.getId();
    }

    return writeJson;
}

// Update from JSON
void Destinations::updateFromJson(json::rvalue readValueJson)
{
    // Update the base Destinations part
    //Destinations::updateFromJson(readValueJson); 

    // Update Destinations-specific details
    id = readValueJson["id"].i();
    destination = readValueJson["destination"].s();
    hasMedia = readValueJson["hasMedia"].b();
    //linkToCoverMedia = readValueJson["linkToCoverMedia"].s();
    // Setting media

    //for (json::rvalue mediaReadValueJson: readValueJson["media"])
    //{
    //   media.push_back(mediaMap.at(mediaReadValueJson["id"].i()));
    //}

    for (json::rvalue mediaReadValueJson: readValueJson["media"]) {
    int mediaId = mediaReadValueJson["id"].i();
    if (mediaMap.find(mediaId) != mediaMap.end()) {
        media.push_back(mediaMap.at(mediaId));
    } else {
        // Handle the missing key case
        // For example, log an error or skip this media
    }
}

    


}