//Libraries: Currently SDL, SDL_image for loading pngs, and iostream
#include "SDL2/SDL.h"
#include <iostream>
#include <SDL2/SDL_image.h>

//Other local objects and resources
#include "Renderer.h"
#include "GameObject.h"
#include "MasterControlProgram.h"

//Constants: currently settings for the screen
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;





int main(int argc, char** argv){
	//Instantiate the renderer and the MCP
	Renderer *renderz = new Renderer(SCREEN_WIDTH, SCREEN_HEIGHT);
	MasterControlProgram *mcp = new MasterControlProgram(renderz);
	
	//loadMap loads an object, and gameLoop runs a rudimentary loop
	mcp->loadMap();
	mcp->gameLoop();
	
	//Clean up
	delete renderz;
	delete mcp;
	
	return 0;
}








