#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define BOARD_SIZE 4
#define KEY_A 97
#define KEY_D 100
#define KEY_W 119
#define KEY_S 115

void Display_board();
void initBoard();
void addNumber();
void moveValues();
void moveDown();
void moveUp();
void moveLeft();
void moveRight();
void check_win();

int board[BOARD_SIZE][BOARD_SIZE] = { 0 }; //Empty board
int score = 0, end = 0, available = 1;

void main(void)
{
	// Initialise graphic window
	int gd = DETECT, gm = 0;
	initgraph(&gd, &gm, "");
	int i = 0;

	printf("Use the keys W,S,A and D to move the tiles Up, Down, Left and Right \n");

	initBoard();
	while (end == 0 && available == 1)      //while a move is possible and while there is no 2048-tile
	{
		setactivepage(i % 2);
		clearviewport();
		Display_board();
		setvisualpage(i % 2);
		moveValues();
		check_win();
		i += 1;
		delay(10);
	}
	clearviewport();
	Display_board(); //Display final board

	if (available == 0)
	{
		printf("You lost !! your score is %d ", score);
	}
	else if (end == 1)
	{
		printf("You won !! your score is %d ", score);
	}
	
	// wait for key pressed
	readkey();

	// close graphic
	closegraph();

}

void Display_board()
{
	// Draw the board
	setcolor(WHITE);
	rectangle(170, 80, 490, 400); //square 320x320
	line(170, 320, 490, 320);       //3 horizontal lines
	line(170, 240, 490, 240);
	line(170, 160, 490, 160);
	line(250, 400, 250, 80);      //3 vertical lines
	line(330, 400, 330, 80);
	line(410, 400, 410, 80);

	//PRINT NUMBERS
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			switch (board[j][i])
			{
			case 2:
				setfillstyle(SOLID_FILL, BROWN);
				floodfill(180+80*i, 90+80*j, WHITE);
				setcolor(WHITE);
				line(170 + 15 + 80 * i, 80 + 15 + 80 * j, 170 + 65 + 80 * i, 80 + 15 + 80 * j);
				line(170 + 15 + 80 * i, 80 + 40 + 80 * j, 170 + 65 + 80 * i, 80 + 40 + 80 * j);
				line(170 + 65 + 80 * i, 80 + 15 + 80 * j, 170 + 65 + 80 * i, 80 + 40 + 80 * j);
				line(170 + 15 + 80 * i, 80 + 40 + 80 * j, 170 + 15 + 80 * i, 80 + 65 + 80 * j);
				line(170 + 15 + 80 * i, 80 + 65 + 80 * j, 170 + 65 + 80 * i, 80 + 65 + 80 * j);
				break;
			case 4:
				setfillstyle(SOLID_FILL, RED);
				floodfill(180 + 80 * i, 90 + 80 * j, WHITE);
				setcolor(WHITE);
				line(170 + 65 + 80 * i, 80 + 15 + 80 * j, 170 + 65 + 80 * i, 80 + 65 + 80 * j);
				line(170 + 15 + 80 * i, 80 + 40 + 80 * j, 170 + 65 + 80 * i, 80 + 40 + 80 * j);
				line(170 + 15 + 80 * i, 80 + 15 + 80 * j, 170 + 15 + 80 * i, 80 + 40 + 80 * j);
				break;
			case 8:
				setfillstyle(SOLID_FILL, BLUE);
				floodfill(180 + 80 * i, 90 + 80 * j, WHITE);
				setcolor(WHITE);
				line(170 + 15 + 80 * i, 80 + 15 + 80 * j, 170 + 15 + 80 * i, 80 + 65 + 80 * j);
				line(170 + 15 + 80 * i, 80 + 15 + 80 * j, 170 + 65 + 80 * i, 80 + 15 + 80 * j);
				line(170 + 15 + 80 * i, 80 + 40 + 80 * j, 170 + 65 + 80 * i, 80 + 40 + 80 * j);
				line(170 + 15 + 80 * i, 80 + 65 + 80 * j, 170 + 65 + 80 * i, 80 + 65 + 80 * j);
				line(170 + 65 + 80 * i, 80 + 15 + 80 * j, 170 + 65 + 80 * i, 80 + 65 + 80 * j);
				break;
			case 16:
				setfillstyle(SOLID_FILL, GREEN);
				floodfill(180 + 80 * i, 90 + 80 * j, WHITE);
				setcolor(WHITE);
				line(170 + 20 + 80 * i, 80 + 15 + 80 * j, 170 + 20 + 80 * i, 80 + 65 + 80 * j);
				line(170 + 35 + 80 * i, 80 + 15 + 80 * j, 170 + 35 + 80 * i, 80 + 65 + 80 * j);
				line(170 + 35 + 80 * i, 80 + 15 + 80 * j, 170 + 60 + 80 * i, 80 + 15 + 80 * j);
				line(170 + 35 + 80 * i, 80 + 40 + 80 * j, 170 + 60 + 80 * i, 80 + 40 + 80 * j);
				line(170 + 35 + 80 * i, 80 + 65 + 80 * j, 170 + 60 + 80 * i, 80 + 65 + 80 * j);
				line(170 + 60 + 80 * i, 80 + 40 + 80 * j, 170 + 60 + 80 * i, 80 + 65 + 80 * j);
				break;
			case 32:
				setfillstyle(SOLID_FILL, DARKGRAY);
				floodfill(180 + 80 * i, 90 + 80 * j, WHITE);
				setcolor(WHITE);
				line(170 + 35 + 80 * i, 80 + 15 + 80 * j, 170 + 35 + 80 * i, 80 + 65 + 80 * j);
				line(170 + 15 + 80 * i, 80 + 15 + 80 * j, 170 + 35 + 80 * i, 80 + 15 + 80 * j);
				line(170 + 15 + 80 * i, 80 + 40 + 80 * j, 170 + 35 + 80 * i, 80 + 40 + 80 * j);
				line(170 + 15 + 80 * i, 80 + 65 + 80 * j, 170 + 35 + 80 * i, 80 + 65 + 80 * j);
				
				line(170 + 45 + 80 * i, 80 + 15 + 80 * j, 170 + 65 + 80 * i, 80 + 15 + 80 * j);
				line(170 + 45 + 80 * i, 80 + 40 + 80 * j, 170 + 65 + 80 * i, 80 + 40 + 80 * j);
				line(170 + 45 + 80 * i, 80 + 65 + 80 * j, 170 + 65 + 80 * i, 80 + 65 + 80 * j);
				line(170 + 65 + 80 * i, 80 + 15 + 80 * j, 170 + 65 + 80 * i, 80 + 40 + 80 * j);
				line(170 + 45 + 80 * i, 80 + 40 + 80 * j, 170 + 45 + 80 * i, 80 + 65 + 80 * j);
				break;
			case 64:
				setfillstyle(SOLID_FILL, MAGENTA);
				floodfill(180 + 80 * i, 90 + 80 * j, WHITE);
				setcolor(WHITE);
				line(170 + 15 + 80 * i, 80 + 15 + 80 * j, 170 + 15 + 80 * i, 80 + 65 + 80 * j);
				line(170 + 15 + 80 * i, 80 + 15 + 80 * j, 170 + 35 + 80 * i, 80 + 15 + 80 * j);
				line(170 + 15 + 80 * i, 80 + 40 + 80 * j, 170 + 35 + 80 * i, 80 + 40 + 80 * j);
				line(170 + 15 + 80 * i, 80 + 65 + 80 * j, 170 + 35 + 80 * i, 80 + 65 + 80 * j);
				line(170 + 35 + 80 * i, 80 + 40 + 80 * j, 170 + 35 + 80 * i, 80 + 65 + 80 * j);

				line(170 + 45 + 80 * i, 80 + 15 + 80 * j, 170 + 45 + 80 * i, 80 + 40 + 80 * j);
				line(170 + 45 + 80 * i, 80 + 40 + 80 * j, 170 + 65 + 80 * i, 80 + 40 + 80 * j);
				line(170 + 65 + 80 * i, 80 + 15 + 80 * j, 170 + 65 + 80 * i, 80 + 65 + 80 * j);
				break;
			case 128:
				setfillstyle(SOLID_FILL, LIGHTBLUE);
				floodfill(180 + 80 * i, 90 + 80 * j, WHITE);
				setcolor(WHITE);
				line(170 + 10 + 80 * i, 80 + 15 + 80 * j, 170 + 10 + 80 * i, 80 + 65 + 80 * j);
				
				line(170 + 20 + 80 * i, 80 + 15 + 80 * j, 170 + 40 + 80 * i, 80 + 15 + 80 * j);
				line(170 + 20 + 80 * i, 80 + 40 + 80 * j, 170 + 40 + 80 * i, 80 + 40 + 80 * j);
				line(170 + 20 + 80 * i, 80 + 65 + 80 * j, 170 + 40 + 80 * i, 80 + 65 + 80 * j);
				line(170 + 40 + 80 * i, 80 + 15 + 80 * j, 170 + 40 + 80 * i, 80 + 40 + 80 * j);
				line(170 + 20 + 80 * i, 80 + 40 + 80 * j, 170 + 20 + 80 * i, 80 + 65 + 80 * j);

				line(170 + 50 + 80 * i, 80 + 15 + 80 * j, 170 + 70 + 80 * i, 80 + 15 + 80 * j);
				line(170 + 50 + 80 * i, 80 + 40 + 80 * j, 170 + 70 + 80 * i, 80 + 40 + 80 * j);
				line(170 + 50 + 80 * i, 80 + 65 + 80 * j, 170 + 70 + 80 * i, 80 + 65 + 80 * j);
				line(170 + 50 + 80 * i, 80 + 15 + 80 * j, 170 + 50 + 80 * i, 80 + 65 + 80 * j);
				line(170 + 70 + 80 * i, 80 + 15 + 80 * j, 170 + 70 + 80 * i, 80 + 65 + 80 * j);
				break;
			case 256:
				setfillstyle(SOLID_FILL, CYAN);
				floodfill(180 + 80 * i, 90 + 80 * j, WHITE);
				setcolor(WHITE);
				line(170 + 10 + 80 * i, 80 + 15 + 80 * j, 170 + 25 + 80 * i, 80 + 15 + 80 * j);
				line(170 + 10 + 80 * i, 80 + 40 + 80 * j, 170 + 25 + 80 * i, 80 + 40 + 80 * j);
				line(170 + 10 + 80 * i, 80 + 65 + 80 * j, 170 + 25 + 80 * i, 80 + 65 + 80 * j);
				line(170 + 25 + 80 * i, 80 + 15 + 80 * j, 170 + 25 + 80 * i, 80 + 40 + 80 * j);
				line(170 + 10 + 80 * i, 80 + 40 + 80 * j, 170 + 10 + 80 * i, 80 + 65 + 80 * j);

				line(170 + 33 + 80 * i, 80 + 15 + 80 * j, 170 + 47 + 80 * i, 80 + 15 + 80 * j);
				line(170 + 33 + 80 * i, 80 + 40 + 80 * j, 170 + 47 + 80 * i, 80 + 40 + 80 * j);
				line(170 + 33 + 80 * i, 80 + 65 + 80 * j, 170 + 47 + 80 * i, 80 + 65 + 80 * j);
				line(170 + 33 + 80 * i, 80 + 15 + 80 * j, 170 + 33 + 80 * i, 80 + 40 + 80 * j);
				line(170 + 47 + 80 * i, 80 + 40 + 80 * j, 170 + 47 + 80 * i, 80 + 65 + 80 * j);

				line(170 + 55 + 80 * i, 80 + 15 + 80 * j, 170 + 70 + 80 * i, 80 + 15 + 80 * j);
				line(170 + 55 + 80 * i, 80 + 40 + 80 * j, 170 + 70 + 80 * i, 80 + 40 + 80 * j);
				line(170 + 55 + 80 * i, 80 + 65 + 80 * j, 170 + 70 + 80 * i, 80 + 65 + 80 * j);
				line(170 + 70 + 80 * i, 80 + 40 + 80 * j, 170 + 70 + 80 * i, 80 + 65 + 80 * j);
				line(170 + 55 + 80 * i, 80 + 15 + 80 * j, 170 + 55 + 80 * i, 80 + 65 + 80 * j);
				break;
			case 512:
				setfillstyle(SOLID_FILL, _LIGHTMAGENTA);
				floodfill(180 + 80 * i, 90 + 80 * j, WHITE);
				setcolor(WHITE);
				line(170 + 10 + 80 * i, 80 + 15 + 80 * j, 170 + 30 + 80 * i, 80 + 15 + 80 * j);
				line(170 + 10 + 80 * i, 80 + 40 + 80 * j, 170 + 30 + 80 * i, 80 + 40 + 80 * j);
				line(170 + 10 + 80 * i, 80 + 65 + 80 * j, 170 + 30 + 80 * i, 80 + 65 + 80 * j);
				line(170 + 10 + 80 * i, 80 + 15 + 80 * j, 170 + 10 + 80 * i, 80 + 40 + 80 * j);
				line(170 + 30 + 80 * i, 80 + 40 + 80 * j, 170 + 30 + 80 * i, 80 + 65 + 80 * j);

				line(170 + 40 + 80 * i, 80 + 15 + 80 * j, 170 + 40 + 80 * i, 80 + 65 + 80 * j);

				line(170 + 50 + 80 * i, 80 + 15 + 80 * j, 170 + 70 + 80 * i, 80 + 15 + 80 * j);
				line(170 + 50 + 80 * i, 80 + 40 + 80 * j, 170 + 70 + 80 * i, 80 + 40 + 80 * j);
				line(170 + 50 + 80 * i, 80 + 65 + 80 * j, 170 + 70 + 80 * i, 80 + 65 + 80 * j);
				line(170 + 70 + 80 * i, 80 + 15 + 80 * j, 170 + 70 + 80 * i, 80 + 40 + 80 * j);
				line(170 + 50 + 80 * i, 80 + 40 + 80 * j, 170 + 50 + 80 * i, 80 + 65 + 80 * j);
				break;
			case 1024:
				setfillstyle(SOLID_FILL, WHITE);
				floodfill(180 + 80 * i, 90 + 80 * j, WHITE);
				setcolor(BLACK);

				line(170 + 10 + 80 * i, 80 + 20 + 80 * j, 170 + 10 + 80 * i, 80 + 60 + 80 * j);

				line(170 + 15 + 80 * i, 80 + 20 + 80 * j, 170 + 15 + 80 * i, 80 + 60 + 80 * j);
				line(170 + 30 + 80 * i, 80 + 20 + 80 * j, 170 + 30 + 80 * i, 80 + 60 + 80 * j);
				line(170 + 15 + 80 * i, 80 + 20 + 80 * j, 170 + 30 + 80 * i, 80 + 20 + 80 * j);
				line(170 + 15 + 80 * i, 80 + 60 + 80 * j, 170 + 30 + 80 * i, 80 + 60 + 80 * j);

				line(170 + 35 + 80 * i, 80 + 20 + 80 * j, 170 + 50 + 80 * i, 80 + 20 + 80 * j);
				line(170 + 35 + 80 * i, 80 + 40 + 80 * j, 170 + 50 + 80 * i, 80 + 40 + 80 * j);
				line(170 + 35 + 80 * i, 80 + 60 + 80 * j, 170 + 50 + 80 * i, 80 + 60 + 80 * j);
				line(170 + 50 + 80 * i, 80 + 20 + 80 * j, 170 + 50 + 80 * i, 80 + 40 + 80 * j);
				line(170 + 35 + 80 * i, 80 + 40 + 80 * j, 170 + 35 + 80 * i, 80 + 60 + 80 * j);

				line(170 + 55 + 80 * i, 80 + 20 + 80 * j, 170 + 55 + 80 * i, 80 + 40 + 80 * j);
				line(170 + 55 + 80 * i, 80 + 40 + 80 * j, 170 + 70 + 80 * i, 80 + 40 + 80 * j);
				line(170 + 70 + 80 * i, 80 + 20 + 80 * j, 170 + 70 + 80 * i, 80 + 60 + 80 * j);
				break;
			case 2048:
				setfillstyle(SOLID_FILL, YELLOW);
				floodfill(180 + 80 * i, 90 + 80 * j, WHITE);
				setcolor(BLACK);

				line(170 + 3 + 80 * i, 80 + 20 + 80 * j, 170 + 17 + 80 * i, 80 + 20 + 80 * j);
				line(170 + 3 + 80 * i, 80 + 40 + 80 * j, 170 + 17 + 80 * i, 80 + 40 + 80 * j);
				line(170 + 3 + 80 * i, 80 + 60 + 80 * j, 170 + 17 + 80 * i, 80 + 60 + 80 * j);
				line(170 + 17 + 80 * i, 80 + 20 + 80 * j, 170 + 17 + 80 * i, 80 + 40 + 80 * j);
				line(170 + 3 + 80 * i, 80 + 40 + 80 * j, 170 + 3 + 80 * i, 80 + 60 + 80 * j);

				line(170 + 23 + 80 * i, 80 + 20 + 80 * j, 170 + 23 + 80 * i, 80 + 60 + 80 * j);
				line(170 + 37 + 80 * i, 80 + 20 + 80 * j, 170 + 37 + 80 * i, 80 + 60 + 80 * j);
				line(170 + 23 + 80 * i, 80 + 20 + 80 * j, 170 + 37 + 80 * i, 80 + 20 + 80 * j);
				line(170 + 23 + 80 * i, 80 + 60 + 80 * j, 170 + 37 + 80 * i, 80 + 60 + 80 * j);

				line(170 + 43 + 80 * i, 80 + 20 + 80 * j, 170 + 43 + 80 * i, 80 + 40 + 80 * j);
				line(170 + 43 + 80 * i, 80 + 40 + 80 * j, 170 + 57 + 80 * i, 80 + 40 + 80 * j);
				line(170 + 57 + 80 * i, 80 + 20 + 80 * j, 170 + 57 + 80 * i, 80 + 60 + 80 * j);

				line(170 + 63 + 80 * i, 80 + 20 + 80 * j, 170 + 77 + 80 * i, 80 + 20 + 80 * j);
				line(170 + 63 + 80 * i, 80 + 40 + 80 * j, 170 + 77 + 80 * i, 80 + 40 + 80 * j);
				line(170 + 63 + 80 * i, 80 + 60 + 80 * j, 170 + 77 + 80 * i, 80 + 60 + 80 * j);
				line(170 + 63 + 80 * i, 80 + 20 + 80 * j, 170 + 63 + 80 * i, 80 + 60 + 80 * j);
				line(170 + 77 + 80 * i, 80 + 20 + 80 * j, 170 + 77 + 80 * i, 80 + 60 + 80 * j);
				break;
			}
		}
	}
}

