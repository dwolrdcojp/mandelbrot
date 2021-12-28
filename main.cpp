#include <iostream>
#include <SDL.h>

int WIDTH = 803;
int HEIGHT = 800;

long double min = -2.0;
long double max =  2.0;

int MAX_ITERATIONS = 200;

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
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
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
				if (n == MAX_ITERATIONS) {
				SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
				SDL_RenderDrawPoint(renderer, x, y);
				}	
			}
		}
	}
	return 0;
}
