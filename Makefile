CC = g++

HEADERS = -Isrc/include -IHeaders

SEARCHDIR = -Lsrc/lib

OUTPUT = -o build/Liederbock

FILES = Files/*.cpp

WINOPT = -mwindows

LIBLINK = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

LINKOPT = -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic

all: windows

windows:
	$(CC) $(HEADERS) $(SEARCHDIR) $(OUTPUT) $(FILES) $(WINOPT) $(LIBLINK) $(LINKOPT)

notstatic:
	$(CC) $(HEADERS) $(SEARCHDIR) $(OUTPUT) $(FILES) $(WINOPT) $(LIBLINK)