#ifndef MATRIX4_H
#define MATRIX4_H
#pragma once

#include "Vector4.h"
#include "Vector3.h"

#define M_PI 3.14159265358979323846264338327950288

class Matrix4
{
    private:
        float a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p;          //16 variabili come le celle della matrice
    public:
        //costruttori----------------------------------------------------------------------------------------------

        Matrix4();

        Matrix4(float x);

        Matrix4(float x1, float x2, float x3, float x4, float x5, float x6, float x7, float x8, float x9, float x10, float x11, float x12, float x13, float x14, float x15, float x16);

        //metodi----------------------------------------------------------------------------------------------

        void stampa_matrice();
        void somma_matrice(const Matrix4 &other);
        void diff_matrice(const Matrix4 &other);        //gli passo un altra matrice da sommare/sottrarre
        void moltScalare(float x);
        void divScalare(float x);
        Vector4 prod_mat_vet(Vector4 &other);       //restituisce un vettore
        Matrix4 prod_mat_mat(Matrix4 &other);         //restituisce una matrice
        Matrix4 Trasposta() const;
        Matrix4 Inversa(Matrix4 &other);
        static Matrix4 perspective(float fov, float aspect, float near, float far);
        static Matrix4 Identity();
        static Matrix4 LookAt(const Vector3& eye, const Vector3& center, const Vector3& up);
        static Matrix4 traslate(const Vector3& translation);
        static Matrix4 rotateX(float degrees);
        static Matrix4 rotateY(float degrees);
        static Matrix4 rotateZ(float degrees);
        static Matrix4 scale(const Vector3& scaling);
        static Matrix4 scale(float uniformScale);
        float Determinante() const;

        //Get & Set----------------------------------------------------------------------------------------------

        Vector4 get_riga1();
        Vector4 get_riga2();
        Vector4 get_riga3();               //le funzioni get restituiscono un Vettore a 3 componenti
        Vector4 get_riga4();  
        Vector4 get_col1();
        Vector4 get_col2();
        Vector4 get_col3();
        Vector4 get_col4();

        void set_riga1(Vector4 &other); 
        void set_riga2(Vector4 &other);               //vector3f &other sono i parametri che gli passo alle funzioni set
        void set_riga3(Vector4 &other);
        void set_riga4(Vector4 &other); 
        void set_col1(Vector4 &other);
        void set_col2(Vector4 &other);
        void set_col3(Vector4 &other);
        void set_col4(Vector4 &other);

        float* data();                //Il metodo data() restituisce proprio l’indirizzo del primo elemento (a), che in memoria è seguito da tutti gli altri (b, c, d, …).

};

#endif
