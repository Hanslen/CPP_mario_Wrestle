#pragma once
#include "BaseEngine.h"
#include "Psyjc3TileManager.h"
#include "FlyingTile.h"

class DemoAMain :
	public BaseEngine
{
public:
	DemoAMain();
	~DemoAMain();
	virtual void GameAction();
	void SetupBackgroundBuffer();
	void MouseDown(int iButton, int iX, int iY);
	void KeyDown(int iKeyCode);
	int InitialiseObjects();
	void DrawStrings();
	void DrawStringsUnderneath();
	int blood;
	static int state_init;
	static int winner;
	static int score;
	static int hasPressEnter;
	void typePlayerName();
	char username[100];
	int usernameindex;

	enum State { stateInit, stateMain, statePaused };
	

private:
	Psyjc3TileManager psyjc3_tile;
	FlyingTile m_oTiles;
	State m_state;
	int playMusic;
	void controlMusic();
	void clearUsername(char *var);
};

