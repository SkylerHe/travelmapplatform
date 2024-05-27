#ifndef PERSISTENCE_H
#define PERSISTENCE_H

#include <map>
#include <string>

template <typename T>
void saveToFile(std::map<int, T> data, std::string filename);

template <typename T>
std::map<int, T> loadFromFile(std::string filename);

#include "persistence.cpp"

#endif // PERSISTENCE_H