//
//  Score.hpp
//  SDL Test
//
//  Created by Thiago Liporace on 20/12/24.
//

#ifndef Label_hpp
#define Label_hpp

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_filesystem.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <string>
#include <sstream>

#include <stdio.h>
#include <string.h>


class Label {
private:
    std::string label;
    SDL_Color color;
    TTF_Font* font;
    
    SDL_Rect rect;
    SDL_Texture* textTexture;
    
public:
    
    SDL_Texture* getTexture() const;
    SDL_Rect getRect() const;
    
    Label(int xPos, int yPos, int initialScore, std::string label);
    
    ~Label();
    
    void setValue(int score);
    
    TTF_Font* getFont();
};

#endif /* Label_hpp */
