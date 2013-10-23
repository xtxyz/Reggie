#include "SDL2/SDL.h"
#include <iostream>
//#include <stdio>
//using namespace std;

int main(int argc, char** argv){
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
		std::cout << SDL_GetError() << std::endl;
		return 1;
	}
	
	SDL_Window *win = nullptr;
	win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	if (win == nullptr){
		std::cout << SDL_GetError() << std::endl;
		return 1;
	}
	
	SDL_Renderer *ren = nullptr;
	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr) {
		std::cout << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Surface *bmp = nullptr;
	bmp = SDL_LoadBMP("./hello.bmp");
	if (bmp == nullptr){
		std::cout << SDL_GetError() << std::endl;
		return 1;
	}
	
	SDL_Texture *tex = nullptr;
	tex = SDL_CreateTextureFromSurface(ren, bmp);
	SDL_FreeSurface(bmp);
	
	SDL_RenderClear(ren);
	SDL_RenderCopy(ren, tex, NULL, NULL);
	SDL_RenderPresent(ren);
	
	SDL_Delay(2000);
	
	SDL_DestroyTexture(tex);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	
	//std::cout << "Lolzy" << std::endl;
	
	SDL_Quit();
	
	return 0;
	
}