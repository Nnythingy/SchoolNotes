// PassStructureToFn2.c 
#include <stdio.h>
#include <string.h>

typedef struct {
	char name[12];
	int  age;
	char gender;
} player_t;

void change_name_and_age(player_t);
void print_player(char *, player_t);

int main(void) {
	player_t player1 = { "Brusco", 23, 'M' };

	change_name_and_age(player1);
	print_player("player1", player1);

	return 0;
}

// To change a player's name and age
void change_name_and_age(player_t player) {
	strcpy(player.name, "Alexandra");
	player.age = 25;
}

// Print player's information
void print_player(char *header, player_t player) {
	printf("%s: name = %s; age = %d; gender = %c\n", header,
	       player.name, player.age, player.gender);
}

