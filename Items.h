#ifndef ITEMS_H_INCLUDED
#define ITEMS_H_INCLUDED
#include"GameObject.h"
#include"Timer.h"
enum ItemType{
    SPIKE,
    TRAMPO,
    HEART,
    NONE,
    EMPTY

};
class Item:public GameObject{
private:
    Timer time;
    GameObject *plateformReference;
    bool visible=true;
    int velY=0;
    int dstY=0;
public:
    Item(LoaderParam *param,int type,GameObject *Pref=NULL):GameObject(param){

        switch(type){
            case SPIKE:
                addTag("spike");

            break;
            case TRAMPO:
                addTag("trampo");
            break;

            case HEART:
                addTag("heart");

            break;
        }
        plateformReference=Pref;
    }

    ~Item(){
        clean();
    }

    void update(){
        if(plateformReference!=NULL){
            position.setX(plateformReference->getVector()->getX()+plateformReference->getWidth()/2-getWidth()/2);
            if(getTag()=="spike"){
                if(time.attendre(1000)&&dstY==velY){
                    if(velY==0){
                        velY=getHeight()+4;
                    }else{
                        velY=0;
                    }
                }else{
                    if(dstY<velY){
                        dstY+=1;
                    }else{
                        if(dstY>velY)dstY-=1;
                    }
                }
                position.setY(plateformReference->getVector()->getY()-getHeight()+2+dstY);
            }else{
                position.setY(plateformReference->getVector()->getY()-getHeight()+2);
            }
        }
        GameObject::update();
    }

    /*function to avoid error when i try to delete the item after player taking it ..*/
    void desSpwan(){
        visible=false;
    }

    void draw(){
        if(visible)GameObject::draw();
    }

    void clean(){
        GameObject::clean();
    }
};


#endif // ITEMS_H_INCLUDED
