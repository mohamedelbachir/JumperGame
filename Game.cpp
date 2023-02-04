#include<fstream>
#include<cstring>
#include"Game.h"
#include"InputHandler.h"
#include"TextureManager.h"
#include"SoundManager.h"
#include"MenuState.h"

Game* Game::s_instance=NULL;

Game::Game() {}

bool Game::init(const char*title,int xpos,int ypos,int width,int height,int flags,bool fullscreen)
{

    this->width=width;

    this->height=height;

    //initialization of SDL library
    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER)<0)
    {
        std::cout<<"Impossible to initialize SDL , Error : "<<SDL_GetError()<<std::endl;
        return false;
    }
    FILE *fileLang=fopen("lang.ini","r");
    if(fileLang==NULL)
    {
        SDL_Locale *l=SDL_GetPreferredLocales();
        fileLang=fopen("lang.ini","w+");
        if(SDL_strcmp(l->language,"FR")==0)
        {
            fprintf(fileLang,"%s",l->language);
        }
        else
        {
            fprintf(fileLang,"EN");
        }
    }
    else
    {
        char s[2];
        fscanf(fileLang,"%s",s);
        setLang(s);
    }

    FILE *fscore=fopen(FILE_SCORE,"r");

    if(fscore==NULL)
    {
        encryptFile(fopen(FILE_SCORE,"w+"),"HIGHSCORE :15,10,5,0,0");
    }
    else
    {
        decryptFile(fscore);
    }

    parseFileConfig();

    if(fullscreen)
    {
        flags=SDL_WINDOW_FULLSCREEN;
    }

    g_pWindow=SDL_CreateWindow(title,xpos,ypos,width,height,flags);
    if(g_pWindow==NULL)
    {
        std::cout<<"Impossible to create Window , Error : "<<SDL_GetError()<<std::endl;
        return false;
    }

    g_pRenderer=SDL_CreateRenderer(g_pWindow,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    if(g_pRenderer==NULL)
    {
        std::cout<<"Impossible to create Renderer , Error : "<<SDL_GetError()<<std::endl;
        return false;
    }
    //TO display transparent rect
    SDL_SetRenderDrawBlendMode(g_pRenderer,SDL_BLENDMODE_BLEND);

    m_pGameStateMachine=new GameStateMachine();
    m_pGameStateMachine->changeState(new MenuState());//=> starting a Menu State

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1");

    m_bRunning=true;
    std::cout<<"Create Window Successfully ... "<<std::endl;
    return true;
}

void Game::parseFileConfig(){
    FILE *fconfig=fopen(FILE_CONFIG,"r");
    if(fconfig){
        char s[255];
        char name[20];
        int data;
        while(fgets(s,255,fconfig)!=NULL){

            sscanf(s,"%s :%d",&name,&data);
            if(strcmp(name,"Sfx")==0){
                theSoundManager::instance()->setPlayingSound(data);
            }

            if(strcmp(name,"Music")==0){
                theSoundManager::instance()->setPlayingMusic(data);
            }
        }
        delete []name;
        delete []s;
    }else{
        fconfig=fopen(FILE_CONFIG,"w+");
        fprintf(fconfig,"Sfx :1\nMusic :1");
    }
    fclose(fconfig);
}
void Game::saveFileConfig(){
    FILE *fconfig=fopen(FILE_CONFIG,"w+");
    fprintf(fconfig,"Sfx :%d\n",theSoundManager::instance()->isSoundPlaying());
    fprintf(fconfig,"Music :%d",theSoundManager::instance()->isMusicPlaying());
    fclose(fconfig);
}

void Game::encryptFile(FILE *file,std::string data)
{
    std::string crypted="";
    for(int i=0; i<data.length(); i++)
    {
        char c=data[i]+key;
        crypted+=c;
    }
    fprintf(file,"%s",crypted.c_str());
    fclose(file);
}

void Game::decryptFile(FILE *file)
{
    char data[255];
    fscanf(file,"%s",data);
    for(int i=0; i<SDL_strlen(data); i++)
    {
        data[i]=data[i]-key;
    }
    fclose(file);
    checkHighScore(data);
}

void Game::checkHighScore(char *data)
{
    char s[255];
    sscanf(data,"%s :%d,%d,%d,%d,%d",s,&highScore[0],&highScore[1]
                                      ,&highScore[2],&highScore[3]
                                      ,&highScore[4]);
    /*for(int i=0;i<5;i++){
        std::cout<<"HS : "<<highScore[i]<<std::endl;
    }*/
    delete []data;
    delete []s;
}

void Game::saveScore()
{
    char data[255];
    sprintf(data,MSG_SCORE,highScore[0],highScore[1]
                          ,highScore[2],highScore[3]
                          ,highScore[4]);
    encryptFile(fopen(FILE_SCORE,"w+"),data);
    delete []data;
}

void Game::handleEvent()
{
    theInputHandler::instance()->update();
}

void Game::update()
{
    m_pGameStateMachine->update();
}

void Game::render()
{

    //color of background renderer
    SDL_SetRenderDrawColor(g_pRenderer,255,255,255,255);

    //clear window renderer
    SDL_RenderClear(g_pRenderer);

    m_pGameStateMachine->render();

    //show the window
    SDL_RenderPresent(g_pRenderer);
}

GameStateMachine *Game::getStateMachine()
{
    return m_pGameStateMachine;
}

int Game::getWindowWidth()
{
    return width;
}

int Game::getWindowHeight()
{
    return height;
}

void Game::clean()
{
    SDL_DestroyWindow(g_pWindow);
    SDL_DestroyRenderer(g_pRenderer);
    m_pGameStateMachine->popState();
    theTextureManager::Instance()->cleanUp();
    theSoundManager::instance()->cleanUp();
    thefontManager::Instance()->cleanUp();
    SDL_Quit();
    saveFileConfig();
}


bool Game::running()
{
    return m_bRunning;
}

void Game::quit()
{
    m_bRunning=false;
}

SDL_Renderer *Game::getRenderer()
{
    return g_pRenderer;
}
void Game::SetWindownShow(bool enable)
{
    if(enable)
        SDL_ShowWindow(g_pWindow);
    else
        SDL_HideWindow(g_pWindow);

}
