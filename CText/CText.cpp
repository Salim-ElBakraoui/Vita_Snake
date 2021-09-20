#include "CText.h"

TTF_Font*    CText::c_pFont    = nullptr;
SDL_Color    CText::c_colFont;

CText::CText(SDL_Renderer* pRenderer, SDL_Point ptTextPos, char* sText):
    m_pTextTex(nullptr)
{
    SDL_Surface* pSurface = TTF_RenderText_Blended(c_pFont, sText, c_colFont);
    m_pTextTex = SDL_CreateTextureFromSurface(pRenderer, pSurface);
    SDL_FreeSurface(pSurface);
    int iW, iH;
    SDL_QueryTexture(m_pTextTex, nullptr, nullptr, &iW, &iH);
    m_rTextBox=SDL_Rect{ptTextPos.x, ptTextPos.y, iW, iH};
}

CText::~CText(){
    if(m_pTextTex)SDL_DestroyTexture(m_pTextTex);
}

void CText::InitGraph(char* sFontPath, SDL_Color colFont, int iPtSize){
    TTF_Init();
    c_colFont = colFont;
    c_pFont = TTF_OpenFont(sFontPath, iPtSize);
}

void CText::ReleaseGraph(){
    TTF_CloseFont(c_pFont);
    TTF_Quit();
}

void CText::Draw(SDL_Renderer* pRenderer){
    SDL_RenderCopy(pRenderer, m_pTextTex, nullptr, &m_rTextBox);
}

void CText::DrawParse(CText* pText, SDL_Renderer* pRenderer){
    pText->Draw(pRenderer);
}

void CText::DeleteFunc(CText* pText){
    delete pText;
}