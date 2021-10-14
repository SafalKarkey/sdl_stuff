#include<SDL2/SDL.h>
#include<stdio.h>
#include<math.h>

typedef struct{
    int x,y;
    short life;
    char* name;
} Man;

SDL_Window* window;
SDL_Renderer* renderer;

//-------------------process switches for events------------------
int processEvents(Man*man)
{   
    int done = 0;
    SDL_Event e;
    while(SDL_PollEvent(&e)){
        switch(e.type){
            case SDL_WINDOWEVENT_CLOSE:
                if(window){
                    SDL_DestroyWindow(window);
                    done = 1;
                }
                break;
            /*case SDL_KEYDOWN:
                switch(e.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        done = 1;
                        break;
                    case SDLK_RIGHT:
                        man->x += 10;
                        break;
                    case SDLK_LEFT:
                        man->x -= 10;
                        break;
                }
                break;*/
            case SDL_QUIT:
                done = 1;
                break;
        }
    }
    //This has much smoother animation (how?)
    const Uint8* state = SDL_GetKeyboardState(NULL);
    if(state[SDL_SCANCODE_LEFT]){
        man->x -= 10;
    }
    if(state[SDL_SCANCODE_RIGHT]){
        man->x += 10;
    }
    if(state[SDL_SCANCODE_UP]){
        man->y -= 10;
    }
    if(state[SDL_SCANCODE_DOWN]){
        man->y += 10;
    }


    return done;
}
//----------------render stuffs--------------------
void doRender(Man*man)
{
    SDL_SetRenderDrawColor(renderer, 0,0,0,0);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255,0,0,50);
    SDL_Rect rect = {man->x,man->y,10,10};
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);
}
//----------------------**main**---------------------
int main()
{   
    //.............initialize part
    if(SDL_Init(SDL_INIT_VIDEO) != 0 ){
        printf("Couldn't initalize\n");
        return -1;
    }

    window = SDL_CreateWindow("game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 700, 700, SDL_WINDOW_SHOWN);
    if(!window){
        printf("Error while initializing window\n");
        return -2;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!renderer){
        printf("Couldn't initialize renderer!\n");
        return -3;
    }

    Man man;
    man.x = 255;
    man.y = 255;
    //events.............
    int done = 0;
    SDL_Event e;
    while(!done){
        done = processEvents(&man);
        doRender(&man);
    }
    SDL_Quit();
    return 0;
}