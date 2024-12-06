# Makefile

CXX = g++
C_FILES = *.cpp objects/*.cpp
MISC_FILES = Makefile README.md arial.ttf
EXE = final
#  Msys/MinGW
ifeq "$(OS)" "Windows_NT"
CFLG=-O3 -Wall -DUSEGLEW
LIBS=-lfreeglut -lglew32 -lglu32 -lopengl32 -lm
CLEAN=rm -f *.exe *.o *.a
else
#  OSX
ifeq "$(shell uname)" "Darwin"
RES=$(shell uname -r|sed -E 's/(.).*/\1/'|tr 12 21)
LDFLAGS  :=$(shell sdl2-config --libs)
CXXFLAGS :=$(shell sdl2-config --cflags)
CFLG=-O3 -Wall -Wno-deprecated-declarations $(CXXFLAGS) -DRES=$(RES)
LIBS= $(LDFLAGS) -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -framework Cocoa -framework OpenGL
# test if glm is installed
#  Linux/Unix/Solaris
else
CFLG= -Wall -g
LIBS=-lglut -lGLU -lGL -lm -lSDL2 -lSDL2_ttf -lSDL2_image -lGLEW
endif
#  OSX/Linux/Unix/Solaris
CLEAN=rm -f $(EXE) *.o *.a objects/*.o
endif

all: $(EXE)
# Dependencies
# Dependencies
army.o : army.cpp

Text.o: Text.cpp Text.h
Camera.o: Camera.cpp Camera.h
shapes.o: shapes.cpp shapes.h
Texture.o: Texture.cpp Texture.h
Shader.o: Shader.cpp Shader.h
Mesh.o: Mesh.cpp Mesh.h
objects/Cylinder.o: objects/Cylinder.cpp objects/Cylinder.h
objects/Sphere.o: objects/Sphere.cpp objects/Sphere.h
objects/Cube.o: objects/Cube.cpp objects/Cube.h
objects/Skybox.o: objects/Skybox.cpp objects/Skybox.h
objects/House.o: objects/House.cpp objects/House.h
objects/Tree.o: objects/Tree.cpp objects/Tree.h


objects/%.o: objects/%.cpp
	$(CXX) -c $(CFLG) -o $@ $<

objects.a: objects/Cylinder.o objects/Sphere.o objects/Cube.o objects/Skybox.o objects/House.o objects/Tree.o
	ar -rcs $@ $^

$(EXE): army.o Text.o Camera.o shapes.o Texture.o Shader.o Mesh.o objects.a
	$(CXX) $(CFLG) -o $@ $^ $(LIBS)


# $(EXE).a: Text.o Camera.o shapes.o Texture.o Shader.o Mesh.o objects/Cylinder.o objects/Sphere.o
# 	ar -rcs $@ $^

# Compile rules
.cpp.o:
	$(CXX) -c $(CFLG) $<

# Clean
clean:
	$(CLEAN)

zip:
	zip -r $(EXE).zip army.cpp $(C_FILES) objects/*.h *.h $(MISC_FILES) textures/ shaders/
