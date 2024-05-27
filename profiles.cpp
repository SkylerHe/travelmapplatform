#include "profiles.h"


using namespace std;
using namespace crow;

extern map<int, Destinations> destinationsMap;

Profiles::Profiles(json::rvalue readValueJson)  
{
    updateFromJson(readValueJson);
}

// Convert to JSON
json::wvalue Profiles::convertToJson() 
{
    json::wvalue writeJson;
    writeJson["id"] = id;
    writeJson["gender"] = gender;
    writeJson["age"] = age;
    //writeJson["linkToCoverDestinations"] = linkToCoverDestinations;
    // Convert destinations to json (Save only the ids)
    int index = 0;
    for (Destinations destinations : destinations) 
    {
        writeJson["destinations"][index]["id"] = destinations.getId();
    }
    return writeJson;
}

// Update from JSON
void Profiles::updateFromJson(json::rvalue readValueJson) 
{
    id = readValueJson["id"].i();
    gender = readValueJson["gender"].s();
    age = readValueJson["age"].i();
    //linkToCoverDestinations = readValueJson["linkToCoverDestinations"].s();

    // Setting detinations
    //for (json::rvalue destinationsReadValueJson: readValueJson["destinations"])
    //{
    //   destinations.push_back(destinationsMap.at(destinationsReadValueJson["id"].i()));
    //}

    for (json::rvalue destinationsReadValueJson: readValueJson["destinations"]) 
    {
        int destinationId = destinationsReadValueJson["id"].i();
        if (destinationsMap.find(destinationId) != destinationsMap.end()) 
        {
            destinations.push_back(destinationsMap.at(destinationId));
        } 
        else 
        {
            // Handle the missing key case
            // For example, log an error or skip this destination
        }
    }

}