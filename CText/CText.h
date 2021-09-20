#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class CText{
private:
    static TTF_Font*    c_pFont;
    static SDL_Color    c_colFont;
private:
    SDL_Texture*    m_pTextTex;
    SDL_Rect        m_rTextBox;
public:
    CText(SDL_Renderer* pRenderer, SDL_Point ptTextPos, char* sText);
    ~CText();
    static void InitGraph(char* sFontPath, SDL_Color colFont, int iPtSize);
    static void ReleaseGraph();
    void Draw(SDL_Renderer* pRenderer);
    static void DrawParse(CText* pText, SDL_Renderer* pRenderer);
    static void DeleteFunc(CText* pText);
};