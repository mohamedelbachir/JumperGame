#ifndef HELPSTATE_H_INCLUDED
#define HELPSTATE_H_INCLUDED
#include "GameState.h"
#include"GameObject.h"
#include"listOfEntity.h"

#include"Player.h"
class HelpState:public GameState
{
private:
    std::vector<GameUI *>listOfUIs;
    static std::string stateID;

    Player *player;
    std::vector<Plateforme*> plateformes;

    Vector2D pointPlayerSpawn;

    UI_Text *Objectif;


    Timer tcount;
    Timer nextTips;

    UI_Text *keyBoardJump;

    UI_Text *warning;

    UI_Text *keyBoard;


    bool leftPress=false;
    bool rightPress=false;
    bool JumpPress=false;

    bool showPressJump=false;
    bool ObjectifDisplay=false;

public:

    HelpState()
    {
        pointPlayerSpawn=Vector2D(100,400);
    }

    ~HelpState();

    void BuildPlateforme(int x,int y,int type,ItemType items,bool isMove=false);

    static void HelpToPlay();

    virtual void update()override;

    virtual void render()override;

    virtual bool onEnter()override;

    virtual bool onExit()override;

    virtual std::string getStateID()const override;

};
#endif // HELPSTATE_H_INCLUDED
