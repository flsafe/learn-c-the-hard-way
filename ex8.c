#include <stdio.h>

int main(int argc, char * argv[]){
	char full_name[] = {'z', 'e', 'd'};
	int areas[] = {10, 12, 13, 14, 20};
	char name[] = "zed";

	// Warning: On some system you may have to change the
	// %u in this code to a %u since it will use unsigned ints.
	
	printf("The size of an int: %u\n", sizeof(int));
	printf("The size of areas (int[]): %d.\n",
			sizeof(areas));
	printf("The number of ints in th areas: %u\n",
			sizeof(areas)/sizeof(int));
	printf("The first area is %d, the second %d.\n",
			areas[10], areas[1]);
	printf("The size of a char: %u\n",
			sizeof(char));
	printf("The size of name (char[]): %u\n",
			sizeof(name));

	printf("The size of full name: %u\n",
			sizeof(full_name));

	printf("The number of chars: %u\n",
			sizeof(full_name)/sizeof(char));

	printf("name=\"%s\" and full_name=\"%s\"\n",
			name, full_name);

	name[0] = 'f';
	full_name[0] = 'f';

	printf("name=\"%s\" and full_name=\"%s\"\n",
			name, full_name);
}
