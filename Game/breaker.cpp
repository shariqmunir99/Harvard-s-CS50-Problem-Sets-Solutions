#include <iostream>
#include "yourgraphics.h"
#include <cstdlib>
#include <fstream>



using namespace std;



char c = '0';
int lives = 3;
int score = 0;
int check = 0;
int screenWidth, screenHeight;
int g = 255, b = 255;
int highScoreHistory[5] = { 0,0,0,0,0 };
int highscore;
bool fireBall_Status = false;




struct rect
{

	int x1 = 0;
	int y1 = 0;
	int x2 = 0;
	int y2 = 0;
	int health;
	bool SpecialEffect = false;


}pad, brick[15][10];  //struct for all rectangles
struct ellipse
{

	int x1 = 520;
	int y1 = 300;
	int x2 = x1 + 30;
	int y2 = y1 + 30;
	int velocityX = 0;
	int velocityY = 2;

}ball;  // strcuct for ellipse


// Function Prototypes

void Welcome();  //Displays The Brick Breakout Screen
void Menu(char& user_choice); //Displays The Menu.
void Borders(); //  Draws The Border lines
void Load(); // Loads The Game
void BrickPrinting_BeforeColission(); // Prints the Grid Of Bricks.
void PaddleMovement(); // Paddle Movement Logic
void BallMovement(); // Ball Movement Logic
void BrickPrinting_AfterColission(int i, int j, int& bonus); // printing the bricks on the basis of their health after collision... i and j are the locations
void Combo(int Bonus); // Applies A Combo Logic and Activates Only When Multiple Bricks Are broken in a row.
void GameWon(); // Prints Game Won On The Screen.
void GameQuit(); //Print Game Quitted On The Screen.
void GameOver(); // Prints Game Over On The Screen.
void Save(); // Saves The Game



