#include <SDL.h>
#include <stdio.h>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Surface* screenSurface = nullptr;

using namespace std;
int main(int argc, char *argv[])
{
    SDL_Window *window = NULL;
    SDL_Surface *surface = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout<< "Error, couldnt be initialized, " << SDL_GetError() << endl;
    }
    else{
        window = SDL_CreateWindow("first win", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED_MASK, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        // cin.get();
        if (window == NULL){
            cout<< "window couldnt be created! " << SDL_GetError() << endl;
        }

        else{

            screenSurface = SDL_GetWindowSurface( window );
            SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF));
            SDL_UpdateWindowSurface(window);

            SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }



        }
    }

    return 0;
}
