SRC_FILES := $(wildcard *.cpp)
OBJ_FILES := $(patsubst %.cpp,%.o,$(SRC_FILES))
CXXFLAGS += -MMD 
CPPFLAGS += -std=c++11

-include $(OBJ_FILES:.o=.d)

all: main.out

main.out: $(OBJ_FILES)
	g++ $(LDFLAGS) -o $@ $^

%.o: %.cpp
	g++ $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f *.o *.d main.out
