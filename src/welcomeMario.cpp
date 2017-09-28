#include "header.h"
#include "templates.h"
#include "welcomeMario.h"
#include "JPGImage.h"

/*
	This class is for the driving Mario
*/
welcomeMario::welcomeMario(BaseEngine* pEngine)
	: DisplayableObject(pEngine),
	right(1)
{
	drive.LoadImage("img/drive.png");
	m_iCurrentScreenX = m_iPreviousScreenX = 20;
	m_iCurrentScreenY = m_iPreviousScreenY = 500;

	m_iDrawHeight = drive.GetHeight();
	m_iDrawWidth = drive.GetWidth();

	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;
	SetVisible(true);
}


welcomeMario::~welcomeMario()
{
}

void welcomeMario::Draw()
{
	drive.RenderImageWithMask(this->GetEngine()->GetForeground(), 0, 0, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, m_iDrawWidth, m_iDrawHeight);

	StoreLastScreenPositionForUndraw();
}


void welcomeMario::DoUpdate(int iCurrentTime)
{
	/*
		Driving Mario always move from left to right and then from right to left
	*/
	if (right == 1){
		drive.LoadImage("img/drive.png");
		m_iCurrentScreenX += 1;
		if (m_iCurrentScreenX > 710){
			right = 0;
		}
	}
	else{
		drive.LoadImage("img/driveleft.png");
		m_iCurrentScreenX -= 1;
		if (m_iCurrentScreenX < 0){
			right = 1;
		}
	}
	RedrawObjects();
}
