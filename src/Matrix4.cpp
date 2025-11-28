#include "Matrix4.h"
#include <iostream>
using namespace std;
#include <cmath>

//COSTRUTTORI ----------------------------------------------------------------------------------------------

Matrix4 :: Matrix4()
{
     a = 0.0;    b = 0.0;    c = 0.0;  
    d = 0.0;    e = 0.0;    f = 0.0;  
    g = 0.0;    h = 0.0;    i = 0.0; 
     j = 0.0;    k = 0.0;    l = 0.0;  
    m = 0.0;    n = 0.0;    o = 0.0; 
    p = 0.0;    
}

Matrix4 :: Matrix4(float x)
{
     a = x;    b = x;    c = x;  
    d = x;    e = x;    f = x;  
    g = x;    h = x;    i = x; 
     j = x;    k = x;    l = x;  
    m = x;    n = x;    o = x; 
    p = x;    
}

Matrix4 :: Matrix4(float x1, float x2, float x3, float x4, float x5, float x6, float x7, float x8, float x9, float x10, float x11, float x12, float x13, float x14, float x15, float x16)
{
    a = x1;    b = x2;    c = x3;  
    d = x4;    e = x5;    f = x6;  
    g = x7;    h = x8;    i = x9; 
     j = x10;    k = x11;    l = x12;  
    m = x13;    n = x14;    o = x15; 
    p = x16;    
}

// FUNZIONE DI STAMPA----------------------------------------------------------------------------------

void Matrix4 :: stampa_matrice()
{
   cout<<"\n "<<endl<<" | "<< a << " "<< b << " "<< c << " "<< d <<" | "<<endl;
                cout<<" | "<< e << " "<< f << " "<< g << " "<< h <<" | "<<endl;
                cout<<" | "<< i << " "<< j << " "<< k << " "<< l <<" | "<<endl;
                cout<<" | "<< m << " "<< n << " "<< o << " "<< p <<" | " <<endl<<endl;
                           
}

// FUNZIONI MATEMATICHE ----------------------------------------------------------------------------------------------------------

void Matrix4 :: somma_matrice(const Matrix4 &other)
{
    a += other.a;   b += other.b;   c += other.c;
    d += other.d;   e += other.e;   f += other.f;           //sommo ciascun element di una matrice con ciascun elemento di un altra matrice
    g += other.g;   h += other.h;   i += other.i;
    j += other.j;   k += other.k;   l += other.l;
    m += other.m;   n += other.n;   o += other.o;
    p += other.p;

}

void Matrix4 :: diff_matrice(const Matrix4 &other)
{
    a -= other.a;   b -= other.b;   c -= other.c;   d -= other.d;
    e -= other.e;   f -= other.f;   g -= other.g;   h -= other.h;          
    i -= other.i;   j -= other.j;   k -= other.k;   l -= other.l;
    m -= other.m;   n -= other.n;   o -= other.o;   p -= other.p;
    
}

void Matrix4 :: moltScalare(float x)
{
    a *= x; b *= x; c *= x;  d *= x;
    e *= x; f *= x; g *= x;  h *= x;
    i *= x; j *= x; k *= x;  l *= x;
    m *= x; n *= x; o *= x;  p *= x;
}  

void Matrix4 :: divScalare(float x)
{
    a /= x; b /= x; c /= x;  d /= x;
    e /= x; f /= x; g /= x;  h /= x;
    i /= x; j /= x; k /= x;  l /= x;
    m /= x; n /= x; o /= x;  p /= x;
}

Vector4 Matrix4 :: prod_mat_vet(Vector4 &other)
{
    float v1, v2, v3, v4;      //variabili del vettore finale restituito

    v1 = a * other.getX() + b * other.getY() + c * other.getZ() + d * other.getW(); 

    v2 = e * other.getX() + f * other.getY() + g * other.getZ() + h * other.getW(); 

    v3 = i * other.getX() + j * other.getY() + k * other.getZ() + l * other.getW(); 

    v4 = m * other.getX() + n * other.getY() + o * other.getZ() + p * other.getW(); 


    Vector4 Vettore_risultante(v1, v2, v3, v4);
    return Vettore_risultante;
}

