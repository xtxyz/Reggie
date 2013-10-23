class MasterControlProgram {
	
	public:
		
		GameObject* masterObjectList[10];
		MasterControlProgram(Renderer *ren);
		~MasterControlProgram();
		int gameLoop();
		int menu();
		int loadMap();
		Renderer *renderz;
		SDL_Event event;
		
};

	MasterControlProgram::MasterControlProgram(Renderer *ren) {
		renderz = ren;
	}

	MasterControlProgram::~MasterControlProgram() {
		
	}
	int MasterControlProgram::menu() {
		return 0;
	}
	
	int MasterControlProgram::gameLoop() {
		bool done = false;
		while (!done) {
			//Logic
			
			
		
			//Output
			renderz->drawBackground();
			masterObjectList[0]->Pump();
			SDL_RenderPresent(renderz->renderer);
			//SDL_Delay(100);
				
			//Input
			while(SDL_PollEvent(&event)){
				switch(event.type) {
					case SDL_QUIT:
					done = true;
					
					case SDL_KEYDOWN:
					done = true;
					
					case SDL_MOUSEBUTTONDOWN:
					done = true;
					
					default:
					
					break;
				}
			}
		}
				return 1;
	}
		
	int MasterControlProgram::loadMap() {
		GameObject *dude = new GameObject(renderz);
		masterObjectList[0] = dude;
		return 0;
	}