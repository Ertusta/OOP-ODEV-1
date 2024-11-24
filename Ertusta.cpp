#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class Student
{
private:
    string *ad;
    string *ogrNo;
    float *araSinav;
    float *ikinciSinav;
    float *odev;
    float *final;
    int *devamSayisi;
    float *ort;
    int size;

public:
    Student(int size);
    ~Student();
    void readFromCSV(const string &fileName);
    void average();
    void print(int arg = -1, const string &fileName = "");
};

Student::Student(int size)
{
    this->size = size;
    ad = new string[size];
    ogrNo = new string[size];
    araSinav = new float[size];
    ikinciSinav = new float[size];
    odev = new float[size];
    final = new float[size];
    devamSayisi = new int[size];
    ort = new float[size];
}

Student::~Student()
{
    delete[] ad;
    delete[] ogrNo;
    delete[] araSinav;
    delete[] ikinciSinav;
    delete[] odev;
    delete[] final;
    delete[] devamSayisi;
    delete[] ort;
}

void Student::readFromCSV(const string &fileName)
{
    ifstream file(fileName);
    if (!file.is_open())
    {
        cout << "Dosya acilamadi: " << fileName << endl;
        return;
    }

    string line;
    int index = 0;

    getline(file, line); // ilk satırı atla

    while (getline(file, line) && index < size)
    {
        stringstream ss(line);

        getline(ss, ad[index], ',');
        getline(ss, ogrNo[index], ',');
        ss >> araSinav[index];
        ss.ignore(1);
        ss >> ikinciSinav[index];
        ss.ignore(1);
        ss >> odev[index];
        ss.ignore(1);
        ss >> final[index];
        ss.ignore(1);

        // Eğer devam sayısı boşsa 0 olarak atayın
        if (!(ss >> devamSayisi[index]))
            devamSayisi[index] = 0;

        index++;
    }

    file.close();
}

void Student::average()
{
    for (int i = 0; i < size; i++)
    {
        // Ortalama :    %20 Ara Sınav,             %20 2. Sınav,           %20 Ödev,         %40 Final
        ort[i] = (araSinav[i] * 0.20) + (ikinciSinav[i] * 0.20) + (odev[i] * 0.20) + (final[i] * 0.40);
    }
}

void Student::print(int arg, const string &fileName)
{
    // Dosyaya yazarken
    ofstream outFile;
    bool toFile = !fileName.empty();
    if (toFile)
    {
        outFile.open(fileName);
        if (!outFile.is_open())
        {
            cout << "Dosya acilamadi: " << fileName << endl;
            return;
        }
    }

    int studentCount = 0; // Geçen ya da kalan öğrenci sayısını takip eder

    for (int i = 0; i < size; i++)
    {
        float ortalama = ort[i];

        // Tüm listeyi yazdır
        if (arg == -1)
        {
            if (toFile)
                outFile << "Ad: " << ad[i] << ", Ogr No: " << ogrNo[i]
                        << ", Ortalama: " << ortalama << ", Devam: " << devamSayisi[i] << endl;
            else
                cout << "Ad: " << ad[i] << ", Ogr No: " << ogrNo[i]
                     << ", Ortalama: " << ortalama << ", Devam: " << devamSayisi[i] << endl;
        }
        // Kalanları yazdır (ortalama < 50)
        else if (arg == 0 && ortalama < 50)
        {
            studentCount++;
            if (toFile)
                outFile << "Ad: " << ad[i] << ", Ogr No: " << ogrNo[i]
                        << ", Ortalama: " << ortalama << ", Devam: " << devamSayisi[i] << endl;
            else
                cout << "Ad: " << ad[i] << ", Ogr No: " << ogrNo[i]
                     << ", Ortalama: " << ortalama << ", Devam: " << devamSayisi[i] << endl;
        }
        // Geçenleri yazdır (ortalama >= 50)
        else if (arg == 1 && ortalama >= 50)
        {
            studentCount++;
            if (toFile)
                outFile << "Ad: " << ad[i] << ", Ogr No: " << ogrNo[i]
                        << ", Ortalama: " << ortalama << ", Devam: " << devamSayisi[i] << endl;
            else
                cout << "Ad: " << ad[i] << ", Ogr No: " << ogrNo[i]
                     << ", Ortalama: " << ortalama << ", Devam: " << devamSayisi[i] << endl;
        }
    }

    // Öğrenci sayısını ekrana yazdır
    if (arg == 1)
    {
        cout << "Gecen ogrenci sayisi: " << studentCount << endl;
    }
    else if (arg == 0)
    {
        cout << "Kalan ogrenci sayisi: " << studentCount << endl;
    }
    else if (arg == -1)
    {
        cout << "Toplam ogrenci sayisi: " << size << endl;
    }

    // Dosya açıldıysa kapat
    if (toFile)
        outFile.close();
}

int countLinesInFile(const string &fileName)
{
    ifstream file(fileName);
    string line;
    int count = 0;

    getline(file, line); // ilk satırı atla

    while (getline(file, line))
    {
        count++;
    }

    return count;
}

int main()
{
    const string fileName = "girdi.csv";

    int studentCount = countLinesInFile(fileName);
    cout << "Toplam ogrenci sayisi: " << studentCount << endl;

    Student students(studentCount);

    students.readFromCSV(fileName);

    students.average();

    int choice;
    while (true)
    {
        cout << "\nSecenekler:\n";
        cout << "0. Tüm ogrenciler\n";
        cout << "1. Kalan ogrenciler\n";
        cout << "2. Gecen ogrenciler\n";
        cout << "3. Dosyaya yazdir\n";
        cout << "4. Cikis\n";
        cout << "Seciminizi yapin: ";
        cin >> choice;

        if (choice == 4)
        {
            cout << "Programdan cikiliyor..." << endl;
            break;
        }

        switch (choice)
        {
        case 0:
            students.print();
            break;
        case 1:
            students.print(0);
            break;
        case 2:
            students.print(1);
            break;
        case 3:
        {
            string outputFileName;
            cout << "Dosya adini girin: ";
            cin >> outputFileName;

            cout << "0. Tüm ogrenciler\n";
            cout << "1. Kalan ogrenciler\n";
            cout << "2. Gecen ogrenciler\n";
            cout << "Seciminizi yapin: ";

            int choice2;
            cin >> choice2;
            if (choice2 == 0)
                students.print(-1, outputFileName);
            else if (choice2 == 1)
                students.print(0, outputFileName);
            else if (choice2 == 2)
                students.print(1, outputFileName);
            else
                cout << "Gecersiz bir secim yaptiniz!" << endl;

            cout << "Veriler " << outputFileName << " dosyasina yazildi." << endl;
            break;
        }
        default:
            cout << "Gecersiz bir secim yaptiniz!" << endl;
            break;
        }
    }

    return 0;
}
