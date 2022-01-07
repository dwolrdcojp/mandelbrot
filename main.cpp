// complile command
//  g++ main.cpp -o main -F/Users/max/Library/Frameworks -framework SDL2 -Wl,-rpath,/Users/max/Library/Frameworks
#include <SDL_keycode.h>
#include <iostream>
#include <SDL.h>
#include <complex>

int WIDTH = 1000;
int HEIGHT = 1000;

long double min = -2.84;
long double max =  1.0;
int MAX_ITERATIONS = 200;
long double factor = 1;

long double map(long double value, long double in_min, long double in_max, long double out_min, long double out_max) {
	return(value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Event event;

	window = SDL_CreateWindow("mandelbrot", 20, 20, 1440, 900, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_RenderSetLogicalSize(renderer, WIDTH, HEIGHT);

	bool is_running = true;
	while (is_running) {
		int count = 0;
		max -= 0.1 * factor;
		min += 0.15 * factor;
		factor *= 0.9349;
		MAX_ITERATIONS += 5;

		if (count > 30) {
			MAX_ITERATIONS *= 1.02;
		}

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
			    is_running = false;
			}else if(event.key.keysym.sym == SDLK_q){
				is_running = false;
			}
		}

		SDL_RenderPresent(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);

		for (int x = 0; x < WIDTH; x++) {
			for (int y = 0; y < HEIGHT; y++) {
			
				long double a = map(x, 0, WIDTH, min, max);
				long double b = map(y, 0, HEIGHT, min, max); 

				long double ai = a;
				long double bi = b;

				int n = 0;

				for (int i = 0; i < MAX_ITERATIONS; i++) {
					
					long double a1 = a * a - b * b;
					long double b1 = 2 * a * b;

					a = a1 + ai;
					b = b1 + bi;

					if ((a + b) > 2) {
						break;
					}

					n++;
				}
				long double bright = map(n, 0, MAX_ITERATIONS, 0, 255);
				
				if ((n == MAX_ITERATIONS) || (bright < 20)) {
					bright = 0;
				}	
				long double red = map(bright * bright, 0, 255 * 255, 0, 255);
				long double green = bright;
				long double blue = map(sqrt(bright), 0, sqrt(255), 0, 255);

				SDL_SetRenderDrawColor(renderer, red, green, blue, SDL_ALPHA_OPAQUE);
				SDL_RenderDrawPoint(renderer, x, y);
			}
		}
		SDL_Delay(150);
		count++;
	}
	return 0;
}
