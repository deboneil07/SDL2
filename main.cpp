#include <SDL.h>
#include <iostream>
#include <SDL_image.h>

using namespace std;
const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 600;

SDL_Window* window = NULL;
// SDL_Surface* surface, *bg = NULL;
SDL_Texture *Texture = NULL;
SDL_Renderer *renderer = NULL;
class LTexture{
    public:
        LTexture();

        ~LTexture();
        
        bool loadFromFile(string path);

        void free();

        void render(int x, int y, SDL_Rect* clip = NULL);

        int getWidth();
        int getHeight();

    private:
        SDL_Texture* mTexture;
        int mWidth;
        int mHeight;
};

int LTexture::getHeight(){
    return mHeight;
}

int LTexture::getWidth(){
    return mWidth;
}
void LTexture::free(){
    if (mTexture != NULL){
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}
bool LTexture::loadFromFile(string path){
    free();

    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL){
        cout<< SDL_GetError()<<endl;
    }
    else{
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == NULL){
            cout<< SDL_GetError()<<endl;
        }
        else{
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        SDL_FreeSurface(loadedSurface);
    }

    mTexture = newTexture;
    return mTexture != NULL;
}

LTexture::LTexture(){
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture(){
    free();
}

void LTexture::render(int x, int y, SDL_Rect* clip){
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};
    if (clip != NULL){
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopy(renderer, mTexture, clip, &renderQuad);
}

const int WALKING_ANIMATION_FRAMES = 4;
SDL_Rect spriteClips[WALKING_ANIMATION_FRAMES];
LTexture spriteSheetTexture;

// SDL_Texture* Loadtexture(string path){
//     SDL_Texture* newTexture = NULL;

//     SDL_Surface* loadedSurface = IMG_Load(path.c_str());
//     if (loadedSurface == NULL){
//         cout<< SDL_GetError() << endl;
//     }
//     else{
//         newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
//         if (newTexture == NULL){
//             cout<< SDL_GetError() << endl;
//         }

//         SDL_FreeSurface(loadedSurface);
//     }

//     return newTexture;
// }
bool init(){
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        cout<<SDL_GetError()<<endl;
        success = false;
    }
    else{
        window = SDL_CreateWindow("Assignment_1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if (window == NULL){
            cout<<SDL_GetError()<<endl;
        }
        else{
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (renderer == NULL){
                cout<< SDL_GetError() << endl;
                success = false;
            }
            else{
                SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
            }
        }
    }


    return success;
}

bool loadMedia(){
    bool success = true;
    // Texture = IMG_LoadTexture(renderer, "./fourth.bmp");
    // if (Texture == NULL){
    //     cout<< SDL_GetError() << endl;
    //     success = false;
    // }

    if (!spriteSheetTexture.loadFromFile("./sheet.png")){
        cout<< SDL_GetError() << endl;
    }
    else{
        //Set top left sprite
        spriteClips[ 0 ].x =   0;
        spriteClips[ 0 ].y =   0;
        spriteClips[ 0 ].w = 64;
        spriteClips[ 0 ].h = 205;

        //Set top right sprite
        spriteClips[ 1 ].x = 64;
        spriteClips[ 1 ].y =   0;
        spriteClips[ 1 ].w = 64;
        spriteClips[ 1 ].h = 205;
        
        //Set bottom left sprite
        spriteClips[ 2 ].x =   128;
        spriteClips[ 2 ].y = 0;
        spriteClips[ 2 ].w = 64;
        spriteClips[ 2 ].h = 205;
        //Set bottom right sprite
        spriteClips[ 3 ].x = 192;
        spriteClips[ 3 ].y = 0;
        spriteClips[ 3 ].w = 64;
        spriteClips[ 3 ].h = 205;
    }


    return success;
}

void close(){
    SDL_DestroyTexture(Texture);
    Texture = NULL;
    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    SDL_DestroyWindow(window);
    window = NULL;

    IMG_Quit();
    SDL_Quit();
}


int main(int argc, char* args[]){
    if (!init()){
        cout<<SDL_GetError()<<endl;
    }
    else{
        if (!loadMedia()){
            cout<<SDL_GetError()<<endl;
        }
        else{
            SDL_Event e;
            bool quit = false;
            int frame = 0;

            while(!quit){
                while (SDL_PollEvent(&e) != 0){
                    if (e.type == SDL_QUIT){
                        quit = true;
                    }
                }

                // SDL_RenderClear(renderer); // clear screen
                // SDL_RenderCopy(renderer, Texture, NULL, NULL); // renders texture to screen
                // SDL_RenderPresent(renderer); //update the renderer

                SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear(renderer);

                // TOP LEFT PART OF VIEWPORT

                // SDL_Rect topleft;
                // topleft.x = 0;
                // topleft.y = 0;
                // topleft.w = SCREEN_WIDTH/2;
                // topleft.h = SCREEN_HEIGHT/2;
                // SDL_RenderSetViewport(renderer, &topleft);
                
                // SDL_RenderCopy(renderer, Texture, NULL, NULL);

                // SDL_Rect topright;
                // topright.x = SCREEN_WIDTH / 2;
                // topright.y = 0;
                // topright.w = SCREEN_WIDTH / 2;
                // topright.h = SCREEN_HEIGHT / 2;
                // SDL_RenderSetViewport(renderer, &topright);

                // SDL_RenderCopy(renderer, Texture, NULL, NULL);

                // SDL_Rect newRect = {SCREEN_WIDTH/4, SCREEN_HEIGHT/4, SCREEN_WIDTH/2, SCREEN_HEIGHT/2};
                // SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
                // SDL_RenderFillRect(renderer, &newRect);

                // SDL_Rect outlineRect = {SCREEN_WIDTH/6, SCREEN_HEIGHT/6, SCREEN_WIDTH * 2/3, SCREEN_HEIGHT * 2/3};
                // SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
                // SDL_RenderDrawRect(renderer, &outlineRect);

                // SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
                // SDL_RenderDrawLine(renderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);

                // SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF);
                // for (int i = 0; i < SCREEN_HEIGHT; i+=4){
                //     SDL_RenderDrawPoint(renderer, SCREEN_WIDTH/2, i);
                // }

                // spriteSheetTexture.render(0, 0, &spriteClips[0]);

                // spriteSheetTexture.render(SCREEN_WIDTH - spriteClips[1].w, 0, &spriteClips[1]);

                // spriteSheetTexture.render(0, SCREEN_HEIGHT - spriteClips[2].h, &spriteClips[2]);
                
                // spriteSheetTexture.render(SCREEN_WIDTH - spriteClips[3].w, SCREEN_HEIGHT - spriteClips[3].h, &spriteClips[3]);

                SDL_Rect* currentClip = &spriteClips[frame / 4];
                spriteSheetTexture.render((SCREEN_WIDTH - currentClip->w) / 2, (SCREEN_HEIGHT - currentClip->h) / 2, currentClip);
                
                SDL_RenderPresent(renderer);
                ++frame;

                if (frame / 4 >= WALKING_ANIMATION_FRAMES){
                    frame = 0;
                }
            }
        }
    }

    close();
    
    return 0;
}