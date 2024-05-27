#ifndef DESTINATIONS_H
#define DESTINATIONS_H

#include <crow.h>
#include <string>
#include "media.h"

class Destinations
{
public:
    Destinations() {}
    Destinations(crow::json::rvalue readValueJson);

    // Getters
    int getId() const { return id; }
    std::string getDestination() const { return destination; }
    bool getHasMedia() const { return hasMedia;}
    std::vector<Media> getMedia() const { return media; }
    //std::string setLinkToMedia() const { return linkToCoverMedia; }


    // Setters
    void setId(int idParam) { id = idParam; }
    void setDestination(std::string destinationParam) { destination = destinationParam; }
    void setHasMedia(bool hasMediaParam) { hasMedia = hasMediaParam;}
    void setMedia(std::vector<Media>& mediaParam) { media = mediaParam; }
    //void setLinkToCoverMedia(std::string LinkToCoverMediaParam) { linkToCoverMedia = LinkToCoverMediaParam; }


    // Convert to JSON.
    crow::json::wvalue convertToJson();

    // Update from JSON.
    void updateFromJson(crow::json::rvalue readValueJson);

private:
    int id;
    std::string destination;
    bool hasMedia;
    std::vector<Media> media;
    //std::string linkToCoverMedia;


};

#endif //DESTINATIONS_H