#include "header.h"
#include "templates.h"
#include "Mario_Object.h"
#include "JPGImage.h"
#include "Mario_bulletObject.h"
#include "Tortoise_Object.h"
#include "DemoAMain.h"

/*
	This class stands for the Mario Object
*/
Mario_Object::Mario_Object(BaseEngine* pEngine)
	:DisplayableObject(pEngine)
	, left(false)
	, jump(false),
	super(0)
{
	m_iCurrentScreenX = m_iPreviousScreenX = 120;
	m_iCurrentScreenY = m_iPreviousScreenY = 330;

	m_iDrawHeight = 70;
	m_iDrawWidth = 70;

	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;

	marioB.LoadImage("img/mario_right.png");
	mario.ShrinkFrom(&marioB,4);
	bullet = 0;
	SetVisible(true);
}


Mario_Object::~Mario_Object()
{
}


void Mario_Object::Draw()
{
	mario.RenderImageWithMask(this->GetEngine()->GetForeground(), 0, 0, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, mario.GetWidth(), mario.GetHeight());
	StoreLastScreenPositionForUndraw();
	
}



void Mario_Object::DoUpdate(int iCurrentTime)
{
	/*
		When the subtortoise hit the mario
	*/
	if ((Tortoise_Object::subX + 10 < m_iCurrentScreenX && Tortoise_Object::subX > 0 && Tortoise_Object::canJump == 0) || (Tortoise_Object::subX < m_iCurrentScreenX && Tortoise_Object::subX > 0 && Tortoise_Object::canJump == 1)){
		/*
			Judge if the sub-tortoise jumped by the Mario or attack Mario
		*/
		if (m_iCurrentScreenY == 330 && Tortoise_Object::subOver == 0){
			Tortoise_Object::subX = -100;
			DisplayableObject* marioBlood = this->GetEngine()->GetDisplayableObject(2);
			if (marioBlood != NULL){
				marioBlood->DoUpdate(20);
			}

			Tortoise_Object::hasSub = 0;
		}
		else{
			Tortoise_Object::subOver = 1;
		}
	}
	/*
		If Mario touch Tortoise, it dies
	*/
	DisplayableObject* tortoise = this->GetEngine()->GetDisplayableObject(1);
	if (tortoise != NULL){
		if (tortoise->GetXCentre() < m_iCurrentScreenX){
			DisplayableObject* marioBlood = this->GetEngine()->GetDisplayableObject(2);
			for (int i = 0; i < 10; i++){
				marioBlood->DoUpdate(20);
			}
		}
	}
	/*
		Mario becomes the super hero
	*/
	if (iCurrentTime == 100){
		marioB.LoadImage("img/super.png");
		mario.ShrinkFrom(&marioB, 3);
		super = 1;
		Mario_bulletObject::superbullet = 1;
	}
	/*
		Mario falls down
	*/
	if (m_iCurrentScreenY < 330 && m_iCurrentScreenY > 180 && jump){
		m_iCurrentScreenY -= 5;
		RedrawObjects();
	}
	else if(jump){
		/*
			Mario fall image changes
		*/
		jump = false;
		if (left){
			if (super == 0){
				marioB.LoadImage("img/mario_left.png");
				mario.ShrinkFrom(&marioB, 4);
			}
			else{
				marioB.LoadImage("img/superleft.png");
				mario.ShrinkFrom(&marioB, 3);
			}
		}
		else{
			if (super == 0){
				marioB.LoadImage("img/mario_right.png");
				mario.ShrinkFrom(&marioB, 4);
			}
			else{
				marioB.LoadImage("img/super.png");
				mario.ShrinkFrom(&marioB, 3);
			}
		}
		m_iCurrentScreenY = 241;
		RedrawObjects();
	}
	/*
		Mario jump
	*/
	if (m_iCurrentScreenY < 330 && m_iCurrentScreenY > 180 && jump == false){
		m_iCurrentScreenY += 5;
		RedrawObjects();
	}
	else if (jump == false){
		m_iCurrentScreenY = 330;
	}
	/*
		Set Mario jump action
	*/
	if (GetEngine()->IsKeyPressed(SDLK_w)&&m_iCurrentScreenY == 330){
		jump = true;
		if (left){
			if (super == 0){
				marioB.LoadImage("img/mario_jump_left.png");
				mario.ShrinkFrom(&marioB, 4);
			}
			else{
				marioB.LoadImage("img/super_jump_left.png");
				mario.ShrinkFrom(&marioB, 3);
			}
		}
		else{
			if (super == 0){
				marioB.LoadImage("img/mario_jump_right.png");
				mario.ShrinkFrom(&marioB, 4);
			}
			else{
				marioB.LoadImage("img/super_jump_right.png");
				mario.ShrinkFrom(&marioB, 3);

			}
		}
		m_iCurrentScreenY -= 20;
		RedrawObjects();
	}
	/*
		Mario moves from right to left
	*/
	if (GetEngine()->IsKeyPressed(SDLK_a)){
		left = true;
		if (super == 0){
			marioB.LoadImage("img/mario_left.png");
			mario.ShrinkFrom(&marioB, 4);
		}
		else{
			marioB.LoadImage("img/superleft.png");
			mario.ShrinkFrom(&marioB, 3);
		}
		m_iCurrentScreenX -= 2;
	}
	/*
		Mario moves from left to right
	*/
	if (GetEngine()->IsKeyPressed(SDLK_d)){
		left = false;
		if (super == 0){
			marioB.LoadImage("img/mario_right.png");
			mario.ShrinkFrom(&marioB, 4);
		}
		else{
			marioB.LoadImage("img/super.png");
			mario.ShrinkFrom(&marioB, 3);
		}
		m_iCurrentScreenX += 2;
	}
	/*
		Mario shoots, the Mario can only contains seven bullets at same time.
	*/
	if (GetEngine()->IsKeyPressed(SDLK_j)){
		int jumpOrNot = rand() % 2;
		if (jumpOrNot == 1){
			Tortoise_Object::wantJump = 1;
		}
		if (DemoAMain::state_init != 4){
			bullet += 1;
			if (bullet > 1){
				DisplayableObject* previous = this->GetEngine()->GetDisplayableObject(bullet + 3);
				if (previous->GetXCentre() > m_iCurrentScreenX + 100){
					this->GetEngine()->StoreObjectInArray(bullet + 4, new Mario_bulletObject(this->GetEngine(), m_iCurrentScreenX, m_iCurrentScreenY, left));
					bullet += 1;
				}
				else if (previous->GetXCentre() < 0){
					this->GetEngine()->StoreObjectInArray(bullet + 4, new Mario_bulletObject(this->GetEngine(), m_iCurrentScreenX, m_iCurrentScreenY, left));
					bullet += 1;
				}
			}
			else{
				this->GetEngine()->StoreObjectInArray(bullet + 4, new Mario_bulletObject(this->GetEngine(), m_iCurrentScreenX, m_iCurrentScreenY, left));
				bullet += 1;
			}
			bullet -= 1;
			/*
				If it is the last bullet, we need to re-assign the first one
			*/
			if (bullet == 7){
				bullet = 0;
			}
		}
	}
	
	/*
		Check Mario bounds
	*/
	if (m_iCurrentScreenX < 0){
		m_iCurrentScreenX = 0;
	}
	if (m_iCurrentScreenX >= GetEngine()->GetScreenWidth() - m_iDrawWidth){
		m_iCurrentScreenX = GetEngine()->GetScreenWidth() - m_iDrawWidth;
	}
	if (m_iCurrentScreenY < 0){
		m_iCurrentScreenY = 0;
	}
	if (m_iCurrentScreenY >= GetEngine()->GetScreenHeight() - m_iDrawHeight){
		m_iCurrentScreenY = GetEngine()->GetScreenHeight() - m_iDrawHeight;
	}
	RedrawWholeScreen();
}

void KeyDown(int iKeyCode){
	//printf("You press somenthing!!");
}

