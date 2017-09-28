#include "header.h"
#include "templates.h"
#include "SelectMashroom.h"
#include "JPGImage.h"
#include "DemoAMain.h"

/*
	This class is the welcome page select Mushroom
*/
SelectMashroom::SelectMashroom(BaseEngine* pEngine)
	:DisplayableObject(pEngine),
	mushRoompos(1)
{
	mushroom1.LoadImage("img/mushroom.png");
	mushroom.ShrinkFrom(&mushroom1, 18);

	m_iCurrentScreenX = m_iPreviousScreenX = 400;
	m_iCurrentScreenY = m_iPreviousScreenY = 220;

	m_iDrawHeight = mushroom.GetHeight();
	m_iDrawWidth = mushroom.GetWidth();

	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;
}


SelectMashroom::~SelectMashroom()
{

}


void SelectMashroom::Draw()
{
	mushroom.RenderImageWithMask(this->GetEngine()->GetForeground(), 0, 0, m_iCurrentScreenX+m_iStartDrawPosX, m_iCurrentScreenY+m_iStartDrawPosY, m_iDrawWidth, m_iDrawHeight);
	StoreLastScreenPositionForUndraw();
}



void SelectMashroom::DoUpdate(int iCurrentTime)
{
	/*
		Select down
	*/
	if (GetEngine()->IsKeyPressed(SDLK_DOWN) && m_iCurrentScreenY != 330){
		m_iCurrentScreenY += 55;
		mushRoompos += 1;
		DemoAMain::state_init = mushRoompos;
		_sleep(200);
	}
	else if (GetEngine()->IsKeyPressed(SDLK_UP) && m_iCurrentScreenY != 220){
		/*
			Select Up
		*/
		m_iCurrentScreenY -= 55;
		mushRoompos -= 1;
		DemoAMain::state_init = mushRoompos;
		_sleep(200);
	}
	else if(GetEngine()->IsKeyPressed(SDLK_RETURN)){
		/*
			confirm the choice
		*/
		DemoAMain::state_init = mushRoompos;
		_sleep(200);
	}
	RedrawObjects();
}
