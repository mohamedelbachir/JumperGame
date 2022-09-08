#ifndef PLATEFORM_H_INCLUDED
#define PLATEFORM_H_INCLUDED
#include"GameObject.h"
enum stylePlateforme{
    REAL,
    FAKE
};
class Plateforme:public GameObject{
private :
    int type;
    bool isCollidePlayer;
public:
    Plateforme(LoaderParam *param,int style):GameObject(param){
        type=style;
        addTag("plateforme");
        isCollidePlayer=false;
    }

    ~Plateforme(){

    }

    void update(){
        if(acceleration.getY()==0)velocity.setY(2);
        GameObject::update();
    }

    void checkCollision(GameObject *other)override
    {

        if(other->getTag()=="player"&&!isCollidePlayer)
        {
            if(isCollide(other))
            {
                if(type==FAKE){
                    acceleration.setY(0.1);
                }
                isCollidePlayer=true;
            }
        }
    }
    void draw(){
        GameObject::draw();
    }

    void clean(){
        GameObject::clean();
    }
};

#endif // PLATEFORM_H_INCLUDED
