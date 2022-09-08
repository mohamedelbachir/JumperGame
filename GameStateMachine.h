#ifndef GAMESTATEMACHINE_H_INCLUDED
#define GAMESTATEMACHINE_H_INCLUDED
#include"GameState.h"
#include<vector>
class GameStateMachine{
private:
    std::vector<GameState*>m_gameStates;
public:
    void pushState(GameState *pState);

    void changeState(GameState *pState);

    void popState();

    void update();

    void render();
};

#endif // GAMESTATEMACHINE_H_INCLUDED
