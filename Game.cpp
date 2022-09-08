#include"Game.h"
#include"InputHandler.h"
#include"TextureManager.h"
#include"PlayState.h"
Game* Game::s_instance=NULL;

Game::Game(){}

bool Game::init(const char*title,int xpos,int ypos,int width,int height,int flags,bool fullscreen){

    this->width=width;

    this->height=height;

    //initialisation de SDL
    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER)<0){
        std::cout<<"Impossible d'initialiser la SDL , Erreur : "<<SDL_GetError()<<std::endl;
        return false;
    }
    if(fullscreen){
        flags=SDL_WINDOW_FULLSCREEN_DESKTOP;
    }
    g_pWindow=SDL_CreateWindow(title,xpos,ypos,width,height,flags);
    if(g_pWindow==NULL){
        std::cout<<"Impossible de creer window , Erreur : "<<SDL_GetError()<<std::endl;
        return false;
    }
    g_pRenderer=SDL_CreateRenderer(g_pWindow,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    if(g_pRenderer==NULL){
        std::cout<<"Impossible de creer Renderer , Erreur : "<<SDL_GetError()<<std::endl;
        return false;
    }

    m_pGameStateMachine=new GameStateMachine();
    m_pGameStateMachine->changeState(new PlayState());

    m_bRunning=true;
    return true;
}

void Game::handleEvent(){
    theInputHandler::instance()->update();
}

void Game::update(){
    m_pGameStateMachine->update();
}

void Game::render(){
    //color of background renderer
    SDL_SetRenderDrawColor(g_pRenderer,255,255,255,255);

    //clear window renderer
    SDL_RenderClear(g_pRenderer);

       m_pGameStateMachine->render();

    //show the window
    SDL_RenderPresent(g_pRenderer);
}

GameStateMachine *Game::getStateMachine(){
    return m_pGameStateMachine;
}

int Game::getWindowWidth(){
    return width;
}

int Game::getWindowHeight(){
    return height;
}

void Game::clean(){
    SDL_DestroyWindow(g_pWindow);
    SDL_DestroyRenderer(g_pRenderer);
    theTextureManager::Instance()->cleanUp();
    m_pGameStateMachine->popState();
    SDL_Quit();
}


bool Game::running(){
    return m_bRunning;
}

void Game::quit(){
    m_bRunning=false;
}

SDL_Renderer *Game::getRenderer(){
    return g_pRenderer;
}
