# Makefile

CXX = g++
C_FILES = Text.cpp Camera.cpp shapes.cpp Texture.cpp Shader.cpp Mesh.cpp Cylinder.cpp
MISC_FILES = Makefile README.md arial.ttf
EXE = project
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
CLEAN=rm -f $(EXE) *.o *.a
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



$(EXE).a: Text.o Camera.o shapes.o Texture.o Shader.o Mesh.o Cylinder.o
	ar -rcs $@ $^

# Compile rules
.cpp.o:
	$(CXX) -c $(CFLG) $<

# Link
$(EXE): army.o $(EXE).a
	$(CXX) $(CFLG) -o $@ $^ $(LIBS)

# Clean
clean:
	$(CLEAN)

zip:
	zip -r $(EXE).zip army.cpp $(C_FILES) objects/*.h Text.h Mesh.h Shader.h Camera.h lib.h shapes.h Texture.h $(MISC_FILES) textures/
