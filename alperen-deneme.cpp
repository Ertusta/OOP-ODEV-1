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
    float *ortalama; // Ortalama notları saklamak için ek bir dizi
    int size; // Öğrenci sayısı

public:
    // Constructor - Öğrenci sayısını dışarıdan alıp dinamik diziler oluşturuyor
    Student(int size) : size(size)
    {
        ad = new string[size];
        ogrNo = new string[size];
        araSinav = new float[size];
        ikinciSinav = new float[size];
        odev = new float[size];
        final = new float[size];
        devamSayisi = new int[size];
        ortalama = new float[size]; // Ortalamalar için dizi oluştur
    }

    // Destructor - Dinamik olarak oluşturulan dizileri serbest bırakır
    ~Student()
    {
        delete[] ad;
        delete[] ogrNo;
        delete[] araSinav;
        delete[] ikinciSinav;
        delete[] odev;
        delete[] final;
        delete[] devamSayisi;
        delete[] ortalama; // Ortalama dizisini de sil
    }

    // CSV dosyasından verileri okuyan metod
    void readFromCSV(const string& fileName)
    {
        ifstream file(fileName);
        if (!file.is_open())
        {
            cerr << "Dosya açılamadı: " << fileName << endl;
            return;
        }

        string line;
        int index = 0;

        // İlk satır başlıkları içeriyor, onu atla
        getline(file, line);

        while (getline(file, line) && index < size)
        {
            stringstream ss(line);

            // Her bir virgülle ayrılmış alanı sırayla okuyun
            getline(ss, ad[index], ','); // Ad
            getline(ss, ogrNo[index], ','); // Öğrenci Numarası
            ss >> araSinav[index]; // Ara Sınav
            ss.ignore(1); // Virgülü atla
            ss >> ikinciSinav[index]; // 2. Sınav
            ss.ignore(1);
            ss >> odev[index]; // Ödev
            ss.ignore(1);
            ss >> final[index]; // Final
            ss.ignore(1);

            // Eğer devam sayısı boşsa 0 olarak atayın
            if (!(ss >> devamSayisi[index]))
                devamSayisi[index] = 0;

            index++;
        }

        file.close();
    }

    // Ortalama hesaplayan metod
    void calculateAverage()
    {
        for (int i = 0; i < size; i++)
        {
            // Ortalama hesaplama: %20 Ara Sınav, %20 2. Sınav, %20 Ödev, %40 Final
            ortalama[i] = (araSinav[i] * 0.20) + (ikinciSinav[i] * 0.20) +
                          (odev[i] * 0.20) + (final[i] * 0.40);
        }
    }


    // Verileri ekrana yazdıran metod
    void print(int arg = -1, const string& fileName = "")
{
    // Dosyaya yazma durumu
    ofstream outFile;
    bool toFile = !fileName.empty();
    if (toFile)
    {
        outFile.open(fileName);
        if (!outFile.is_open())
        {
            cerr << "Dosya açılamadı: " << fileName << endl;
            return;
        }
    }

    int studentCount = 0; // Geçen ya da kalan öğrenci sayısını takip eder

    for (int i = 0; i < size; i++)
    {
        float ortalama = (araSinav[i] * 0.20) + (ikinciSinav[i] * 0.20) +
                         (odev[i] * 0.20) + (final[i] * 0.40);

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
        cout << "Geçen öğrenci sayısı: " << studentCount << endl;
    }
    else if (arg == 0)
    {
        cout << "Kalan öğrenci sayısı: " << studentCount << endl;
    }
    else if (arg == -1)
    {
        cout << "Toplam öğrenci sayısı: " << size << endl;
    }

    // Dosya açıldıysa kapat
    if (toFile)
        outFile.close();
}



};

// Öğrenci sayısını dosyadan bulmak için fonksiyon
int countLinesInFile(const string& fileName)
{
    ifstream file(fileName);
    string line;
    int count = 0;

    // İlk satır başlıkları içeriyor, onu atla
    getline(file, line);

    while (getline(file, line))
    {
        count++;
    }

    return count;
}

int main()
{
    string fileName = "ogrenci.csv";

    // Öğrenci sayısını dosyadan okuyarak belirleyin
    int studentCount = countLinesInFile(fileName);
    cout << "Toplam öğrenci sayısı: " << studentCount << endl;

    Student students(studentCount);

    // Verileri CSV dosyasından oku
    students.readFromCSV(fileName);

    // Ortalamaları hesapla
    students.calculateAverage();

    students.print(0);
   

    return 0;
}
