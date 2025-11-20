#include <iostream>
#include <complex>
#include <boost/multiprecision/complex128.hpp>
#include <boost/multiprecision/float128.hpp>
#include <SDL2/SDL.h>
#include <cmath>

using namespace boost::multiprecision;
using std::abs;

SDL_Window* window = SDL_CreateWindow("Fractal Deep Zoom",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1200,800,0);
SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

float scale = 1.0;
float iterations = 240.0;
float CUTOFF = 2.0;
float XX = 3.0;
float YY = 2.0;
int Val = 0;
float offsetX = -0.75;
float offsetY = 0.0;

std::complex<float> C(0.0, 0.0);
std::complex<float> Z(0.0, 0.0);

float Xscale = (XX/1200)/scale;
float Yscale = (YY/800)/scale;

void clearScreen() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}

void setPixel(int X, int Y, Uint8 r=255 ,Uint8 g=255 ,Uint8 b=255 ,Uint8 a=255) {
	SDL_SetRenderDrawColor(renderer ,r, g, b, a);
	SDL_RenderDrawPoint(renderer, X, Y);
}

void drawToDisplay() {

}

int main(int argc, char* argv[]) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		return -1;
	}

	if (!window) {
		SDL_Quit();
		return -1;
	}

	SDL_Event event;
	bool running = true;
	clearScreen();
	for (int X = -600; X < 601; X++) {
		for (int Y = -400; Y < 401; Y++) {
			C.real((X*Xscale)+offsetX);
			C.imag((Y*Yscale)+offsetY);
			Z.real(0.0);
			Z.imag(0.0);
			Val = 0;
			for (int N = 0; N < iterations; N++) {
				Z = (Z*Z) + C;
				if (std::abs(Z) > CUTOFF) {
					Val = N;
					setPixel(X+600, Y+400, (Val*4)%255, (Val*5)%255, (Val*6)%255);
					//setPixel(X+600, Y+400, (Val*5)%255, (Val*5)%255, (Val*5)%255);
					break;
				}
			}
		}
	}
	SDL_RenderPresent(renderer);
	std::cout << "Done." << std::endl;
	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
			}
		}
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	return 0;
}