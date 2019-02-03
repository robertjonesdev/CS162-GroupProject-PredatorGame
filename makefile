#Project name, used for naming zip
PROJECT = Group_Project_Group16

#Final executable name
BIN = Predator-Prey

#automatically includes all cpp files in directory
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:%.cpp=%.o)

#generates dependencies automatically, adopted from https://stackoverflow.com/a/21086223
CXX = g++
CXXFLAGS = -std=c++11 -MD -MP -g
$(BIN): $(OBJECTS)
	${CXX} ${CXXFLAGS} -o $@ $^

-include $(SOURCES:%.cpp=%.d)

#allows memory leak checking with "make valgrind"
.PHONY : valgrind
valgrind:
	@valgrind --leak-check=full --track-origins=yes ./$(BIN)

#zips all cpp hpp pdf and makefiles with "make zip"
.PHONY : zip
zip:
	zip $(PROJECT).zip *.cpp *.hpp *.pdf makefile

#makes "make clean" work on Windows too, adapted from https://stackoverflow.com/questions/2463037/calling-windows-commands-e-g-del-from-a-gnu-makefile
ifeq ($(OS),Windows_NT)
    RM = cmd /C del /Q /F
else
    RM = rm -f
endif

#removes binary, .d (dependency), .o files
.PHONY : clean
clean:
	$(RM) $(BIN) *.d *.o core