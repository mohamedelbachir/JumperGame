#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include"GameObject.h"
#include"InputHandler.h"
#include"AnimManger.h"
#define MAX_VELOCITY 8.f
#define JUMP_HEIGHT 6
#define GRAVITY 0.2
enum stateAnim
{
    IDLE,
    JUMP
};
class Player:public GameObject,public AnimManager
{
private:
    bool isgrounded=false;
    GameObject *refCollide;

public:

    Player(LoaderParam *param):GameObject(param),AnimManager(param->getAnimSpeed())
    {

        std::vector<SDL_Rect> idleAnim;

        std::vector<SDL_Rect> jumpAnim;

        idleAnim.push_back(
            {0,0,28,32}
        );
        jumpAnim.push_back(
            {28,0,28,32}
        );

        addAnimationFrame(IDLE,idleAnim);

        addAnimationFrame(JUMP,jumpAnim);

    }

    ~Player() {}

    void draw()override
    {
        GameObject::draw();
    }

    void update()override
    {

        if(position.getY()>theGame::Instance()->getWindowHeight()+10)
        {
            position.setY(-10);
        }
        if(theInputHandler::instance()->isKeyDown(SDL_SCANCODE_LEFT))
        {
            velocity.setX(-2);
            if(position.getX()+getWidth()<0)
            {
                position.setX(theGame::Instance()->getWindowWidth()-getWidth());
                velocity.setX(2);
            }
        }
        else
        {

            if(theInputHandler::instance()->isKeyDown(SDL_SCANCODE_RIGHT))
            {
                velocity.setX(2);
                if(position.getX()>theGame::Instance()->getWindowWidth()+getWidth())
                {
                    position.setX(-getWidth()+2);
                    velocity.setX(-2);
                }
            }
            else
            {
                if(isgrounded)
                    velocity.setX(0);
            }

        }

        if(refCollide!=NULL)
        {
            if(!isCollide(refCollide))
            {
                isgrounded=false;
            }
        }
        else
        {
            isgrounded=false;
        }

        if(theInputHandler::instance()->isKeyDown(SDL_SCANCODE_SPACE)&&isgrounded)
        {

            velocity.setY(-JUMP_HEIGHT);
            changeAnimationTo(JUMP);
            isgrounded=false;
        }

        if(velocity.getY()>0){
            changeAnimationTo(IDLE);
        }

        if(!isgrounded)
        {
            if(velocity.getY()<MAX_VELOCITY){
               acceleration.setY(GRAVITY);
            }else{
               velocity.setY(MAX_VELOCITY);
            }
        }
        else
        {
            velocity.setY(refCollide->getVelocity().getY());
            acceleration.setY(refCollide->getAcceleration().getY());
        }
        //source de dl'animation
        src=getAnimRect();

        GameObject::update();
    }
    bool isGrounted(){
        return isgrounded;
    }

    void checkCollision(GameObject *other)override
    {

        if(other->getTag()=="plateforme")
        {
            if(!isgrounded)
            {
                if(isCollide(other))
                {
                    isgrounded=true;
                    refCollide=other;
                }
            }
        }
    }

    bool en_collision(SDL_Rect& a, SDL_Rect&b)override
    {
        bool checkAABBCollision;

        checkAABBCollision=GameObject::en_collision(a,b);


        if(checkAABBCollision)
        {
            if(velocity.getY()<0)
            {
                checkAABBCollision=false;
            }
            else
            {
                if(a.y>=b.y)
                {
                    checkAABBCollision=false;
                }
                else if(a.y+a.h>=b.y+b.h)
                {
                    checkAABBCollision=false;
                }
                if(checkAABBCollision){
                    if(a.x+a.w-a.w/8<=b.x)
                    {
                        checkAABBCollision=false;
                    }
                    else if(a.x+3>=b.x+b.w)
                    {
                        checkAABBCollision=false;
                    }
                }
                if(checkAABBCollision){
                     if(a.y+a.h>b.y+2){
                        position.setY(b.y-a.h+2);
                     }
                }

            }
        }

        return checkAABBCollision;
    }

    void clean()override
    {
        GameObject::clean();
        cleanAnimationData();
    }
};

#endif // PLAYER_H_INCLUDED
