#include "header.h"
#include "templates.h"
#include "Tortoise_Object.h"
#include "JPGImage.h"

/*
	These variables stand for some states of sub-Tortoise
*/
int Tortoise_Object::subX = 0;
int Tortoise_Object::hasSub = 0;
int Tortoise_Object::subOver = 0;
int Tortoise_Object::wantJump = 0;
int Tortoise_Object::canJump = 0;
/*
	This class is for the tortoise object
*/
Tortoise_Object::Tortoise_Object(BaseEngine* pEngine)
	:DisplayableObject(pEngine),
	left(1),
	up(true),
	fly(false),
	action(0),
	randAction(0),
	size(1),
	rotate_val(0),
	direction(0)
{
	tortoise2.LoadImage("img/tortoise_left.png");
	tortoise.ShrinkFrom(&tortoise2, 1);
	m_iCurrentScreenX = m_iPreviousScreenX = 610;
	m_iCurrentScreenY = m_iPreviousScreenY = 150;

	m_iDrawHeight = tortoise.GetHeight();
	m_iDrawWidth = tortoise.GetWidth();

	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;
	SetVisible(true);

	/*
		sub tortoise
	*/
	Tortoise_Object::subX = m_iCurrentScreenX;
	subY = 330;
	subTortoise1.LoadImage("img/tortoise_left.png");
	subTortoise.ShrinkFrom(&subTortoise1, 4);
}


Tortoise_Object::~Tortoise_Object()
{
}


void Tortoise_Object::Draw()
{
	tortoise.RenderImageWithMask(this->GetEngine()->GetForeground(), 0, 0, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, m_iDrawWidth, m_iDrawHeight);
	
	if (Tortoise_Object::hasSub == 1){
		subTortoise.RenderImageWithMask(this->GetEngine()->GetForeground(), 0, 0, Tortoise_Object::subX, subY, subTortoise.GetWidth(), subTortoise.GetHeight());
	}
	StoreLastScreenPositionForUndraw();
}


void Tortoise_Object::DoUpdate(int iCurrentTime)
{
	/*
		The movement of the subTortoise
	*/
	if (Tortoise_Object::hasSub == 1){
		Tortoise_Object::subX -= 3;
		if (Tortoise_Object::subX < 0){
			Tortoise_Object::hasSub = 0;
		}
	}
	/*
		Every 100 times of the loop, rand a new action for the tortoise
	*/
	if (action == 100){
		action = 0;
		randAction = rand() % 7;
		do{
			randAction = rand() % 7;
		} while (fly && randAction == 2);
		up = true;
		/*
			If the Mario shoot, the tortoise will have some possiblity to jump the bullet
		*/
		if (Tortoise_Object::wantJump != 0){
			randAction = 4;
			Tortoise_Object::wantJump = 0;
		}
		/*
			Add a sub Tortoise, 50% for a big subTortoise, 50% for a small subTortoise
		*/
		if (Tortoise_Object::hasSub == 0){
			Tortoise_Object::subX = m_iCurrentScreenX;
			Tortoise_Object::hasSub = 1;
			Tortoise_Object::canJump = rand()%2;
			Tortoise_Object::subOver = 0;
			if (Tortoise_Object::canJump == 1){
				subTortoise.ShrinkFrom(&subTortoise1, 8);
				subY = 360;
			}
			else{
				subTortoise.ShrinkFrom(&subTortoise1, 4);
				subY = 330;
			}
		}
	}
	switch (randAction)
	{
		case 0:moveLeft(); break;
		case 1:moveRight(); break;
		case 2:moveUp(); break;
		case 3:moveShake();break;
		case 4:moveFly();break;
		case 5:moveBig(); break;
		case 6:moveSmall(); break;
		default:
			break;
	}
	/*
		left is 0 means cannot move to left, 1 means must move to left, 2 means can move to right and left both
	*/
	if (m_iCurrentScreenX < 200){
		left = 0;
		direction = 1;
	}else if (m_iCurrentScreenX > 610){
		left = 1;
		direction = 0;
	}
	else{
		left = 2;
	}
	if (action > 46){
		up = false;
	}
	action++;
	RedrawObjects();
}

//rand 0 action
void Tortoise_Object::moveLeft(){
	direction = 0;
	if (size == 1){
		m_iCurrentScreenY = 150;
	}
	else{
		m_iCurrentScreenY = 270;
	}
	if (left != 0){
		m_iCurrentScreenX -= 3;
	}
	tortoise2.LoadImage("img/tortoise_left.png");
	tortoise.ShrinkFrom(&tortoise2, size);
}
//rand 1 action
void Tortoise_Object::moveRight(){
	direction = 1;
	if (size == 1){
		m_iCurrentScreenY = 150;
	}
	else{
		m_iCurrentScreenY = 270;
	}
	if (left != 1){
		m_iCurrentScreenX += 3;
	}
	tortoise2.LoadImage("img/tortoise_right.png");
	tortoise.ShrinkFrom(&tortoise2, size);
}
//rand 2 action
void Tortoise_Object::moveUp(){
	if (up){
		m_iCurrentScreenY -= 30;
	}
	else{
		m_iCurrentScreenY += 30;
	}
	action += 4;
}
//rand 3 action
void Tortoise_Object::moveShake(){
	if (rotate_val == 0){
		rotate_val = 1;
	}
	else{
		rotate_val = 0;
	}
	moveLeft();
}
//rand 4 action
void Tortoise_Object::moveFly(){
	fly = true;
	if (direction == 1){
		tortoise2.LoadImage("img/tortoise_flyright.png");
		tortoise.ShrinkFrom(&tortoise2, size);
		m_iCurrentScreenY = 40;
	}
	else{
		tortoise2.LoadImage("img/tortoise_flyleft.png");
		tortoise.ShrinkFrom(&tortoise2, size);
		m_iCurrentScreenY = 40;
	}
	if (direction == 1){
		m_iCurrentScreenX += 3;
	}
	else{
		m_iCurrentScreenX -= 3;
	}
}
//rand 5 action
void Tortoise_Object::moveBig(){
	tortoise.ShrinkFrom(&tortoise2, 1);
	m_iDrawHeight = tortoise.GetHeight();
	m_iDrawWidth = tortoise.GetWidth();
	m_iCurrentScreenY = 135;
	size = 1;
	moveUp();
}
//rand 6 action
void Tortoise_Object::moveSmall(){
	tortoise.ShrinkFrom(&tortoise2, 2);
	m_iDrawHeight = tortoise.GetHeight();
	m_iDrawWidth = tortoise.GetWidth();
	m_iCurrentScreenY = 255;
	size = 2;
	moveUp();
}
//rand 7 action
void Tortoise_Object::moveRocket()
{
	if (up){
		m_iCurrentScreenY -= 30;
	}
	else{
		m_iCurrentScreenY += 30;
	}
	action += 4;
}
