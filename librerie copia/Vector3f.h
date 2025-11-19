#ifndef VECTOR3F_H
#define VECTOR3F_H
#pragma once

class Vector3f
{
    private:
        float x, y, z;
    public:
        Vector3f();     //costruttore di default

        Vector3f(float a);  //passa un valore a tutte e tre le componeneti del vettore

        Vector3f(float a, float b, float c);    //vettore con 3 componenti diverse
        


        void sommaVett(const Vector3f &other);   //richiamo della funzione, passaggio dell oggetto vector3f nelle variabili locali della funzione
        void diffVett(const Vector3f &other);
        void moltScal(float a);   //richiamo della funzione e passaggio di una variabile a
        void divScal(float a);
        void ProdVett(const Vector3f &other);

        float getX();
        void setX(float a);         //funzioni get e set per le variabili x, y, z per accedervi e modificarle

        float getY();
        void setY(float a);
        
        float getZ();
        void setZ(float a);

        void stampaVett();          //stampa del Vector3f

};

#endif