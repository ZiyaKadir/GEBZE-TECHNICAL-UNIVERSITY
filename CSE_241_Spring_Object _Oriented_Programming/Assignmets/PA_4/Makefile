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



# SRC_DIR := .
# OBJ_DIR := .
# SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
# OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
# LDFLAGS := ...
# CPPFLAGS += -std=c++11
# CXXFLAGS += -MMD
# -include $(OBJ_FILES:.o=.d)
# main.out: $(OBJ_FILES)
# g++ $(LDFLAGS) -o $@ $ˆ
# $(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
# g++ $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<