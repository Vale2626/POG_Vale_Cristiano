#include "Vector4.h"
#include <iostream>

using namespace std;

//COSTRUTTORI ----------------------------------------------------------------------------------------------

Vector4 :: Vector4()          //vettore di default con 4 componenti = 0
{
    x = 0;
    y = 0;
    z = 0;
    w = 0;
}

Vector4 :: Vector4(float a)               //vettore con 4 componenti uguali
{
    x = a;
    y = a;
    z = a;
    w = a;
}

Vector4 :: Vector4(float a, float b, float c, float d)            //vettore con 4 componenti diverse
{
    x = a;
    y = b;
    z = c;
    w = d;
}

//METODI ------------------------------------------------------------------------------------------------

//GET

float Vector4 :: getX()
{
    return x;
}

float Vector4 :: getY()
{
    return y;
}

float Vector4 :: getZ()
{
    return z;
    
}
float Vector4 :: getW()
{
    return w;
}

//SET 

void Vector4 :: setX(float a)
{
    x = a;
}

void Vector4 :: setY(float a)
{
    y = a;
}

void Vector4 :: setZ(float a)
{
    z = a;
}

void Vector4 :: setW(float a)
{
    w = a;
}

// FUNZIONE DI STAMPA ------------------------------------------------------------------------------------------------------------

void Vector4 :: stampaVett()
{
    cout<<"("<<x<<","<<y<<","<<z<<","<<w<<")"<<endl<<endl;
}

// FUNZIONI MATEMATICHE ----------------------------------------------------------------------------------------------------------

void Vector4 :: sommaVett(const Vector4 &other)
{
    x += other.x;
    y += other.y;
    z += other.z;                           //prende i valori del primo vettore e li somma con i valori del secondo
    w += other.w;
}

void Vector4 :: diffVett(const Vector4 &other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;                           ////prende i valori del primo vettore e li sottrae con i valori del secondo
    w -= other.w;
}

void Vector4 :: moltScal(float a)
{
    x *= a;
    y *= a;
    z *= a;
    w *= a;
}

void Vector4 :: divScal(float a)
{
    x /= a;
    y /= a;
    z /= a;
    w /= a;
}

