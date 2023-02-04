#ifndef GAMESTATEMACHINE_H_INCLUDED
#define GAMESTATEMACHINE_H_INCLUDED
#include"GameState.h"
#include<vector>
class GameStateMachine{
private:
    std::vector<GameState*>m_gameStates;
    bool isShowBackState=false;
public:
    void pushState(GameState *pState);

    void changeState(GameState *pState);

    void setDisplayBackState(bool enable);

    GameState *getCurrentState();

    void popState();

    void update();

    void clean();

    void render();
};

#endif // GAMESTATEMACHINE_H_INCLUDED
