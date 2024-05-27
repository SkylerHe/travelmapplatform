#ifndef NOTES_H
#define NOTES_H

#include <crow.h>
#include <string>
#include "media.h"

class Notes : public Media
{
public:
    Notes() {}
    Notes(crow::json::rvalue readValueJson);

    // Getters
    int getWordCounts() const { return wordCounts; }
    std::string getNotesCategory() const { return notesCategory; }

    // Setters
    void setWordCounts(int wordCountsParam) { wordCounts = wordCountsParam; }
    void setNotesCategory(std::string notesCategoryParam) { notesCategory = notesCategoryParam; }

    // Convert to JSON.
    crow::json::wvalue convertToJson();

    // Update from JSON.
    void updateFromJson(crow::json::rvalue readValueJson);

private:
    int wordCounts;
    std::string notesCategory;
};

#endif //NOTES_H