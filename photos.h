#ifndef PHOTOS_H
#define PHOTOS_H

#include <crow.h>
#include <string>
#include "media.h"

class Photos : public Media
{
public:
    Photos() {}
    Photos(crow::json::rvalue readValueJson);

    // Getters
    double getPhotosSize() const { return photosSize; }
    std::string getPhotosCategory() const { return photosCategory; }

    // Setters
    void setPhotosSize(double photosSizeParam) { photosSize = photosSizeParam; }
    void setPhotosCategory(std::string photosCategoryParam) { photosCategory = photosCategoryParam; }

    // Convert to JSON.
    crow::json::wvalue convertToJson();

    // Update from JSON.
    void updateFromJson(crow::json::rvalue readValueJson);

private:
    double photosSize;
    std::string photosCategory;
};

#endif //PHOTOS_H