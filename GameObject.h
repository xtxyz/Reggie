class GameObject {

	public:
	
	SDL_Rect destRect;
	SDL_Rect clipRect;
	SDL_Texture *tex;
	int animationSet;
	int animationPos;
	int animationState;
	Renderer *renderer;
	
	GameObject(Renderer *ren);
	~GameObject();
	void Roll(int i);
	void Pump();

	

};

GameObject::GameObject(Renderer *ren) {
	tex = ren->loadTexture("dude_2.png");
	renderer = ren;
	animationPos = 0;
}
GameObject::~GameObject(){
	SDL_DestroyTexture(tex);
}
void GameObject::Roll(int i){
	destRect.x = i*100; destRect.y = 0; destRect.w = 100; destRect.h = 100;
	clipRect.x = animationPos*100; clipRect.y = 0; clipRect.w = 100; clipRect.h = 100;
	renderer->renderTextureRot(tex, &clipRect, &destRect, i*90);
	if (animationPos<3){
		animationPos++;
	}
	else {animationPos = 0;}
}

void GameObject::Pump() {
	destRect.x = 10; destRect.y = 0; destRect.w = 100; destRect.h = 100;
	clipRect.x = animationPos*100; clipRect.y = 0; clipRect.w = 100; clipRect.h = 100;
	renderer->renderTextureRot(tex, &clipRect, &destRect, 0);
	if (animationPos<3) {
		animationPos++;
	}
	else {animationPos = 0;}
}


// SDL_Texture *background = graphie->loadTexture("background3.png", graphie->renderer);
	// SDL_Texture *foreground = graphie->loadTexture("dude1.png", graphie->renderer);
	
	// if (background == nullptr || foreground == nullptr)
		// return 5;
	
	// for (int a = 0; a < 10; a++){
	// for (int i = 0; i < 4; i++) {
	// SDL_RenderClear(graphie->renderer);
	
	// graphie->renderTexture(background, graphie->renderer, 0, 0);
	
	// SDL_Rect dest;
	// dest.x = i*100; dest.y = 0; dest.w = 100; dest.h = 100;
	// SDL_Rect clip;
	// clip.x = i*250; clip.y = 0; clip.w = 250; clip.h = 250;
	
	// SDL_RenderCopyEx(graphie->renderer, foreground, &clip, &dest, i*90, NULL, SDL_FLIP_NONE);
	
	// SDL_RenderPresent(graphie->renderer);
	
	// SDL_Delay(300);
	// }
	// }
	
	
	// SDL_DestroyTexture(background);
	// SDL_DestroyTexture(foreground);