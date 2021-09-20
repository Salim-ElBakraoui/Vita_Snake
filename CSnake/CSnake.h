/*
 * CSnake.h
 *
 *  Created on: 13 sept. 2021
 *      Author: eleve
 */
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <parameters.h>

enum e_direction{
	DIR_NONE = 0,
	DIR_LEFT,
	DIR_RIGHT,
	DIR_UP,
	DIR_DOWN,
};

class CSnake {
private:
	static SDL_Texture*	c_pTextureHead;
	static SDL_Texture* c_pTextureBody;
	static SDL_Texture* c_pTextureTail;
private:
	class CSection{
	public:
		CSection*		m_pPrev;
		CSection*		m_pNext;
		unsigned int 	m_uDirection;
		int				m_iPosX, m_iPosY;
	public:
		CSection(CSection* pPrev, CSection* pNext, unsigned int uDirection, int iPosX, int iPosY);
		~CSection();
	};
private:
	CSection*	m_pHead;
	CSection*	m_pTail;
	int			m_uNbSection;
	SDL_Color	m_colHead;
	SDL_Color	m_colTail;
	SDL_Color	m_colBody;
public:
	CSnake();
	~CSnake();
	void Draw(SDL_Renderer* pRenderer);
	void Move();
	int  ChangeDirection(unsigned int uDirection);
	void GrowUp();
	void Shrink();
	int	 IsOnCell(int iPosX, int iPosY);
	int  IsFoodDetected(SDL_Point ptFoodCell);
	int	 IsBiteHimself();
	static void InitGraph(SDL_Renderer* pRenderer, char* sTexHeadFileStr, char* sTexBodyFileStr, char* sTexTailFileStr);
	static void ReleaseGraph();


};
