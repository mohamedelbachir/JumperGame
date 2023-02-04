#include"InputHandler.h"
#include<iostream>
#include"Game.h"
InputHandler* InputHandler::s_instance=0;

InputHandler::InputHandler()
{
    //initilisation of mouse button state
    for(int i=0; i<3; i++)
    {
        m_mouseStates.push_back(false);
    }

    //initilisation of window event state
    for(int i=0; i<sizeof(window_states); i++)
    {
        m_windowState.push_back(false);
    }
}

void InputHandler::update(){

    SDL_Event event;

    m_keyState=SDL_GetKeyboardState(0);

    while(SDL_PollEvent(&event)){

        switch(event.type){

            case SDL_QUIT:
                theGame::Instance()->quit();
                break;

            //when mouse is pressed
            case SDL_MOUSEBUTTONDOWN:

                if(event.button.button==SDL_BUTTON_LEFT){
                    m_mouseStates[LEFT]=true;
                }

                if(event.button.button==SDL_BUTTON_MIDDLE){
                    m_mouseStates[MIDDLE]=true;
                }

                if(event.button.button==SDL_BUTTON_RIGHT){
                    m_mouseStates[RIGHT]=true;
                }
            break;

            case SDL_MOUSEMOTION:
                m_mousePosition.x=event.motion.x;
                m_mousePosition.y=event.motion.y;
            break;

            //when he release
            case SDL_MOUSEBUTTONUP:

                if(event.button.button==SDL_BUTTON_LEFT){
                    m_mouseStates[LEFT]=false;
                }

                if(event.button.button==SDL_BUTTON_MIDDLE){
                    m_mouseStates[MIDDLE]=false;
                }

                if(event.button.button==SDL_BUTTON_RIGHT){
                    m_mouseStates[RIGHT]=false;
                }

            break;
            case SDL_WINDOWEVENT:

                switch(event.window.event){

                    case SDL_WINDOWEVENT_ENTER:
                        m_windowState[MOUSE_FOCUS]=true;
                    break;

                    case SDL_WINDOWEVENT_LEAVE:
                        m_windowState[MOUSE_FOCUS]=false;
                    break;

                    case SDL_WINDOWEVENT_FOCUS_GAINED:
                        m_windowState[KEYBOARD_FOCUS]=true;
                    break;

                    case SDL_WINDOWEVENT_FOCUS_LOST:
                        m_windowState[KEYBOARD_FOCUS]=false;
                    break;
                }
        }
    }
}

SDL_Point InputHandler::getMousePosition(){
    return m_mousePosition;
}

bool InputHandler::isKeyDown(SDL_Scancode key){
    if(m_keyState!=NULL)
    {
        if(m_keyState[key]==1){
            return true;
        }else{
            return false;
        }
    }
    return false;
}

bool InputHandler::getMouseButtonState(int buttonNumber)
{
    return m_mouseStates[buttonNumber];
}