Matrix4 Matrix4 :: prod_mat_mat(Matrix4 &other)
{
    float a1_1, a1_2, a1_3, a1_4, a2_1, a2_2, a2_3, a2_4, a3_1, a3_2, a3_3, a3_4, a4_1, a4_2, a4_3, a4_4;

    //prima riga
    a1_1 = a * other.a + b * other.e + c * other.i + d * other.m;

    a1_2 = a * other.b + b * other.f + c * other.j + d * other.n;

    a1_3 = a * other.c + b * other.g + c * other.k + d * other.o;

    a1_4 = a * other.d + b * other.h + c * other.l + d * other.p;

    //secodna riga

    a2_1 = e * other.a + f * other.e + g * other.i + h * other.m;

    a2_2 = e * other.b + f * other.f + g * other. j + h * other.n;

    a2_3 = e * other.c + f * other.g + g * other.k + h * other.o;

    a2_4 = e * other.d + f * other.h + g * other.l + h * other.p;

    // terza riga

    a3_1 = i * other.a + j * other.e + k * other.i + l * other.m;

    a3_2 = i * other.b + j * other.f + k * other. j + l * other.n;

    a3_3 = i * other.c + j * other.g + k * other.k + l * other.o;

    a3_4 = i * other.d + j * other.h + k * other.l + l * other.p;

    //quarta riga

    a4_1 = m * other.a + n * other.e + o * other.i + p * other.m;

    a4_2 = m * other.b + n * other.f + o * other. j + p * other.n;

    a4_3 = m * other.c + n * other.g + o * other.k + p * other.o;

    a4_4 = m * other.d + n * other.h + o * other.l + p * other.p;

    Matrix4 Matrice_risultante(a1_1, a1_2, a1_3, a1_4, a2_1, a2_2, a2_3, a2_4, a3_1, a3_2, a3_3, a3_4, a4_1, a4_2, a4_3, a4_4);
    return Matrice_risultante;

}

Matrix4 Matrix4 :: Trasposta() const
{
    float a1_1, a1_2, a1_3, a1_4, a2_1, a2_2, a2_3, a2_4, a3_1, a3_2, a3_3, a3_4, a4_1, a4_2, a4_3, a4_4;

    a1_1 = a;
    a1_2 = e;
    a1_3 = i;
    a1_4 = m;
    a2_1 = b;
    a2_2 = f;
    a2_3 = j;
    a2_4 = n;
    a3_1 = c;
    a3_2 = g;
    a3_3 = k;
    a3_4 = o;
    a4_1 = d;
    a4_2 = h;
    a4_3 = l;
    a4_4 = p;

    Matrix4 Matrice_Trasposta(a1_1, a1_2, a1_3, a1_4, a2_1, a2_2, a2_3, a2_4, a3_1, a3_2, a3_3, a3_4, a4_1, a4_2, a4_3, a4_4);
    return Matrice_Trasposta;
}

float Matrix4 :: Determinante() const          //conti sbagliati?
{
    float det;
    
    det = (a * ( f * (k * p - l * o) - g * (j * p - n * i) + n * (j * o - k * n))) - (b * ( e * (p * k - o * i) - g * (p * i - l * m) + n * (i * o - k * m))) + (c * (e * (p * j - n * l) - f * (p * i - m * l) + h * (n * i - m * j))) - (d * (e * (o * j - k * n) - f * (o * i - k * m) + g * (i * n - j * m)));
    return det;
}



//Get & Set--------------------------------------------------------------------------------------------------------------

Vector4 Matrix4 :: get_riga1()
{
    float x1 = a;
    float x2 = b;
    float x3 = c;
    float x4 = d;

    Vector4 vettore(x1, x2, x3, x4);
    return vettore;
}

Vector4 Matrix4 :: get_riga2()
{
    float x1 = e;
    float x2 = f;
    float x3 = g;
    float x4 = h;

    Vector4 vettore(x1, x2, x3, x4);
    return vettore;
}

