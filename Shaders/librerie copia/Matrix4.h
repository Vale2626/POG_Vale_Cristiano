#ifndef MATRIX4_H
#define MATRIX4_H
#pragma once

#include "Vector4f.h"

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
        Vector4f prod_mat_vet(Vector4f &other);       //restituisce un vettore
        Matrix4 prod_mat_mat(Matrix4 &other);         //restituisce una matrice
        Matrix4 Trasposta(const Matrix4 &other);
        Matrix4 Inversa(Matrix4 &other);
        float Determinante(Matrix4 &other);

        //Get & Set----------------------------------------------------------------------------------------------

        Vector4f get_riga1();
        Vector4f get_riga2();
        Vector4f get_riga3();               //le funzioni get restituiscono un Vettore a 3 componenti
        Vector4f get_riga4();  
        Vector4f get_col1();
        Vector4f get_col2();
        Vector4f get_col3();
        Vector4f get_col4();

        void set_riga1(Vector4f &other); 
        void set_riga2(Vector4f &other);               //vector3f &other sono i parametri che gli passo alle funzioni set
        void set_riga3(Vector4f &other);
        void set_riga4(Vector4f &other); 
        void set_col1(Vector4f &other);
        void set_col2(Vector4f &other);
        void set_col3(Vector4f &other);
        void set_col4(Vector4f &other);

};

#endif