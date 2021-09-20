/*
 * CApp.cpp
 *
 *  Created on: 13 sept. 2021
 *      Author: eleve
 */

#include <iostream>
#include <cstdio>
#include <ctime>

using namespace std;

#include <macros.h>
#include <parameters.h>

#include "CApp.h"

enum e_status_flags{
	ST_ALL_CLEARED		= 0x00000000,
	ST_SDL_INITIATED	= 0x00000001,
	ST_TTF_INITIATED	= 0x00000002,
	ST_APP_INIT_FAILED	= 0x80000000,
	ST_APP_PAUSED		= 0x00000100,
	ST_APP_GAMEOVER		= 0x00001000,
};

Uint32 CApp::_AppTimerTimeCallback(Uint32 interval, CApp* pApp){
	if(mIsBitsSet(pApp->m_uStatus, ST_APP_PAUSED) || mIsBitsSet(pApp->m_uStatus, ST_APP_GAMEOVER))
			return interval;

	while(pApp->m_pTexts->Card()>5){
		delete ((CText*)pApp->m_pTexts->Popfront());
	}
	pApp->m_iTime+= interval/1000;
	return interval;
}


Uint32 CApp::_AppTimerAnimateCallback(Uint32 interval, CApp* pApp){
	if(mIsBitsSet(pApp->m_uStatus, ST_APP_PAUSED) || mIsBitsSet(pApp->m_uStatus, ST_APP_GAMEOVER))
			return interval;

	static SDL_Rect rGameArea = {
			APP_WINDOW_PADDING-1,
			APP_WINDOW_PADDING-1,
			(SNAKE_POS_MAX_X)*(SNAKE_SECTION_SIZE+SNAKE_SECTION_SPACING)+1,
			(SNAKE_POS_MAX_Y)*(SNAKE_SECTION_SIZE+SNAKE_SECTION_SPACING)+1};
	
	// --- GAME AREA DRAWING --- //
//	SDL_SetRenderDrawColor(pApp->m_pRenderer, pApp->m_colBkgnd.r, pApp->m_colBkgnd.g, pApp->m_colBkgnd.b, pApp->m_colBkgnd.a);
//	SDL_RenderClear(pApp->m_pRenderer);
	 SDL_RenderCopy(pApp->m_pRenderer, pApp->m_pBGTexture, nullptr, &SDL_Rect{0,0,1920,1080});
	 SDL_SetRenderDrawColor(pApp->m_pRenderer, 255, 255, 255, 255);
	 SDL_RenderDrawRect(pApp->m_pRenderer, &rGameArea);


	// // --- SCORE RENDERING --- //
	char buf[64];
	sprintf(buf,"%04d",pApp->m_iScore);
	pApp->m_pTexts->Pushback(new CText(pApp->m_pRenderer, SDL_Point{APP_WINDOW_PADDING, 5}, buf));

	sprintf(buf,"%04d",pApp->m_iTime);
	pApp->m_pTexts->Pushback(new CText(pApp->m_pRenderer, SDL_Point{APP_WINDOW_PADDING+(SNAKE_POS_MAX_X)*(SNAKE_SECTION_SIZE+SNAKE_SECTION_SPACING)-100,5}, buf));
	if(pApp->m_pTexts->Getback())((CText*)pApp->m_pTexts->Getback())->Draw(pApp->m_pRenderer);

	// --- SNAKE LOGIC --- //
	if(pApp->m_pSnake)pApp->m_pSnake->Draw(pApp->m_pRenderer); //test
	if(pApp->m_pSnake)pApp->m_pSnake->Move();

	// --- FOOD LOGIC--- //
	if(!pApp->m_iSnakeFoodTimeout){
		pApp->m_ptSnakeFoodLoc = SDL_Point{rand()%SNAKE_POS_MAX_X, rand()%SNAKE_POS_MAX_Y};
		pApp->m_iSnakeFoodTimeout = 10+rand()%40+1;
	}

	if(pApp->m_ptSnakeFoodLoc.x==-1)pApp->m_iSnakeFoodTimeout--;
	else {
		SDL_RenderCopy(pApp->m_pRenderer, pApp->m_pFoodTexture, nullptr,
				&(SDL_Rect){
						APP_WINDOW_PADDING+pApp->m_ptSnakeFoodLoc.x*(SNAKE_SECTION_SIZE+SNAKE_SECTION_SPACING)+SNAKE_FOOD_PADDING,
						APP_WINDOW_PADDING+pApp->m_ptSnakeFoodLoc.y*(SNAKE_SECTION_SIZE+SNAKE_SECTION_SPACING)+SNAKE_FOOD_PADDING,
						SNAKE_FOOD_SIZE,
						SNAKE_FOOD_SIZE}
		);
	}

	// --- FOOD DETECTION --- //
	if (pApp->m_pSnake->IsFoodDetected(pApp->m_ptSnakeFoodLoc)){
		pApp->m_pSnake->GrowUp();
		pApp->m_pSound->CollectPlay();
		pApp->m_ptSnakeFoodLoc = SDL_Point{-1,-1};
		pApp->m_iScore += 50;
	}

	// --- POISON LOGIC --- //
	if(!pApp->m_iSnakePoisonTimeout){
		pApp->m_ptSnakePoisonLoc = SDL_Point{rand()%SNAKE_POS_MAX_X, rand()%SNAKE_POS_MAX_Y};
		pApp->m_iSnakePoisonTimeout = 40+rand()%80+1;
	}

	if(pApp->m_ptSnakePoisonLoc.x==-1)pApp->m_iSnakePoisonTimeout--;
	else {
		SDL_RenderCopy(pApp->m_pRenderer, pApp->m_pPoisonTexture, nullptr,
						&(SDL_Rect){
								APP_WINDOW_PADDING+pApp->m_ptSnakePoisonLoc.x*(SNAKE_SECTION_SIZE+SNAKE_SECTION_SPACING)+SNAKE_FOOD_PADDING,
								APP_WINDOW_PADDING+pApp->m_ptSnakePoisonLoc.y*(SNAKE_SECTION_SIZE+SNAKE_SECTION_SPACING)+SNAKE_FOOD_PADDING,
								SNAKE_FOOD_SIZE,
								SNAKE_FOOD_SIZE}
		);
	}

	// --- POISON DETECTION --- //
	if (pApp->m_pSnake->IsFoodDetected(pApp->m_ptSnakePoisonLoc)){
		pApp->m_pSnake->Shrink();
		pApp->m_pSound->PoisonPlay();
		pApp->m_ptSnakePoisonLoc = SDL_Point{-1,-1};
		pApp->m_iScore -= 50;
	}

	// --- SELF-BITING DETECTION --- //

	if(pApp->m_pSnake->IsBiteHimself()){
		mBitsSet(pApp->m_uStatus, ST_APP_GAMEOVER);
	}
	// --- RENDERING --- //
	SDL_RenderPresent(pApp->m_pRenderer);
	return interval;
}


