#include <stdio.h>
#include <stdlib.h>

#define N 15

int chessboard[N + 1][N + 1] = {0};

int whoseTrun = 0;

void initGame(void);
void printChessboard(void);
void playChess(void);
int judge(int, int);

void initGame(void) {
	char c;

	printf("please input y to enter game: ");
	c = getchar();

	if('y' != c && 'Y' != c) exit(0);

	system("clear");

	printChessboard();
}

void printChessboard(void) {
	int i, j;
	for(i = 0; i <= N; i++) {
		for(j = 0; j <= N; j++) {
			if(i == 0) {
				printf("%3d", j);
			} else if(j == 0) {
				printf("%3d\n", i);
			} else if(chessboard[i][j] == 1) {
				printf("  ●");
			} else if(chessboard[i][j] == 2) {
				printf("  ○");
			} else {
				printf("  *");
			}
		}
		printf("\n");
	}
}

void playChess(void) {
	int i, j, winner;
	if(whoseTrun % 2 == 1) {
		printf("Player 1, please input chess position: ");
		scanf("%d %d", &i, &j);
		
		while(chessboard[i][j] != 0) {
			printf("This position has been taken, please input another one: ");
			scanf("%d %d", &i, &j);
		}

		chessboard[i][j] = 1;
	} else {
		printf("Player 2, pleaes input chess position: ");
		scanf("%d %d", &i, &j);

		while(chessboard[i][j] != 0) {
			printf("This position has been taken, please input another one: ");
			scanf("%d %d", &i, &j);
		}

		chessboard[i][j] = 2;
	}

	system("clear");

	printChessboard();

	if(judge(i, j)) {
		if(1 == whoseTrun % 2) {
			printf("Player 1 wins! \n");
			exit(0);
		} else {
			printf("Player 2 wins! \n");
			exit(0);
		}
	}
}

int judge(int x, int y) {
	int i, j;
	int t =2 - whoseTrun % 2;

	for(i = x - 4, j = y; i <=x; i++) {
		if(i >= 1 && i <= N - 4 && t == chessboard[i][j] && t == chessboard[i + 1][j]
			&& t == chessboard[i + 2][j] && t == chessboard[i + 3][j]
			&& t == chessboard[i + 4][j]) return 1;
	}

	for(i = x, j = y - 4; j <= y; j++) {
		if(j >= 1 && i <= N - 4 && t == chessboard[i][j] && t == chessboard[i][j + 1]
			&& t == chessboard[i][j + 2] && t == chessboard[i][j + 3]
			&& t == chessboard[i][j + 4]) return 1;
	}

	for(i = x - 4, j = y - 4; i <= x, j <= y; i++, j++) {
		if(i >= 1 && i <= N - 4 && j >= 1 && j <= N -4 && t == chessboard[i][j] && t == chessboard[i + 1][j + 1]
			&& t == chessboard[i + 2][j + 2] && t == chessboard[i + 3][j + 3]
			&& t == chessboard[i + 4][j + 4]) return 1;
	}

	for(i = x + 4, j = y - 4; i >= 1, j <= y; i--, j++) {
		if(i >= 1 && i <= N -4 && j >= 1 && j <= N - 4 && t == chessboard[i][j] && t == chessboard[i - 1][j + 1]
			&& t == chessboard[i - 2][j + 2] && t == chessboard[i - 3][j + 3]
			&& t == chessboard[i - 4][j + 4]) return 1; 
	}
	
	return 0;
}

int main(void) {
	initGame();

	while(1) {
		whoseTrun++;
		playChess();
	}

	return 0;
}