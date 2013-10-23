class Renderer {
	public:
	
		SDL_Window *window = nullptr;
		SDL_Renderer *renderer = nullptr;
		
		Renderer(const int SCREEN_WIDTH, const int SCREEN_HEIGHT);
		~Renderer();
		void logSDLError(std::ostream &os, const std::string &msg);
		SDL_Texture* loadTexture(const std::string &file);
		void renderTextureFull(SDL_Texture *tex, int x, int y);
		void renderTextureRot(SDL_Texture *obj, SDL_Rect *clip, SDL_Rect *dest, int rot);
		int drawBackground();
		
		
};


		/**
		* Log an SDL error with some error message to the output stream of our choice
		* @param os The output stream to write the message too
		* @param msg The error message to write, format will be msg error: SDL_GetError()
		*/
		void Renderer::logSDLError(std::ostream &os, const std::string &msg){
		os << msg << " error: " << SDL_GetError() << std::endl;
		}

		/**
		* Loads an image into a texture on the rendering device
		* @param file The image file to load
		* @return the loaded texture, or nullptr if something went wrong.
		*/
		SDL_Texture* Renderer::loadTexture(const std::string &file){
			//Initialize to nullptr to avoid dangling pointer issues
			SDL_Texture *texture = nullptr;
			//Load the image
			texture = IMG_LoadTexture(renderer, file.c_str());
			if (texture == nullptr)
				logSDLError(std::cout, "LoadTexture");
			return texture;
		}

		/**
		* Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
		* the texture's width and height
		* @param tex The source texture we want to draw
		* @param x The x coordinate to draw too
		* @param y The y coordinate to draw too 
		*/
		void Renderer::renderTextureFull(SDL_Texture *tex, int x, int y){
			//Setup the destination rectangle to be at the position we want
			SDL_Rect dst;
			dst.x = x;
			dst.y = y;

			//Query the texture to get its width and height to use
			SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
			SDL_RenderCopy(renderer, tex, NULL, &dst);
		}
		
		void Renderer::renderTextureRot (SDL_Texture *obj, SDL_Rect *clip, SDL_Rect *dest, int rot){
			SDL_RenderCopyEx(renderer, obj, clip, dest, rot, NULL, SDL_FLIP_NONE);
		}
		
		int Renderer::drawBackground() {
			SDL_Texture *background = loadTexture("background3.png");
			renderTextureFull(background, 0, 0);
			return 1;
		}
		
		//Constructor
		Renderer::Renderer(const int SCREEN_WIDTH, const int SCREEN_HEIGHT) {
			if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
			logSDLError(std::cout, "SDL_Init");
			}
	
			if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
				logSDLError(std::cout, "IMG_Init");
			}
	
			window = SDL_CreateWindow("Mah winxorz", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
			if (window == nullptr){
				logSDLError(std::cout, "CreateWindow");
			}
	
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer == nullptr) {
				logSDLError(std::cout, "CreateRenderer");
			}
		}
		Renderer::~Renderer() {
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
			IMG_Quit();
			SDL_Quit();
		}