/*
 * CSnake.cpp
 *
 *  Created on: 13 sept. 2021
 *      Author: eleve
 */

#include <cassert>
#include <iostream>
using namespace std;

#include "CSnake.h"

SDL_Texture* CSnake::c_pTextureHead = nullptr;
SDL_Texture* CSnake::c_pTextureBody = nullptr;
SDL_Texture* CSnake::c_pTextureTail = nullptr;

void CSnake::InitGraph(SDL_Renderer* pRenderer, char* sTexHeadFileStr, char* sTexBodyFileStr, char* sTexTailFileStr){
	c_pTextureHead = IMG_LoadTexture(pRenderer, sTexHeadFileStr);
	c_pTextureBody = IMG_LoadTexture(pRenderer, sTexBodyFileStr);
	c_pTextureTail = IMG_LoadTexture(pRenderer, sTexTailFileStr);

}

void CSnake::ReleaseGraph(){
	if(c_pTextureTail)SDL_DestroyTexture(c_pTextureTail);
	if(c_pTextureBody)SDL_DestroyTexture(c_pTextureBody);
	if(c_pTextureHead)SDL_DestroyTexture(c_pTextureHead);
}

CSnake::CSection::CSection(CSection* pPrev, CSection* pNext, unsigned int uDirection, int iPosX, int iPosY){
	m_pPrev = pPrev;
	if(m_pPrev)m_pPrev->m_pNext = this;

	m_pNext = pNext;
	if(m_pNext)m_pNext->m_pPrev = this;

	if(m_pPrev && m_uDirection==DIR_NONE)m_uDirection = m_pPrev->m_uDirection;
	else m_uDirection = uDirection;
	m_iPosX = iPosX;
	m_iPosY = iPosY;
}

CSnake::CSection::~CSection(){
	if(m_pNext)m_pNext->m_pPrev = m_pPrev;
	if(m_pPrev)m_pPrev->m_pNext = m_pNext;
}


CSnake::CSnake() {
	m_uNbSection = 0;

	m_pHead = m_pTail = new CSnake::CSection(nullptr, nullptr, DIR_RIGHT, SNAKE_POS_INITIAL_X, SNAKE_POS_INITIAL_Y);
	m_uNbSection++;

	m_colHead = SNAKE_HEAD_COLOR;
	m_colBody = SNAKE_BODY_COLOR;
	m_colTail = SNAKE_TAIL_COLOR;

	for(int k=0; k<SNAKE_INITIAL_LENGTH-1; k++)
		GrowUp();
}

CSnake::~CSnake() {
	CSnake::CSection* pCache = m_pHead;
	while(m_pHead){
		m_pHead = m_pHead->m_pNext;
		delete pCache;
		if(m_pHead)pCache = m_pHead;
		m_uNbSection--;
	}
}

void CSnake::GrowUp(){
	assert(m_pHead!=NULL);
	assert(m_pTail!=NULL);
	assert(m_uNbSection!=0);

	switch(m_pTail->m_uDirection){
	case DIR_UP:
		m_pTail=new CSnake::CSection(m_pTail, NULL, DIR_UP, m_pTail->m_iPosX, m_pTail->m_iPosY+1);
		m_uNbSection++;
		break;
	case DIR_DOWN:
		m_pTail=new CSnake::CSection(m_pTail, NULL, DIR_DOWN, m_pTail->m_iPosX, m_pTail->m_iPosY-1);
		m_uNbSection++;
		break;
	case DIR_LEFT:
		m_pTail=new CSnake::CSection(m_pTail, NULL, DIR_LEFT, m_pTail->m_iPosX+1, m_pTail->m_iPosY);
		m_uNbSection++;
		break;
	case DIR_RIGHT:
		m_pTail=new CSnake::CSection(m_pTail, NULL, DIR_RIGHT, m_pTail->m_iPosX-1, m_pTail->m_iPosY);
		m_uNbSection++;
		break;
	case DIR_NONE:
		m_pTail=new CSnake::CSection(m_pTail, NULL, DIR_NONE, m_pTail->m_iPosX-1, m_pTail->m_iPosY);
		m_uNbSection++;
		break;
	default:
		break;
	}
}

