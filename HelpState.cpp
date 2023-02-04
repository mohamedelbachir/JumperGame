#include"HelpState.h"

std::string HelpState::stateID="HELP";

HelpState::~HelpState()
{

}

void HelpState::update()
{

    if(theInputHandler::instance()->isKeyDown(SDL_SCANCODE_ESCAPE)&&theGame::Instance()->getStateMachine()->getCurrentState()->getStateID()!="PLAY")
    {
        theGame::Instance()->getStateMachine()->popState();
        SDL_Delay(250);
    }

    if(player->getNumberOfHeart()>1){
        Objectif->changeTexte((theGame::Instance()->getLang()=="EN")?"You are Reach , Congrats"
                                                                    :"Tu as atteint le coeur, felicitation");
        Objectif->changeTexteColor(127,51,0,255);
        Objectif->getVector()->setX(theGame::Instance()->getWindowWidth()/2-Objectif->getWidth()/2);
    }

    if(player->isDead()){
         player->setHeart(1);
         player->getVector()->setX(pointPlayerSpawn.getX());
         player->getVector()->setY(pointPlayerSpawn.getY());
    }

    if(theInputHandler::instance()->isKeyDown(SDL_SCANCODE_LEFT)||theInputHandler::instance()->isKeyDown(SDL_SCANCODE_A)){
        leftPress=true;
    }

    if(theInputHandler::instance()->isKeyDown(SDL_SCANCODE_RIGHT)||theInputHandler::instance()->isKeyDown(SDL_SCANCODE_D)){
        rightPress=true;
    }

    if(rightPress&&leftPress&&!JumpPress){
        showPressJump=true;
    }

    if(theInputHandler::instance()->isKeyDown(SDL_SCANCODE_SPACE)&&showPressJump){
        JumpPress=true;
    }

    if(showPressJump&&!JumpPress){
        keyBoard->setOpacity(0);
        keyBoardJump->setOpacity(SDL_ALPHA_OPAQUE);
        ObjectifDisplay=true;
    }else{
        keyBoardJump->setOpacity(0);
        if(JumpPress){
            Objectif->setOpacity(SDL_ALPHA_OPAQUE);
        }
    }

    player->update();
    for(size_t i=0; i<listOfUIs.size(); i++)
    {
        listOfUIs[i]->update();

    }

    for(size_t i=0; i<plateformes.size(); i++)
    {
        plateformes[i]->checkCollisionToPlayer(player);
        plateformes[i]->update();

        player->checkCollision(plateformes[i]);

    }

}

void HelpState::render()
{

    for(size_t i=0; i<listOfUIs.size(); i++)
    {
        listOfUIs[i]->draw();
    }
    for(size_t i=0; i<plateformes.size(); i++)
    {
        plateformes[i]->draw();
    }

    if(player->getNumberOfHeart()>1){
       if(tcount.attendre(1000)){
         theGame::Instance()->getStateMachine()->popState();
       }
    }
    player->draw();
}

