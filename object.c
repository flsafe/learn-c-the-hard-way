#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "object.h"
#include <assert.h>

void Object_destroy(void *self)
{
	assert(self != NULL);

	Object *obj = self;

	if(obj){
		if(obj->description) free(obj->description);
		free(obj);
	}
}

void Object_describe(void *self)
{
	assert(self != NULL);

	Object *obj = self;
	assert(! (printf("%s.\n", obj->description) < 0));
}

int Object_init(void *self)
{
	assert(self != NULL);

	// do nothing really
	return 1;
}

void *Object_move(void *self, Direction direction)
{
	assert(self != NULL);
	assert(direction == NORTH ||direction == SOUTH || 
		   direction == EAST  || direction == WEST);

	assert(! (printf("You can't go in that direction.\n") < 0));
	return NULL;
}

int Object_attack(void *self, int damage)
{
	assert(! (printf("You can't attack that.\n") < 0));
	return 0;
}

void *Object_new(size_t size, Object proto, char *description)
{
	assert(size != 0);
	assert(description != NULL);

	if(!proto.init) proto.init = Object_init;
	if(!proto.describe) proto.describe = Object_describe;
	if(!proto.destroy) proto.destroy = Object_destroy;
	if(!proto.attack) proto.attack = Object_attack;
	if(!proto.move) proto.move = Object_move;

	Object *el = calloc(1, size);
	assert(el != NULL);

	*el = proto;

	// copy the description over
	el->description = strdup(description);
	assert(el->description != NULL);

	if(!el->init(el)){
		// looks like it didn't initialize properly
		el->destroy(el);
		return NULL;
	} else {
		// all done, we made an object of any type
		return el;
	}
}
