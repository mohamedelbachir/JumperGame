#include<cstdlib>
#include<ctime>
#include"PlayState.h"
#include"listOfEntity.h"
#define MINSPACETILE 50
#define MAXPLATEFORME 50
std::string PlayState::stateID="PLAY";

PlayState::~PlayState(){}


void PlayState::update(){

    for(int i=0;i<plateformes.size();i++){
        int ymax=abs(theGame::Instance()->getWindowHeight()-yInit);
        if(plateformes[i]->getPosition().getY()>theGame::Instance()->getWindowHeight()+ymax){
            std::vector<GameObject*>::iterator it;
            it=plateformes.begin();
            plateformes[i]->clean();
            delete plateformes[i];
            plateformes.erase(it+i);
            generatePlateforme();
            continue;
        }
        player->checkCollision(plateformes[i]);
        plateformes[i]->checkCollision(player);
        plateformes[i]->update();
        player->checkCollision(plateformes[i]);
    }
    player->update();
}

void PlayState::render(){
    for(int i=0;i<plateformes.size();i++){
        plateformes[i]->draw();
    }
    player->draw();
    SDL_SetRenderDrawColor(theGame::Instance()->getRenderer(),0,0,255,255);
    SDL_Rect pile={xPile,yPile,wPile,hPile};
        SDL_RenderDrawRect(theGame::Instance()->getRenderer(),&pile);
}

void PlayState::generatePlateforme(){
    int x,y;
    x=rand()%(xPile+wPile-xPile+1)-xPile;
    y=yPile;

    int type=rand()%2;
    if(!isSponPlayer){
        if(plateformes.size()>1){
            if(type==FAKE){
                type=REAL;
            }
            player->getPosition().setX(x);
            player->getPosition().setY(y-player->getHeight());
            isSponPlayer=true;
        }
    }
    std::string file;

    if(type==REAL){
        file="real_plateform";
    }else{
        file="fake_plateform";
    }

    GameObject *plateform=new Plateforme(new LoaderParam( x,
                                                          y,
                                                          32,8,file),type);
    plateform->scale(1.5);
    plateformes.push_back(plateform);

}

bool PlayState::onEnter(){
    srand(time(NULL));
    wPile=theGame::Instance()->getWindowWidth()-32*1.5;
    xPile=0;

    theTextureManager::Instance()->load("assets/player.png","player",theGame::Instance()->getRenderer());

    player=new Player(new LoaderParam(100,
                                      300,
                                      28,32,"player"));
    player->addTag("player");
    //player->scale(1.5);

    theTextureManager::Instance()->load("assets/plateforme_0.png","real_plateform",theGame::Instance()->getRenderer());
    theTextureManager::Instance()->load("assets/plateforme_1.png","fake_plateform",theGame::Instance()->getRenderer());

    yInit=yPile=theGame::Instance()->getWindowHeight()-100;
    for(int i=0;i<MAXPLATEFORME;i++){
        generatePlateforme();
        yPile-=MINSPACETILE;
        hPile=abs(yPile);
    }
    std::cout<<"Enter game State"<<std::endl;
    return true;
}

bool PlayState::onExit(){

    std::cout<<"sortie game State"<<std::endl;

    theTextureManager::Instance()->clearFromTextureMap("player");
    theTextureManager::Instance()->clearFromTextureMap("plateforme0");
    for(int i=0;i<plateformes.size();i++){
        plateformes[i]->clean();
    }
    player->clean();
    plateformes.clear();
    return true;
}

std::string PlayState::getStateID()const{
    return stateID;
}
