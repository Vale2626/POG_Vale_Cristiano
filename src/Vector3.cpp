
#include "Vector3.h"
#include <iostream>
#include <cmath>

using namespace std;

//COSTRUTTORI ----------------------------------------------------------------------------------------------

Vector3 :: Vector3()          //costruttore di default, :: serve per definire i metodi del file.h (in questo caso il costruttore vuoto)
{
    x = 0;
    y = 0;
    z = 0;      
}

Vector3 :: Vector3(float a)           //definzione di coastruttore con tre variabili
{
    x = a;
    y = a;
    z = a;
}

Vector3 :: Vector3(float a, float b, float c)      //definizione di un costruttore con tre variabili differenti
{
    x = a;
    y = b;
    z = c;
}

//METODI GET E SET ----------------------------------------------------------------------------------------------

//GET

float Vector3 :: getX()                //è di tipo float perchè è una funzione che ritorna un valore, in questo caso x. 
{
    return x;
}

float Vector3 :: getY()                
{
    return y;
}

float Vector3 :: getZ()              
{
    return z;
}

//SET

void Vector3 :: setX(float a)
{
    x = a;
}

void Vector3 :: setY(float a)
{
    y = a;
}

void Vector3 :: setZ(float a)
{
    z = a;
}

// FUNZIONE DI STAMPA-----------------------------------------------------

void Vector3 :: stampaVett()
{
    cout<<"\n ("<<x<<","<<y<<","<<z<<")"<<endl<<endl;
}

// FUNZIONI MATEMATICHE ----------------------------------------------------------------------------------------------------------

Vector3 Vector3 :: sommaVett(const Vector3 &other) const
{
    return Vector3(x + other.x, y + other.y, z + other.z);       //prende i valori del primo vettore e li somma con i valori del secondo
}

Vector3 Vector3 :: diffVett(const Vector3 &other) const
{
    return Vector3(x - other.x, y - other.y, z - other.z);                           ////prende i valori del primo vettore e li sottrae con i valori del secondo
}

void Vector3 :: moltiplicaPer(float a)           //moltiplicazione di un vettore per un valorwe numerico
{
    x *= a;
    y *= a;
    z *= a;  
}

void Vector3 :: divScal(float a)
{
    x /= a;
    y /= a;
    z /= a;
}

Vector3 Vector3 :: ProdVett(const Vector3 &other) const
{
    return Vector3(
        (y * other.z) - (z * other.y),  // newX
        (z * other.x) - (x * other.z),  // newY
        (x * other.y) - (y * other.x)   // newZ
    );
      
}

float Vector3 :: MoltScal(const Vector3& other) const
{
   return x * other.x + y * other.y + z * other.z;
}

float Vector3::magnitude() const {      //Ci serve per poter normalizzare il vettore
    return std::sqrt(x*x + y*y + z*z);
}
// Restituisce una *nuova* copia normalizzata del vettore
Vector3 Vector3::normalized() const {
    float mag = magnitude();
    if (mag > 0.0f) {
        return Vector3(x / mag, y / mag, z / mag);
    }
    // Se la magnitudine è 0, restituisce un vettore nullo
    return Vector3(0.0f, 0.0f, 0.0f); 
}