// Function Definitions
void Welcome()
{
	cout << "     *********                          **          *********                              **";
	cout << "\n     ***    ***             **          **          ***    ***                             **   **";
	cout << "\n     ***     ***            **          **  **      ***     ***                            **  **";
	cout << "\n     ***    ***                         ** **       ***    ***                             ** **";
	cout << "\n     **********    ** ***   **  ******  ****        **********    ** ***   ******  ******  ****      ******  ** ***";
	cout << "\n     ***     ***   ***   *  **  ******  ** **       ***     ***   ***   *  **  **      **  ** **     **  **  ***   *";
	cout << "\n     ***      ***  **       **  **      **  **      ***      ***  **       ******  ******  **  **    ******  **";
	cout << "\n     ***     ***   **       **  ******  **   **     ***     ***   **       **      **  **  **   **   **      **";
	cout << "\n     **********    **       **  ******  **    **    **********    **       ******  ******  **    **  ******  **";
	cout << "\n\n\n\n\n \t\t\t\t\t By Abdul Ahad Usman And Shariq Munir";
	cout << "\n\n\n\n\n\n\n\n\n\n\n \t\t\t\t\t\tPress  C to Continue.";
	bool flag = false;
	while (true) {
		c = getKey();
		if (c == 'c') break;
		system("Color A"); system("Color B"); system("Color C"); system("Color 5");

	}
	cls();
}
void Menu(char& user_choice)
{
	bool menu = true;
	gotoxy(0, 3);
	Welcome();
	while (menu)
	{

		int screenWidth, screenHeight;
		SetProcessDPIAware();
		getWindowDimensions(screenWidth, screenHeight);
		showConsoleCursor(false);

		cls();


		gotoxy(0, 3);
		cout << "     *********                          **          *********                              **";
		cout << "\n     ***    ***             **          **          ***    ***                             **   **";
		cout << "\n     ***     ***            **          **  **      ***     ***                            **  **";
		cout << "\n     ***    ***                         ** **       ***    ***                             ** **";
		cout << "\n     **********    ** ***   **  ******  ****        **********    ** ***   ******  ******  ****      ******  ** ***";
		cout << "\n     ***     ***   ***   *  **  ******  ** **       ***     ***   ***   *  **  **      **  ** **     **  **  ***   *";
		cout << "\n     ***      ***  **       **  **      **  **      ***      ***  **       ******  ******  **  **    ******  **";
		cout << "\n     ***     ***   **       **  ******  **   **     ***     ***   **       **      **  **  **   **   **      **";
		cout << "\n     **********    **       **  ******  **    **    **********    **       ******  ******  **    **  ******  **";
		system("Color B");
		cout << "\n\n\n	1)\tNew Game";

		cout << "\n\n	2)\tLoad Game";
		cout << "\n\n	3)\tInstructions";
		cout << "\n\n	4)\tHigh Scores";
		cout << "\n\n	5)\tQuit";
		c = getKey();
		while (c != 'b')
		{
			c = getKey();
			if (c == '1')
			{
				c = 'b';
				menu = false;
			}
			if (c == '2')
			{
				c = 'b';
				menu = false;
				user_choice = '2';
			}
			if (c == '3')
			{
				cls();

				gotoxy(0, 0);
				cout << "CONTROLS:-";
				cout << "\n\n- Press 'A' or 'D' to Move The Paddle Left or Right.";
				cout << "\n- Press 'P' To Pause The Game and 'R' to resume it.";
				cout << "\n- Press 'S' To Save the Game to Play it later.";
				cout << "\n- Press 'Q' To Quit The Game. ";
				cout << "\n\nGAME MECHANICS:-";
				cout << "\n\n- A Player has 3 Lives.";
				cout << "\n- Each Time The Ball Misses The Paddle 1 One Live is Lost.";
				cout << "\n- After All Lives are Lost the Player Loses and The Game Is Over.";
				cout << "\n- Destroy All The Bricks to Win.";
				cout << "\n\nBRICKS INFO:-";
				cout << "\n\n Takes 1 Hit To break ";
				cout << "\n\n Takes 2 Hits To break";
				cout << "\n\n Takes 3 Hits To break";
				cout << "\n\n Enables FireBall Effect";
				cout << "\n\n Note: The Fireball Effect Ends After 2 Paddle Colissions";
				cout << "\n\n Fun Fact: There is an Easter Egg in the Game Controls";
				cout<<   " \n           Try To Find It!";
				drawRectangle(10 + 400, screenHeight / 2 + 20, 150 + 600, screenHeight / 2 + 40, 0, 0, 0, 240, 128, 128);
				drawRectangle(10 + 400, screenHeight / 2 + 60, 150 + 600, screenHeight / 2 + 80, 0, 0, 0, 251, 77, 40);
				drawRectangle(10 + 400, screenHeight / 2 + 100, 150 + 600, screenHeight / 2 + 120, 0, 0, 0, 234, 60, 83);
				drawRectangle(10 + 400, screenHeight / 2 + 140, 150 + 600, screenHeight / 2 + 160, 0, 0, 0, 136, 8, 8);
				gotoxy(2, 28);
				cout << "Press b To Go Back: ";
				while (c != 'b')
				{
					c = getKey();
				}
				gotoxy(0, 0);
			}
			if (c == '4')
			{
				cls();
				gotoxy(0, 0);
				cout << "\n\n\n\n\n\n";
				cout << "\t\t\t\t\t\t     HighScores\n\n\n";
				for (int i = 0, j = 1; i < 5; i++, j++)
				{
					cout << "\t\t\t\t\t   " << j << ")\t\t  " << highScoreHistory[i] << "\n\n";
				}
				cout << "\n\n\n\n\t\t\t\t\t\t Press b To Go Back:";
				c = getKey();
				while (c != 'b')
				{
					c = getKey();
					drawLine(300 + 75, 110, 600 + 75, 110, 255, 255, 0);
					drawLine(300 + 75, 110 + 40, 600 + 75, 110 + 40, 255, 255, 0);

					drawLine(300 + 75, 110, 300 + 75, 500, 255, 255, 0);
					drawLine(300 + 120, 110, 300 + 120, 500, 255, 255, 0);

					drawLine(600 + 75, 110, 600 + 75, 500, 255, 255, 0);
					drawLine(600 + 30, 110, 600 + 30, 500, 255, 255, 0);

					drawLine(300 + 75, 500, 600 + 75, 500, 255, 255, 0);
					drawLine(300 + 75, 500 - 55, 600 + 75, 500 - 55, 255, 255, 0);
				}
			}
		}
	}
}
void Borders()
{
	drawLine(0, 10, screenWidth, 10, 255, 255, 0);
	drawLine(0, 90, screenWidth, 90, 255, 255, 0);
	drawLine(screenWidth / 2, 10, screenWidth / 2, 90, 255, 255, 0);
	drawLine(0, 10, 0, screenHeight, 255, 255, 0);
	drawLine(screenWidth, 10, screenWidth, screenHeight, 255, 255, 0);
}
void Load()
{
	ifstream read("storage.txt");
	if (read)
	{
		read >> pad.x1 >> pad.x2 >> pad.y1 >> pad.y2 >> ball.x1 >> ball.x2 >> ball.y1 >> ball.y2 >> lives >> score >> fireBall_Status >> g >> b;
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				read >> brick[i][j].x1 >> brick[i][j].x2 >> brick[i][j].y1 >> brick[i][j].y2 >> brick[i][j].health;

			}
		}
		read.close();
	}

}
void BrickPrinting_BeforeColission()
{
	for (int i = 4, k = 60; i < 15; i++)
	{

		for (int j = 0; j < 10; j++)
		{
			if (brick[i][j].SpecialEffect == true && brick[i][j].health > 0)
			{
				drawRectangle(brick[i][j].x1, brick[i][j].y1, brick[i][j].x2, brick[i][j].y2, 0, 0, 0, 136, 8, 8);

			}
			else if (brick[i][j].health == 3)
			{

				drawRectangle(brick[i][j].x1, brick[i][j].y1, brick[i][j].x2, brick[i][j].y2, 0, 0, 0, 234, 60, 83);

			}
			else if (brick[i][j].health == 2)
			{
				drawRectangle(brick[i][j].x1, brick[i][j].y1, brick[i][j].x2, brick[i][j].y2, 0, 0, 0, 251, 77, 40);

			}
			else if (brick[i][j].health == 1)
			{
				drawRectangle(brick[i][j].x1, brick[i][j].y1, brick[i][j].x2, brick[i][j].y2, 0, 0, 0, 240, 128, 128);

			}
			else if (brick[i][j].health == 0)
			{
				drawRectangle(brick[i][j].x1, brick[i][j].y1, brick[i][j].x2, brick[i][j].y2, 0, 0, 0, 0, 0, 0);

			}
		}
	}
}
void PaddleMovement()
{
	c = getKey();
	if (pad.x1 > 0 && pad.x2 < screenWidth)
	{

		if (c == 'd')
		{
			drawRectangle(pad.x1, pad.y1, pad.x2, pad.y2, 0, 0, 0, 0, 0, 0);

			pad.x1 += 25;
			pad.x2 += 25;
			drawRectangle(pad.x1, pad.y1, pad.x2, pad.y2, 0, 0, 0, 255, 255, 0);

		}

		if (c == 'a')
		{

			drawRectangle(pad.x1, pad.y1, pad.x2, pad.y2, 0, 0, 0, 0, 0, 0);

			pad.x1 -= 25;
			pad.x2 -= 25;
			drawRectangle(pad.x1, pad.y1, pad.x2, pad.y2, 0, 0, 0, 255, 255, 0);

		}
	}
	else if (pad.x1 <= 0)
	{

		if (c == 'd')
		{

			drawRectangle(pad.x1, pad.y1, pad.x2, pad.y2, 0, 0, 0, 0, 0, 0);

			pad.x1 += 25;
			pad.x2 += 25;
			drawRectangle(pad.x1, pad.y1, pad.x2, pad.y2, 0, 0, 0, 255, 255, 0);

		}
	}
	else if (pad.x2 >= screenWidth)
	{

		if (c == 'a')
		{

			drawRectangle(pad.x1, pad.y1, pad.x2, pad.y2, 0, 0, 0, 0, 0, 0);
			pad.x1 -= 25;
			pad.x2 -= 25;
			drawRectangle(pad.x1, pad.y1, pad.x2, pad.y2, 0, 0, 0, 255, 255, 0);
		}
	}
}
void BallMovement()
{
	if (c == 'j')
	{
		ball.velocityX = -2;
		ball.velocityY = 0;
	}
	else if (c == 'l')
	{
		ball.velocityX = 2;
		ball.velocityY = 0;
	}
	else if (c == 'i')
	{
		ball.velocityX = 0;
		ball.velocityY = -2;
	}
	else if (c == 'k')
	{
		ball.velocityX = 0;
		ball.velocityY = 2;
	}
	drawEllipse(ball.x1, ball.y1, ball.x2, ball.y2, 0, 0, 0, 0, 0, 0);
	ball.x1 += ball.velocityX;
	ball.x2 += ball.velocityX;
	ball.y1 += ball.velocityY;
	ball.y2 += ball.velocityY;
	drawEllipse(ball.x1, ball.y1, ball.x2, ball.y2, 0, 0, 0, 255, g, b);
	delay(8);

}
void BrickPrinting_AfterColission(int i, int j, int& bonus)
{
	if (brick[i][j].health == 2)
	{
		drawRectangle(brick[i][j].x1, brick[i][j].y1, brick[i][j].x2, brick[i][j].y2, 0, 0, 0, 251, 77, 40);


	}
	else if (brick[i][j].health == 1)
	{
		drawRectangle(brick[i][j].x1, brick[i][j].y1, brick[i][j].x2, brick[i][j].y2, 0, 0, 0, 240, 128, 128);

	}
	else if (brick[i][j].health == 0)
	{
		score++;
		bonus++;
		Combo(bonus);
		check++;
		drawRectangle(brick[i][j].x1, brick[i][j].y1, brick[i][j].x2, brick[i][j].y2, 0, 0, 0, 0, 0, 0);
	}
}
void PaddleColission(int &Bonus, int &fireBall_Counter)
{
	if (ball.x2 >= pad.x1 && ball.x1 <= pad.x2 && ball.y2 == pad.y1)
	{ 	//Deflection at an agnle of 180;
		Bonus = 0;
		gotoxy(10, 2);
		cout << "Score:" << score << "       ";
		gotoxy(0, 0);
		if (fireBall_Status == true)
			fireBall_Counter++;
		if (fireBall_Counter > 1)
		{
			fireBall_Status = false;
			fireBall_Status = 0;
			g = 255, b = 255;
			gotoxy(75, 2);
			cout << "                   ";
			gotoxy(0, 0);
		}
		if (ball.x2 >= ((pad.x1 + pad.x2) / 2) - 5 && ball.x1 <= ((pad.x1 + pad.x2) / 2) + 5 && ball.y2 == pad.y1)
		{
			ball.velocityX = 0;
			ball.velocityY = -2;

		}


		//Deflection at an angle of 30 From The Right side of the Pad;
		else if ((ball.x1 >= ((pad.x1 + pad.x2) / 2) + 5 && ball.x1 <= ((((pad.x1 + pad.x2) / 2) + 5) + pad.x2) / 2 && ball.y2 == pad.y1))
		{
			ball.velocityX = 1;
			ball.velocityY = -2;

		}



		//Deflection at an angle of 45 from the right side of the Pad;
		else if ((ball.x1 >= ((((pad.x1 + pad.x2) / 2) + 5) + pad.x2) / 2 && ball.x1 <= pad.x2 && ball.y2 == pad.y1))
		{
			ball.velocityX = 2;
			ball.velocityY = -2;

		}


		//Deflection at an angle 30 From The Left Side Of The Pad;

		else if (((ball.x2 >= (((pad.x1 + pad.x2) / 2) - 5) + pad.x1) / 2) && ball.x1 <= ((pad.x1 + pad.x2) / 2) - 5 && ball.y2 == pad.y1)
		{
			ball.velocityX = -1;
			ball.velocityY = -2;

		}


		//Deflection at an angle 45 From The Left Side Of The Pad;
		else if (ball.x2 >= pad.x1 && ball.x2 <= ((((pad.x1 + pad.x2) / 2) - 5) + pad.x2) / 2 && ball.y2 == pad.y1)
		{
			ball.velocityX = -2;
			ball.velocityY = -2;
		}
	}
}
void BrickColission(int &Bonus)
{
	//collision with the bricks
	for (int i = 4; i < 15; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (brick[i][j].health > 0)
			{

				if (brick[i][j].x1 < ball.x2 && brick[i][j].x2>ball.x1 && brick[i][j].y1< ball.y2 + ball.velocityY && brick[i][j].y2> ball.y1 + ball.velocityY)
				{
					if (brick[i][j].SpecialEffect == 1)
					{
						fireBall_Status = true;
						g = 0;
						b = 0;
						gotoxy(75, 2);
						cout << "Fireball Activated";
						gotoxy(0, 0);
					}
					if (fireBall_Status)
					{

						brick[i][j].health = 0;
						Bonus++;
						score++;
						check++;
						Combo(Bonus);
						drawRectangle(brick[i][j].x1, brick[i][j].y1, brick[i][j].x2, brick[i][j].y2, 0, 0, 0, 0, 0, 0);
					}
					else
					{
						gotoxy(0, 0);
						brick[i][j].health--;
						ball.velocityY *= -1;
						BrickPrinting_AfterColission(i, j, Bonus);
					}
				}
				else if (ball.x2 + ball.velocityX > brick[i][j].x1 && ball.x1 + ball.velocityX<brick[i][j].x2 && ball.y2>brick[i][j].y1 && ball.y1 < brick[i][j].y2)
				{
					if (brick[i][j].SpecialEffect == 1)
					{
						fireBall_Status = true;
						g = 0;
						b = 0;

						gotoxy(75, 2);
						cout << "Fireball Activated";
						gotoxy(0, 0);
					}
					if (fireBall_Status)
					{

						brick[i][j].health = 0;
						Bonus++;
						score++;
						check++;
						Combo(Bonus);
						drawRectangle(brick[i][j].x1, brick[i][j].y1, brick[i][j].x2, brick[i][j].y2, 0, 0, 0, 0, 0, 0);
					}


					else
					{
						Bonus++;
						score++;
						brick[i][j].health--;
						ball.velocityX *= -1;
						BrickPrinting_AfterColission(i, j, Bonus);
					}
				}


			}
		}
	}
}
void Combo(int Bonus)
{
	if (Bonus > 1)
	{
		int y;
		y = score;
		Bonus--;
		score = y + Bonus;
		gotoxy(10, 2);
		cout << "Score:" << y << "+" << Bonus << "=" << score;
		gotoxy(0, 0);
	}
	else if (Bonus <= 1)
	{

		gotoxy(10, 2);
		cout << "Score:" << score << "       ";
		gotoxy(0, 0);
	}
}
void GameWon()
{

	cls();
	gotoxy(0, 0);
	cout << "\n\n\n\n\n\n\n\n\n            ***********                                         ***     ***     ***";
	cout << "\n            ***********                                         ***     ***     ***";
	cout << "\n            ***     ***                                         ***     ***     ***";
	cout << "\n            ***		                                        ***     ***     ***";
	cout << "\n            ***  ******   ******   *********   ******		***     ***     ***  ******  *******";
	cout << "\n            ***  ******       **   **  *  **   **  **		***     ***     ***  **  **  *******";
	cout << "\n            ***     ***   ******   **  *  **   ******		***     ***     ***  **  **  **   **";
	cout << "\n            ***********   **  **   **  *  **   **               *******************  **  **  **   **";
	cout << "\n            ***********   ******   **  *  **   ******		*******************  ******  **   **";
	while (true)
	{
		system("Color 4"); delay(1000); system("Color 5"); delay(1000); system("Color 6"); delay(1000); system("Color 1"); delay(1000); system("Color 8");


	}

}
void GameOver()
{
	gotoxy(0, 6);
	cout << "\n            ***********                                        ***********";
	cout << "\n            ***********                                        ***********";
	cout << "\n            ***     ***                                        ***     ***";
	cout << "\n            ***                                                ***     ***";
	cout << "\n            ***  ******   ******   *********   ******          ***     ***   **        **   ******  ** *** ";
	cout << "\n            ***  ******       **   **  *  **   **  **          ***     ***    **      **    **  **  ***   *";
	cout << "\n            ***     ***   ******   **  *  **   ******          ***     ***     **    **     ******  **   ";
	cout << "\n            ***********   **  **   **  *  **   **              ***********      **  **      **      ** ";
	cout << "\n            ***********   ******   **  *  **   ******          ***********       ****       ******  **";
	cout << "\n\n\n \n\n\n\n\n                                               Press E To Exit.";
	c = getKey();
	while (c != 'e')
	{
		system("Color 4"); delay(500); system("Color 7"); delay(500); //system("Color 6"); delay(1000); system("Color 1"); delay(1000); system("Color 8");
		c = getKey();

	}
	cls();
}
void GameQuit()
{
	gotoxy(0, 4);
	cout << "\n***********                                        ***********                        **        **                   **";
	cout << "\n***********                                        ***********                 **     **        **                   **";
	cout << "\n***     ***                                        ***     ***                 **   ******    ******                 **";
	cout << "\n***                                                ***     ***                      ******    ******                 **";
	cout << "\n***  ******   ******   *********   ******          ***     ***      **    **   **     **        **      ******   ******";
	cout << "\n***  ******       **   **  *  **   **  **          ***  ********    **    **   **     **        **      **  **   **  **";
	cout << "\n***     ***   ******   **  *  **   ******          ***  ********    **    **   **     **        **      ******   **  **";
	cout << "\n***********   **  **   **  *  **   **              *********** **   **    **   **     ** **     ** **   **       **  **";
	cout << "\n***********   ******   **  *  **   ******          ***********  **  ********   **     *****     *****   ******   ******";
	cout << "\n\n\n \n\n\n\n\n                                               Press E To Exit.";
	c = getKey();
	while (c != 'e')
	{
		system("Color 4"); delay(500); system("Color 7"); delay(500); //system("Color 6"); delay(1000); system("Color 1"); delay(1000); system("Color 8");
		c = getKey();

	}
	cls();
}
void Save()
{
	ofstream store("storage.txt");
	store << pad.x1 << " " << pad.x2 << " " << pad.y1 << " " << pad.y2 << " " << ball.x1 << " " << ball.x2 << " " << ball.y1 << " " << ball.y2 << " " << lives << " " << score << " " << fireBall_Status << " " << g << " " << b << " ";
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			store << brick[i][j].x1 << " " << brick[i][j].x2 << " " << brick[i][j].y1 << " " << brick[i][j].y2 << " " << brick[i][j].health << " ";

		}
	}
	store.close();
}


