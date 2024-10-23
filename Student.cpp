#include <string>

using namespace std;

class Student
{

    string *ad;
    string *ogrNo;
    float *araSinav;
    float *ikinciSinav;
    float *odev;
    float *final;
    int *devamSayisi;

    // constructer
    Student(int size)
    {

        ad = new string[size];
        ogrNo = new string[size];
        araSinav = new float[size];
        ikinciSinav = new float[size];
        odev = new float[size];
        final = new float[size];
        devamSayisi = new int[size];
    }

    // destrcuter
    ~Student()
    {
        delete[] ad;
        delete[] ogrNo;
        delete[] araSinav;
        delete[] ikinciSinav;
        delete[] odev;
        delete[] final;
        delete[] devamSayisi;
    }

    void readFromCSV()
    {
    }

    void average()
    {
    }

    void print()
    {
    }
};

int main()
{

    return 96;
}