#include "header.h"
#include "templates.h"
#include "Mario_bulletObject.h"
#include "JPGImage.h"
#include "DemoAMain.h"
#include "Tortoise_Object.h"

/*
	This variable stands for whether Mario is a super hero or not, if it is 1, then its bullet 
	is superbullet which will contain more damage, else is just a common bullet.
*/
int Mario_bulletObject::superbullet = 0;
/*
	This class is the bullet class
*/
Mario_bulletObject::Mario_bulletObject(BaseEngine* pEngine, int x, int y, bool left)
	:DisplayableObject(pEngine),
	posX(x),
	posY(y),
	posLeft(left),
	over(0)
{
	m_iCurrentScreenX = m_iPreviousScreenX = posX+30;
	m_iCurrentScreenY = m_iPreviousScreenY = posY+20;

	m_iDrawHeight = 50;
	m_iDrawWidth = 50;

	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;
	explosion.LoadImage("img/explosion.png");
	if (posLeft){
		m_iCurrentScreenX -= 40;
		fireBullet2.LoadImage("img/fire_ball_left.png");
	}
	else{
		fireBullet2.LoadImage("img/fire_ball_right.png");
	}
	
	fireBullet.ShrinkFrom(&fireBullet2, 3);
	SetVisible(true);

}


Mario_bulletObject::~Mario_bulletObject()
{
}


void Mario_bulletObject::Draw()
{
	fireBullet.RenderImageWithMask(this->GetEngine()->GetForeground(), 0, 0, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, fireBullet.GetWidth(), fireBullet.GetHeight());
	StoreLastScreenPositionForUndraw();
}


void Mario_bulletObject::DoUpdate(int iCurrentTime)
{
	/*
		Determine the bullet will go left or right
	*/
	if (posLeft){
		m_iCurrentScreenX -= 6;
	}
	else{
		m_iCurrentScreenX += 6;
	}
	/*
		judge is the bullet attack the tortoise or not
	*/
	DisplayableObject* tortoise = this->GetEngine()->GetDisplayableObject(1);
	/*
		When it attacks the tortoise, it will change its image to a explosion image
	*/
	if ((m_iCurrentScreenX > tortoise->GetXCentre() - 50) && (tortoise->GetYCentre() == 279 || tortoise->GetYCentre() == 334)){
		fireBullet.ShrinkFrom(&explosion, 7);
	}
	/*
		The bullet has attacked the tortoise, and update the tortoise blood and remove that bullet
		from the screen
	*/
	if (m_iCurrentScreenX > tortoise->GetXCentre()){
		if (m_iCurrentScreenX != 1006 && over == 0){
			if (tortoise->GetYCentre() == 279 || tortoise->GetYCentre() == 334){
				DisplayableObject* tortoiseBlood = this->GetEngine()->GetDisplayableObject(3);
				if (DemoAMain::winner == -1){
					tortoiseBlood->DoUpdate(10);
				}

				DemoAMain::score += 10;
				m_iCurrentScreenX = 1000;
			}
			over = 1;
		}
	}
	
	/*
		If the bullet attacks the subTortoise which is big(means the bullet can shoot it)
	*/
	if (Tortoise_Object::hasSub == 1 && Tortoise_Object::canJump == 0){
		if (m_iCurrentScreenX > (Tortoise_Object::subX - 50)){
			fireBullet.ShrinkFrom(&explosion, 7);
		}
		if (m_iCurrentScreenX > Tortoise_Object::subX){
			if (m_iCurrentScreenX < 1000){
				Tortoise_Object::hasSub = 0;
			}
			m_iCurrentScreenX = 1000;
		}
	}
	RedrawObjects();
}


int Mario_bulletObject::getPosX()
{
	return m_iCurrentScreenX;
}
