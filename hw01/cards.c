/* Code that evaluates the values of face cards and others for Blackjack.
Original concept from the book Head First C.

Copyright 2014 Lyra Silverwolf
License: Free for Public Use

*/

 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char prompt_for_user[] = "Enter the card name: ";
char card_name[2];
int value = 0;
int count = 0;

/* Prompts the user for input and puts the reply in the given buffer.

   User input is truncated to the first two characters.

   prompt: string prompt to display
   card_name: buffer where result is stored
*/

void  check_values(int *val, int *count)
{
	if ((*val > 2) && (*val < 7)) {
		*count = *count + 1;
	} else if (*val == 10) {
		*count = *count - 1;
	}
	printf("Current count: %i\n", *count);
}
		
void assign_values(char card_name[], int *val)
{
	switch(card_name[0]) {
	case 'K':
	case 'Q':
	case 'J':
		*val = 10;
		break;
	case 'A':
		*val = 11;
		break;
	default:
		*val = atoi(card_name);
		if ((*val < 2) || (*val > 10)) {
			puts("I don't understand that value!");
		}
	}
	check_values(&value, &count);
	
}

int main()
{
	while (card_name[0] != 'X') {
		puts(prompt_for_user);
		fgets(card_name, 3, stdin);
		printf("The card name is %s\n", card_name);
		assign_values(card_name, &value);
	}
	return 0;
}
