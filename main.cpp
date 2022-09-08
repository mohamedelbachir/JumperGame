#include"Game.h"
#include<windows.h>
#include<cstdio>

//variable de definition de FPS maximale
const int FPS=800;

//temps minimale pour effacer et afficher sur ecran
const float DELAYTIME=1000.0f/FPS;
int main(int argc, char* args[])
{
    //variable d'activation et de debugging console
    AllocConsole();
    freopen("CON","w",stdout);

    //instance singleton jeu
    theGame::Instance()->init("Jumper",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,534,650);

    Uint32 frameStart=SDL_GetTicks();
    Uint32 elapsedTime=0;

    while(theGame::Instance()->running()){

        theGame::Instance()->handleEvent();

        theGame::Instance()->update();
        theGame::Instance()->render();

        elapsedTime=SDL_GetTicks()-frameStart;

        if(elapsedTime<DELAYTIME)
        {
            SDL_Delay((int)DELAYTIME);//=>pour obtenir 60FPS
            frameStart=SDL_GetTicks();
        }
    }

    //nettoyage du jeu
    theGame::Instance()->clean();

    //system("PAUSE");
    return EXIT_SUCCESS;
}
