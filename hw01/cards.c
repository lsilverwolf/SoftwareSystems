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

/* This function decides whether or not to increment or decrement the counter

	val: the card value 
   		value is the number on the card, 10 for face cards and 11 for ace
	count: the counter for how good it is to take a hit
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
	
/* This function assigns values to the face cards and others based on user input

	card_name: the name of the card truncated to 2 characters
	val: the value of the card to be set in this function
*/	
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

/* Main asks the user to input a card and then calls assign_values
*/
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
