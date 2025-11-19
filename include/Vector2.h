#ifndef Vector2_H       //Significa: "If Not Defined" (Se non è definito...)
#define Vector2_H       //Significa: "...allora definisci il simbolo Vector2_H."


class Vector2
{
    public:
        float x,y;
    
    public:
        Vector2();

        Vector2(float a);

        Vector2(float a, float b);

        Vector2 sommaVett(const Vector2 &other) const;
        Vector2 diffVett(const Vector2 &other) const;
    
        void moltiplicaPer(float a);
        void divScal(float a);
        float MoltScal(const Vector2 &other) const;

        float magnitude() const;
        Vector2 normalized() const;

        float getX();
        void setX(float a);

        float getY();
        void setY(float a);

        void stampaVett();

};

#endif