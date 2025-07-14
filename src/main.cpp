/**       
* @file           main.cpp
* @description    main fonksiyonunun bulunduğu kaynak dosyası. Bu dosyada ayrıca dosya okuma, otomatik işlemler ve menü fonksiyonları da bulunmakta
* @course         1.Öğretim C grubu
* @assignment     1.Ödev
* @date           23.11.2024 (sonradan güncellendi) 
* @author         Melike Zeynep Çolak(melike.colak3@ogr.sakarya.edu.tr)
*/ 
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Kromozom.hpp"
using namespace std;

Kromozom* dnaOku(const string& dosyaAdi); // Dosya okuma işlemini gerçekleştiren fonksiyon
void otomatikIslemler(Kromozom* ilkKromozom,const string& dosyaAdi);// otomatik işlemleri yerine getiren fonksiyon
void menu(); //Menüyü kullanıcıya gösteren fonksiyon

int main() 
{
    Kromozom kromozom;
    Kromozom* dna = dnaOku("dna.txt");// dosya okuma işlemi yapılıyor 

    int secim = 0;
    while (secim < 6) 
    {
        menu();// menü kullanıcıya gösterilir
        cin >> secim; // kullanıcınınn seçimi alınır
        
        switch (secim) // seçime göre gerekli menü işlemleri yapılır
        {
        case 1:

            int satir, index;
            cout << "Mutasyon olusturmak istediginiz kromozomun satir numarasini ve sonrasinda gen numarasini giriniz: "; cin >> satir >> index;//kullanıcıdan bir satır numarası ve o satırda bir gen numarası alınır
            kromozom.mutasyon(dna, satir, index);// alınan satır ve gen indexiyle mutasyon gerçekleştirilir
            break;

        case 2:

            int satir1, satir2;
            cout << "Caprazlama yapmak için iki farklı satir seciniz (satirlari lütfen teker teker seciniz) :"; cin >> satir1 >> satir2; //kullanıcıdan iki satır numarası alınır
            kromozom.caprazlama(dna, satir1, satir2);//alınan iki satır numarasındaki kromozomlar caprazlanarak listenin sonuna eklenirler
            break;

        case 3:
            otomatikIslemler(dna, "islemler.txt");// işlemler.txt deki işlemleri gerçekleştirir
            
            break;

        case 4:
            kromozom.ekranaYazdir(dna);
            break;

        case 5:

            kromozom.kromozomlariYazdir(dna);// listedeki tüm kromozomları yazdırır
            break;

        default:
            break;
        }
    }
    
    while (dna) // bellek serbest bırakılır
    { 
        Kromozom* gec = dna;   
        dna = dna->sonraki; 
        delete gec; 

    }
}

void menu() 
{
    cout << "1. Mutasyon\n"             // menü seçenekleri
         << "2. Caprazlama\n"
         << "3. Otomatik Islemler\n"
         << "4. Ekrana Yazdir (kucuk geni bulma)\n"
         << "5. Kromozomlari Yazdir\n"
         << "6. Cikis\n"<<endl;
    cout << "Seciminiz: "<< endl;
}

Kromozom* dnaOku(const string& dosyaAdi) // dna.txt yi okuma fonksiyonu 
{
    ifstream dosya(dosyaAdi);
    
    Kromozom* ilk = nullptr;
    Kromozom* gec = nullptr;

    string satir;

    while (getline(dosya, satir)) 
    {
        istringstream iss(satir);                   // satırda karakter karakter okuma işlemi yapılır
        Kromozom* yeniKromozom = new Kromozom();

        char harf;
        
        while (iss >> harf) // dosyadan karakter karakter okunup listeye eklenir
        {
            yeniKromozom->genEkle(harf);
        }

        if (!ilk) // eğer dosya boş ise yeni eklenenen kromozomu ilk kromozom yapar
        {
            ilk = yeniKromozom;
            gec = ilk;
        } 
        else 
        {
            gec->sonraki = yeniKromozom;    // dosya boş değilse sona ekleme yapar 
            gec = gec->sonraki;
        }
    }

    return ilk;
}
void otomatikIslemler(Kromozom* ilkKromozom, const string& dosyaAdi) 
{ 
    ifstream file("islemler.txt");    // islemler.txt okunur
    string line;
    Kromozom kromozom;
    while (getline(file, line))        // dosya sonuna kadar karakter karakter okuma işlemi yapılır 
    {
        istringstream iss(line); 
        char islem; int secim1, secim2;       // hangi işlem olduğu ve parametreleri okunur 
        iss >> islem >> secim1 >> secim2; 
        if (islem == 'C' && secim1 && secim2) 
        { 
            kromozom.caprazlama(ilkKromozom, secim1, secim2);  // eğer C harfi okunduysa ilgili kromozomlar arasında çaprazlama işlemi yapılır
        } 
        else if (islem == 'M'&& secim1 && secim2) 
        { 
            kromozom.mutasyon(ilkKromozom, secim1, secim2);    // eğer M harfi okunduysa ilgili satır ve gene mutasyon işlemi yapılır
        } 
        else
        {
            cout<<"Islemler.txt icinde gecersiz islem bicimi kullandınız. Lutfen dikkat ediniz.."<<endl;
        }
    } 

    cout << "Otomatik islemler basariyla tamamlandi. Tum kromozomlari gormek icin ekrana yazdir secenegini seciniz..  " << endl;
     
}











