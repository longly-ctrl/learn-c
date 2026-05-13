#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "dbg.h"

#define MAX_DATA 100

typedef enum EyeColor {
	BLUE_EYES, GREEN_EYES, BROWN_EYES,
	BLACK_EYES, OTHER_EYES
} EyeColor;

const char *EYE_COLOR_NAMES[] = {
	"Blue", "Green", "Brown", "Black", "Other"
};

typedef struct Person {
	int age;
	char first_name[MAX_DATA];
	char last_name[MAX_DATA];
	EyeColor eyes;
	float income;
} Person;

int strip_and_check_name(char *name)
{
	int i = 0;
	int len = 0;

	check(name != NULL, "Name is NULL.");

	len = strlen(name);
	check(len > 0, "Name is empty.");

	if(name[len - 1] == '\n') {
		name[len - 1] = '\0';
		len--;
	}

	check(len > 0, "Name is empty.");

	for(i = 0; i < len; i++) {
		check(!isspace((unsigned char)name[i]),
				"Name cannot contain whitespace.");
	}

	return 0;

error:
	return -1;
}

int main(int argc, char *argv[])
{
	Person you = {.age = 0};
	int i = 0;
	char *in = NULL;

	printf("What's your First Name? ");
	in = fgets(you.first_name, MAX_DATA-1, stdin);
	check(in != NULL, "Failed to read first name.");
	check(strip_and_check_name(you.first_name) == 0, "Invalid first name.");

	printf("What's your Last Name? ");
	in = fgets(you.last_name, MAX_DATA-1, stdin);
	check(in != NULL, "Failed to read last name.");
	check(strip_and_check_name(you.last_name) == 0, "Invalid last name.");

	printf("How old are you?");
	int rc = fscanf(stdin, "%d", &you.age);
	check(rc > 0, "You have to enter a unmber.");

	printf("What color are your eyes:\n");
	for(i = 0; i <= OTHER_EYES; i++) {
		printf("%d) %s\n", i+1, EYE_COLOR_NAMES[i]);
	}
	printf("> ");
	
	int eyes = -1;
	rc = fscanf(stdin, "%d", &eyes);
	check(rc > 0, "You have to enter a number.");

	you.eyes = eyes - 1;
	check(you.eyes <= OTHER_EYES && you.eyes >= 0, "Do it right, that's not an option.");

	printf("How much do you make an hour? ");
	rc = fscanf(stdin, "%f", &you.income);
	check(rc > 0, "Enter a floating point number.");

	printf("-----RESULTS-----\n");

	printf("First Name: %s\n", you.first_name);
	printf("Last Name: %s\n", you.last_name);
	printf("Age: %d\n", you.age);
	printf("Eyes: %s\n", EYE_COLOR_NAMES[you.eyes]);
	printf("Income: %f\n", you.income);

	return 0;
error:
	return -1;
}
