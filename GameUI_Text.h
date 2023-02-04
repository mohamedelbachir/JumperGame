#ifndef GAMEUI_TEXT_H_INCLUDED
#define GAMEUI_TEXT_H_INCLUDED
#include"GameUI.h"
#include"FontManager.h"
#include<sstream>
class UI_Text:public GameUI
{
private:
    std::string FontId;
    std::string texte=" ";

    SDL_Rect src;
    SDL_Color textColor= {0,0,0,255};

    static int instance;

    bool isInit;

    bool fontChange=false;

        Uint32 wrapLength(std::string str){
            std::vector<int> charLen;
            int k=0;
            for(int i=0;i<str.length();i++){
                if(str[i]!='\n'){
                    k++;
                }else{
                    charLen.push_back(k);
                    k=0;
                }
            }
            int great=0;
            for(int i=0;i<charLen.size();i++){
                if(great<charLen[i]){
                    great=charLen[i];
                }
            }
            charLen.clear();
            return great;
       }

public:


    UI_Text(std::string texte,int x,int y,std::string fontId)
    {

        std::stringstream ss;
        ss<<instance;
        std::string ext;
        ss>>ext;

        Id="texte"+ext;

        position=Vector2D(x,y);

        isInit=true;

        this->FontId=fontId;

        changeTexte(texte);

        instance++;
    }
    ~UI_Text(){

    }

    void update()override
    {

    }

    void draw()override
    {

        src= {0,0,width,height};
        SDL_SetTextureColorMod(theTextureManager::Instance()->getTextureMap(Id),textColor.r,
                                                                    textColor.g,textColor.b);
        theTextureManager::Instance()->draw(Id,position.getX(),position.getY()
                                            ,width,height,src,theGame::Instance()->getRenderer());
        /*Just for debugging*/
        //src.x=position.getX();
        //src.y=position.getY();

        //SDL_SetRenderDrawColor(theGame::Instance()->getRenderer(),0,0,0,255);
        //SDL_RenderDrawRect(theGame::Instance()->getRenderer(),&src);
    }


    void clean()override
    {
        thefontManager::Instance()->clearFromFontMap(FontId);
        theTextureManager::Instance()->clearFromTextureMap(Id);
    }

    void changeTexte(std::string texte)
    {
        SDL_Color nativeColor={255,255,255,255};
        int val=0;
        if(texte.length()>100){
             val=wrapLength(texte);
        }
        Uint32 wrap=val*TTF_FontLineSkip(thefontManager::Instance()->getFontMap(FontId))/3;
        if(wrap>20){
            wrap-=20;
        }
        if(isInit){

            this->texte=texte;

            SDL_Surface *t_surface=(wrap!=0)? TTF_RenderText_Blended_Wrapped(thefontManager::Instance()->getFontMap(FontId),texte.c_str(),nativeColor,wrap)
                                            : TTF_RenderText_Blended(thefontManager::Instance()->getFontMap(FontId),texte.c_str(),nativeColor);

            SDL_Texture *texture = SDL_CreateTextureFromSurface(theGame::Instance()->getRenderer(),
                                   t_surface);

            theTextureManager::Instance()->setTexture(Id,texture);

            SDL_QueryTexture(texture,NULL, NULL,&width, &height);

            isInit=false;

        }else if(this->texte!=texte||fontChange){

            this->texte=texte;

            SDL_Surface *t_surface=(wrap!=0)? TTF_RenderText_Blended_Wrapped(thefontManager::Instance()->getFontMap(FontId),texte.c_str(),nativeColor,wrap)
                                            : TTF_RenderText_Blended(thefontManager::Instance()->getFontMap(FontId),texte.c_str(),nativeColor);

            SDL_Texture *texture = SDL_CreateTextureFromSurface(theGame::Instance()->getRenderer(),
                                   t_surface);

            theTextureManager::Instance()->setTexture(Id,texture);

            SDL_QueryTexture(texture,NULL, NULL,&width, &height);

            SDL_FreeSurface(t_surface);
        }
    }

    void changeTexte(int val){

        std::stringstream ss;
        ss<<val;

        std::string txt;
        ss>>txt;

        changeTexte(txt);
    }

    void setFontText(std::string fontPath)
    {
         if(thefontManager::Instance()->getFontMap(fontPath)!=NULL){
            fontChange=true;
            FontId=fontPath;
            changeTexte(texte);
            fontChange=false;
         }
    }

    void changeTexteColor(int r,int g,int b,int a){
        textColor.r=r;
        textColor.g=g;
        textColor.b=b;
        textColor.a=a;
    }


};

#endif // GAMEUI_TEXT_H_INCLUDED
