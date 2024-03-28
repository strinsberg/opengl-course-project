GAME = hummer_assault

SRCDIR = src
INCDIR = -I include
LIBDIR  = -L /usr/lib/

COMPILERFLAGS = -Wall --std=c++11
CXX = g++
CXXFLAGS = $(COMPILERFLAGS) $(INCDIR)
GLLIBS = -lglut -lGL -lGLU

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: all
all: $(GAME)


$(GAME):
	$(CXX) $(CXXFLAGS) -o $(GAME) $(SRCDIR)/*.cpp $(LIBDIR) $< $(GLLIBS)


.PHONY: clean
clean:
	rm -rf *~ *.o $(GAME)
