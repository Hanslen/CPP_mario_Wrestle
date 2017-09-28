#include "header.h"
#include "templates.h"
#include "Psyjc3_1Object.h"


Psyjc3_1Object::Psyjc3_1Object(BaseEngine* pEngine)
	:DisplayableObject(pEngine)
{
	// Current and previous coordinates for the object - set them the same initially
	m_iCurrentScreenX = m_iPreviousScreenX = 100;
	m_iCurrentScreenY = m_iPreviousScreenY = 100;
	// The object coordinate will be the top left of the object
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;
	// Record the ball size as both height and width
	m_iDrawWidth = 50;
	m_iDrawHeight = 50;
	// And make it visible
	SetVisible(true);
}


Psyjc3_1Object::~Psyjc3_1Object()
{
}


void Psyjc3_1Object::Draw(void)
{
	GetEngine()->DrawScreenOval(
		m_iCurrentScreenX, m_iCurrentScreenY,
		m_iCurrentScreenX + m_iDrawWidth - 1,
		m_iCurrentScreenY + m_iDrawHeight - 1,
		0x00ff00);
	// This will store the position at which the object was drawn
	// so that the background can be drawn over the top.
	// This will then remove the object from the screen.
	StoreLastScreenPositionForUndraw();
}


void Psyjc3_1Object::DoUpdate(int iCurrentTime)
{
	// Change position if player presses a key
	if (GetEngine()->IsKeyPressed(SDLK_w))
		m_iCurrentScreenY -= 2;
	if (GetEngine()->IsKeyPressed(SDLK_s))
		m_iCurrentScreenY += 2;
	if (GetEngine()->IsKeyPressed(SDLK_a))
		m_iCurrentScreenX -= 2;
	if (GetEngine()->IsKeyPressed(SDLK_d))
		m_iCurrentScreenX += 2;
	// Ensure that the object gets redrawn on the display, if something changed

	if (m_iCurrentScreenX < 0)
		m_iCurrentScreenX = 0;
	if (m_iCurrentScreenX >= GetEngine()->GetScreenWidth() - m_iDrawWidth)
		m_iCurrentScreenX = GetEngine()->GetScreenWidth() - m_iDrawWidth;
	if (m_iCurrentScreenY < 0)
		m_iCurrentScreenY = 0;
	if (m_iCurrentScreenY >= GetEngine()->GetScreenHeight() - m_iDrawHeight)
		m_iCurrentScreenY = GetEngine()->GetScreenHeight() - m_iDrawHeight;
	RedrawObjects();
}
