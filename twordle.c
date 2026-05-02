//Author: Ally Sisonickk
//Date: 4/27/26
//Purpose: Project 10

#include <stdio.h>
#include <stdbool.h>

#define WORD_LEN 5
#define MAX_GUESSES 6

void readrandomWord(char word[]);
void getGuess(char guess[]);
bool isvalidGuess(char guess[]);
void makeLowercase(char word[]);
void saveGuess(char guesses[][WORD_LEN + 1], char guess[], int guessNUM);
void displayGuesses(char guesses[][WORD_LEN + 1], int numGuesses, char mystery[]);
void displayoneGuess(char guess[], char mystery[]);
bool isWinner(char guess[], char mystery[]);
void displayWin(char guess[], int guessNUM);
void displayLoss(void);

int main(void) {
	char mystery[WORD_LEN + 1];
	char guess[WORD_LEN + 1];
	char guesses[MAX_GUESSES][WORD_LEN + 1];
	
	int guessNUM = 0;
	bool won = false;
	
	readrandomWord(mystery);
	makeLowercase(mystery);
	
	while (guessNUM < MAX_GUESSES && !won) {
		if (guessNUM == MAX_GUESSES - 1) {
			printf("FINAL GUESS: "); 
		}
		else {
			printf("GUESS %d! Enter your guess: ", guessNUM + 1);
		}
		
		getGuess(guess);
		makeLowercase(guess);
		
		while (!isvalidGuess(guess)) {
			printf("Invalid guess. Enter a 5 letter word: ");
			getGuess(guess);
			makeLowercase(guess); }
		saveGuess(guesses, guess, guessNUM);
		guessNUM++;
		
		printf("=====================================\n");
		
		if (isWinner(guess, mystery)) {
			displayWin(guess, guessNUM);
			won = true;
		}
		else {
			displayGuesses(guesses, guessNUM, mystery);
		}
	}
	
	if (!won) {
		displayLoss();
	}
	
	return 0;
}
		
void readrandomWord(char word[]) {
	FILE *file = fopen("mystery.txt", "r");
	if (file == NULL) {
		printf("Could not open mystery.txt\n");
		word[0] = '\0';
		return;
	}
	
	fscanf(file, "%5s", word);
	word[WORD_LEN] = '\0';
	fclose(file);
}

void getGuess(char guess[]) {
	scanf("%5s", guess);
	guess[WORD_LEN] = '\0';
}

bool isvalidGuess(char guess[]) {
	int i = 0;
	while (guess[i] != '\0') {
		if (!((guess[i] >= 'a' && guess[i] <= 'z') ||
			(guess[i] >= 'A' && guess[i] <= 'Z'))) {
			return false;
		}
		i++;
	}
	return i == WORD_LEN;
}

void makeLowercase(char word[]) {
	int i;
	for (i = 0; word[i] != '\0'; i++) {
		if (word[i] >= 'A' && word[i] <= 'Z') {
			word[i] = word[i] + 32;
		}
	}
}

void saveGuess(char guesses[][WORD_LEN + 1], char guess[], int guessNUM) {
	int i;
	for (i = 0; i < WORD_LEN; i++) {
		guesses[guessNUM][i] = guess[i];
	}
	
	guesses[guessNUM][WORD_LEN] = '\0';
}

void displayGuesses(char guesses[][WORD_LEN + 1], int numGuesses, char mystery[]) {
	int i;
	for (i = 0; i < numGuesses; i++) {
		displayoneGuess(guesses[i], mystery);
	}
}

void displayoneGuess(char guess[], char mystery[]) {
	int i, j;
	bool usedMystery[WORD_LEN] = {false, false, false, false, false};
	char display[WORD_LEN + 1];
	char arrows[WORD_LEN + 1];
	
	for (i = 0; i < WORD_LEN; i++) {
		display[i] = guess[i];
		arrows[i] = ' ';
	}
	
	display[WORD_LEN] = '\0';
	arrows[WORD_LEN] = '\0';
	
	for (i = 0; i < WORD_LEN; i++) {
		if (guess[i] == mystery[i]) {
			display[i] = guess[i] - 32;
			usedMystery[i] = true;
		}
	}
	for (i = 0; i < WORD_LEN; i++) {
		if (guess[i] != mystery[i]) {
			for (j = 0; j < WORD_LEN; j++) {
				if(!usedMystery[j] && guess[i] == mystery[j]) {
					arrows[i] = '^';
					usedMystery[j] = true;
					break;
				}
			}
		}
	}
	
	printf("%s\n", display);
	printf("%s\n", arrows);
}

bool isWinner(char guess[], char mystery[]) {
	int i;
	for (i = 0; i < WORD_LEN; i++) {
		if (guess[i] != mystery[i]) {
			return false;
		}
	}
	
	return true;
}

void displayWin(char guess[], int guessNUM) {
	int i;
	printf("            ");
	
	for(i = 0; i < WORD_LEN; i++) {
		if (guess[i] >= 'a' && guess[i] <= 'z') {
			printf("%c", guess[i] - 32);
		}
		else {
			printf("%c", guess[i]);
		}
	}
	printf("\n");
	printf("      You won in %d guesses\n", guessNUM);
	printf("            GOATED!\n");
}

void displayLoss(void) {
	printf("You lost, better luck next time!\n");
}
