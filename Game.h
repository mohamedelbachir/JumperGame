#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <cstdlib>
#include<iostream>
#include <SDL.h>
#include"GameStateMachine.h"

//initialisation singleton class pour le jeu
class Game{
private:

    //variable si le jeu se lance
    bool m_bRunning=false;

    SDL_Window *g_pWindow=NULL;
    SDL_Renderer *g_pRenderer=NULL;

    //variable de recuperation etat de jeu
    GameStateMachine *m_pGameStateMachine;

    static Game* s_instance;

    int width;

    int height;

    Game();
public:

    static Game *Instance()
    {
        if(s_instance==NULL){
            s_instance=new Game();
        }
        return s_instance;
    }

    ~Game(){
        clean();
    }
    /**
        @brief init
        brief of initialising window
        @param title : title of window
        @param xpos,ypos :position of window
        @param width,height : size of window
        @param fullscreen: boolean for fullscreen setting
        @return boolean for window and renderer initializing true in case is good otherwise false
    */
    bool init(const char*title,int xpos,int ypos,int width,int height,int flags=0,bool fullscreen=false);

    /**
        @brief render
        render of window
    */
    void render();

    /**
        @brief update
        update of window
    */
    void update();

    /**
        @brief handleEvent
        handle input , mouse and something else to user
    */
    void handleEvent();

    /**
        @brief clean
        function to clean Windown and free Up Memory
    */ 
    void clean();

    /**
        @brief running
        @return boolean to check if window is Running

    */
    bool running();

    /**
        @brief quit
        brief  to close Window
    */
    void quit();

    /**
        @brief getRenderer
        get current renderer on the window
    */
    SDL_Renderer *getRenderer();

    /**
        @brief getWindowWidth
       getsize of window
       @return widthOfWindow
    */
    int getWindowWidth();

    /**
         @brief getWindowHeight
       getsize of window
       @return heightOfWindow
    */
    int getWindowHeight();

    /**
        @brief getStateMachine
        @return the curent state of window
    */
    GameStateMachine *getStateMachine();
};
typedef Game theGame;
#endif // GAME_H_INCLUDED
