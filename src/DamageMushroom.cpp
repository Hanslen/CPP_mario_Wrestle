#include "header.h"
#include "templates.h"
#include "DamageMushroom.h"
#include "Mario_Object.h"
#include "JPGImage.h"
#include "DemoAMain.h"

/*
	This class is the mushroom contains power, if it is eaten by Mario, the Mario will
	become super hero, and the damage of attack will increase.
*/
DamageMushroom::DamageMushroom(BaseEngine* pEngine)
	:DisplayableObject(pEngine),
	mushRoomOver(0)
{
	mushroom1.LoadImage("img/mushroom.png");
	mushroom.ShrinkFrom(&mushroom1, 18);

	m_iCurrentScreenX = m_iPreviousScreenX = 400;
	m_iCurrentScreenY = m_iPreviousScreenY = 150;

	m_iDrawHeight = mushroom.GetHeight();
	m_iDrawWidth = mushroom.GetWidth();

	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;
}


DamageMushroom::~DamageMushroom()
{
}

void DamageMushroom::Draw()
{
	mushroom.RenderImageWithMask(this->GetEngine()->GetForeground(), 0, 0, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, m_iDrawWidth, m_iDrawHeight);
	StoreLastScreenPositionForUndraw();
}

void DamageMushroom::DoUpdate(int iCurrentTime)
{
	/*
		Check if the mushroom need to fall down or move from right to left.
	*/
	if (m_iCurrentScreenY < 348){
		m_iCurrentScreenY += 4;
	}
	if (m_iCurrentScreenY == 350){
		m_iCurrentScreenX -= 3;
	}

	/*
		Check Can Mario eat the mushroom or not.
	*/
	DisplayableObject* mario = this->GetEngine()->GetDisplayableObject(0);
	if (mario->GetXCentre() > GetXCentre() + 8 && mario->GetXCentre() < GetXCentre() + 18){

		/*
			Is Mario eats the mushroom or jump the mushroom
		*/
		if (mario->GetYCentre() == 365 && mushRoomOver == 0){
			m_iCurrentScreenX = -100;
			m_iCurrentScreenY = 300;
			mario->DoUpdate(100);
		}
		else{
			mushRoomOver = 1;
		}
	}
	RedrawObjects();
}