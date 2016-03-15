TARGET = RayTracer

SRC =  main.cpp\
		Device.cpp \
		Driver.cpp \
		Window.cpp \
		Event.cpp \
		Raytracer.cpp \
		Ray.cpp \
		GeometryBuffer.cpp \
		MaterialBuffer.cpp \
		Camera.cpp \
		MathCalc.cpp \
		CollisionCalc.cpp \
		SceneNode.cpp \
		RenderBuffer.cpp \
		Log.cpp \
		LightCalc.cpp \
		ReflexionCalc.cpp \
		Model.cpp \

LIBS = SDL2 GL GLEW SDL2_image

MODE = release
BIN_DIR = bin/$(MODE)/
OBJ_DIR = obj/$(MODE)/
SRC_DIR = src/
INC_DIR = include/ /usr/include/SDL2/

OBJ = $(patsubst %.cpp,$(OBJ_DIR)%.o,$(SRC))
DEPENDENCIES = $(OBJ:.o=.d)
ARBO = $(sort $(dir $(DEPENDENCIES) $(OBJ_DIR)))
INCLUDES = $(addprefix -I,$(INC_DIR))
LIBRARIES = $(addprefix -l,$(LIBS))
CXXFLAGS = -MMD -W -Wall -Werror
LDFLAGS = -W -Wall -Werror
CXX = g++ -std=c++14

.PHONY: all clean fclean re debug release

all: $(MODE)

release: CXXFLAGS += -O3
release: LDFLAGS += -O3
release: $(TARGET)

debug: CXXFLAGS += -O0 -g3
debug: LDFLAGS += -O0 -g3
debug: CPPFLAGS += -D_DEBUG
debug: $(TARGET)

$(TARGET): $(BIN_DIR)$(TARGET) | $(ARBO)

$(BIN_DIR)$(TARGET): $(OBJ) | $(BIN_DIR)
	$(CXX) $(LDFLAGS) -o $@ $(OBJ) $(LIBRARIES)

$(OBJ): | $(ARBO)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(ARBO):
	mkdir -p $@

-include $(DEPENDENCIES)

clean:
	$(RM) $(OBJ)
	$(RM) $(DEPENDENCIES)
	$(RM) -r $(ARBO)
	$(RM) .*.swp

fclean: clean
	$(RM) $(TARGET)

re: fclean release

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $< $(INCLUDES)
