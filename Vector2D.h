#ifndef VECTOR2D_H_INCLUDED
#define VECTOR2D_H_INCLUDED
#include<cmath>
class Vector2D{
private:
    float m_x;
    float m_y;
public:

    Vector2D(){
        m_x=0.0f;
        m_y=0.0f;
    }

    Vector2D(float x,float y){
        m_x=x;
        m_y=y;
    }

    int lenght(){
        return sqrt(m_x*m_x+m_y*m_y);
    }
    float getX(){
        return m_x;

    }
    float getY(){
        return m_y;
    }
    void setX(float x){
        m_x=x;
    }
    void setY(float y){
        m_y=y;
    }

    Vector2D operator +(Vector2D const &v){
        return Vector2D(m_x+v.m_x,m_y+v.m_y);
    }

    void operator +=(Vector2D const &v){
        this->m_x+=v.m_x;
        this->m_y+=v.m_y;
    }

    Vector2D operator -(Vector2D const &v){
        return Vector2D(m_x-v.m_x,m_y-v.m_y);
    }

    void operator -=(Vector2D const &v){
        this->m_x-=v.m_x;
        this->m_y-=v.m_y;
    }

    Vector2D operator /(int n){
        return Vector2D(m_x/n,m_y/n);
    }

    void operator /=(int n){
        this->m_x/=n;
        this->m_y/=n;
    }


    Vector2D operator *(int n){
        return Vector2D(m_x*n,m_y*n);
    }

    void operator *=(int n){
        this->m_x*=n;
        this->m_y*=n;
    }

};
#endif // VECTOR2D_H_INCLUDED
