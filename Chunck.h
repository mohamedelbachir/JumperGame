#ifndef CHUNCK_H_INCLUDED
#define CHUNCK_H_INCLUDED
#include<cstdlib>
#include<ctime>
#include"GameObject.h"
class Chunck
{
private :
    std::vector<GameObject*> listOfObject;
    SDL_Rect position;
public:
    Chunck(int x,int y,int w,int h,int randPlateforme){

        srand(time(NULL));
        position= {x,y,w,h};

        int oldPosX,oldPosY;

        int posX,posY;

        for(int i=0; i<randPlateforme; i++)
        {
            posX=rand()%(x+w-x+1)+x;
            posY=rand()%(y+h-y+1)+y;

            if(listOfObject.size()>0){
                if(oldpo)
            }
            oldPosX=posX;
            oldPosY=posY;
        }

    }
    ~Chunck(){}

    void update()
    {
        for(int i=0;i<listOfObject.size();i++){

        }

    }
    void draw()
    {
        for(int i=0;i<listOfObject.size();i++){

        }
    }

    void clean()
    {
        for(int i=0;i<listOfObject.size();i++){

        }
    }
};

#endif // CHUNCK_H_INCLUDED