void initBoard()         //Board with a 2 and a 4 (random positions)
{
	int i1=0, j1=0, i2=0, j2=0;

	srand(time(NULL)); //init rand()
	i1 = rand() % BOARD_SIZE; //i random index between 0 and 3
	j1 = rand() % BOARD_SIZE; //j random index between 0 and 3
	
	board[i1][j1] = 2;         //2 appears on the board at a random position

	i2 = rand() % BOARD_SIZE; //i random index between 0 and 3
	j2 = rand() % BOARD_SIZE; //j random index between 0 and 3

	while (i2==i1 || j2==j1) {  //we want different position for the 2 random numbers
		i2 = rand() % BOARD_SIZE; //i random index between 0 and 3
		j2 = rand() % BOARD_SIZE; //j random index between 0 and 3
	}
	board[i2][j2] = 4;         //4 appears on the board at a random position
}

void addNumber()         //add a 2 or a 4 to the board
{
	int i_temp = 0, j_temp = 0;
	int chance;

	srand(time(NULL)); //init rand()
	i_temp = rand() % BOARD_SIZE; //i random
	j_temp = rand() % BOARD_SIZE; //j random

	while (board[i_temp][j_temp] != 0)     //the number must appear on a empty spot
	{
		i_temp = rand() % BOARD_SIZE; //i random
		j_temp = rand() % BOARD_SIZE; //j random
	}

	chance = rand() % 100;
	if (chance <= 80)
	{
		board[i_temp][j_temp] = 2;         //2 appears on the board at a random position (80%)
	}
	else
	{
		board[i_temp][j_temp] = 4;         //4 appears on the board at a random position (20%)
	}
}
	

