#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include "ex19.h"

int Monster_attack(void *self, int damage)
{
	assert(self != NULL);

	Monster *monster = self;

	assert(! (printf("You attack %s!\n", monster->_(description)) < 0));

	monster->hit_points -= damage;

	if(monster->hit_points > 0){
		assert(! (printf("It is still alive.\n") < 0));
		return 0;
	} else {
		assert(! (printf("It is dead!\n") < 0));
		return 1;
	}
}

int Monster_init(void *self){
	assert(self != NULL);

	Monster *monster = self;
	monster->hit_points = 10;
	return 1;
}

Object MonsterProto = {
	.init = Monster_init,
	.attack = Monster_attack
};

void *Room_move(void *self, Direction direction)
{
	assert(self != NULL);
	assert(direction == NORTH || direction == SOUTH ||
		   direction == EAST  || direction == WEST);

	Room *room = self;
	Room *next = NULL;

	if(direction == NORTH && room->north){
		assert(! (printf("You go north, into:\n") < 0));
		next = room->north;
	} else if(direction == SOUTH && room->south){
		assert(! (printf("You go south into:\n") < 0));
		next = room->south;
	} else if(direction == EAST && room->east){
		assert(! (printf("You go east into:\n") < 0));
		next = room->east;
	} else if(direction == WEST && room->west){
		assert(! (printf("You go west into:\n") < 0));
		next = room->west;
	} else {
		assert(! (printf("You can't go in that direction!\n") < 0));
		next = NULL;
	}

	if(next){
		next->_(describe)(next);
	}

	return next;
}

int Room_attack(void *self, int damage){
	assert(self != NULL);

	Room *room = self;
	Monster *monster = room->bad_guy;

	if(monster){
		monster->_(attack)(monster, damage);
		return 1;
	} else {
		assert(! (printf("You flail in the air at nothing.\n") < 0));
		return 0;
	}
}

Object RoomProto = {
	.move = Room_move,
	.attack = Room_attack
};

void *Map_move(void *self, Direction direction){
	assert(self != NULL);
	assert(direction == NORTH || direction == SOUTH || 
		   direction == EAST  || direction == WEST);

	Map *map = self;
	Room *location = map->location;
	Room *next = NULL;

	next = location->_(move)(location, direction);

	if(next){
		map->location = next;
	}

	return next;
}

int Map_attack(void *self, int damage){
	assert(self != NULL);

	Map *map = self;
	Room *location = map->location;

	return location->_(attack)(location, damage);
}

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

Object MapProto = {
	.init = Map_init,
	.move = Map_move,
	.attack = Map_attack
};

int process_input(Map *game){
	assert(game != NULL);

	assert(! (printf("\n> ") < 0));

	char ch = getchar();
	getchar();

	int damage = rand() % 4;

	switch(ch){
		case -1:
			assert(! (printf("Giving up? You suck.\n") < 0));
			return 0;
			break;

		case 'n':
			game->_(move)(game, NORTH);
			break;

		case 's':
			game->_(move)(game, SOUTH);
			break;

		case 'e':
			game->_(move)(game, EAST);
			break;

		case 'w':
			game->_(move)(game, WEST);
			break;

		case 'a':
			game->_(attack)(game, damage);
			break;

		case 'l':
			assert(! (printf("You can go:\n") < 0));

			if(game->location->north) assert(! (printf("NORTH\n") < 0));
			if(game->location->south) assert(! (printf("SOUTH\n") < 0));
			if(game->location->east) assert(! (printf("EAST\n") < 0));
			if(game->location->west) assert(! (printf("WEST\n") < 0));
			break;

		default:
			assert(! (printf("What?: %d\n", ch) < 0));
	}

	return 1;
}

int main(int argc, char *argv[]){
	srand(time(NULL));

	Map *game = NEW(Map, "The Hall of the Minotaur.");
	assert(game != NULL);

	assert(! (printf("You enter the ") < 0));
	game->location->_(describe)(game->location);

	while(process_input(game)){
	}

	return 0;
}
