#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include "game_core.h"

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
	.attack = Monster_attack,
	.init = Monster_init
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

Object MapProto = {
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
