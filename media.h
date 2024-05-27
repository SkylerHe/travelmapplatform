#ifndef MEDIA_H
#define MEDIA_H

#include <crow.h>
#include <string>

class Media
{
public:
    Media() {}
    Media(crow::json::rvalue readValueJson);

    // Getters
    int getId() const { return id; }
    bool getIsPublic() const { return isPublic; }
    std::string getMediaType() const { return mediaType; }

    // Setters
    void setId(int idParam) { id = idParam; }
    void setIsPublic(bool isPublicParam) { isPublic = isPublicParam; }
    void setMediaType(std::string mediaTypeParam) { mediaType = mediaTypeParam; }

    // Convert to JSON.
    crow::json::wvalue convertToJson();

    // Update from JSON.
    void updateFromJson(crow::json::rvalue readValueJson);

private:
    int id;
    bool isPublic;
    std::string mediaType;
};

#endif //MEDIA_H