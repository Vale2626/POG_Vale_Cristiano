#include "Vector4f.h"
#include <iostream>

using namespace std;

//COSTRUTTORI ----------------------------------------------------------------------------------------------

Vector4f :: Vector4f()          //vettore di default con 4 componenti = 0
{
    x = 0;
    y = 0;
    z = 0;
    w = 0;
}

Vector4f :: Vector4f(float a)               //vettore con 4 componenti uguali
{
    x = a;
    y = a;
    z = a;
    w = a;
}

Vector4f :: Vector4f(float a, float b, float c, float d)            //vettore con 4 componenti diverse
{
    x = a;
    y = b;
    z = c;
    w = d;
}

//METODI ------------------------------------------------------------------------------------------------

//GET

float Vector4f :: getX()
{
    return x;
}

float Vector4f :: getY()
{
    return y;
}

float Vector4f :: getZ()
{
    return z;
    
}
float Vector4f :: getW()
{
    return w;
}

//SET 

void Vector4f :: setX(float a)
{
    x = a;
}

void Vector4f :: setY(float a)
{
    y = a;
}

void Vector4f :: setZ(float a)
{
    z = a;
}

void Vector4f :: setW(float a)
{
    z = a;
}

// FUNZIONE DI STAMPA ------------------------------------------------------------------------------------------------------------

void Vector4f :: stampaVett()
{
    cout<<"("<<x<<","<<y<<","<<z<<","<<w<<")"<<endl<<endl;
}

// FUNZIONI MATEMATICHE ----------------------------------------------------------------------------------------------------------

void Vector4f :: sommaVett(const Vector4f &other)
{
    x += other.x;
    y += other.y;
    z += other.z;                           //prende i valori del primo vettore e li somma con i valori del secondo
    w += other.w;
}

void Vector4f :: diffVett(const Vector4f &other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;                           ////prende i valori del primo vettore e li sottrae con i valori del secondo
    w -= other.w;
}

void Vector4f :: moltScal(float a)
{
    x *= a;
    y *= a;
    z *= a;
    w *= a;
}

void Vector4f :: divScal(float a)
{
    x /= a;
    y /= a;
    z /= a;
    w /= a;
}

