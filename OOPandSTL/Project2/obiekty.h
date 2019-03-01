#ifndef OBIEKTY_H_INCLUDED
#define OBIEKTY_H_INCLUDED

#include <istream>
#include <ostream>

// ------Matrix-------
class Matrix
{
private:
    float xx, xy, yx, yy;
public:
    Matrix(float xx, float xy, float yx, float yy) : xx(xx), xy(xy), yx(yx), yy(yy) {}
    Matrix() : xx(0), xy(0), yx(0), yy(0) {}
    float getXX() { return xx; }
    float getXY() { return xy; }
    float getYX() { return yx; }
    float getYY() { return yy; }
    friend std::ostream& operator<< (std::ostream&, Matrix const&);
    Matrix operator* (int);
    Matrix operator-();
    operator float() const;
};


// --------Vector--------
class Vector
{
private:
    float x, y;
public:
    Vector(float x, float y) : x(x), y(y) {}
    Vector() : x(0), y(0) {}
    float getX() { return x; }
    float getY() { return y; }
    friend std::ostream& operator<< (std::ostream&, Vector const&);
    Vector operator-(const Vector);
    void operator-=(Vector);
    Vector operator* (Matrix&);
    Vector& operator++();
    Vector operator++(int);
    bool operator==(Vector&);
    float & operator[](int el);
    const float & operator[](int el) const;
};

#endif // OBIEKTY_H_INCLUDED
