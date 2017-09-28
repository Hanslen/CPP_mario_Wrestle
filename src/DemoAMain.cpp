#include "header.h"
#include "templates.h"
#include "DemoAMain.h"
#include "DemoBObject.h"
#include "Psyjc3_1Object.h"
#include "Mario_Object.h"
#include "Mario_bulletObject.h"
#include "Tortoise_Object.h"
#include "bloodObject.h"
#include "SelectMashroom.h"
#include "DamageMushroom.h"
#include "FlyingTile.h"
#include "welcomeMario.h"
#include <Windows.h>
#include <mmsystem.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "JPGImage.h"
using namespace std;

/*
	For music playing
*/
#pragma comment( lib, "Winmm.lib" )
/*
	In Windows.h, includes winuser.h, which defines the Win32 API LoadImage() function, in order to load <Windows.h>
	successfully, I need to undef LoadImage.
*/
/*
	To ensure we can unload the windows.h
*/
#undef LoadImage
int DemoAMain::state_init = 0;
int DemoAMain::winner = -1;
int DemoAMain::score = 0;
int DemoAMain::hasPressEnter = 0;
DemoAMain::DemoAMain()
	: BaseEngine(6),
	blood(300),
	usernameindex(0),
	m_state(stateMain),
	playMusic(1)
{
	strcpy(username, "initial");
	clearUsername(username);

	PlaySound(TEXT("bgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}


DemoAMain::~DemoAMain()
{
}

/*
	0 for welcome page, 1 for start the game, 2 for tutorial, 3 for leaderboard
*/
void DemoAMain::SetupBackgroundBuffer()
{
	ImageData im, im2;
	switch (state_init)
	{
	case 0:
		im2.LoadImage("img/bg2.png");
		im.ShrinkFrom(&im2, 1);
		im.RenderImageWithMask(this->GetBackground(), 0, 0, 0, 0, im.GetWidth(), im.GetHeight()); 
		DemoAMain::hasPressEnter = 0;
		usernameindex = 0;
		strcpy(username, "");
		break;
	case 1:
		im2.LoadImage("img/bg1.jpg");
		im.ShrinkFrom(&im2, 1);
		im.RenderImageWithMask(this->GetBackground(), 0, 0, 0, 0, im.GetWidth(), im.GetHeight());
		//Specify the flower tiles
		m_oTiles.SetSize(15, 1);

		// Go to state paused
		m_state = stateMain;
		break;
	case 2:
		//show the tutorial
		im2.LoadImage("img/tutorial.png");
		im.ShrinkFrom(&im2, 1);
		im.RenderImageWithMask(this->GetBackground(), 0, 0, 0, 0, im.GetWidth(), im.GetHeight());
		break;
	case 3:
		im2.LoadImage("img/bg1.jpg");
		im.ShrinkFrom(&im2, 1);
		im.RenderImageWithMask(this->GetBackground(), 0, 0, 0, 0, im.GetWidth(), im.GetHeight());
		
		break;
	default:
		break;
	}

}

/*
	Override the GameAction, because we need to pause the game.
*/
void DemoAMain::GameAction()
{
	switch (m_state)
	{
	case stateInit:
		DrawStringsUnderneath();
		Redraw(true);
			break;
	case statePaused:
		DrawStringsUnderneath();
		Redraw(true);
		break;
	case stateMain:
		// Only tell objects to move when not paused etc
		UpdateAllObjects(GetModifiedTime());
		break;
	}
}

/*
	Click function for control(pause or resume the music)
*/
void DemoAMain::MouseDown(int iButton, int iX, int iY)
{
	if (iX > 630 && iX < 781 && iY > 5 && iY < 35){
		controlMusic();
	}
	
}

/*
	Control(Stop or resume) the music
*/
void DemoAMain::controlMusic(){
	if (playMusic == 1){
		PlaySound(NULL, NULL, SND_NODEFAULT);
		playMusic = 0;
	}
	else{
		PlaySound(TEXT("bgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		playMusic = 1;
	}
	Redraw(true);
}

/*
	Clear the username char*
*/
void DemoAMain::clearUsername(char *var){
	int i = 0;
	while (var[i] != '\0') {
		var[i] = '\0';
		i++;
	}
}

/*
	0 for welcome page, 
	1 for start the game, 
	2 for tutorial, 
	3 for leaderboard,
	4 for win/lose
*/
void DemoAMain::KeyDown(int iKeyCode)
{
	string letters = "abcdefghijklmnopqrstuvwxyz";
	if (state_init == 4){
		/*
			Store the username
		*/
		if (iKeyCode < 123 && iKeyCode > 96){
			username[usernameindex] = letters[iKeyCode - 97];
			usernameindex++;
		}
		/*
			If the player press delete, delete that character from the username
		*/
		else if (iKeyCode == 8){
			usernameindex--;
			if (usernameindex < 0){
				usernameindex = 0;
			}
			username[usernameindex] = '\0';
			Redraw(true);
		}
		/*
			Store the play information to the rankboard.txt
		*/
		ofstream myfile("rankboard.txt", ios::app);
		std::string sscore = std::to_string(DemoAMain::score + 10);
		std::string winnerstate = "";
		if (winner == 0){
			winnerstate = "wins";
		}
		else{
			winnerstate = "loses";
		}
		switch (iKeyCode){
		case SDLK_RETURN:
			printf("Store to the file!\n");
			//store the score to the rankboard.txt
			username[usernameindex] = ' ';
			if (myfile.is_open())
			{
				if (usernameindex == 0){
					strcpy(username,"Secret man ");
				}
				myfile << username + sscore +"scores, "+winnerstate+" the game" + "\n";
				myfile.close();
			}
			else cout << "Unable to open file";

			usernameindex = 0; 
			clearUsername(username);
			 break;
		default:break;
		}

	}
	switch (iKeyCode)
	{
	case SDLK_RETURN:
		DemoAMain::hasPressEnter = 1;
		if (state_init == 1 || state_init == 0||winner != -1 || state_init == 4){
			if (state_init == 0){
				state_init = 1;
			}
			if (winner != -1 && state_init != 0){
				state_init = 0;
				winner = -1;
				_sleep(200);
			}
			SetupBackgroundBuffer();
			InitialiseObjects();
			Redraw(true);
			
		}
		else if (state_init == 2 || state_init == 3){
			SetupBackgroundBuffer();
			InitialiseObjects();
			Redraw(true);
		}
		break;
	case SDLK_SPACE:
		/*
			At tutorial or ranking stage, press space will go back to the main page
		*/
		if (state_init == 2 || state_init == 3){
			state_init = 0;
			SetupBackgroundBuffer();
			InitialiseObjects();
			Redraw(true);
		}
		else if (state_init == 1){
			/*
				Pause the  game or resume the game
			*/
			if (m_state == statePaused){
				m_state = stateMain;
				PlaySound(TEXT("bgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			}
			else{
				m_state = statePaused;
				PlaySound(NULL, NULL, SND_NODEFAULT);
			}
		}
		break;
	}
}


int DemoAMain::InitialiseObjects()
{
	// Record the fact that we are about to change the array - so it doesn't get used elsewhere without reloading it
	DrawableObjectsChanged();
	// Destroy any existing objects
	DestroyOldObjects();

	switch (state_init)
	{
		/*
			Welcome stage
		*/
	case 0:
		CreateObjectArray(3);
		StoreObjectInArray(0, new SelectMashroom(this));
		StoreObjectInArray(1, new welcomeMario(this));
		StoreObjectInArray(2, NULL);
		break;
		/*
			Playing stage
		*/
	case 1:
		// Creates an array to store the objects
		// Needs to have room for the NULL at the end
		CreateObjectArray(13);
		// You MUST set the array entry after the last one that you create to NULL, so that the system knows when to stop.
		// i.e. The LAST entry has to be NULL. The fact that it is NULL is used in order to work out where the end of the array is.
		StoreObjectInArray(0, new Mario_Object(this));
		StoreObjectInArray(1, new Tortoise_Object(this));
		StoreObjectInArray(2, new bloodObject(this, 10));
		StoreObjectInArray(3, new bloodObject(this, 450));
		StoreObjectInArray(4, new DamageMushroom(this));
		StoreObjectInArray(12, NULL); break;
		/*
			Tutorial stage
		*/
	case 2:
		CreateObjectArray(2);
		StoreObjectInArray(0, new welcomeMario(this));
		StoreObjectInArray(1, NULL);
		break;
		/*
			Ranking stage
		*/
	case 3:
		CreateObjectArray(2);
		StoreObjectInArray(0, new welcomeMario(this));
		StoreObjectInArray(1, NULL);
		break;
		/*
			Win/lose stage
		*/
	case 4:
		CreateObjectArray(2);
		if (DemoAMain::winner == 0){
			StoreObjectInArray(0, new Mario_Object(this));
		}
		else{
			StoreObjectInArray(0, new Tortoise_Object(this));
		}
		StoreObjectInArray(1, NULL);
	default:
		break;
	}

	return 0;
}


void DemoAMain::DrawStrings()
{
	switch (state_init)
	{
	case 0:break;
	case 1:
		if (DemoAMain::hasPressEnter == 1){
			CopyBackgroundPixels(0, 0, GetScreenWidth(), 30);
			DrawScreenString(280, 10, "Mario adventure", 0xffffff, NULL);
			//Mario blood block
			DrawScreenString(10, 430, "Mario", 0xffffff, NULL);

			//Boss blood block
			DrawScreenString(450, 430, "Boss", 0xffffff, NULL);
		}
		break;
	case 3:
		if (DemoAMain::hasPressEnter == 1){
			/*
				read the file to display the rank board
			*/
			DrawScreenString(300, 10, "Rank board", 0xffffff, NULL);
			
			string line;
			ifstream myfile("rankboard.txt");
			int totalLine = 0;
			if (myfile.is_open()){
				while (getline(myfile, line)){
					totalLine++;
				}
				//returning to beginning of file after getLines
				myfile.clear();
				myfile.seekg(0, ios::beg);
				int rankPosy = 60;
				int displayFrom = 0;
				if (totalLine < 12){
					displayFrom = 0;
				}
				else{
					displayFrom = totalLine - 11;
				}
				//Only display the latest 11 records
				while (getline(myfile, line))
				{
					char *cstr = new char[line.length() + 1];
					strcpy(cstr, line.c_str());
					if (displayFrom == 0){
						DrawScreenString(180, rankPosy, cstr, 0xffffff, NULL);
						rankPosy += 30;
					}
					else{
						displayFrom--;
					}
				}
				myfile.close();
			}
			else {
				DrawScreenString(220, 120, "Can not open that file", 0xffffff, NULL);
			}
			DrawScreenString(180, 450, "Press space to go the main page", 0xffffff, NULL);
		}
		break;
	case 4:
		DrawScreenString(320, 180, "Game Over", 0xffffff, NULL);
		if (DemoAMain::winner == 0){
			DrawScreenString(320, 210, "You win! :-)", 0xffffff, NULL);
			std::string s = std::to_string(score);
			const char* cstr = s.c_str();
			char buffer[256];
			strncpy(buffer, "Your score is ", sizeof(buffer));
			strncat(buffer, cstr, sizeof(buffer));
			DrawScreenString(280, 240, buffer, 0xffffff, NULL);
			/*
				Draw the flower tiles on the screen
			*/
			m_oTiles.SetBaseTilesPositionOnScreen(25, 440);
			m_oTiles.DrawAllTiles(this,
				this->GetBackground(),
				0, 0, 14, 0);

		}
		else{
			DrawScreenString(320, 210, "You lose! :-(", NULL);
			std::string s = std::to_string(score);
			const char* cstr = s.c_str();
			char buffer[256];
			strncpy(buffer, "Your score is ", sizeof(buffer));
			strncat(buffer, cstr, sizeof(buffer));
			DrawScreenString(280, 240, buffer, 0xffffff, NULL);
		}
		DrawScreenString(50, 530, "Press \"enter\" to save and back to the main page!",0xffffff, NULL);
		InitialiseObjects();
	default:
		break;
	}
}


/*
	Display the text such as
	score of the player, music control, the username player types
*/
void DemoAMain::DrawStringsUnderneath()
{
	char buf[128];
	if (playMusic == 0){
		DrawScreenString(620, 5, "Play Music", 0xffffff, NULL);
	}
	else{
		DrawScreenString(620, 5, "Stop Music", 0xffffff, NULL);
	}
	switch (state_init)
	{
	case 0:break;
	case 1:
		if (DemoAMain::hasPressEnter == 1){
			sprintf(buf, "Score: %6d", score);
			DrawScreenString(50, 10, buf, 0x00ffff, NULL);
			if (m_state == stateMain){
				DrawScreenString(70, 530, "w,s,a,d to control, j to shoot, space to pause.", 0xffffff, NULL);
			}
			else{
				DrawScreenString(70, 530, "w,s,a,d to control, j to shoot, space to continue.", 0xffffff, NULL);
			}
		}
		break;
	case 4:
		sprintf(buf, "Your name: %s", username);
		DrawScreenString(200, 350, buf, 0x00ffff, NULL); break;
		break;
	default:
		break;
	}
	
}
