all: travelAPI run-unit-tests static-analysis 

travelAPI: travelAPI.o profiles.o destinations.o photos.o media.o notes.o GenericAPI.o 
	g++ -lpthread travelAPI.o profiles.o destinations.o photos.o media.o notes.o GenericAPI.o -o travelAPI

travelAPI.o: travelAPI.cpp profiles.h destinations.h photos.h media.h notes.h GenericAPI.h persistence.h
	g++ -Wall -c travelAPI.cpp 

profiles.o: profiles.cpp profiles.h
	g++ -Wall -c profiles.cpp

destinations.o: destinations.cpp destinations.h
	g++ -Wall -c destinations.cpp 

media.o: media.cpp media.h
	g++ -Wall -c media.cpp 

notes.o: notes.cpp notes.h
	g++ -Wall -c notes.cpp

photos.o: photos.cpp photos.h
	g++ -Wall -c photos.cpp  

GenericAPI.o: GenericAPI.cpp GenericAPI.h photos.h notes.h media.h destinations.h profiles.h
	g++ -Wall -c GenericAPI.cpp 







GenericAPITest: GenericAPITest.cpp GenericAPI.o profiles.o destinations.o media.o photos.o notes.o
	g++ -lpthread GenericAPITest.cpp GenericAPI.o profiles.o destinations.o media.o photos.o notes.o -o GenericAPITest

persistenceTest: persistenceTest.cpp persistence.h photos.o notes.o media.o profiles.o destinations.o
	g++ -lpthread persistenceTest.cpp photos.o notes.o media.o profiles.o destinations.o -o persistenceTest

mediaTest: mediaTest.cpp media.cpp media.h media.o
	g++ -lpthread mediaTest.cpp media.o -o mediaTest

notesTest: notesTest.cpp notes.cpp notes.h notes.o
	g++ -lpthread notesTest.cpp notes.o -o notesTest 

photosTest: photosTest.cpp photos.cpp photos.h photos.o
	g++ -lpthread photosTest.cpp photos.o -o photosTest

destinationsTest: destinationsTest.cpp destinations.cpp destinations.h destinations.o
	g++ -lpthread destinationsTest.cpp destinations.o -o destinationsTest

profilesTest: profilesTest.cpp profiles.cpp profiles.h profiles.o
	g++ -lpthread profilesTest.cpp profiles.o -o profilesTest



run-unit-tests: GenericAPITest persistenceTest
	./GenericAPITest ./persistenceTest ./destinationsTest ./profilesTest ./mediaTest ./notesTest ./photosTest		

static-analysis:
	cppcheck *.cpp

clean:
	rm -f *.o travelAPI GenericAPITest persistenceTest profilesTest destinationsTest mediaTest notesTest photosTest

