#include <stdio.h>
#include <SDL2/SDL.h>
#include <assert.h>
#define BOOL u32
#define TRUE 1
#define FALSE 0
#define internal static

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 576

typedef Uint32 u32;
typedef Uint64 u64;
typedef Sint32 i32;
typedef Sint64 i64;
typedef struct 
{
	int x;
	int y;
	int w;
	int h;
} rect_t;

internal void FillRect(rect_t rect, u32 pixel_color, u32 *screen_pixels)
{
	assert(screen_pixels); //making sure that pixels exist
	for (int row = 0; row < rect.h; ++row)
	{
		for (int col = 0; col < rect.w; ++col)
		{
			screen_pixels[(row + rect.y)*SCREEN_WIDTH + col + rect.x] = pixel_color;
		}
	}
}





int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window *win = SDL_CreateWindow("Spell Checker", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,0);//not interested in the position of the window.
	assert(win);

	SDL_Renderer *renderer = SDL_CreateRenderer(win, 0, SDL_RENDERER_SOFTWARE);
	assert(renderer);


	SDL_PixelFormat *format =  SDL_AllocFormat(SDL_PIXELFORMAT_RGB888);

	SDL_Texture *screen = SDL_CreateTexture(renderer, format->format, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH,SCREEN_HEIGHT);
	assert(screen);

	u32 *screen_pixels = (u32*) calloc(SCREEN_WIDTH * SCREEN_WIDTH , sizeof(u32));
	assert(screen_pixels);

	rect_t square = {0,0,30,30}; //start at origin 
	square.x = (SCREEN_WIDTH-square.w)/2; //bringing square in the middle
	square.y = (SCREEN_HEIGHT-square.h)/2;
	u32 pixel_color = SDL_MapRGB(format, 0, 0, 255);
	FillRect(square, pixel_color, screen_pixels);

	BOOL pressed_up = FALSE;
	BOOL pressed_down = FALSE;
	BOOL pressed_left = FALSE;
	BOOL pressed_right = FALSE;

	// SDL_Delay(5000);
	BOOL done = FALSE;
	while(!done)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				done = TRUE;
				break;
			}

			if (event.type != SDL_KEYDOWN && event.type != SDL_KEYUP) //if user press down key -> exit
			{
				break;
			}

			SDL_Keycode code = event.key.keysym.sym;
			switch (code)
			{
				case SDLK_ESCAPE: //exit on escape as well.
					done = event.type == SDL_KEYDOWN;
					break;
				case SDLK_UP:
					pressed_up = event.type == SDL_KEYDOWN;
					break;
				case SDLK_DOWN:
					pressed_down = event.type == SDL_KEYDOWN;
					break;
				case SDLK_LEFT:
					pressed_left = event.type == SDL_KEYDOWN;
					break;
				case SDLK_RIGHT:
					pressed_right = event.type == SDL_KEYDOWN;
					break;

				default:
					break; //exit on every other key.
			}	

		}	

		memset(screen_pixels, 0 , SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(u32)); //flushing the array of previous screen_pixels

		if (pressed_up)
		{
			square.y -= 1;
		}

		if (pressed_down)
		{
			square.x += 1;
		}

		if(pressed_left)
		{
			square.x -= 1;
		}
		if(pressed_right)
		{
			square.x +=1;
		}

		FillRect(square,255, screen_pixels); //updating the screen_pixels based on movement.



		//some magic functions to handle the window after user interaction
		SDL_UpdateTexture(screen, NULL, screen_pixels, SCREEN_WIDTH * sizeof(u32));
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, screen, NULL, NULL);
		SDL_RenderPresent(renderer);
		SDL_Delay(50);


		
	}
}
