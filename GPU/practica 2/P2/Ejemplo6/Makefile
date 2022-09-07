CXX=dpcpp
CXXFLAGS=-I. -g -O0
LIBS=

%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

debug: debug.o
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS) 

clean:
	rm -f debug *.o
