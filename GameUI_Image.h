#ifndef GAMEUI_IMAGE_H_INCLUDED
#define GAMEUI_IMAGE_H_INCLUDED
#include"GameUI.h"
#include<sstream>
class UI_Image:public GameUI{
private:
    SDL_Rect src;
    static int instance;
public:

    UI_Image(std::string idImage,int x,int y)
    {
        std::stringstream ss;
        ss<<instance;
        std::string ext;
        ss>>ext;

        Id="image"+ext;
        position=Vector2D(x,y);
        SDL_QueryTexture(theTextureManager::Instance()->getTextureMap(idImage),NULL,NULL,&width,&height);
        theTextureManager::Instance()->setTexture(Id,theTextureManager::Instance()->getTextureMap(idImage));
        src={0,0,width,height};
        instance++;
    }

    UI_Image(std::string idImage,int x,int y,int srcw,int srch):UI_Image(idImage,x,y)
    {
        src={0,0,srcw,srch};
        width=srcw;
        height=srch;
    }

    UI_Image(std::string idImage,int x,int y,int srcx,int srcy, int srcw,int srch):UI_Image(idImage,x,y,srcw,srch){
        src.x=srcx;
        src.y=srcy;
    }

    ~UI_Image(){
    }

    void update()override{
        GameUI::update();
    }

    void draw()override{
        theTextureManager::Instance()->draw(Id,position.getX(),position.getY()
                                            , width,height,src,theGame::Instance()->getRenderer());
    }

    void setSourceDisplay(SDL_Rect src){
        this->src=src;
    }

    void clean() override{
        TextureManager::Instance()->clearFromTextureMap(Id);
    }

};


#endif // GAMEUI_IMAGE_H_INCLUDED