bool HelpState::onEnter()
{
    //==
    thefontManager::Instance()->load("assets/fonts/big_noodle_titling.ttf",55,"BIG TITLE");
    thefontManager::Instance()->load("assets/fonts/big_noodle_titling.ttf",45,"FONT TITLE");
    thefontManager::Instance()->load("assets/fonts/font.ttf",15,"FONT UI");
    thefontManager::Instance()->load("assets/fonts/font.ttf",20,"FONT UIX");

    //==
    TextureManager::Instance()->load("assets/UI/MenuTile.png","file",theGame::Instance()->getRenderer());
    TextureManager::Instance()->load("assets/images/landBg.jpg","Background",theGame::Instance()->getRenderer());

    //==== [Texture for Player] ====
    theTextureManager::Instance()->load("assets/images/player.png","player",theGame::Instance()->getRenderer());

    //==== [Texture for assets/Item      ] ====
    theTextureManager::Instance()->load("assets/images/spike.png","spike",theGame::Instance()->getRenderer());
    theTextureManager::Instance()->load("assets/images/trampoline2.png","trampoline",theGame::Instance()->getRenderer());
    theTextureManager::Instance()->load("assets/images/Heart.png","heart",theGame::Instance()->getRenderer());


    listOfUIs.push_back(new UI_Image("Background",theGame::Instance()->getWindowWidth()/2-1280/2,theGame::Instance()->getWindowHeight()-800));

    SDL_Rect rc[3]=
    {
        {0,64*8,64,64},//DEFAULT STATE SOURCE ON TILESHEET
        {64,64*8,64,64},//HOVER STATE ON TILESHEET
        {0,64*8,64,64}// CLICK STATE ON TILESHEET
    };
    UI_Button *btn_back=new UI_Button("idBtnBackBtn","file",25,25,64,64,rc,HelpToPlay);
    listOfUIs.push_back(btn_back);

    UI_Text *title=new UI_Text((theGame::Instance()->getLang()=="EN")?"TUTORIAL":"TUTORIEL",0,50,"FONT TITLE");
    title->getVector()->setX(theGame::Instance()->getWindowWidth()/2-title->getWidth()/2);
    title->changeTexteColor(127,51,0,255);

    listOfUIs.push_back(title);

    //==
    keyBoard=new UI_Text((theGame::Instance()->getLang()=="EN")?"(1) You can move using [arrow] key or ([A] : Left , [D]: Right)"
                                                                        :"(1)Deplacez avec fleche directionnelle ou ([A] : Gauche [D]: Droite)"
                                                                        ,0,pointPlayerSpawn.getY()+75,"FONT UI");
    keyBoard->getVector()->setX(pointPlayerSpawn.getX()-70);
    keyBoard->changeTexteColor(0,0,0,255);

    listOfUIs.push_back(keyBoard);

    //==
    warning=new UI_Text((theGame::Instance()->getLang()=="EN")?"(Warning !!!)"
                                                                        :"(Attention !!!) "
                                                                        ,0,500-50*3+4,"FONT UI");
    warning->getVector()->setX(130-warning->getWidth());
    warning->changeTexteColor(255,0,0,255);

    listOfUIs.push_back(warning);

    //==
    keyBoardJump=new UI_Text((theGame::Instance()->getLang()=="EN")?"(2) To Jump you can Press [SPACE]"
                                                                        :"(2) Pour Sauter appuyez sur [ESPACE] "
                                                                        ,0,keyBoard->getVector()->getY()-keyBoard->getHeight()-30,"FONT UI");
    keyBoardJump->getVector()->setX(keyBoard->getVector()->getX()+keyBoard->getWidth()-180);
    keyBoardJump->changeTexteColor(0,0,0,255);
    keyBoardJump->setOpacity(0);

    listOfUIs.push_back(keyBoardJump);

    //==
    Objectif=new UI_Text((theGame::Instance()->getLang()=="EN")?"(i) So your goal is to get the heart and try to not fall"
                                                                        :"(i) Votre but est d'atteindre le coeur"
                                                                        ,0,title->getVector()->getY()+title->getHeight()+20,"FONT UIX");
    Objectif->getVector()->setX(theGame::Instance()->getWindowWidth()/2-Objectif->getWidth()/2);
    Objectif->changeTexteColor(0,0,0,255);
    Objectif->setOpacity(0);

    listOfUIs.push_back(Objectif);

    //==
    player=new Player(new LoaderParam(pointPlayerSpawn.getX(),
                                      pointPlayerSpawn.getY(),
                                      28,32,"player"));

    player->setHeart(1);

    //== Construction of Guide Scene

    //**
    BuildPlateforme(100,500,REAL,NONE,false);
    BuildPlateforme(132,500,REAL,NONE,false);

    //     **
    //**
    BuildPlateforme(132+32*4,500-50,REAL,NONE,false);
    BuildPlateforme(132+32*5,500-50,REAL,NONE,false);

    //    **
    //     **
    //**
    BuildPlateforme(132+32*2+10,500-50*3+8*1.5,FAKE,NONE,false);
    BuildPlateforme(132+20,500-50*3+8*1.5,REAL,SPIKE,false);
    BuildPlateforme(132+32*4,500-50*3+8*1.5,REAL,NONE,false);

    //    ***
    //     **
    //**
    BuildPlateforme(132+32*5,500-50*3+8*1.5,REAL,NONE,false);
    BuildPlateforme(132+32*8,500-50*3+8*1.5,REAL,TRAMPO,false);

    //      *
    //  &
    //
    //    ***
    //     **
    //**
    BuildPlateforme(132+32*2,500-50*5+8*1.5,REAL,EMPTY,false);

    BuildPlateforme(theGame::Instance()->getWindowWidth()-32*3,500-50*7+2*8*1.5,REAL,HEART,false);

    std::cout<<"enter Help State"<<std::endl;
    return true;
}

void HelpState::BuildPlateforme(int x,int y,int type,ItemType items,bool isMove)
{
    std::string file;

    if(type==REAL)
    {
        file="real_plateform";
    }
    else
    {
        file="fake_plateform";
    }

    Plateforme *plateform=new Plateforme(new LoaderParam( x,
                                         y,
                                         32,8,file),type,items,isMove);
    plateform->scale(1.5);
    plateformes.push_back(plateform);

}
bool HelpState::onExit()
{
    //thefontManager::Instance()->cleanUp();

    std::cout<<"exit start of help state"<<std::endl;
    thefontManager::Instance()->clearFromFontMap("FONT TITLE");
    thefontManager::Instance()->clearFromFontMap("BIG TITLE");
    thefontManager::Instance()->clearFromFontMap("FONT TITLE");
    thefontManager::Instance()->clearFromFontMap("FONT UI");

    for(size_t i=0; i<listOfUIs.size(); i++)
    {
        listOfUIs[i]->clean();
    }
    listOfUIs.clear();

    std::vector<Plateforme*>::iterator it=plateformes.begin();
    for(size_t i=0; i<plateformes.size(); i++)
    {
        plateformes[i]->clean();
        plateformes.erase(it+i);
    }

    plateformes.clear();
    player->clean();
    delete player;

    std::cout<<"exit end of help state"<<std::endl;
    return true;
}

void HelpState::HelpToPlay(){
    theGame::Instance()->getStateMachine()->popState();
}

std::string HelpState::getStateID()const
{
    return stateID;
}