CApp::CApp():
	m_uStatus(ST_ALL_CLEARED),
	m_iTime(0),
	m_ptSnakeFoodLoc(SDL_Point{-1,-1}),
	m_ptSnakePoisonLoc(SDL_Point{-1,-1}),
	m_iSnakeFoodTimeout(0),
	m_iSnakePoisonTimeout(0),
	m_iScore(0){
	srand((unsigned int)time(nullptr));

	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_GAMECONTROLLER)){
		cerr << "SDL Initialization failed: " << SDL_GetError() << endl;
		mBitsSet(m_uStatus, ST_APP_INIT_FAILED);
	}

	m_pWindow = SDL_CreateWindow("The Snake Game but it's C++", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, APP_WINDOW_WIDTH, APP_WINDOW_HEIGHT, 0);
	if(!m_pWindow){
		cerr << "SDL CreateWindow() failed: " << SDL_GetError() << endl;
		mBitsSet(m_uStatus, ST_APP_INIT_FAILED);
	}

	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);
	if(!m_pRenderer){
		cerr << "SDL Hardware CreateRenderer() failed, resorting to creating a software renderer" << endl;
		m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_SOFTWARE);
		if(!m_pRenderer){
			cerr << "SDL Software CreateRenderer() failed: " << SDL_GetError() << endl;
			mBitsSet(m_uStatus, ST_APP_INIT_FAILED);
		}
	}
	mBitsSet(m_uStatus, ST_SDL_INITIATED);
	TTF_Init();
	m_pFont = TTF_OpenFont(APP_MAIN_FONT_FILE_NAME, 20);
	if(m_pFont==nullptr){
			cerr << "TTF failed to load font file: " <<  SDL_GetError() << endl;
			mBitsSet(m_uStatus, ST_APP_INIT_FAILED);
	}
	else
		mBitsSet(m_uStatus, ST_TTF_INITIATED);

	m_colBkgnd 	= APP_WINDOW_COLOR_BKGND;
	m_colLimits = APP_WINDOW_COLOR_LIMITS;

	m_pFoodTexture 		= IMG_LoadTexture(m_pRenderer, APP_FOOD_APPLE_PATH);
	m_pPoisonTexture	= IMG_LoadTexture(m_pRenderer, APP_FOOD_POISON_PATH);
	m_pBGTexture		= IMG_LoadTexture(m_pRenderer, APP_DEFAULT_BG_PATH);
	SDL_GameControllerOpen(0);
	CSnake::InitGraph(m_pRenderer, APP_SNAKE_HEAD_PATH, APP_SNAKE_BODY_PATH, APP_SNAKE_TAIL_PATH);
	CText::InitGraph(APP_MAIN_FONT_FILE_NAME, SDL_Color{0xFF, 0xFF, 0xFF, 0xFF}, 40);

	Run();

}

