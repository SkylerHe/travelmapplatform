#ifndef PROFILES_H
#define PROFILES_H

#include <crow.h>
#include "destinations.h"
#include <string>


class Profiles
{
public:
    Profiles() {}
    Profiles(crow::json::rvalue readValueJson);

    // Getters
    int getId() const { return id; }
    std::vector<Destinations> getDestinations() const { return destinations; }
    std::string getGender() const { return gender; }
    int getAge() const { return age; }
    //std::string setLinkToCoverDestinations() const { return linkToCoverDestinations; }

    // Setters
    void setId(int idParam) { id = idParam; }
    void setDestinations(std::vector<Destinations>& destinationsParam) { destinations = destinationsParam; }
    void setGender(std::string genderParam) { gender = genderParam; }
    void setAge(int ageParam) { age = ageParam; }
    //void setLinkToCoverDestinations(std::string linkToCoverDestinationsParam) { linkToCoverDestinations = linkToCoverDestinationsParam; }

    // Convert to JSON.
    crow::json::wvalue convertToJson();

    // Update from JSON.
    void updateFromJson(crow::json::rvalue readValueJson);

private:
    int id;
    std::vector<Destinations> destinations;
    std::string gender;
    int age;
    //std::string linkToCoverDestinations;
};

#endif // PROFILES_H