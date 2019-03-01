#include "obiekty.h"

std::ostream& operator<< (std::ostream &wyjscie, Matrix const& m)
{
   wyjscie << "|" << m.xx << " " << m.xy <<"|"<< std::endl << "|"<<m.yx << " " <<m.yy<<"|";
   return wyjscie;
}

Matrix operator* (double b, Matrix &m)
{
    return Matrix(m.getXX()*b, m.getXY()*b, m.getYX()*b, m.getYY()*b);
}

Matrix Matrix :: operator*(int f)
{
    return Matrix(f*xx, f*xy, f*yx, f*yy);
}

Matrix Matrix :: operator-()
{
    return Matrix(-xx, -xy, -yx, -yy);
}

Matrix :: operator float() const
{
    return xx * yy - xy * yx;
}

std::ostream& operator<< (std::ostream &out, Vector const& v)
{
   out << "(" << v.x << ", " << v.y << ")";
   return out;
}

Vector Vector :: operator-(const Vector v)
{
    return Vector(x-v.x, -v.y);
}

Vector Vector :: operator* (Matrix& a)
{
    return Vector(x *a.getXX() + y*a.getYX(), x * a.getXY() + y*a.getYY());
}


void Vector :: operator-=(Vector v)
{
    x = x - v.x;
    y = y - v.y;
}

Vector& Vector :: operator++()
{
    this->x++;
    this->y++;
    return *this;
}

Vector Vector :: operator++(int)
{
    Vector result(*this);
    ++(*this);
    return result;
}

bool Vector :: operator==(Vector& v)
{
    return (x == v.getX() && y == v.getY());
}

float & Vector :: operator[](int el)
{
    if(el == 0) return x;
    if(el == 1) return y;
}

const float & Vector :: operator[](int el) const
{
    if(el == 0) return x;
    if(el == 1) return y;
}
