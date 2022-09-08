#ifndef INPUTHANDLER_H_INCLUDED
#define INPUTHANDLER_H_INCLUDED
#include<vector>
#include<SDL.h>

enum mouses_state
{
    LEFT=0,
    MIDDLE=1,
    RIGHT=0
};

class InputHandler
{
private:

    InputHandler();

    ~InputHandler() {}

    static InputHandler* s_instance;

    std::vector<bool>m_mouseStates;

    SDL_Point m_mousePosition;

    const Uint8 *m_keyState;


public:
    static InputHandler* instance()
    {
        if(s_instance==0)
        {
            s_instance=new InputHandler();
        }
        return s_instance;
    }

    /**
        @brief update
        function to handle the update of input when user use it
    */
    void update();

    /**
        @brief getMouseButtonState
        function to get a state of mouse button
        @param buttonNumber : the state of the mouse [LEFT,RIGHT,MIDDLE]
        @return true when the mouse has correspond to the request
    */
    bool getMouseButtonState(int buttonNumber);

    /**
        @brief isKeyDown
        function to get Input of user
        @param key:the Key who pressed
        @return true if is pressed
    */
    bool isKeyDown(SDL_Scancode key);

    /**
        @brief clean
        function to use when we have allocate dynamic arrays

    */
    void clean();

    /**
        @brief getMousePosition
        function to allow to get mouse coordinate on window
        @return position of mouse in window
    */
    SDL_Point getMousePosition();
};
typedef InputHandler theInputHandler;


#endif // INPUTHANDLER_H_INCLUDED
