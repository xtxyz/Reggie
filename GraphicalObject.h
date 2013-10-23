class GraphicalObject {

	public:
		GraphicalObject(){
	
		}
		~GraphicalObject(){
	
		}
	
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

};