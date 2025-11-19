#ifndef MATRIX3_H
#define MATRIX3_H
#pragma once

#include "Vector3.h"

class Matrix3
{
    private:
        float a, b, c, d, e, f, g, h, i;        //9 variabili come le celle della matrice

    public:
        //costruttori ----------------------------------------------------------------------------------------------

        Matrix3();      //costruttore di default 

        Matrix3(float x);            //costruttore che permette di avere una matrice con tutti ewlementi uguali ( x ).

        Matrix3(float x1, float x2, float x3, float x4, float x5, float x6, float x7, float x8, float x9);       //costruttore con matrice avente tutti elementi differenti


        //metodi ----------------------------------------------------------------------------------------------

        void stampa_matrice();
        void somma_matrice(const Matrix3 &other);
        void diff_matrice(const Matrix3 &other);        //gli passo un altra matrice da sommare/sottrarre
        void moltScalare(float x);
        void divScalare(float x);
        Vector3 prod_mat_vet(Vector3 &other);       //restituisce un vettore
        Matrix3 prod_mat_mat(Matrix3 &other);         //restituisce una matrice
        Matrix3 Trasposta() const;
        Matrix3 Inversa(Matrix3 &other);
        float Determinante() const;


        //Get & Set ----------------------------------------------------------------------------------------------

        Vector3 get_riga1();
        Vector3 get_riga2();
        Vector3 get_riga3();               //le funzioni get restituiscono un Vettore a 3 componenti
        Vector3 get_col1();
        Vector3 get_col2();
        Vector3 get_col3();

        void set_riga1(Vector3 &other); 
        void set_riga2(Vector3 &other);               //Vector3 &other sono i parametri che gli passo alle funzioni set
        void set_riga3(Vector3 &other);
        void set_col1(Vector3 &other);
        void set_col2(Vector3 &other);
        void set_col3(Vector3 &other);

        
};

#endif
