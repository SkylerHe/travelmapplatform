#include "media.h"

using namespace std;
using namespace crow;


Media::Media(json::rvalue readValueJson)  
{
    updateFromJson(readValueJson);
}


// Convert to JSON
json::wvalue Media::convertToJson() 
{
    // Convert the base media part
    //json::wvalue writeJson = Media::convertToJson();

    // Add media-specific details
    json::wvalue writeJson;
    writeJson["id"] = id;
    writeJson["isPublic"] = isPublic;
    writeJson["mediaType"] = mediaType;

    return writeJson;
}

// Update from JSON
void Media::updateFromJson(json::rvalue readValueJson)
{
    // Update the base Destinations part
    // Media::updateFromJson(readValueJson); 

    // Update Destinations-specific details
    id = readValueJson["id"].i();
    isPublic = readValueJson["isPublic"].b();
    mediaType = readValueJson["mediaType"].s();


}