void moveValues()
{
	int place = 0;
	int copy_board[BOARD_SIZE][BOARD_SIZE] = { 0 };  //create a copy
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			copy_board[i][j] = board[i][j];
		}
	}

	if (_kbhit)
	{
		int ch = _getch();
		switch (ch)
		{
		case KEY_S:
			moveDown();
			break;
		case KEY_W:
			moveUp();
			break;
		case KEY_A:
			moveLeft();
			break;
		case KEY_D:
			moveRight();
			break;
		default:
			/*DO NOTHING */
			return;
		}
	}

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (board[i][j] == 0 && copy_board[i][j]!=board[i][j])  //we want a random number on an empty spot and only if the board changed
			{
				place = 1;
				available = 1;
			}
		}
	}
	if (place == 1)   //if there is an empty spot
	{
		addNumber();
	}

	int condition = 0;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (board[i][j] != 0) //the board is changed and full, a move is possible/available
			{
				if (copy_board[i][j] != board[i][j])
				{
					condition = 1;
				}
			}
			else
			{
				condition = 1;  //the case when the board is not full, so a move is possible
			}
		}
	}
	
	if (condition == 0)    //if the entire board is full and no move is possible
	{
		available = 0;
	}
}

void moveUp()       //Third-party code: https://github.com/munish-02/2048/blob/master/2048.CPP
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (board[i][j] == 0)
				continue;
			for (int k = i + 1; k < BOARD_SIZE; k++)
			{
				if (board[i][j] == board[k][j])  //if two spots are equal, a new tile is created with the sum of the two numbers
				{
					board[i][j] *= 2;
					board[k][j] = 0;
					score += board[i][j];
					break;
				}
				if (board[k][j] != 0)
					break;
			}

		}
	}
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (board[i][j] == 0)       //if there is an empty spot, the tile is moved
			{
				for (int k = i + 1; k < BOARD_SIZE; k++)
				{
					if (board[k][j] != 0)
					{
						board[i][j] = board[k][j];
						board[k][j] = 0;
						break;
					}
				}
			}
		}
	}

}

