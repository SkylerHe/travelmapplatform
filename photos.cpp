#include "photos.h"

using namespace std;
using namespace crow;


Photos::Photos(json::rvalue readValueJson)  
{
    updateFromJson(readValueJson);
}


// Convert to JSON
json::wvalue Photos::convertToJson() 
{
    // Convert the base Media part
    json::wvalue writeJson = Media::convertToJson();

    // Add Notes-specific details
    writeJson["photosSize"] = photosSize;
    writeJson["photosCategory"] = photosCategory;

    return writeJson;
}

// Update from JSON
void Photos::updateFromJson(json::rvalue readValueJson) 
{
    // Update the base Media part
    Media::updateFromJson(readValueJson); 

    // Update Notes-specific details
    photosSize = readValueJson["photosSize"].d();
    photosCategory = readValueJson["photosCategory"].s();

}