void CSnake::Draw(SDL_Renderer* pRenderer){
	CSection* pScan = m_pHead;

		while(pScan){
			SDL_Rect rSnake{
							APP_WINDOW_PADDING+(pScan->m_iPosX*(SNAKE_SECTION_SIZE+SNAKE_SECTION_SPACING)),
							APP_WINDOW_PADDING+(pScan->m_iPosY*(SNAKE_SECTION_SIZE+SNAKE_SECTION_SPACING)),
							SNAKE_SECTION_SIZE,
							SNAKE_SECTION_SIZE};

			if(!pScan->m_pPrev)
				SDL_RenderCopy(pRenderer, c_pTextureHead, nullptr, &rSnake);
			else if(!pScan->m_pNext)
				SDL_RenderCopy(pRenderer, c_pTextureTail, nullptr, &rSnake);
			else
				SDL_RenderCopy(pRenderer, c_pTextureBody, nullptr, &rSnake);

			pScan=pScan->m_pNext;
		}
}

void CSnake::Move(){
	CSection *pScan=m_pHead;
	while(pScan){
		switch (pScan->m_uDirection) {
		case DIR_LEFT:
			if (pScan->m_iPosX>0)pScan->m_iPosX --;
			else pScan->m_iPosX = SNAKE_POS_MAX_X-1;
			break;
		case DIR_RIGHT:
			if (pScan->m_iPosX+1<SNAKE_POS_MAX_X)pScan->m_iPosX ++;
			else pScan->m_iPosX = SNAKE_POS_MIN_X;
			break;
		case DIR_UP:
			if (pScan->m_iPosY>0)pScan->m_iPosY --;
			else pScan->m_iPosY = SNAKE_POS_MAX_Y-1;
			break;
		case DIR_DOWN:
			if (pScan->m_iPosY+1<SNAKE_POS_MAX_Y)pScan->m_iPosY ++;
			else pScan->m_iPosY = SNAKE_POS_MIN_Y;
			break;
		case DIR_NONE:
		default:
			break;
		}
		pScan=pScan->m_pNext;
	}
	pScan=m_pTail;
	while(pScan && pScan->m_pPrev){
		pScan->m_uDirection = pScan->m_pPrev->m_uDirection;
		pScan=pScan->m_pPrev;
	}
}

int CSnake::ChangeDirection(unsigned int uDirection){
	switch (uDirection) {
		case DIR_LEFT:
			if(m_pHead->m_uDirection!=DIR_RIGHT
			&& m_pHead->m_pNext->m_iPosX!=m_pHead->m_iPosX-1)
				m_pHead->m_uDirection = DIR_LEFT;
			return 1;
			//no break;
		case DIR_RIGHT:
			if(m_pHead->m_uDirection!=DIR_LEFT
				&& m_pHead->m_pNext->m_iPosX!=m_pHead->m_iPosX+1)
				m_pHead->m_uDirection = DIR_RIGHT;
			return 1;
			//no break;
		case DIR_UP:
			if(m_pHead->m_uDirection!=DIR_DOWN
				&& m_pHead->m_pNext->m_iPosY!=m_pHead->m_iPosY-1)m_pHead->m_uDirection = DIR_UP;
			return 1;
			//no break;
		case DIR_DOWN:
			if(m_pHead->m_uDirection!=DIR_UP
			&& m_pHead->m_pNext->m_iPosY!=m_pHead->m_iPosY+1)m_pHead->m_uDirection = DIR_DOWN;
			return 1;
			//no break;
		default:
			break;
		}
		return 0;
}

int CSnake::IsFoodDetected(SDL_Point ptFoodCell){
	if(ptFoodCell.x == m_pHead->m_iPosX && ptFoodCell.y == m_pHead->m_iPosY)
		return 1;
	return 0;
}

void CSnake::Shrink(){
	if (m_uNbSection==2)
			return;

	CSection* pCache = m_pTail;
	m_pTail=pCache->m_pPrev;
	delete pCache;
	m_uNbSection--;

}

int CSnake::IsOnCell(int iPosX, int iPosY){
	CSection* pScan = m_pHead;
	while(pScan){
		if(pScan->m_iPosX == iPosX && pScan->m_iPosY == iPosY)
			return 1;
		pScan = pScan->m_pNext;
	}
	return 0;
}

int CSnake::IsBiteHimself(){
	CSection* pScan = m_pHead->m_pNext;
	while(pScan){
		if(pScan->m_iPosX == m_pHead->m_iPosX && pScan->m_iPosY == m_pHead->m_iPosY)
			return 1;
		pScan = pScan->m_pNext;
	}
	return 0;
}

