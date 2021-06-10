CFLAGS = $(shell sdl2-config --cflags) -Wall
LDLIBS := $(shell sdl2-config --libs)  -lSDL2_gfx

