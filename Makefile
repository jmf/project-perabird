.SUFFIXES: 
.PHONY: clean mrproper run
EXEC_NAME=test

CROSS=false

CXX=g++
DEST=bin

ifeq ($(CROSS),true)
	CXX=i486-mingw32-g++
	LIBS= -lmingw32 -mwindows -lSDLmain -lopengl32 -lglu32
	DEST=build/windows/
	EXEC=$(EXEC_NAME).exe
	INCLUDES=
else
	LIBS=-lGL -lGLU
	EXEC=$(EXEC_NAME)
endif

LIBS+=-lSDL -lSDL_mixer -lSDL_image -lSDL_net -lcrypto -lIrrlicht
INCLUDES+=-I include/

CXXFLAGS=-g

LDFLAGS=$(LIBS)

SRC=$(wildcard src/*.cpp)
OBJ=$(SRC:.cpp=.o)

all: $(EXEC)
	mkdir -p $(DEST)
	cp $(EXEC) $(DEST)
	rm $(EXEC)
$(EXEC): $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS) $(CXXFLAGS)

src/%.o: src/%.cpp
	$(CXX) -o $@ -c $< $(INCLUDES) $(CXXFLAGS)


clean:
	rm src/*.o

mrproper: clean
	rm $(EXEC)

run: $(EXEC)
	./$(EXEC)

