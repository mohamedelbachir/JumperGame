#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <cstdlib>
#include<iostream>
#include <SDL.h>
#include"GameStateMachine.h"
//====
#define MSG_SCORE "HIGHSCORE :%d,%d,%d,%d,%d"
#define FILE_SCORE "Data"
#define FILE_CONFIG "config.ini"
//====
class Game{
private:

    ///boolean to set if the Game running
    bool m_bRunning=false;

    SDL_Window *g_pWindow=NULL;
    SDL_Renderer *g_pRenderer=NULL;

    ///variable to get/set State to display
    /// \sa GameStateMachine
    GameStateMachine *m_pGameStateMachine;

    static Game* s_instance;

    int width;

    int height;

    std::string lang;

    int highScore[5]={15,10,5,0,0};

    int key=100;

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

    void setLang(std::string l){
        if(l!="EN"&&l!="FR"){
            l="EN";
        }
        lang=l;
    }

    std::string getLang(){
        return lang;
    }

    int getHighScore(int i){
        return highScore[i];
    }

    void setHighScore(int val,int i){
        highScore[i]=val;
    }
    void encryptFile(FILE *file,std::string data);

    void decryptFile(FILE *file);

    void checkHighScore(char *data);

    void saveScore();

    void parseFileConfig();

    void saveFileConfig();

    /**
        @brief init
        brief of initialization window and SDL library
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
        function to clean Window and free Up Memory
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
       get a size of window
       @return widthOfWindow
    */
    int getWindowWidth();

    /**
         @brief getWindowHeight
       get a size of window
       @return heightOfWindow
    */
    int getWindowHeight();

    /**
        @brief getStateMachine
        @return the current state of window
    */
    GameStateMachine *getStateMachine();

    void SetWindownShow(bool enable);
};
typedef Game theGame;
#endif // GAME_H_INCLUDED
