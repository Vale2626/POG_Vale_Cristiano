#ifndef Vector4_H
#define Vector4_H
#pragma once

class Vector4
{
    private:
    
        float x, y, z, w;

    public:
        Vector4();

        Vector4(float a);                                      //COSTRUTTORI

        Vector4(float a, float b, float c, float d);


        //metodi

        void sommaVett(const Vector4 &other);
        void diffVett(const Vector4 &other);
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

        void stampaVett();      //funzione di stampa del vettore Vector4

};

#endif