CApp::~CApp() {
	CText::ReleaseGraph();
	CSnake::ReleaseGraph();

	SDL_RemoveTimer(m_iTimerIDtimer);
	SDL_RemoveTimer(m_iTimerIDanimate);

	if(m_pTexts)delete m_pTexts;
	if(m_pSound)delete m_pSound;
	if(m_pSnake)delete m_pSnake;

	SDL_DestroyTexture(m_pBGTexture);
	SDL_DestroyTexture(m_pPoisonTexture);
	SDL_DestroyTexture(m_pFoodTexture);

	if(m_pFont)TTF_CloseFont(m_pFont);
	if(m_pRenderer)SDL_DestroyRenderer(m_pRenderer);
	if(m_pWindow)SDL_DestroyWindow(m_pWindow);

	TTF_Quit();
	SDL_Quit();
}

int CApp::Run(){
	if(mIsBitsSet(m_uStatus, ST_APP_INIT_FAILED))
		return m_uStatus;

	SDL_Event	event;
	int 		quit = 0;

	m_pSnake			= new CSnake();
	m_pSound			= new CSound();
	m_pTexts			= new CContainer((t_ptfV)CText::DeleteFunc);

	m_iTimerIDanimate = SDL_AddTimer(APP_TIMER_TICK_MS, (SDL_TimerCallback)_AppTimerAnimateCallback , this);
	m_iTimerIDtimer   = SDL_AddTimer(1000, (SDL_TimerCallback)_AppTimerTimeCallback, this);

	while(!quit){
		while(SDL_PollEvent(&event)){
			switch(event.type){
			case SDL_CONTROLLERBUTTONDOWN:
				switch(event.cbutton.button){
				case SDL_CONTROLLER_BUTTON_BACK:
					quit = 1;
					break;
				case SDL_CONTROLLER_BUTTON_DPAD_UP:
					m_pSnake->ChangeDirection(DIR_UP);
					break;
				case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
					m_pSnake->ChangeDirection(DIR_DOWN);
					break;
				case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
					m_pSnake->ChangeDirection(DIR_LEFT);
					break;
				case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
					m_pSnake->ChangeDirection(DIR_RIGHT);
					break;
				case SDL_CONTROLLER_BUTTON_START:
					if(mIsBitsClr(m_uStatus, ST_APP_PAUSED)){
						m_pSound->MusicPause();
						mBitsSet(m_uStatus, ST_APP_PAUSED);
						m_pSound->PausePlay();
					}
					else {
						m_pSound->MusicPlay();
						mBitsClr(m_uStatus, ST_APP_PAUSED);
						m_pSound->PausePlay();
					}
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}
	}
	return m_uStatus;
}

