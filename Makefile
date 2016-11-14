# Define required macros here

PROGRAM = lettersjuggler

CXXSOURCES = lj.cpp keyboard_dweller.cpp gtk_letters_window.cpp
CXXOBJECTS = $(CXXSOURCES:.cpp=.o)
CXXFLAGS = -std=c++11 `pkg-config --cflags gtk+-2.0`
CXXLIBS = -lX11 `pkg-config gtk+-2.0 --libs`
CXX = g++ 

all: $(PROGRAM)

$(PROGRAM): $(CXXOBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(CXXOBJECTS) $(CXXLIBS) 

ljt.o: lj.cpp
	$(CXX) $(CXXFLAGS) -c lj.cpp $(CXXLIBS)

keyboard_dweller.o: keyboard_dweller.h lj_thread_communication.h keyboard_dweller.cpp
	$(CXX) $(CXXFLAGS) -c keyboard_dweller.cpp $(CXXLIBS)
	
gtk_letters_window.o: gtk_letters_window.h lj_thread_communication.h gtk_letters_window.cpp
	$(CXX) $(CXXFLAGS) -c gtk_letters_window.cpp $(CXXLIBS)
	
clean:
	$(RM) -f *.o core *.core

run:
	./$(PROGRAM)