Vector4 Matrix4 :: get_riga3()
{
    float x1 = i;
    float x2 = j;
    float x3 = k;
    float x4 = l;

    Vector4 vettore(x1, x2, x3, x4);
    return vettore;
}

Vector4 Matrix4 :: get_riga4()
{
    float x1 = m;
    float x2 = n;
    float x3 = o;
    float x4 = p;

    Vector4 vettore(x1, x2, x3, x4);
    return vettore;
}

Vector4 Matrix4 :: get_col1()
{
    float x1 = a;
    float x2 = e;
    float x3 = i;
    float x4 = m;

    Vector4 vettore(x1, x2, x3, x4);
    return vettore;
}

Vector4 Matrix4 :: get_col2()
{
    float x1 = b;
    float x2 = f;
    float x3 = j;
    float x4 = n;

    Vector4 vettore(x1, x2, x3, x4);
    return vettore;
}

Vector4 Matrix4 :: get_col3()
{
    float x1 = c;
    float x2 = g;
    float x3 = k;
    float x4 = o;

    Vector4 vettore(x1, x2, x3, x4);
    return vettore;
}

Vector4 Matrix4 :: get_col4()
{
    float x1 = d;
    float x2 = h;
    float x3 = l;
    float x4 = p;

    Vector4 vettore(x1, x2, x3, x4);
    return vettore;
}

void Matrix4 :: set_riga1(Vector4 &other)
{
    a = other.getX();
    b = other.getY();
    c = other.getZ();
    d = other.getW();
}

void Matrix4 :: set_riga2(Vector4 &other)
{
    e = other.getX();
    f = other.getY();
    g = other.getZ();
    h = other.getW();
}

void Matrix4 :: set_riga3(Vector4 &other)
{
    i = other.getX();
    j = other.getY();
    k = other.getZ();
    l = other.getW();
}

void Matrix4 :: set_riga4(Vector4 &other)
{
    m = other.getX();
    n = other.getY();
    o = other.getZ();
    p = other.getW();
}

void Matrix4 :: set_col1(Vector4 &other)
{
    a = other.getX();
    e = other.getY();
    i = other.getZ();
    m = other.getW();
}

void Matrix4 :: set_col2(Vector4 &other)
{
    b = other.getX();
    f = other.getY();
    j = other.getZ();
    n = other.getW();
}

void Matrix4 :: set_col3(Vector4 &other)
{
    c = other.getX();
    g = other.getY();
    k = other.getZ();
    o = other.getW();
}

void Matrix4 :: set_col4(Vector4 &other)
{
    d = other.getX();
    h = other.getY();
    l = other.getZ();
    p = other.getW();
}

Matrix4 Matrix4 :: perspective(float fov, float aspect, float near, float far)
{
    Matrix4 Mat4;
    
    // Coefficienti di scala
    float yScale = 1.0 / tan((M_PI / 180) * fov / 2);       
    float xScale = yScale / aspect;

    // yScale (1,1) --> comprime o espande l’asse Y in base al campo visivo verticale (fov)
    //xScale (0,0) -->

    Mat4.a = xScale;
    Mat4.b = 0.0f;
    Mat4.c = 0.0f;
    Mat4.d = 0.0f;
    Mat4.e = 0.0f;
    Mat4.f = yScale;
    Mat4.g = 0.0f;
    Mat4.h = 0.0f;
    Mat4.i = 0.0f;
    Mat4.j = 0.0f;
    Mat4.k = -(far + near) / (far - near);
    Mat4.l = -( 2.0f * far * near) / (far - near);
    Mat4.m = 0.0;
    Mat4.n = 0.0;
    Mat4.o = -1.0f;
    Mat4.p = 0.0f;

    return Mat4;
    
}

float* Matrix4::data() { 
    return &a; 
}

