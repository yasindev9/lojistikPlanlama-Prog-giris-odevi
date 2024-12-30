//Geliştirici : Yasin Durak
//Öğrenci No : B241200067
//Ödev No : 1
//Ödev Konusu : Lojistik Planlama   
#include <iostream>
#include <iomanip>
#include <locale.h>
#include "ConsoleColor.h"
#include <Windows.h>
#include <fstream>
using namespace std;
void matrisDegerVer();
void matrisOlustur();
void konumKontrol();
void adresYaz();
void matrisGuncelle();
void kuryeIlerlet();
void dosyaYazdir();
void yolBul();
void yolHesapla();
void ciz(char c, int lenght);
int x;
int y;
int randX[5];
int randY[5];
int* adresler[5];
int matrisSayac = 0;
int musteriSayac = 0;
int toplamYol = 0;
char baslat;
char cikis;
int i = 0;

struct
{
    int matrisDeger;
    int matrisX;
    int matrisY;
    bool musteri = false;
    bool yol = false;
} matris[101];

int main()
{
    srand(time(NULL));
    setlocale(LC_ALL, "Turkish");
    matrisDegerVer();
    adresYaz();
    matrisOlustur();
    kuryeIlerlet();
    yolHesapla();
    dosyaYazdir();
    cout << green << "Programı kapatmak için (x) : ";
    cin >> cikis;
    switch (cikis)
    {
    case 'x':
        exit;
        break;
    default:
        exit;
        break;
    }
    cout << white;
}

void matrisDegerVer()
{
    x = 0;
    y = 0;
    matrisSayac = 0;
    for (int i = 0; i < 5; i++)
    {
        randX[i] = rand() % 10;
        randY[i] = rand() % 10;
    }
    for (y; y < 10; y++)
    {
        for (x; x < 10; x++)
        {
            matris[matrisSayac].matrisX = x;
            matris[matrisSayac].matrisY = y;
            konumKontrol();
            matris[matrisSayac].matrisDeger = rand() % 100 + 1;
            matrisSayac++;
        }
        x = 0;
    }
}

void matrisOlustur()
{
    x = 0;
    y = 0;
    matrisSayac = 0;
    for (y; y < 10; y++)
    {
        for (x; x < 10; x++)
        {
            konumKontrol();
            if (matris[matrisSayac].musteri == true)
            {
                cout << left << blue << matris[matrisSayac].matrisDeger << "\t";
                matrisSayac++;
            }
            else
            {
                cout << left << white << matris[matrisSayac].matrisDeger << "\t";
                matrisSayac++;
            }
        }
        x = 0;
        cout << endl;
    }
    ciz('-', 75);
    //kuryeIlerlet();
}

void konumKontrol()
{
    i = 0; musteriSayac = 0;
    for (i; i < 5; i++)
    {
        if (randX[i] == matris[matrisSayac].matrisX && randY[i] == matris[matrisSayac].matrisY)
        {
            matris[matrisSayac].musteri = true;
            adresler[i] = &matris[matrisSayac].matrisDeger;
            musteriSayac++; yolBul();
        }
    }
}

void matrisGuncelle()
{
    matrisSayac = 0;
    x = 0;
    y = 0;
    for (int y = 0; y < 10; y++)
    {
        for (int x = 0; x < 10; x++)
        {
            if (y == 0 && x == 0)
            {
                if (matris[matrisSayac].musteri == true)
                {
                    cout << left << red << "K";
                    Sleep(200);
                    cout << left << green << matris[matrisSayac].matrisDeger << "\t";
                    Sleep(200);
                    matrisSayac++;
                }
                else
                {
                    cout << left << red << "K";
                    Sleep(200);
                    cout << left << yellow << matris[matrisSayac].matrisDeger << "\t";
                    Sleep(200);
                    matrisSayac++;
                }

            }
            else if (matris[matrisSayac].musteri == true)
            {
                cout << left << red << "K";
                Sleep(200);
                cout << left << green << matris[matrisSayac].matrisDeger << "\t";
                Sleep(200);
                matrisSayac++;
            }
            else if (matris[matrisSayac].yol == true)
            {
                cout << left << yellow << matris[matrisSayac].matrisDeger << "\t";
                Sleep(200);
                matrisSayac++;
            }
            else
            {
                cout << left << white << matris[matrisSayac].matrisDeger << "\t";
                Sleep(200);
                matrisSayac++;
            }
        }
        cout << endl;
    }
}

void kuryeIlerlet()
{
    cout << white << "Kuryeyi yola çıkarmak için (k) : ";
    cin >> baslat;
    switch (baslat)
    {
    case 'k':
        matrisGuncelle();
        break;
    case 'K':
        matrisGuncelle();
        break;
    default:
        cout << "HATA! KODU TEKRAR BAŞLAT!";
        break;
    }
}

void adresYaz()
{
    for (int i = 0; i < 5; i++)
    {
        cout << "Konum (" << randY[i] << ", " << randX[i] << ") - Adres: " << adresler[i] << endl;
    }
    ciz('*', 75);
}

void dosyaYazdir()
{
    cout << red << "Toplam yol: " << toplamYol << endl;
    cout << red << "Cost.txt başarıyla oluşturuldu!" << endl;

    ofstream dosyaYaz("Cost.txt");
    if (dosyaYaz.is_open())
    {
        for (int i = 0; i < 5; i++)
        {
            dosyaYaz << "Konum (" << randY[i] << ", " << randX[i] << ") - Adres: " << adresler[i] << endl;
        }
        dosyaYaz << "Toplam yol: " << toplamYol;
        dosyaYaz.close();
    }
}

void yolBul()
{
    static int oncekiX = -1, oncekiY = -1;
    static bool firstRun = true;

    if (firstRun)
    {
        oncekiX = 0;
        oncekiY = 0;
        firstRun = false;
    }

    int simdikiX = matris[matrisSayac].matrisX;
    int simdikiY = matris[matrisSayac].matrisY;

    int adimX = (simdikiX > oncekiX) ? 1 : -1;
    for (int x = oncekiX; x != simdikiX; x += adimX)
    {
        for (int i = 0; i < 100; i++)
        {
            if (matris[i].matrisX == x && matris[i].matrisY == oncekiY)
            {
                matris[i].yol = true;
                break;
            }
        }
    }

    int adimY = (simdikiY > oncekiY) ? 1 : -1;
    for (int y = oncekiY; y != simdikiY; y += adimY)
    {
        for (int i = 0; i < 100; i++)
        {
            if (matris[i].matrisX == simdikiX && matris[i].matrisY == y)
            {
                matris[i].yol = true;
                break;
            }
        }
    }
    oncekiX = simdikiX;
    oncekiY = simdikiY;
}

void yolHesapla()
{
    matrisSayac = 0;
    for (int i = 0; i < 10; i++)
    {
        for (int i = 0; i < 10; i++)
        {
            if (matris[matrisSayac].yol == true || matris[matrisSayac].musteri == true)
            {
                toplamYol += matris[matrisSayac].matrisDeger;
            }
            matrisSayac++;
        }
    }
}


void ciz(char c, int lenght)
{
    for (int i = 0; i <= lenght; i++)
    {
        cout << red << c;
    }
    cout << endl;
}