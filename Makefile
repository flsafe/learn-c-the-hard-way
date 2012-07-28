CFLAGS=-Wall -g

all: ex19

ex19: object.o

mini_game: mini_game.c object.c game_core.o

ex22_main: ex22_main.c ex22.o

clean:
	rm -f ex19
	rm -f object.o
	rm -f mini_game
	rm -f game_core.o
	rm -f ex22.o
	rm -f ex22_main
