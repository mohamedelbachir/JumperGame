#include"AboutState.h"
#define CONTENT_COLOR SDL_Colour{0,0,0,255}

std::string AboutState::stateID="ABOUT";

AboutState::~AboutState()
{

}

void AboutState::update()
{

    if(theInputHandler::instance()->isKeyDown(SDL_SCANCODE_ESCAPE)&&theGame::Instance()->getStateMachine()->getCurrentState()->getStateID()!="PLAY")
    {
        theGame::Instance()->getStateMachine()->popState();
        SDL_Delay(250);
    }

    for(size_t i=0; i<listOfUIs.size(); i++)
    {
        //listOfUIs[i]->setOpacity(counter);
        listOfUIs[i]->update();
    }

    /*if(counter<=SDL_ALPHA_OPAQUE-3){
        counter+=2;
    }*/
}

void AboutState::render()
{

    for(size_t i=0; i<listOfUIs.size(); i++)
    {
        listOfUIs[i]->draw();
    }
}

bool AboutState::onEnter()
{
    thefontManager::Instance()->load("assets/fonts/big_noodle_titling.ttf",55,"BIG TITLE");

    thefontManager::Instance()->load("assets/fonts/big_noodle_titling.ttf",40,"FONT TITLE");
    thefontManager::Instance()->load("assets/fonts/font.ttf",30,"FONT UI");

    TextureManager::Instance()->load("assets/UI/MenuTile.png","file",theGame::Instance()->getRenderer());
    TextureManager::Instance()->load("assets/images/landBg.jpg","Background",theGame::Instance()->getRenderer());

    listOfUIs.push_back(new UI_Image("Background",theGame::Instance()->getWindowWidth()/2-1280/2,theGame::Instance()->getWindowHeight()-800));

    SDL_Rect rc[3]=
    {
        {0,64*8,64,64},//DEFAULT STATE SOURCE ON TILESHEET
        {64,64*8,64,64},//HOVER STATE ON TILESHEET
        {0,64*8,64,64}// CLICK STATE ON TILESHEET
    };
    UI_Button *btn_back=new UI_Button("idBtnBackBtn","file",25,25,64,64,rc,AboutToPlay);
    listOfUIs.push_back(btn_back);

    UI_Text *t_title=new UI_Text("JUMPER V1.0",0,130,"BIG TITLE");
    t_title->getVector()->setX(theGame::Instance()->getWindowWidth()/2-t_title->getWidth()/2);
    t_title->changeTexteColor(CONTENT_COLOR.r,CONTENT_COLOR.b,CONTENT_COLOR.g,CONTENT_COLOR.a);
    listOfUIs.push_back(t_title);

    UI_Text *t_lauteur=new UI_Text((theGame::Instance()->getLang()=="FR")?"PROGRAMMEUR/DESIGNEUR":"PROGRAMMER/DESIGNER",0,t_title->getVector()->getY()+t_title->getHeight()+15,"FONT TITLE");
    t_lauteur->getVector()->setX(theGame::Instance()->getWindowWidth()/2-t_lauteur->getWidth()/2);
    t_lauteur->changeTexteColor(127,51,0,255);
    listOfUIs.push_back(t_lauteur);

    UI_Text *t_auteur=new UI_Text("{DEV/PB};",0,t_lauteur->getVector()->getY()+t_lauteur->getHeight()-5,"FONT UI");
    t_auteur->getVector()->setX(theGame::Instance()->getWindowWidth()/2-t_auteur->getWidth()/2);
    t_auteur->changeTexteColor(CONTENT_COLOR.r,CONTENT_COLOR.b,CONTENT_COLOR.g,CONTENT_COLOR.a);
    listOfUIs.push_back(t_auteur);

    UI_Text *t_ltools=new UI_Text((theGame::Instance()->getLang()=="FR")?"OUTILS/TECHNOLOGIE":"TOOLS/TECHNOLOGY",0,t_auteur->getVector()->getY()+t_auteur->getHeight()+15,"FONT TITLE");
    t_ltools->getVector()->setX(theGame::Instance()->getWindowWidth()/2-t_ltools->getWidth()/2);
    t_ltools->changeTexteColor(127,51,0,255);
    listOfUIs.push_back(t_ltools);

    UI_Text *t_tools=new UI_Text("C/C++,SDL",0,t_ltools->getVector()->getY()+t_ltools->getHeight()-5,"FONT UI");
    t_tools->getVector()->setX(theGame::Instance()->getWindowWidth()/2-t_tools->getWidth()/2);
    t_tools->changeTexteColor(CONTENT_COLOR.r,CONTENT_COLOR.b,CONTENT_COLOR.g,CONTENT_COLOR.a);
    listOfUIs.push_back(t_tools);

    UI_Text *t_lother=new UI_Text((theGame::Instance()->getLang()=="FR")?"CREATION SON":"SOUND MAKER",0,t_tools->getVector()->getY()+t_tools->getHeight()+15,"FONT TITLE");
    t_lother->getVector()->setX(theGame::Instance()->getWindowWidth()/2-t_lother->getWidth()/2);
    t_lother->changeTexteColor(127,51,0,255);
    listOfUIs.push_back(t_lother);

    UI_Text *t_other=new UI_Text("BXFR",0,t_lother->getVector()->getY()+t_lother->getHeight()-5,"FONT UI");
    t_other->getVector()->setX(theGame::Instance()->getWindowWidth()/2-t_other->getWidth()/2);
    t_other->changeTexteColor(CONTENT_COLOR.r,CONTENT_COLOR.b,CONTENT_COLOR.g,CONTENT_COLOR.a);
    listOfUIs.push_back(t_other);

    /*for(size_t i=0; i<listOfUIs.size(); i++)
    {
        listOfUIs[i]->setOpacity(0);
    }
    */
    std::cout<<"enter about State"<<std::endl;
    return true;
}

bool AboutState::onExit()
{

    std::cout<<"exit of about state"<<std::endl;
    thefontManager::Instance()->clearFromFontMap("FONT TITLE");
    for(size_t i=0; i<listOfUIs.size(); i++)
    {
        listOfUIs[i]->clean();
    }
    listOfUIs.clear();
    std::cout<<"exit end of pause state"<<std::endl;
    return true;
}

void AboutState::AboutToPlay(){
    theGame::Instance()->getStateMachine()->popState();
}

std::string AboutState::getStateID()const
{
    return stateID;
}
