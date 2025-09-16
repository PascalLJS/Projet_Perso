#include <iostream>
#include <SDL2/SDL.h>
using namespace std;

const int WIDTH = 800, HEiGHT = 600;

// main() is where program execution begins.
int main(int arc, char *argv[]) {

   SDL_Init(SDL_INIT_EVERYTHING);

   SDL_Window *window = SDL_CreateWindow("testing SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEiGHT, SDL_WINDOW_ALLOW_HIGHDPI);
   
   SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

   if(NULL == window)
      return 1;

   SDL_Event windowEvent;

   SDL_Rect rectangle;
   rectangle.x = 5;
   rectangle.y = 5;
   rectangle.h = 50;
   rectangle.w = 50;

   while (true) {
      if(SDL_PollEvent(&windowEvent)) {
         if(SDL_QUIT == windowEvent.type)
         break;
      }
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
      SDL_RenderClear(renderer);

      SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
      SDL_RenderDrawRect(renderer, &rectangle);

      SDL_RenderPresent(renderer);
   }
   
   SDL_DestroyWindow(window);
   SDL_Quit();

   return EXIT_SUCCESS;
}