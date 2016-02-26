#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include<fstream>
#include<iostream>
#include "Character.h"

using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event Event;
SDL_Texture *background,*menu1,*menu2,*selected,*tierra,*birds,*nubes;
SDL_Rect rect_background,rect_character,rect_menu1,rect_menu2,rect_selected,rect_tierra,rect_birds,rect_nubes;




int main( int argc, char* args[] )
{
    //Init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return 10;
    }
    //Creates a SDL Window
    if((window = SDL_CreateWindow("Image Loading", 100, 100, 1200/*WIDTH*/, 600/*HEIGHT*/, SDL_WINDOW_RESIZABLE | SDL_RENDERER_PRESENTVSYNC)) == NULL)
    {
        return 20;
    }
    //SDL Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
    if (renderer == NULL)
    {
        std::cout << SDL_GetError() << std::endl;
        return 30;
    }

    ofstream escritura("mi_archivo.txt");
    escritura<<"1.png"<<endl;
    escritura<<"2.png"<<endl;
    escritura<<"3.png"<<endl;
    escritura<<"4.png"<<endl;
    escritura.flush();
    escritura.close();

    ifstream lectura("mi_archivo.txt");

    string str;
    char* name;


    //Init textures
    lectura>>str;

    background = IMG_LoadTexture(renderer,str.c_str());
    rect_background.x = 0;
    rect_background.y = 0;
    rect_background.w = 1200;
    rect_background.h = 600;

    lectura>>str;

    tierra = IMG_LoadTexture(renderer,str.c_str());
    rect_tierra.x = 0;
    rect_tierra.y = 0;
    rect_tierra.w = 1200;
    rect_tierra.h = 600;

    lectura>>str;
    nubes = IMG_LoadTexture(renderer,str.c_str());
    rect_nubes.x = 0;
    rect_nubes.y = 0;
    rect_nubes.w = 1200;
    rect_nubes.h = 600;

    lectura>>str;
    birds = IMG_LoadTexture(renderer,str.c_str());
    rect_birds.x = 0;
    rect_birds.y = 0;
    rect_birds.w = 1200;
    rect_birds.h = 600;

    lectura.close();
    menu1 = IMG_LoadTexture(renderer,"menu1.png");
    rect_menu1.x = 0;
    rect_menu1.y = 0;
    rect_menu1.w = 1200;
    rect_menu1.h = 600;

    menu2 = IMG_LoadTexture(renderer,"menu2.png");
    rect_menu2.x = 0;
    rect_menu2.y = 0;
    rect_menu2.w = 1200;
    rect_menu2.h = 600;


    Character* character = new Character(renderer);
    bool start=true;
    bool select=false;
    int first=0;
    selected=menu1;
    rect_selected=rect_menu1;

    //Main Loop
    while(true)
    {
        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT)
            {
                return 0;
            }
            if(Event.type == SDL_KEYDOWN)
            {
                if(Event.key.keysym.sym == SDLK_d)
                    rect_character.x++;
                if(Event.key.keysym.sym == SDLK_a)
                    rect_character.x--;
                if((Event.key.keysym.sym == SDLK_UP)||(Event.key.keysym.sym == SDLK_DOWN)){

                    if(start){
                        first=1;
                        selected=menu1;
                        rect_selected=rect_menu1;
                        start=false;

                    }
                    else{

                        selected=menu2;
                        rect_selected=rect_menu2;
                        start=true;

                    }

                }

                if(Event.key.keysym.sym == SDLK_KP_ENTER){

                   if(first==0){
                        select=true;
                   }
                   else{
                        if(!start){

                            select=true;
                        }
                        else{
                            return 0;
                        }
                   }

                }
            }




        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);





        if(select){
            SDL_RenderCopy(renderer, background, NULL, &rect_background);
            SDL_RenderCopy(renderer, tierra, NULL, &rect_tierra);
            SDL_RenderCopy(renderer, nubes, NULL, &rect_nubes);
            SDL_RenderCopy(renderer, birds, NULL, &rect_birds);
        }
        else{
            SDL_RenderCopy(renderer, selected, NULL, &rect_selected);
        }

        character->logic();
        character->draw();

        SDL_RenderPresent(renderer);
    }

	return 0;
}
