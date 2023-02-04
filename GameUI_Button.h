#ifndef GAMEUI_BUTTON_H_INCLUDED
#define GAMEUI_BUTTON_H_INCLUDED
enum button_state
{
    MOUSE_OUT,
    MOUSE_HOVER,
    CLICKED
};
struct UI_Color
{
    SDL_Color col[3][2]=
    {
        //[DEFAULT STATE]
        {
            {0,0,0,255},      // = > border Color
            {255,255,255,255} // = > fill Color
        },

        //[HOVER STATE]
        {
            {0,0,0,255},      // = > border Color
            {200,200,255,255} // = > fill Color
        },

        //[FILL STATE]
        {
            {0,0,0,255},      // = > border Color
            {255,255,255,255} // = > fill Color
        }

    };

};
enum
{
    LEFT_DIR,
    CENTER_DIR,
    RIGHT_DIR
};
class UI_Button:public GameUI
{
private:

    enum buttonType
    {
        BUTTON_WITH_TEXT_AND_RECT_BORDER,
        BUTTON_WITH_TEXT_AND_IMAGE_BORDER,
        BUTTON_WITHOUT_TEXT_AND_IMAGE_BORDER
    };

    UI_Image *bg=nullptr;
    UI_Text *texteBtn=nullptr;

    void (*m_callback)();
    bool m_bRealease=true;

    UI_Color border;

    SDL_Rect srcState[3];
    int m_currentFrame=MOUSE_OUT;

    int type=BUTTON_WITH_TEXT_AND_RECT_BORDER;

    int textBtnAlignment;

    std::string fontId;

private:

    void init(std::string idBtn,std::string texteButton,std::string bgButton,int x,int y,int w,int h,int choice)
    {
        Id=idBtn;
        position=Vector2D(x,y);
        width=w;
        height=h;

        switch(choice)
        {
            case BUTTON_WITH_TEXT_AND_RECT_BORDER:
                texteBtn=new UI_Text(texteButton,0,0,fontId);
                break;

            case BUTTON_WITH_TEXT_AND_IMAGE_BORDER:
                texteBtn=new UI_Text(texteButton,0,0,fontId);

            case BUTTON_WITHOUT_TEXT_AND_IMAGE_BORDER:
                bg=new UI_Image(bgButton,position.getX(),position.getY(),srcState[MOUSE_OUT].x,srcState[MOUSE_OUT].y
                                ,srcState[MOUSE_OUT].w,srcState[MOUSE_OUT].h);
                break;
        }

        type=choice;
    }
public:

    UI_Button(std::string idBtn,std::string texteButton,std::string fontId,int x,int y,int w,int h,void (*callback)(),int alignment=CENTER_DIR):m_callback(callback)
    {
        this->fontId=fontId;
        init(idBtn,texteButton,"",x,y,w,h,BUTTON_WITH_TEXT_AND_RECT_BORDER);
        textBtnAlignment=alignment;
    }

    UI_Button(std::string idBtn,std::string texteButton,std::string fontId,std::string idBgButtonState,int x,int y,int w,int h,SDL_Rect srcState[3],void (*callback)()):m_callback(callback)
    {
        this->fontId=fontId;
        for(int i=0; i<3; i++)
        {
            this->srcState[i]=srcState[i];
        }
        init(idBtn,texteButton,idBgButtonState,x,y,w,h,BUTTON_WITH_TEXT_AND_IMAGE_BORDER);
    }

    UI_Button(std::string idBtn,std::string idBgButtonState,int x,int y,int w,int h,SDL_Rect srcState[3],void (*callback)()):m_callback(callback)
    {
        for(int i=0; i<3; i++)
        {
            this->srcState[i]=srcState[i];
        }
        init(idBtn,"",idBgButtonState,x,y,w,h,BUTTON_WITHOUT_TEXT_AND_IMAGE_BORDER);
    }

    ~UI_Button()
    {

    }

    void update()override
    {
        Vector2D mousePosition=Vector2D(theInputHandler::instance()->getMousePosition().x,theInputHandler::instance()->getMousePosition().y);
        if(theInputHandler::instance()->getMouseButtonState(LEFT)&&m_currentFrame!=MOUSE_HOVER){
            m_bRealease=false;
        }
        if(mousePosition.getX()<(position.getX()+width) &&mousePosition.getX()>position.getX()&&mousePosition.getY()<(position.getY()+height)&&mousePosition.getY()>position.getY())
        {

            if(theInputHandler::instance()->getMouseButtonState(LEFT)&&m_bRealease)
            {
                m_currentFrame=CLICKED;
                if(m_callback!=nullptr)
                    m_callback();
                m_bRealease=false;
            }
            else if(!theInputHandler::instance()->getMouseButtonState(LEFT))
            {
                m_currentFrame=MOUSE_HOVER;
                m_bRealease=true;
            }
        }
        else
        {
            m_currentFrame=MOUSE_OUT;
        }
    }

    void draw()override
    {
        switch(type)
        {

        case BUTTON_WITH_TEXT_AND_RECT_BORDER:
            SDL_Rect dst;
            dst.x=position.getX();
            dst.y=position.getY();
            dst.w=width;
            dst.h=height;

            SDL_SetRenderDrawColor(theGame::Instance()->getRenderer(),border.col[m_currentFrame][1].r, border.col[m_currentFrame][1].g,border.col[m_currentFrame][1].b,border.col[m_currentFrame][1].a);
            SDL_RenderFillRect(theGame::Instance()->getRenderer(),&dst);

            SDL_SetRenderDrawColor(theGame::Instance()->getRenderer(),border.col[m_currentFrame][0].r, border.col[m_currentFrame][0].g,border.col[m_currentFrame][0].b,border.col[m_currentFrame][0].a);
            SDL_RenderDrawRect(theGame::Instance()->getRenderer(),&dst);
            switch(textBtnAlignment)
            {
            case CENTER_DIR:
                texteBtn->getVector()->setX(position.getX()+width/2-texteBtn->getWidth()/2);
                texteBtn->getVector()->setY(position.getY()+height/2-texteBtn->getHeight()/2+2);
                break;
            }
            texteBtn->draw();

            break;


        case BUTTON_WITHOUT_TEXT_AND_IMAGE_BORDER:
            bg->setSourceDisplay(srcState[m_currentFrame]);
            bg->getVector()->setX(position.getX());
            bg->getVector()->setY(position.getY());
            bg->setSize(width,height);
            bg->draw();
        break;

        case BUTTON_WITH_TEXT_AND_IMAGE_BORDER:
            bg->setSourceDisplay(srcState[m_currentFrame]);
            bg->getVector()->setX(position.getX());
            bg->getVector()->setY(position.getY());
            bg->setSize(width,height);
            bg->draw();

            switch(textBtnAlignment)
            {
                case CENTER_DIR:
                    texteBtn->getVector()->setX(position.getX()+width/2-texteBtn->getWidth()/2);
                    texteBtn->getVector()->setY(position.getY()+height/2-texteBtn->getHeight()/2+2);
                    break;
            }

            texteBtn->draw();
            break;
        }
    }

    void clean() override
    {
        if(texteBtn!=nullptr){
            texteBtn->clean();
        }
        if(bg!=nullptr){
            bg->clean();
        }
    }

};


#endif // GAMEUI_BUTTON_H_INCLUDED
