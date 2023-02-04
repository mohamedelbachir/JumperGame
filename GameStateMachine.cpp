#include<cstdlib>
#include"GameStateMachine.h"
void GameStateMachine::pushState(GameState* pState){
    m_gameStates.push_back(pState);
    m_gameStates.back()->onEnter();
}
void GameStateMachine::popState(){
    if(!m_gameStates.empty()){
        if(m_gameStates.back()->onExit()){
            m_gameStates.back()=nullptr;
            delete m_gameStates.back();
            std::vector<GameState*>::iterator it=m_gameStates.end();
            m_gameStates.erase(it-1);
        }
    }
}
void GameStateMachine::changeState(GameState* pState){
    if(!m_gameStates.empty()){
        /*if(m_gameStates.back()->getStateID()==pState->getStateID()){
            return;
        }*/
        if(m_gameStates.back()->onExit()){
            m_gameStates.back()=nullptr;
            delete m_gameStates.back();
            std::vector<GameState*>::iterator it=m_gameStates.end();
            m_gameStates.erase(it-1);

        }
    }
    m_gameStates.push_back(pState);
    m_gameStates.back()->onEnter();
}
void GameStateMachine::setDisplayBackState(bool enable){
    isShowBackState=enable;
}

void GameStateMachine::update(){

    if(!m_gameStates.empty()){
        m_gameStates.back()->update();
    }
}

void GameStateMachine::render(){
    if(!m_gameStates.empty()){
        if(m_gameStates.size()>=2){
            if(isShowBackState){
                m_gameStates[m_gameStates.size()-2]->render();
            }
        }
        m_gameStates.back()->render();
    }
}

void GameStateMachine::clean(){
    for(size_t i=0;i<m_gameStates.size();i++){
        if(m_gameStates[i]->onExit()){
            m_gameStates[i]=nullptr;
            delete m_gameStates[i];
        }
    }
    m_gameStates.clear();
}

GameState *GameStateMachine::getCurrentState(){
    return (!m_gameStates.empty())?m_gameStates.back():nullptr;
}
