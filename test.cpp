#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <crow.h>
#include <doctest.h>
#include "University.h"
#include "persistence.h"

using namespace std;
using namespace crow;


TEST_CASE("Saving to a file and loading from a file.") 
{
    // Load a resources to read.
    map<string, University> universityMap;
    universityMap["Royal Holloway University of London"] = University{json::load(R"({   "web_pages":"https://rhul.ac.uk","name":"Royal Holloway University of London","domains":"rhul.ac.uk", "country":"United Kingdom", "alpha_two_code":"GB", "state-province":"null"     })")};
    universityMap["University of Portsmouth"] = University{json::load(R"({   "state-province":"null","alpha_two_code":"GB","name":"University of Portsmouth","country":"United Kingdom","web_pages":"https://myport.port.ac.uk","domains":"myport.ac.uk"   })")};

    // Perform the action
    saveToFile<University>(universityMap, "persistenceTest.json");
    map<string, University> universityMapLoaded = loadFromFile<University>("persistenceTest.json");

    // Check the results
    CHECK(universityMap.size() == universityMapLoaded.size()); // Ensure saved and loaded map are the same size.
    CHECK(universityMap.at("Royal Holloway University of London").getId() == universityMapLoaded.at("Royal Holloway University of London").getId()); // Validate the resource content
    CHECK(universityMap.at("Royal Holloway University of London").getDomains() == universityMapLoaded.at("Royal Holloway University of London").getDomains()); // Validate the resource content
    CHECK(universityMap.at("University of Portsmouth").getId() == universityMapLoaded.at("University of Portsmouth").getId()); // Validate the resource content
    CHECK(universityMap.at("University of Portsmouth").getDomains() == universityMapLoaded.at("University of Portsmouth").getDomains()); // Validate the resource content
}