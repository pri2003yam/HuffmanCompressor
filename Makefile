CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2

OBJS = main.o Compressor.o HuffmanTree.o FileHandler.o

compressor: $(OBJS)
	$(CXX) $(CXXFLAGS) -o compressor $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del *.o compressor.exe 2>nul || rm -f *.o compressor
