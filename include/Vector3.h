#ifndef Vector3_H
#define Vector3_H
#pragma once

class Vector3
{
    public:
        float x, y, z;
    public:
        Vector3();     //costruttore di default

        Vector3(float a);  //passa un valore a tutte e tre le componeneti del vettore

        Vector3(float a, float b, float c);    //vettore con 3 componenti diverse
        


        Vector3 sommaVett(const Vector3 &other) const;   //richiamo della funzione, passaggio dell oggetto Vector3 nelle variabili locali della funzione
        Vector3 diffVett(const Vector3 &other) const ;
        Vector3 ProdVett(const Vector3 &other) const;
        void moltiplicaPer(float a);  //richiamo della funzione e passaggio di una variabile a
        void divScal(float a);
        float MoltScal(const Vector3& other) const;
        

        float magnitude() const;
        Vector3 normalized() const;

        float getX();
        void setX(float a);         //funzioni get e set per le variabili x, y, z per accedervi e modificarle

        float getY();
        void setY(float a);
        
        float getZ();
        void setZ(float a);

        void stampaVett();          //stampa del Vector3

};

#endif