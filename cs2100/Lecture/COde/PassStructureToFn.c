// PassStructureToFn.c 
#include <stdio.h>
#include <string.h>

typedef struct {
	char name[12];
	int  age;
	char gender;
} player_t;

void print_player(char [], player_t);

int main(void) {
	player_t player1 = { "Brusco", 23, 'M' },
			 player2;

	strcpy(player2.name, "July");
	player2.age = 21;
	player2.gender = 'F';

	print_player("player1", player1);
	print_player("player2", player2);

	return 0;
}

// Print player's information
void print_player(char header[], player_t player) {
	printf("%s: name = %s; age = %d; gender = %c\n", header,
			player.name, player.age, player.gender);
}

