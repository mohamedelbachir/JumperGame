#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED
#include"Game.h"
#include"TextureManager.h"
#include"LoaderParam.h"
#include"Vector2D.h"
class GameObject
{
protected:

    Vector2D position;

    Vector2D velocity;

    Vector2D acceleration;

    std::string textureID;

    int width;

    int height;

    SDL_Rect src;

    std::string tag;

public:

    GameObject(LoaderParam *param)
    {
        position=Vector2D(param->getPosition().x,param->getPosition().y);

        velocity=Vector2D(0,0);

        acceleration=Vector2D(0,0);

        width=param->getPosition().w;

        height=param->getPosition().h;

        textureID=param->getTextureID();

        src={0,0,width,height};


    }
    virtual ~GameObject(){}
    virtual void draw()
    {
        theTextureManager::Instance()->draw(textureID
                                            ,(int)position.getX(),position.getY(),width,height
                                            ,src
                                            ,theGame::Instance()->getRenderer());
    };

    virtual void update()
    {
        velocity+=acceleration;
        position+=velocity;
    }

    virtual void clean() {}

    virtual void checkCollision(GameObject *other){}

    virtual bool isCollide(GameObject *other)
    {
        SDL_FRect otherRect;
        otherRect.x=other->getVector()->getX();
        otherRect.y=other->getVector()->getY();
        otherRect.w=other->getWidth();
        otherRect.h=other->getHeight();

        SDL_FRect rpos;
        rpos.x=position.getX();
        rpos.y=position.getY();
        rpos.w=width;
        rpos.h=height;

        return en_collision(rpos, otherRect);
    }

    virtual bool en_collision(SDL_FRect& a, SDL_FRect& b){
        float topA,leftA,rightA,bottomA;
        float topB,leftB,rightB,bottomB;
        topA=a.y;
        leftA=a.x;
        rightA=a.x+a.w;
        bottomA=a.y+a.h;

        topB=b.y;
        leftB=b.x;
        rightB=b.x+b.w;
        bottomB=b.y+b.h;

        if (bottomA < topB)
        {
            return false;
        }
        if (topA> bottomB)
        {
            return false;
        }
        if (rightA < leftB)
        {
            return false;
        }
        if (leftA> rightB)
        {
            return false;
        }
        return true;

    }

    Vector2D* getVector(){
        return &position;
    }

    void scale(float vscale){
        if(vscale>0){
          width*=vscale;
          height*=vscale;
        }
    }
    int getWidth(){
        return width;
    }

    int getHeight(){
        return height;
    }

    void addTag(std::string tagName){
        tag=tagName;
    }

    std::string getTag(){
        return tag;
    }

    Vector2D* getVelocity(){
        return &velocity;
    }

    Vector2D getAcceleration(){
        return acceleration;
    }

    void setAcceleration(Vector2D a){
        acceleration=a;
    }
};

#endif // GAMEOBJECT_H_INCLUDED
