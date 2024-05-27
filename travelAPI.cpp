#include <crow.h>
#include <map>
#include <csignal>
#include <string>
#include "profiles.h"
#include "destinations.h"
#include "media.h"
#include "photos.h"
#include "notes.h"
#include "GenericAPI.h"
#include "persistence.h"

using namespace std;
using namespace crow;

// Load resources from files.
map<int, Profiles> profilesMap = loadFromFile<Profiles>("profiles.json");
map<int, Destinations> destinationsMap = loadFromFile<Destinations>("destinations.json");
map<int, Media> mediaMap = loadFromFile<Media>("media.json");
map<int, Photos> photosMap = loadFromFile<Photos>("photos.json");
map<int, Notes> notesMap = loadFromFile<Notes>("notes.json");

int main() 
{
    // Create GenericAPIs to use in the CROW_ROUTES
    GenericAPI<Profiles>::resourceMap = profilesMap;
    GenericAPI<Destinations>::resourceMap = destinationsMap;
    GenericAPI<Media>::resourceMap = mediaMap;
    GenericAPI<Photos>::resourceMap = photosMap;
    GenericAPI<Notes>::resourceMap = notesMap;

    // Setup the simple web service.
    SimpleApp app;

    // Define resources:

    // Profiles
    CROW_ROUTE(app, "/api/profiles").methods("POST"_method)(GenericAPI<Profiles>::createResource);
    CROW_ROUTE(app, "/api/profiles").methods("GET"_method)(GenericAPI<Profiles>::readAllResources);
    CROW_ROUTE(app, "/api/profiles/<int>").methods("GET"_method)(GenericAPI<Profiles>::readResource);
    CROW_ROUTE(app, "/api/profiles/<int>").methods("PUT"_method)(GenericAPI<Profiles>::updateResource);
    CROW_ROUTE(app, "/api/profiles/<int>").methods("DELETE"_method)(GenericAPI<Profiles>::deleteResource);

    // Destinations
    CROW_ROUTE(app, "/api/destinations").methods("POST"_method)(GenericAPI<Destinations>::createResource);
    CROW_ROUTE(app, "/api/destinations").methods("GET"_method)(GenericAPI<Destinations>::readAllResources);
    CROW_ROUTE(app, "/api/destinations/<int>").methods("GET"_method)(GenericAPI<Destinations>::readResource);
    CROW_ROUTE(app, "/api/destinations/<int>").methods("PUT"_method)(GenericAPI<Destinations>::updateResource);
    CROW_ROUTE(app, "/api/destinations/<int>").methods("DELETE"_method)(GenericAPI<Destinations>::deleteResource);

    // Media
    CROW_ROUTE(app, "/api/media").methods("POST"_method)(GenericAPI<Media>::createResource);
    CROW_ROUTE(app, "/api/media").methods("GET"_method)(GenericAPI<Media>::readAllResources);
    CROW_ROUTE(app, "/api/media/<int>").methods("GET"_method)(GenericAPI<Media>::readResource);
    CROW_ROUTE(app, "/api/media/<int>").methods("PUT"_method)(GenericAPI<Media>::updateResource);
    CROW_ROUTE(app, "/api/media/<int>").methods("DELETE"_method)(GenericAPI<Media>::deleteResource);

    // Photos
    CROW_ROUTE(app, "/api/photos").methods("POST"_method)(GenericAPI<Photos>::createResource);
    CROW_ROUTE(app, "/api/photos").methods("GET"_method)(GenericAPI<Photos>::readAllResources);
    CROW_ROUTE(app, "/api/photos/<int>").methods("GET"_method)(GenericAPI<Photos>::readResource);
    CROW_ROUTE(app, "/api/photos/<int>").methods("PUT"_method)(GenericAPI<Photos>::updateResource);
    CROW_ROUTE(app, "/api/photos/<int>").methods("DELETE"_method)(GenericAPI<Photos>::deleteResource);

    // Notes
    CROW_ROUTE(app, "/api/notes").methods("POST"_method)(GenericAPI<Notes>::createResource);
    CROW_ROUTE(app, "/api/notes").methods("GET"_method)(GenericAPI<Notes>::readAllResources);
    CROW_ROUTE(app, "/api/notes/<int>").methods("GET"_method)(GenericAPI<Notes>::readResource);
    CROW_ROUTE(app, "/api/notes/<int>").methods("PUT"_method)(GenericAPI<Notes>::updateResource);
    CROW_ROUTE(app, "/api/notes/<int>").methods("DELETE"_method)(GenericAPI<Notes>::deleteResource);


    // Run the web service app.
    app.port(18888).run();
        
    // After the web service stops running:

    // Perform persistence of resources
    saveToFile<Profiles>(GenericAPI<Profiles>::resourceMap, "profiles.json");
    saveToFile<Destinations>(GenericAPI<Destinations>::resourceMap, "destinations.json");
    saveToFile<Media>(GenericAPI<Media>::resourceMap, "media.json");
    saveToFile<Photos>(GenericAPI<Photos>::resourceMap, "photos.json");
    saveToFile<Notes>(GenericAPI<Notes>::resourceMap, "notes.json");

}