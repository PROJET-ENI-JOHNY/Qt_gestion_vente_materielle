#ifndef CONVERSION_H
#define CONVERSION_H
#include <string>
using namespace std;

class CONVERSION
{
private:
    string Unite(int n);
    string Dizaine(int n);
    string Centaine(int n);
    string Mille(int n);
    string Milliard(int n);
    string Million(int n);
public:
    CONVERSION();
    string Convertir(double d);
    string Convertir(int d);
};

#endif // CONVERSION_H