void moveDown()        //Third-party code: https://github.com/munish-02/2048/blob/master/2048.CPP
{
	for (int i = 3; i >= 0; i--)
	{
		for (int j = 3; j >= 0; j--)
		{
			if (board[i][j] == 0)
				continue;
			for (int k = i - 1; k >= 0; k--)
			{
				if (board[i][j] == board[k][j])   //if two spots are equal, a new tile is created with the sum of the two numbers
				{
					board[i][j] *= 2;
					board[k][j] = 0;
					score += board[i][j];
					break;
				}
				if (board[k][j] != 0)
					break;
			}

		}
	}
	for (int i = 3; i >= 0; i--)
	{
		for (int j = 3; j >= 0; j--)
		{
			if (board[i][j] == 0)    //if there is an empty spot, the tile is moved
			{
				for (int k = i - 1; k >= 0; k--)
				{
					if (board[k][j] != 0)
					{
						board[i][j] = board[k][j];
						board[k][j] = 0;
						break;
					}
				}
			}
		}
	}

}



void moveLeft()        //Third-party code: https://github.com/munish-02/2048/blob/master/2048.CPP
{
	
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (board[i][j] == 0)
				continue;
			for (int k = j + 1; k < 4; k++)
			{
				if (board[i][j] == board[i][k])  //if two spots are equal, a new tile is created with the sum of the two numbers
				{
					board[i][j] *= 2;
					board[i][k] = 0;
					score += board[i][j];
					break;
				}
				if (board[i][k] != 0)
					break;
			}

		}
	}
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (board[i][j] == 0)      //if there is an empty spot, the tile is moved
			{
				for (int k = j + 1; k < BOARD_SIZE; k++)
				{
					if (board[i][k] != 0)
					{
						board[i][j] = board[i][k];
						board[i][k] = 0;
						break;
					}
				}
			}
		}
	}

}

void moveRight()            //Third-party code: https://github.com/munish-02/2048/blob/master/2048.CPP
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 3; j >= 0; j--)
		{
			if (board[i][j] == 0)
				continue;
			for (int k = j - 1; k >= 0; k--)
			{
				if (board[i][j] == board[i][k])  //if two spots are equal, a new tile is created with the sum of the two numbers
				{
					board[i][j] *= 2;
					board[i][k] = 0;
					score += board[i][j];
					break;
				}
				if (board[i][k] != 0)
					break;
			}

		}
	}
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 3; j >= 0; j--)
		{
			if (board[i][j] == 0)     //if there is an empty spot, the tile is moved
			{
				for (int k = j - 1; k >= 0; k--)
				{
					if (board[i][k] != 0)
					{
						board[i][j] = board[i][k];
						board[i][k] = 0;
						break;
					}
				}
			}
		}
	}

}


void check_win()
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (board[i][j] == 2048)   //condition to win the game
			{
				end = 1;
			}
		}
	}
}

