#ifndef PLAYSTATE_H_INCLUDED
#define PLAYSTATE_H_INCLUDED
#include<vector>
#include "GameState.h"
#include"GameObject.h"
#include"Player.h"
class PlayState:public GameState{
private:
      static std::string stateID;
      Player *player;
      std::vector<GameObject*> plateformes;

      int xPile,yPile,wPile,hPile;

      int yInit;

      bool isSponPlayer;

public:
    PlayState(){
       xPile=yPile=wPile=hPile=0;
       isSponPlayer=false;
    }

    ~PlayState();

    void generatePlateforme();

    virtual void update()override;

    virtual void render()override;

    virtual bool onEnter()override;

    virtual bool onExit()override;

    virtual std::string getStateID()const override;
};
#endif // PLAYSTATE_H_INCLUDED
