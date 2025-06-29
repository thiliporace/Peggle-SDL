//
//  Score.cpp
//  SDL Test
//
//  Created by Thiago Liporace on 20/12/24.
//

#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>

#include <iostream>
#include <string>
#include <sstream>

#include "SdlManager.hpp"
#include "Label.hpp"

using namespace std;

Label::Label(int xPos, int yPos, int initialScore, std::string label): label(label) {
    if (TTF_Init() == -1) {
        cout << "Erro ao inicializar TTF: " << TTF_GetError() << endl;
        return;
    }
    
    font = TTF_OpenFont("NewYork.ttf", 24);
    if (!font) {
        cout << "Erro na fonte: " << TTF_GetError() << endl;
        return;
    }
    
    color = {255, 255, 255, 255};
    rect.x = xPos;
    rect.y = yPos;
    
    // Inicializa o texto com o valor inicial do score
    setValue(initialScore);
}

Label::~Label() {
    if (textTexture) SDL_DestroyTexture(textTexture);
    if (font) TTF_CloseFont(font);
}

void Label::setValue(int score) {
    
    if (textTexture) {
        SDL_DestroyTexture(textTexture);
        textTexture = nullptr;
    }
    
    std::ostringstream oss;
    oss << label << score;
    std::string scoreText = oss.str();
    
    SDL_Surface* surface = TTF_RenderText_Solid(font, scoreText.c_str(), color);
    if (!surface) {
        cout << "Erro na surface: " << TTF_GetError() << endl;
        return;
    }
    
    SdlManager* sdlManager = SdlManager::getInstance();
    textTexture = SDL_CreateTextureFromSurface(sdlManager->getRenderer(), surface);
    if (!textTexture) {
        cout << "Erro na textura: " << SDL_GetError() << endl;
    }
    
    rect.w = surface->w;
    rect.h = surface->h;
    
    SDL_FreeSurface(surface);
}

TTF_Font* Label::getFont(){
    return font;
}

SDL_Texture* Label::getTexture() const {
    return textTexture;
}

SDL_Rect Label::getRect() const {
    return rect;
}