Matrix4 Matrix4 :: Identity()
{
    Matrix4 Mat4;
    Mat4.a = 1.0f;
    Mat4.b = 0.0f;
    Mat4.c = 0.0f;
    Mat4.d = 0.0f;
    Mat4.e = 0.0f;
    Mat4.f = 1.0f;
    Mat4.g = 0.0f;
    Mat4.h = 0.0f;
    Mat4.i = 0.0f;
    Mat4.j = 0.0f;
    Mat4.k = 1.0f;
    Mat4.l = 0.0f;
    Mat4.m = 0.0;
    Mat4.n = 0.0;
    Mat4.o = 0.0f;
    Mat4.p = 1.0f;

    return Mat4;
}

Matrix4 Matrix4 :: LookAt( const Vector3& eye, const  Vector3& center, const Vector3& up)
{
    Vector3 forward = (center.diffVett(eye)).normalized();
    Vector3 side = (forward.ProdVett(up)).normalized(); //la Z (forward) punta verso la camera, e nella matrice LookAt non devi cambiare segni.
    Vector3 up_right =  side.ProdVett(forward); //cross è il prodotto vettoriale

        Matrix4 Mat4;

        //prima riga, asse x
        Mat4.a = side.x;
        Mat4.b = side.y;
        Mat4.c = side.z;
        Mat4.d = - side.MoltScal(eye);
        //secdonda riga, asse y
        Mat4.e = up_right.x;
        Mat4.f = up_right.y;
        Mat4.g = up_right.z;
        Mat4.h = - up_right.MoltScal(eye);
        //terza riga, asse z
        Mat4.i = -forward.x;
        Mat4.j = -forward.y;
        Mat4.k = -forward.z;
        Mat4.l = forward.MoltScal(eye);
        //quarta riga
        Mat4.m = 0.0f;
        Mat4.n = 0.0f;
        Mat4.o = 0.0f;
        Mat4.p = 1.0f;    

        return Mat4;

}

Matrix4 Matrix4 :: traslate(const Vector3& translation)
{
    Matrix4 Mat4;

    
    Mat4.a = 1.0;
    Mat4.b = 0.0f;
    Mat4.c = 0.0f;
    Mat4.d = translation.x;
    Mat4.e = 0.0f;
    Mat4.f = 1.0f;
    Mat4.g = 0.0f;
    Mat4.h = translation.y;
    Mat4.i = 0.0f;
    Mat4.j = 0.0f;
    Mat4.k = 1.0f;
    Mat4.l = translation.z;
    Mat4.m = 0.0;
    Mat4.n = 0.0;
    Mat4.o = 0.0f;
    Mat4.p = 1.0f;

    return Mat4;

}

Matrix4 Matrix4 :: rotateX(float degrees)
{
    float rad = degrees * (M_PI / 180.0f);
    float c = std::cos(rad);
    float s = std::sin(rad);

    Matrix4 Mat4 = Matrix4::Identity();
    Mat4.f = c;
    Mat4.g = -s;
    Mat4.j = s;
    Mat4.k = c;
    return Mat4;
}

Matrix4 Matrix4 :: rotateY(float degrees)
{
    float rad = degrees * (M_PI / 180.0f);
    float c = std::cos(rad);
    float s = std::sin(rad);

    Matrix4 Mat4 = Matrix4::Identity();
    Mat4.a = c;
    Mat4.c = s;
    Mat4.i = -s;
    Mat4.k = c;
    return Mat4;
}

Matrix4 Matrix4 :: rotateZ(float degrees)
{
    float rad = degrees * (M_PI / 180.0f);
    float c = std::cos(rad);
    float s = std::sin(rad);

    Matrix4 Mat4 = Matrix4::Identity();
    Mat4.a = c;
    Mat4.b = -s;
    Mat4.e = s;
    Mat4.f = c;
    return Mat4;
}

Matrix4 Matrix4 :: scale(const Vector3& scaling)
{
    Matrix4 Mat4 = Matrix4::Identity();

    Mat4.a = scaling.x;
    Mat4.f = scaling.y;
    Mat4.k = scaling.z;

    return Mat4;
}

Matrix4 Matrix4 :: scale(float uniformScale)        //matrice di scalatura per i modelli 3D troppo grandi
{
    Vector3 factors(uniformScale, uniformScale, uniformScale);
    return Matrix4::scale(factors);
}
