#ifndef PIKSEL_H_INCLUDED
#define PIKSEL_H_INCLUDED

class Piksel
{
private:
    int x, y;
public:
    Piksel() : x(0), y(0) {}
    Piksel(int x, int y) : x(x), y(y) {}
    int getX(){ return x; }
    int getY(){ return y; }
};

#endif // PIKSEL_H_INCLUDED
