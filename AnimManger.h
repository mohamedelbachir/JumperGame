#ifndef ANIMMANGER_H_INCLUDED
#define ANIMMANGER_H_INCLUDED
#include<vector>
class AnimManager{
protected:

    std::map<int,std::vector<SDL_Rect>> arrayFrame;

    int curentAnimation=0;

    int animSpeed=1;

    int curentFrame=0;

public:

     AnimManager(int speedAnimation){

        animSpeed=speedAnimation;

     }

    ~AnimManager(){}

    void addAnimationFrame(int animID,std::vector<SDL_Rect> src)
    {
        arrayFrame[animID]=src;
    }

    SDL_Rect getAnimRect()
    {
        return arrayFrame[curentAnimation][curentFrame];
    }

    void changeAnimationTo(int animID)
    {
        curentAnimation=animID;
    }

    void setCurrentFrame(int cur)
    {
        curentFrame=cur;
    }

    void cleanAnimationData(){
        std::map<int,std::vector<SDL_Rect>>::iterator it;
        for(it=arrayFrame.begin();it!=arrayFrame.end();it++){
            it->second.clear();
        }
        arrayFrame.clear();
    }
};


#endif // ANIMMANGER_H_INCLUDED
