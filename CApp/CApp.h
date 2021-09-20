/*
 * CApp.h
 *
 *  Created on: 13 sept. 2021
 *      Author: eleve
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <random>

#include <CSnake.h>
#include <CSound.h>
#include <CContainer.h>
#include <CText.h>


#define VITA

#ifdef COMPUTER
	#define APP_SNAKE_HEAD_PATH	"Resources/Snake/texHead.png"
	#define APP_SNAKE_BODY_PATH	"Resources/Snake/texBody.png"
	#define APP_SNAKE_TAIL_PATH "Resources/Snake/texTail.png"

	#define APP_FOOD_APPLE_PATH		"Resources/Food/apple.png"
	#define APP_FOOD_POISON_PATH 	"Resources/Food/poison.png"

	#define APP_DEFAULT_BG_PATH		"Resources/App/bg.jpg"
#endif //ifdef COMPUTER

#ifdef VITA
	#define APP_SNAKE_HEAD_PATH		"app0://Resources/Snake/texHead.png"
	#define APP_SNAKE_BODY_PATH		"app0://Resources/Snake/texBody.png"
	#define APP_SNAKE_TAIL_PATH 	"app0://Resources/Snake/texTail.png"

	#define APP_FOOD_APPLE_PATH	 	"app0://Resources/Food/apple.png"
	#define APP_FOOD_POISON_PATH 	"app0://Resources/Food/poison.png"

	#define APP_DEFAULT_BG_PATH		"app0://Resources/App/bg.jpg"
#endif //ifdef VITA

class CApp {
private:
	SDL_Window*		m_pWindow;
	SDL_Renderer*	m_pRenderer;

	SDL_Color		m_colBkgnd;
	SDL_Color		m_colLimits;

	SDL_TimerID		m_iTimerIDanimate;
	SDL_TimerID		m_iTimerIDtimer;

	SDL_Point		m_ptSnakeFoodLoc;
	SDL_Point		m_ptSnakePoisonLoc;

	TTF_Font*		m_pFont;

	CSnake*			m_pSnake;

	CContainer*		m_pScoreTexts;
	CContainer*		m_pTimerTexts;

	int				m_iSnakeFoodTimeout, m_iSnakePoisonTimeout;

	SDL_Texture*	m_pFoodTexture;
	SDL_Texture*	m_pPoisonTexture;
	SDL_Texture*	m_pBGTexture;
	SDL_Texture*	m_pTextGameover;
	SDL_Texture*	m_pTextPaused;


	SDL_Rect		m_rTextGameover;
	SDL_Rect		m_rTextPaused;
	
	CSound*			m_pSound;

	unsigned int	m_uStatus;
	int				m_iTime, m_iScore;
public:
	CApp();
	~CApp();
	int Run();
private:
	static Uint32 _AppTimerAnimateCallback(Uint32 interval, CApp* pApp);
	static Uint32 _AppTimerTimeCallback(Uint32 interval, CApp* pApp);
};

