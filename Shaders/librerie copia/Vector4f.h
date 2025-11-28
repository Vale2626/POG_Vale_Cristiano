#ifndef VECTOR4F_H
#define VECTOR4F_H
#pragma once

class Vector4f
{
    private:
    
        float x, y, z, w;

    public:
        Vector4f();

        Vector4f(float a);                                      //COSTRUTTORI

        Vector4f(float a, float b, float c, float d);


        //metodi

        void sommaVett(const Vector4f &other);
        void diffVett(const Vector4f &other);
        void moltScal(float a);
        void divScal(float a);          //sia per la moltiplicazione che per la divisione, uso un valore a che moltiplica e divide un vettore

        float getX();
        void setX(float a);

        float getY();
        void setY(float a);

        float getZ();
        void setZ(float a);

        float getW();
        void setW(float a);

        void stampaVett();      //funzione di stampa del vettore Vector4f

};

#endif