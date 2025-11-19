#include "Matrix3.h"
#include <iostream>
using namespace std;

//COSTRUTTORI ----------------------------------------------------------------------------------------------

Matrix3 :: Matrix3()
{
    a = 0.0;    b = 0.0;    c = 0.0;  
    d = 0.0;    e = 0.0;    f = 0.0;  
    g = 0.0;    h = 0.0;    i = 0.0;     
}

Matrix3 :: Matrix3(float x)
{
    a = x;   b = x;  c = x;
    d = x;   e = x;  f = x;
    g = x;   h = x;  i = x;
}

Matrix3 :: Matrix3(float x1, float x2, float x3, float x4, float x5, float x6, float x7, float x8, float x9)
{
    a = x1;   b = x2;  c = x3;
    d = x4;   e = x5;  f = x6;
    g = x7;   h = x8;  i = x9;
}

// FUNZIONE DI STAMPA----------------------------------------------------------------------------------

void Matrix3 :: stampa_matrice()
{
    cout<<"\n "<<endl<<" | "<< a << " "<< b << " "<< c << " | "<<endl;
                            cout<<" | "<< d << " "<< e << " "<< f << " | "<<endl;
                            cout<<" | "<< g << " "<< h << " "<< i << " | "<<endl<<endl;
}


// FUNZIONI MATEMATICHE ----------------------------------------------------------------------------------------------------------

void Matrix3 :: somma_matrice(const Matrix3 &other)
{
    a += other.a;   b += other.b;   c += other.c;
    d += other.d;   e += other.e;   f += other.f;           //sommo ciascun element di una matrice con ciascun elemento di un altra matrice
    g += other.g;   h += other.h;   i += other.i;
}

void Matrix3 :: diff_matrice(const Matrix3 &other)
{
    a -= other.a;   b -= other.b;   c -= other.c;
    d -= other.d;   e -= other.e;   f -= other.f;           
    g -= other.g;   h -= other.h;   i -= other.i;
}

void Matrix3 :: moltScalare(float x)
{
    a *= x; b *= x; c *= x;
    d *= x; e *= x; f *= x;
    g *= x; h *= x; i *= x;
}           
                                                                //moltiplico o divido gli elementi della matrice per un valore x    
void Matrix3 :: divScalare(float x)
{
    a /= x; b /= x; c /= x;
    d /= x; e /= x; f /= x;
    g /= x; h /= x; i /= x;
}

Vector3 Matrix3 :: prod_mat_vet(Vector3 &other)
{
    float v1, v2, v3;      //variabili del vettore finale restituito

    v1 = a * other.getX() + b * other.getY() + c * other.getZ(); 

    v2 = d * other.getX() + e * other.getY() + f * other.getZ(); 

    v3 = g * other.getX() + h * other.getY() + i * other.getZ(); 

    Vector3 Vettore_risultante(v1, v2, v3);
    return Vettore_risultante;
}

Matrix3 Matrix3 :: prod_mat_mat(Matrix3 &other)
{
    float a1_1, a1_2, a1_3, a2_1, a2_2, a2_3, a3_1, a3_2, a3_3;         //dichiarazione dei nuovi elementi della matrice risultante dal prodotto tra le due matrici

    //prima riga:
    a1_1 = a * other.a + b * other.d + c * other.g;

    a1_2 = a * other.b + b * other.e + c * other.h;

    a1_3 = a * other.c + b * other.f + c * other.i;

    //seconda riga:
    a2_1 = d * other.a + e * other.d + f * other.g;

    a2_2 = d * other.b + e * other.e + f * other.h;                             //calcolo degli elementi singoli della matrice risultante tramite la moltiplicazione tra due matrici

    a2_3 = d * other.c + e * other.f + f * other.i;

    //terza riga:

    a3_1 = g * other.a + h * other.d + i * other.g;

    a3_2 = g * other.b + h * other.e + i * other.h;

    a3_3 = g * other.c + h * other.f + i * other.i;

    Matrix3 matrice_risultante(a1_1, a1_2, a1_3, a2_1, a2_2, a2_3, a3_1, a3_2, a3_3);
    return matrice_risultante;
}

Matrix3 Matrix3 :: Trasposta() const
{
    float a1_1, a1_2, a1_3, a2_1, a2_2, a2_3, a3_1, a3_2, a3_3; 

    a1_1 = a;
    a1_2 = d;
    a1_3 = g;
    a2_1 = b;
    a2_2 = e;
    a2_3 = h;
    a3_1 = c;
    a3_2 = f;
    a3_3 = i;

    Matrix3 Mat_trasposta(a1_1, a1_2, a1_3, a2_1, a2_2, a2_3, a3_1, a3_2, a3_3);
    return Mat_trasposta; 
}

float Matrix3 :: Determinante() const
{
    float det;
    det = a * (e * i - h * f) - b * (d * i - g * f)+ c * (d * h - g * e);

    return det;
}

//Get & Set--------------------------------------------------------------------------------------------------------------

Vector3 Matrix3 :: get_riga1()
{
    float x1 = a;
    float x2 = b;
    float x3 = c;

    Vector3 vettore(x1, x2, x3);
    return vettore;
}

Vector3 Matrix3 :: get_riga2()
{
    float x1 = d;
    float x2 = e;
    float x3 = f;

    Vector3 vettore(x1, x2, x3);
    return vettore;
}

Vector3 Matrix3 :: get_riga3()
{
    float x1 = g;
    float x2 = h;
    float x3 = i;

    Vector3 vettore(x1, x2, x3);
    return vettore;
}

Vector3 Matrix3 :: get_col1()
{
    float x1 = a;
    float x2 = d;
    float x3 = g;

    Vector3 vettore(x1, x2, x3);
    return vettore;
}

Vector3 Matrix3 :: get_col2()
{
    float x1 = b;
    float x2 = e;
    float x3 = h;

    Vector3 vettore(x1, x2, x3);
    return vettore;
}
Vector3 Matrix3 :: get_col3()
{
    float x1 = c;
    float x2 = f;
    float x3 = i;

    Vector3 vettore(x1, x2, x3);
    return vettore;
}

void Matrix3 :: set_riga1(Vector3 &other)
{
    a = other.getX();
    b = other.getY();
    c = other.getZ();
}

void Matrix3 :: set_riga2(Vector3 &other)
{
    d = other.getX();
    e = other.getY();
    f = other.getZ();
}

void Matrix3 :: set_riga3(Vector3 &other)
{
    g = other.getX();
    h = other.getY();
    i = other.getZ();
}

void Matrix3 :: set_col1(Vector3 &other)
{
    a = other.getX();
    d = other.getY();
    g = other.getZ();
}

void Matrix3 :: set_col2(Vector3 &other)
{
    b = other.getX();
    e = other.getY();
    h = other.getZ();
}

void Matrix3 :: set_col3(Vector3 &other)
{
    c = other.getX();
    f = other.getY();
    i = other.getZ();
}








