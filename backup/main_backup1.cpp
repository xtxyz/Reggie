#include "SDL2/SDL.h"
#include <iostream>
#include <SDL2/SDL_image.h>

#include "Renderer.h"
#include "GameObject.h"
//#include "MasterControlProgram.h"


const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;





int main(int argc, char** argv){
	
	Renderer *renderz = new Renderer(SCREEN_WIDTH, SCREEN_HEIGHT);
	GameObject *dude = new GameObject(renderz);
	
	for(int a = 0; a < 10; a++){
	for(int i = 0; i<4; i++) {
	renderz->drawBackground();
	dude->Pump(a);
	SDL_RenderPresent(renderz->renderer);
	SDL_Delay(100);
	}}
	delete renderz;
	
	return 0;
}




