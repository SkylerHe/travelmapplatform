#ifndef GENERIC_API_H
#define GENERIC_API_H

#include <crow.h>
#include <map>
#include <string>

template<typename T> 
class GenericAPI 
{
public:
    static std::map<int, T> resourceMap;
    static crow::response createResource(crow::request req);
    static crow::response readResource(int id); 
    static crow::response readAllResources();
    static void updateResource(crow::request req, crow::response& res, int id); 
    static crow::response deleteResource(int id); 
};

#endif // GENERIC_API_H