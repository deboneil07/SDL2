#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include <SDL_image.h>

enum KeyPressSurfaces {
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Window *window = NULL;
SDL_Surface *surface, *draw = NULL;

SDL_Surface* KeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
SDL_Surface* CurrentSurface = NULL;

using namespace std;

SDL_Surface* loadSurface(string path){
    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
    if (loadedSurface == NULL){
        cout<<SDL_GetError()<<endl;
    }

    return loadedSurface;
}
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

    // draw = SDL_LoadBMP("first.bmp");
    // if (draw == NULL) {
    //     cout<< "error loading image" << SDL_GetError() <<endl;
    // }

    KeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = IMG_Load("./first.bmp");
    if (KeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL){
        cout<< SDL_GetError()<<endl;
        success = false;
    }

    KeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("./second.bmp");
    if (KeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL){
        cout<< SDL_GetError()<<endl;
        success = false;
    }

    KeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("./third.bmp");
    if (KeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL){
        cout<< SDL_GetError()<<endl;
        success = false;
    }

    KeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("./fourth.bmp");
    if (KeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL){
        cout<< SDL_GetError()<<endl;
        success = false;
    }

    KeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("./fifth.bmp");
    if (KeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL){
        cout<< SDL_GetError()<<endl;
        success = false;
    }

    return success;
}

void close(){
    // SDL_FreeSurface( draw );
    // draw = NULL;

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

            CurrentSurface = KeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

            while (!quit){
                while( SDL_PollEvent( &e ) != 0 ){
                    if( e.type == SDL_QUIT ) {
                        quit = true;
                    }
                    else if(e.type == SDL_KEYDOWN){
                        switch(e.key.keysym.sym){
                            case SDLK_UP:
                            CurrentSurface = KeyPressSurfaces[KEY_PRESS_SURFACE_UP];
                            break;

                            case SDLK_DOWN:
                            CurrentSurface = KeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
                            break;

                            case SDLK_LEFT:
                            CurrentSurface = KeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
                            break;

                            case SDLK_RIGHT:
                            CurrentSurface = KeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
                            break;

                            default:
                            CurrentSurface = KeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
                            break;
                        }
                    }
                }

                SDL_BlitSurface( CurrentSurface, NULL, surface, NULL );
                SDL_UpdateWindowSurface(window);
                
                // SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }

            } 
        }
    }

    close();

    return 0;
}
