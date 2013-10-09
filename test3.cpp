#include "SDL2/SDL.h"
#include <iostream>
#include <SDL2/SDL_image.h>


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int TILE_SIZE = 40;

/**
* Log an SDL error with some error message to the output stream of our choice
* @param os The output stream to write the message too
* @param msg The error message to write, format will be msg error: SDL_GetError()
*/

void logSDLError(std::ostream &os, const std::string &msg){
	os << msg << " error: " << SDL_GetError() << std::endl;
}

/**
* Loads a BMP image into a texture on the rendering device
* @param file The image file to load
* @param ren The renderer to load the texture onto
* @return the loaded texture, or nullptr if something went wrong.
*/

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren){
	//Initialize to nullptr to avoid dangling pointer issues
	SDL_Texture *texture = nullptr;
	//Load the image
	texture = IMG_LoadTexture(ren, file.c_str());
	if (texture == nullptr)
		logSDLError(std::cout, "LoadTexture");
	return texture;
}

/**
* Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
* the texture's width and height
* @param tex The source texture we want to draw
* @param ren The renderer we want to draw too
* @param x The x coordinate to draw too
* @param y The y coordinate to draw too 
*/

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y){
	//Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	//Query the texture to get its width and height to use
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(ren, tex, NULL, &dst);
}



int main(int argc, char** argv){
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		logSDLError(std::cout, "SDL_Init");
		return 1;
	}
	
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
		logSDLError(std::cout, "IMG_Init");
		return 1;
	}
	
	SDL_Window *window = SDL_CreateWindow("Lesson 2", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr){
		logSDLError(std::cout, "CreateWindow");
		return 2;
	}
	
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		logSDLError(std::cout, "CreateRenderer");
		return 3;
	}

	SDL_Texture *background = loadTexture("background2.png", renderer);
	SDL_Texture *foreground = loadTexture("foreground2.png", renderer);
	
	if (background == nullptr || foreground == nullptr)
		return 4;
	
	SDL_RenderClear(renderer);
	int bW, bH;
	SDL_QueryTexture(background, NULL, NULL, &bW, &bH);
	renderTexture(background, renderer, 0, 0);
	renderTexture(background, renderer, bW, 0);
	renderTexture(background, renderer, 0, bH);
	renderTexture(background, renderer, bW, bH);
	
	int iW, iH;
	SDL_QueryTexture(foreground, NULL, NULL, &iW, &iH);
	int x = SCREEN_HEIGHT / 2 -iW / 2;
	int y = SCREEN_HEIGHT / 2 -iH / 2;
	renderTexture(foreground, renderer, x, y);
	
	SDL_RenderPresent(renderer);
	
	SDL_Delay(2000);
	
	SDL_DestroyTexture(background);
	SDL_DestroyTexture(foreground);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	
	//std::cout << "Lolzy" << std::endl;
	
	SDL_Quit();
	
	return 0;
	
}