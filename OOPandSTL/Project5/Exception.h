#ifndef EXCEPTION_H_INCLUDED
#define EXCEPTION_H_INCLUDED

using namespace std;

class Exception
{
private:
    char * desc;
public:
    Exception(char * whatEx) : desc(whatEx) {}
    ~Exception() { if(desc) delete [] desc; }
    Exception(const Exception& ex) {}
    const char * whatEx()
    {
        cout << "Exception: ";
        return desc;
    }
};

#endif // EXCEPTION_H_INCLUDED
