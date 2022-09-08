#ifndef LOADERPARAM_H_INCLUDED
#define LOADERPARAM_H_INCLUDED
#include<SDL.h>
class LoaderParam
{
private:

    std::string textureID;

    int animSpeed=1;

    SDL_Rect dst;
public:
    LoaderParam(int x,int y,int w,int h,std::string textureID,int speedAnim=1)
    {
        dst={x,y,w,h};

        animSpeed=speedAnim;

        this->textureID=textureID;
    }

    SDL_Rect getPosition()
    {
        return dst;
    }

    std::string getTextureID()
    {
        return textureID;
    }

    int  getAnimSpeed()
    {
        return animSpeed;
    }
};


#endif // LOADERPARAM_H_INCLUDED
