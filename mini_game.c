#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include "game_core.h"

int Map_init(void *self){
	assert(self != NULL);

	Map *map = self;

	Room *hall = NEW(Room, "The great Hall");
	assert(hall != NULL);

	Room *throne = NEW(Room, "The throne room");
	assert(throne != NULL);

	Room *arena = NEW(Room, "The arena with the minotaur");
	assert(arena != NULL);

	Room *kitchen = NEW(Room, "Kitchen, you hav the knife now");
	assert(kitchen != NULL);

	arena->bad_guy = NEW(Monster, "The evil minotaur");
	assert(arena->bad_guy != NULL);

	hall->north = throne;

	throne->west = arena;
	throne->east = kitchen;
	throne->south = hall;

	arena->east = throne;
	kitchen->west = throne;

	map->start = hall;
	map->location = hall;

	return 1;
}

Object MapProto;

int main(int argc, char *argv[]){
	srand(time(NULL));

	MapProto.init = Map_init;
	Map *game = NEW(Map, "The Hall of the Minotaur.");
	assert(game != NULL);

	assert(! (printf("You enter the ") < 0));
	game->location->_(describe)(game->location);

	while(process_input(game)){
	}

	return 0;
}
