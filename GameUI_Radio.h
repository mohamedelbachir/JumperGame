#ifndef GAMEUI_RADIO_H_INCLUDED
#define GAMEUI_RADIO_H_INCLUDED
#include"GameUI.h"
#include<SDL_ttf.h>
#include<sstream>
#define MAX_TEXTURE_TARGET_SIZE 1000
struct radioElement{
    UI_Text  *text;
    UI_Image *radioShape;
    int Id;
};
class UI_Radio:public GameUI
{
private:

    bool isInit;
    std::vector<radioElement> listRadioElement;
    SDL_Rect src;
public:

    UI_Radio(int x,int y,int w,int h){
        Id="radio";
        width=w;
        height=h;
        position=Vector2D(x,y);
        SDL_Texture *shapeTexture;
        shapeTexture=SDL_CreateTexture(theGame::Instance()->getRenderer(),SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,w,h);
        theTextureManager::Instance()->setTexture(Id,shapeTexture);
    }

    ~UI_Radio(){
        theTextureManager::Instance()->clearFromTextureMap(Id);
    }

    void addItems(std::string items,std::string tFont,int id=-1){
        radioElement r;
        if(id==-1){
           r.Id=listRadioElement.size();
        }else{
            r.Id=id;
        }
        if(listRadioElement.size()==0){
            r.text=new UI_Text(items,0,0,tFont);
        }else{
            radioElement last=listRadioElement.back();
            r.text=new UI_Text(items,last.text->getVector()->getX(),last.text->getVector()->getY()+last.text->getHeight()+10,tFont);
        }
        r.radioShape=new UI_Image("CheckTile",r.text->getVector()->getX()+r.text->getWidth()+20,r.text->getVector()->getY(),0,0,64,64);
        listRadioElement.push_back(r);
    }

    void update()override
    {
        for(size_t i=0;i<listRadioElement.size();i++){
            listRadioElement[i].text->update();
            listRadioElement[i].radioShape->update();
        }
    }

    void draw()override
    {
        src= {0,0,width,height};
        SDL_SetRenderTarget(theGame::Instance()->getRenderer(), theTextureManager::Instance()->getTextureMap(Id));
        for(size_t i=0;i<listRadioElement.size();i++){
            listRadioElement[i].text->draw();
            listRadioElement[i].radioShape->draw();
        }
        SDL_SetRenderTarget(theGame::Instance()->getRenderer(),NULL);
        SDL_SetTextureBlendMode(theTextureManager::Instance()->getTextureMap(Id),SDL_BLENDMODE_BLEND);
        theTextureManager::Instance()->draw(Id, position.getX(),position.getY(),width,height,src,theGame::Instance()->getRenderer());
    }


    void clean()override
    {
        for(size_t i=0;i<listRadioElement.size();i++){
            listRadioElement[i].text->clean();
            listRadioElement[i].radioShape->clean();
        }
        listRadioElement.clear();
        theTextureManager::Instance()->clearFromTextureMap(Id);
    }
};

#endif // GAMEUI_RADIO_H_INCLUDED
