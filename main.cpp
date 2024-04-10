#include <SDL.h>
#include <stdio.h>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Window *window = NULL;
SDL_Surface *surface, *draw = NULL;


using namespace std;
bool init(){
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        cout<< "Error" << SDL_GetError() << endl;
        return false;
    }
    else{
        window = SDL_CreateWindow("test win", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if (window == NULL){
            cout<< "Error" << SDL_GetError() << endl;
        }
        else{
            surface = SDL_GetWindowSurface(window);
            
        }
    }

    return success;
}


bool loadMedia() {
    bool success = true;

    draw = SDL_LoadBMP("first.bmp");
    if (draw == NULL) {
        cout<< "error loading image" << SDL_GetError() <<endl;
    }

    return success;
}

void close(){
    SDL_FreeSurface( draw );
    draw = NULL;

    SDL_DestroyWindow( window );
    window = NULL;

    SDL_Quit();
}

int main(int argc, char* args[]){

    if (!init()) {
        cout<<"error"<<SDL_GetError()<<endl;
    }
    else{
        if (!loadMedia()){
            cout<< "failed to load media" <<endl;
        }
        else{

            bool quit = false;
            SDL_Event e;

            while (!quit){
                while( SDL_PollEvent( &e ) != 0 ){
                    if( e.type == SDL_QUIT ) {
                        quit = true;
                    }
                }

                SDL_BlitSurface( draw, NULL, surface, NULL );
                SDL_UpdateWindowSurface(window);
                // SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }

            } 
        }
    }

    close();

    return 0;
}
