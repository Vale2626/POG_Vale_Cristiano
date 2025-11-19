#include "Vector2.h"
#include <iostream>     //Serve a includere la libreria standard di Input/Output di C++.
#include<cmath>

using namespace std;

//COSTRUTTORI

Vector2 :: Vector2()
{
    x = 0;
    y = 0;
}

Vector2 :: Vector2(float a)
{
    x = a;
    y = a;
}

Vector2 :: Vector2(float a, float b)
{
    x = a;
    y = b;
    
}

//GET

float Vector2 :: getX()                //è di tipo float perchè è una funzione che ritorna un valore, in questo caso x. 
{
    return x;
}

float Vector2 :: getY()                
{
    return y;
}

//SET

void Vector2 :: setX(float a)
{
    x = a;
}

void Vector2 :: setY(float a)
{
    y = a;
}

//funzione di stampa

void Vector2 :: stampaVett()
{
    cout<<"\n ("<<x<<","<<y<<")"<<endl<<endl;
}

//funzioni matematiche

Vector2 Vector2 :: sommaVett(const Vector2 &other) const
{
    return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2 :: diffVett(const Vector2 &other) const
{
    return Vector2(x - other.x, y - other.y);
}

void Vector2 :: moltiplicaPer(float a)
{
    x *= a;
    y *= a;
}

void Vector2 :: divScal(float a)
{
    x /= a;
    y /= a;
}

float Vector2 :: MoltScal( const Vector2& other) const
{
    return x * other.x + y * other.y;
}

float Vector2 :: magnitude() const
{
    return std :: sqrt(x*x + y*y);
}

Vector2 Vector2 :: normalized() const 
{
    float mag = magnitude();
    if(mag > 0.0f)
    {
        return Vector2(x / mag, y / mag);
    }

    //// Se la magnitudine è 0, restituisce un vettore nullo
    return Vector2(0.0f, 0.0f);
}


