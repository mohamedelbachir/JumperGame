#ifndef ABOUTSTATE_H_INCLUDED
#define ABOUTSTATE_H_INCLUDED
#include "GameState.h"
#include"GameObject.h"
#include"listOfEntity.h"
class AboutState:public GameState
{
private:
    std::vector<GameUI *>listOfUIs;
    static std::string stateID;

    int counter=0;
public:

    AboutState()
    {

    }

    ~AboutState();

    virtual void update()override;

    virtual void render()override;

    virtual bool onEnter()override;

    virtual bool onExit()override;

    static void AboutToPlay();

    virtual std::string getStateID()const override;

};
#endif // ABOUTSTATE_H_INCLUDED
