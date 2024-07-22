#include <iostream> 
#include <conio.h> 
#include <windows.h>
using namespace std; 

const int width = 80; // Game area width
const int height = 20; // Game area height

int snakeHeadCordX, snakeHeadCordY; // Snake's head coordinate X-axis and Y-axis
int foodCordX, foodCordY; // Food coordinate X-axis and Y-axis
int playerScore; // Player's score
int snakeTailLen; // Snake's tail length
int snakeTailX[100], snakeTailY[100]; 
enum snakesDirection { STOP = 0, LEFT, RIGHT, UP, DOWN }; 
snakesDirection sDir; 
bool isGameOver; // To check is gameover or not

/*-----------------------Initialization of all variables-----------------------------*/
void GameInit() 
{ 
	isGameOver = false; 
	sDir = STOP; 
	snakeHeadCordX = width / 2; 
	snakeHeadCordY = height / 2; 
	foodCordX = rand() % width; 
	foodCordY = rand() % height; 
	playerScore = 0; 
} 

/*------------------------Game render function--------------------------------*/
void GameRender(string playerName) 
{ 
	system("cls"); // command to clear console

    // Loop to display upper wall of game area
	for (int i = 0; i < width + 2; i++) 
		cout << "-"; 
	cout << endl; 

    // Loop to display side walls of game area
	for (int i = 0; i < height; i++) { 
		for (int j = 0; j <= width; j++) { 
			if (j == 0 || j == width) 
				cout << "|"; 
			
			// display head of snake
			if (i == snakeHeadCordY && j == snakeHeadCordX) 
				cout << "0"; 

			// display food
			else if (i == foodCordY && j == foodCordX) 
				cout << "#"; 

			// display snake's tail
			else { 
				bool prTail = false; 
				for (int k = 0; k < snakeTailLen; k++) { 
					if (snakeTailX[k] == j 
						&& snakeTailY[k] == i) { 
						cout << "0"; 
						prTail = true; 
					} 
				} 
				if (!prTail) 
					cout << " "; 
			} 
		} 
		cout << endl; 
	} 

	// Display bottom wall of game area
	for (int i = 0; i < width + 2; i++) 
		cout << "-"; 
	cout << endl; 

	// Display player's score
	cout << playerName << "'s Score: " << playerScore << "\t\tPress 'x' to quit."; 
} 

/*------------------------Game Update function---------------------------*/
void UpdateGame() 
{ 
	int prevX = snakeTailX[0]; 
	int prevY = snakeTailY[0]; 
	int prev2X, prev2Y; 
	snakeTailX[0] = snakeHeadCordX; 
	snakeTailY[0] = snakeHeadCordY; 

	for (int i = 1; i < snakeTailLen; i++) { 
		prev2X = snakeTailX[i]; 
		prev2Y = snakeTailY[i]; 
		snakeTailX[i] = prevX; 
		snakeTailY[i] = prevY; 
		prevX = prev2X; 
		prevY = prev2Y; 
	} 

	// Move snake
	switch (sDir) { 
	case LEFT: 
		snakeHeadCordX--; 
		break; 
	case RIGHT: 
		snakeHeadCordX++; 
		break; 
	case UP: 
		snakeHeadCordY--; 
		break; 
	case DOWN: 
		snakeHeadCordY++; 
		break; 
	} 

	// Game over conditions
	if (snakeHeadCordX >= width || snakeHeadCordX < 0 || snakeHeadCordY >= height || snakeHeadCordY < 0) 
	{
        isGameOver = true; 
        cout<<"\n\nGAME OVER!\n\n";
    } 

	for (int i = 0; i < snakeTailLen; i++) { 
		if (snakeTailX[i] == snakeHeadCordX && snakeTailY[i] == snakeHeadCordY) 
		{
            isGameOver = true; 
            cout<<"\n\nGAME OVER!\n\n";
        }
	} 

	// Regenerate food, increase player's score and increase snake length
	if (snakeHeadCordX == foodCordX && snakeHeadCordY == foodCordY) { 
		playerScore += 10; 
		foodCordX = rand() % width; 
		foodCordY = rand() % height; 
		snakeTailLen++; 
	} 
} 

/*-----------------------Function to take user input---------------------------*/
void UserInput() 
{ 
	if (_kbhit()) { 
		switch (_getch()) { 
		case 'a': 
			sDir = LEFT; 
			break; 
		case 'd': 
			sDir = RIGHT; 
			break; 
		case 'w': 
			sDir = UP; 
			break; 
		case 's': 
			sDir = DOWN; 
			break; 
		case 'x': 
			isGameOver = true; 
			break; 
		} 
	} 
} 

int main() 
{ 
	string playerName; 
	cout << "\n---------------------------------------------\n";
	cout << "Enter your name: "; 
	cin >> playerName;
	cout << "---------------------------------------------\n";
 

	GameInit(); 
	while (!isGameOver) { 
		GameRender(playerName); 
		UserInput(); 
		UpdateGame(); 
		Sleep(100); 
	} 

	return 0; 
}
