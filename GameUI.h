#ifndef GAMEUI_H_INCLUDED
#define GAMEUI_H_INCLUDED
#include"Vector2D.h"
#include<iostream>
#include<SDL.h>
#include"TextureManager.h"
#include"Game.h"
#include"InputHandler.h"
class GameUI
{
protected:
    Vector2D position;
    int width,height;
    std::string Id;
    int opacity=255;
    GameUI *parent=NULL;
    bool isCheckingMouse=false;
public:

    GameUI() {}

    virtual ~GameUI()
    {

    }

    virtual void update(){
        checkMouseEvent();
    }

    virtual void draw()=0;

    virtual void clean() {}

    Vector2D* getVector()
    {
        return &position;
    }

    int getWidth()
    {
        return width;
    }

    int getHeight()
    {
        return height;
    }

    void setOpacity(int val){
        opacity=val;
        SDL_SetTextureAlphaMod(theTextureManager::Instance()->getTextureMap(Id),opacity);
    }

    void setTextureColor(Uint8 r,Uint8 g,Uint8 b){
        SDL_SetTextureColorMod(theTextureManager::Instance()->getTextureMap(Id),r,g,b);
    }

    std::string getIdWidget(){
        return Id;
    }

    void setSize(int nW=-1,int nH=-1)
    {
        if(nW>0){
            width=nW;
        }
        if(nH>0){
            height=nH;
        }
    }
    void checkMouseEvent(){
        SDL_Rect shape;
        if(parent==NULL){
            shape.x=position.getX();
            shape.y=position.getY();
        }else{
            shape.x=position.getX()+parent->getVector()->getX();
            shape.y=position.getY()+parent->getVector()->getY();
        }
        shape.w=width;
        shape.h=height;
        SDL_Point mouse=theInputHandler::instance()->getMousePosition();
        if(SDL_PointInRect(&mouse,&shape)==SDL_TRUE){
            isCheckingMouse=true;
        }else{
            isCheckingMouse=false;
        }
    }

    bool isHover(){
       return isCheckingMouse;
    }

    bool isClick(){
        return isCheckingMouse&&theInputHandler::instance()->getMouseButtonState(LEFT);
    }

    void SetParent(GameUI *p){
        parent=p;
    }
};

#endif // GAMEUI_H_INCLUDED
