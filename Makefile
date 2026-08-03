
CXX = g++

CXXFLAGS = -std=c++11 -Wall -g

TARGET = os_simulator

OBJS = main.o ProcessScheduler.o MemoryManager.o FileSystem.o CustomShell.o


all: $(TARGET)


$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)



main.o: main.cpp CustomShell.h
	$(CXX) $(CXXFLAGS) -c main.cpp

ProcessScheduler.o: ProcessScheduler.cpp ProcessScheduler.h Process.h
	$(CXX) $(CXXFLAGS) -c ProcessScheduler.cpp

MemoryManager.o: MemoryManager.cpp MemoryManager.h
	$(CXX) $(CXXFLAGS) -c MemoryManager.cpp

FileSystem.o: FileSystem.cpp FileSystem.h
	$(CXX) $(CXXFLAGS) -c FileSystem.cpp

CustomShell.o: CustomShell.cpp CustomShell.h ProcessScheduler.h MemoryManager.h FileSystem.h
	$(CXX) $(CXXFLAGS) -c CustomShell.cpp


clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run