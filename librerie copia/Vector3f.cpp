
#include "Vector3f.h"
#include <iostream>

using namespace std;

//COSTRUTTORI ----------------------------------------------------------------------------------------------

Vector3f :: Vector3f()          //costruttore di default, :: serve per definire i metodi del file.h (in questo caso il costruttore vuoto)
{
    x = 0;
    y = 0;
    z = 0;      
}

Vector3f :: Vector3f(float a)           //definzione di coastruttore con tre variabili
{
    x = a;
    y = a;
    z = a;
}

Vector3f :: Vector3f(float a, float b, float c)      //definizione di un costruttore con tre variabili differenti
{
    x = a;
    y = b;
    z = c;
}

//METODI GET E SET ----------------------------------------------------------------------------------------------

//GET

float Vector3f :: getX()                //è di tipo float perchè è una funzione che ritorna un valore, in questo caso x. 
{
    return x;
}

float Vector3f :: getY()                
{
    return y;
}

float Vector3f :: getZ()              
{
    return z;
}

//SET

void Vector3f :: setX(float a)
{
    x = a;
}

void Vector3f :: setY(float a)
{
    y = a;
}

void Vector3f :: setZ(float a)
{
    z = a;
}

// FUNZIONE DI STAMPA-----------------------------------------------------

void Vector3f :: stampaVett()
{
    cout<<"\n ("<<x<<","<<y<<","<<z<<")"<<endl<<endl;
}

// FUNZIONI MATEMATICHE ----------------------------------------------------------------------------------------------------------

void Vector3f :: sommaVett(const Vector3f &other)
{
    x += other.x;
    y += other.y;
    z += other.z;                           //prende i valori del primo vettore e li somma con i valori del secondo
}

void Vector3f :: diffVett(const Vector3f &other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;                           ////prende i valori del primo vettore e li sottrae con i valori del secondo
}

void Vector3f :: moltScal(float a)
{
    x *= a;
    y *= a;
    z *= a;  
}

void Vector3f :: divScal(float a)
{
    x /= a;
    y /= a;
    z /= a;
}

void Vector3f :: ProdVett(const Vector3f &other)
{
      x = ((y * other.z) - (z * other.y)); 
      y = ((z * other.x) - (x * other.z));           //creo tre variabili copia (c1,c2,c3) per calcolarmii 3 elementi del vettore e poi riassegnarli a x,y,z
      z = ((x * other.y) - (y * other.x));
      
}