int main()
{

	int Bonus = 0;
	char user_choice = 1;
	int fireBall_Counter = 0;

	SetProcessDPIAware();
	getWindowDimensions(screenWidth, screenHeight);
	cls();



#pragma region HighScore Reading from the File


	// reading highscore file to load the highscore
	ifstream readhs("highscore.txt");

	for (int i = 0; i < 5; i++)
	{
		readhs >> highScoreHistory[i];
	}
	highscore = highScoreHistory[0];
#pragma endregion



	// calling menu function to start
	Menu(user_choice);

#pragma region Initializing Brick And Paddle Positions



	//inializing bricks position
	gotoxy(0, 0);
	cls();
	brick[0][0].x1 = 0;
	brick[0][0].y1 = 60;
	brick[0][0].x2 = brick[0][0].x1 + screenWidth / 10;
	brick[0][0].y2 = brick[0][0].y1 + 20;

	//initializing paddle coordinates
	pad.x1 = 450;
	pad.y1 = screenHeight - 40;
	pad.x2 = pad.x1 + 200;
	pad.y2 = pad.y1 + 15;
#pragma endregion




#pragma region Health And Powers Assigning


	for (int i = 4, k = 60; i < 15; i++)
	{

		for (int j = 0; j < 10; j++)
		{
			brick[i][j].health = (rand() % (5 - 3 + 1)) + 1;
			if ((i == 9 && j == 5) || (i == 12 && j == 1) || (i == 6 && j == 8))
			{
				brick[i][j].SpecialEffect = true;
			}
			else
				brick[i][j].SpecialEffect = false;

			brick[i][j].x1 = brick[0][0].x1 + (j * (screenWidth / 10));
			brick[i][j].y1 = (i * k);
			brick[i][j].x2 = brick[i][j].x1 + screenWidth / 10;
			brick[i][j].y2 = (i + 1) * 20;
		}

		k = 20;
	}
#pragma endregion



	//Loads The Game
	if (user_choice == '2')
	{
		Load();
	}



	//Ends The Game If User Presses '5' in the Menu.
	else if (user_choice == 5)
	{
		return 0;
	}


#pragma region Screen Beautification


	//Formatting of The Screen
	gotoxy(95, 2);
	cout << "Lives:";
	gotoxy(30, 2);
	cout << "High Score : " << highscore;
	gotoxy(10, 2);
	cout << "Score:" << score;

	drawRectangle(0, 0, screenWidth, screenHeight, 0, 0, 0, 0, 0, 0); //Draws a Black Rectangle Just for beautification of the game.
	gotoxy(0, 0);

#pragma endregion


#pragma region Printing Life Circles


	//Drawing the Circles for lifes.
	if (lives == 3)
	{

		drawEllipse(920, 38, 950, 65, 204, 0, 0, 204, 0, 0);
		drawEllipse(970, 38, 1000, 65, 204, 0, 0, 204, 0, 0);
		drawEllipse(1020, 38, 1050, 65, 204, 0, 0, 204, 0, 0);
	}
	else if (lives == 2)
	{
		drawEllipse(920, 38, 950, 65, 204, 0, 0, 204, 0, 0);
		drawEllipse(970, 38, 1000, 65, 204, 0, 0, 204, 0, 0);
	}
	else if (lives == 1)
	{
		drawEllipse(920, 38, 950, 65, 204, 0, 0, 204, 0, 0);

	}
	showConsoleCursor(false);
#pragma endregion



#pragma region Printing Brick And paddle Initially


	//Printing the bricks
	BrickPrinting_BeforeColission();



	//Printing The paddle
	drawRectangle(pad.x1, pad.y1, pad.x2, pad.y2, 0, 0, 0, 255, 255, 0);

#pragma endregion

	//Main loop
	while (true)
	{
		//drawing borders
		Borders();



		//moving the paddle
		PaddleMovement();


		//printing and moving the ball at the start
		drawEllipse(ball.x1, ball.y1, ball.x2, ball.y2, 0, 0, 0, 0, 0, 0);
		ball.x1;
		ball.x2;
		ball.y1 += ball.velocityY;
		ball.y2 += ball.velocityY;

		drawEllipse(ball.x1, ball.y1, ball.x2, ball.y2, 0, 0, 0, 255, g, b);

#pragma region Paddle Colission

PaddleColission(Bonus, fireBall_Counter);

#pragma endregion

#pragma region Border Colission


		//Coliision Detection at Borders;
		if (ball.x1 < 0 || ball.x2 > screenWidth) {
			ball.velocityX *= -1;
		}
		else if (ball.y1 < 93)
		{
			ball.velocityY *= -1;
		}

		BallMovement();
#pragma endregion

#pragma region Brick Collision

		BrickColission(Bonus);

#pragma endregion

#pragma region Lives Lost


		//life loosing
		if (ball.y2 > pad.y2 + 70)
		{
			lives--;
			fireBall_Status = false;
			g = 255;
			b = 255;
			gotoxy(75, 2);
			cout << "                   ";
			gotoxy(0, 0);
			drawRectangle(pad.x1, pad.y1, pad.x2, pad.y2, 0, 0, 0, 0, 0, 0);
			pad.x1 = 450;
			pad.x2 = 650;
			drawRectangle(pad.x1, pad.y1, pad.x2, pad.y2, 0, 0, 0, 255, 255, 0);
			if (lives == 2)
			{

				drawEllipse(ball.x1, ball.y1, ball.x2, ball.y2, 0, 0, 0);
				drawEllipse(1020, 38, 1050, 65, 0, 0, 0, 0, 0, 0);

			}
			else if (lives == 1)
			{
				drawEllipse(970, 38, 1000, 65, 0, 0, 0, 0, 0, 0);

			}
			ball.x1 = 520;
			ball.y1 = 300;
			ball.x2 = ball.x1 + 30;
			ball.y2 = ball.y1 + 30;
			ball.velocityX = 0;
			ball.velocityY = 2;


			drawEllipse(ball.x1, ball.y1, ball.x2, ball.y2, 0, 0, 0, 255, 255, 255);
			delay(200);


		}

#pragma endregion

#pragma region Highscore


		if (score > highscore)
		{
			highscore = score;
		}
		gotoxy(30, 2);
		cout << "High Score : " << highscore;


		//save game
		if (c == 's')
		{
			Save();
		}


#pragma endregion

#pragma region Game Winning,Ending,Quiting And Pausing


		if (lives == 0)
		{

			cls();
			gotoxy(55, 14);
			GameOver();

			break;
		}
		//game pause
		if (c == 'p')
		{
			gotoxy(65, 2);
			cout << "Paused";
			gotoxy(0, 0);
			Borders();
			while (1)
			{
				Borders();
				c = getKey();
				if (c == 'r')
				{
					gotoxy(65, 2);
					cout << "      ";
					gotoxy(0, 0);
					break;
				}
			}
		}
		//game won
		if (check == 100)
		{
			GameWon();
			break;
		}
		//game quitting
		if (c == 'q')
		{
			cls();
			gotoxy(55, 14);
			GameQuit();

			break;

		}

	}
#pragma endregion

#pragma region highScore History

	// storing the history of previous five highscores

	bool exist = false;

	for (int i = 0; i < 5; i++)
	{
		if (score == highScoreHistory[i])
		{
			exist = true;
		}

	}

	if (!exist)
	{

		if (score > highScoreHistory[4])
		{

			highScoreHistory[4] = score;
		}

	}

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (highScoreHistory[j] < highScoreHistory[j + 1])
			{
				int temp = highScoreHistory[j + 1];
				highScoreHistory[j + 1] = highScoreHistory[j];
				highScoreHistory[j] = temp;
			}
		}
	}


	ofstream writehs("highscore.txt");
	for (int i = 0; i < 5; i++)
	{
		writehs << highScoreHistory[i] << " ";
	}

#pragma endregion


}
