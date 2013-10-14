#include "SDL2/SDL.h"
#include <iostream>
#include <SDL2/SDL_image.h>
#include "GameObject.h"
#include "MasterControlProgram.h"


const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

/**
* Log an SDL error with some error message to the output stream of our choice
* @param os The output stream to write the message too
* @param msg The error message to write, format will be msg error: SDL_GetError()
*/

void logSDLError(std::ostream &os, const std::string &msg){
	os << msg << " error: " << SDL_GetError() << std::endl;
}

/**
* Loads an image into a texture on the rendering device
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
SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;

int init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		logSDLError(std::cout, "SDL_Init");
		return 2;
	}
	
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
		logSDLError(std::cout, "IMG_Init");
		return 3;
	}
	
	window = SDL_CreateWindow("Mah winxorz", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr){
		logSDLError(std::cout, "CreateWindow");
		return 4;
	}
	
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		logSDLError(std::cout, "CreateRenderer");
		return 5;
	}
	return 1;
}




int main(int argc, char** argv){
	
	if(init() != 1){return 1;}
	
	MasterControlProgram  *MCP = new MasterControlProgram();
	
	SDL_Texture *background = loadTexture("background3.png", renderer);
	SDL_Texture *foreground = loadTexture("dude1.png", renderer);
	
	if (background == nullptr || foreground == nullptr)
		return 5;
	
	for (int a = 0; a < 10; a++){
	for (int i = 0; i < 4; i++) {
	SDL_RenderClear(renderer);
	
	renderTexture(background, renderer, 0, 0);
	
	SDL_Rect dest;
	dest.x = i*100; dest.y = 0; dest.w = 100; dest.h = 100;
	SDL_Rect clip;
	clip.x = i*250; clip.y = 0; clip.w = 250; clip.h = 250;
	
	SDL_RenderCopyEx(renderer, foreground, &clip, &dest, i*90, NULL, SDL_FLIP_NONE);
	
	SDL_RenderPresent(renderer);
	
	SDL_Delay(300);
	}
	}
	
	
	SDL_DestroyTexture(background);
	SDL_DestroyTexture(foreground);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	
	IMG_Quit();
	SDL_Quit();
	
	return 0;
}





