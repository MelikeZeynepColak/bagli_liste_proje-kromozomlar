/**       
* @file           Kromozom.cpp
* @description    Kromozom sınıfındaki kurucu,yıkıcı ve diğer işlemleri yapan fonksiyonların gövdelerinin bulunduğu kaynak dosyası
* @course         1.Öğretim C grubu
* @assignment     1.Ödev
* @date           23.11.2024 (sonradan güncellendi)
* @author         Melike Zeynep Çolak(melike.colak3@ogr.sakarya.edu.tr)
*/ 
#include <iostream>
#include "Kromozom.hpp"

using namespace std;


Kromozom::Kromozom() : ilk(nullptr),son(nullptr), sonraki(nullptr) {} //kurucu fonksiyon

Kromozom::~Kromozom()
{
    while (ilk !=nullptr ) // Tüm genleri serbest bırakan yıkıcı fonksiyon
    { 
        Gen* gec = ilk;           // ilk adres yedeklenir
        ilk = ilk->sonraki;       // listede bir ilerleyerek önceki gen silinir
        delete gec;
    }

}

void Kromozom::genEkle(char veri) 
{
    Gen* yeniGen = new Gen(veri);             //yeni eklenecek olan gen tanımlanır

    if (ilk == nullptr)                      // eğer liste boş ise yeni gelen direkt ilk yapılır
    {
        ilk = yeniGen;
        son = yeniGen;

    } else 
    {                       
       if(son->sonraki==nullptr)
       {
            son->sonraki = yeniGen;       // listenin sonuna yeni gen eklenir
            yeniGen->onceki = son;
            son=yeniGen;
       }
        
    }
}

void Kromozom::kromozomlariYazdir(Kromozom* ilkKromozom) 
{
    if(ilkKromozom==nullptr)
    {
        cout<<"Liste bos...."<<endl;                    // ilk kromozomun ilk adresi null ise liste boş demektir
    }
    else
    {
        cout<<"------------- Kromozomlar yazdiriliyor ----------"<<endl;
        while (ilkKromozom !=nullptr ) 
        {
            Gen* gen = ilkKromozom->ilk;             //ilk kromozomun ilk geninin adresini yedekler 
            while (gen != nullptr) 
            {
                cout << gen->veri << ' ';     // genleri sonuna kadar yazdırır
                gen = gen->sonraki;
            }

            cout << endl;
            ilkKromozom = ilkKromozom->sonraki;               // bir sonraki kromozoma geçer ve döngü son kromozom da yazdırılana kadar devam eder
        }
    }
    
}

void Kromozom::ekranaYazdir(Kromozom* ilkKromozom)
{
    if (ilkKromozom==nullptr)
    {
        cout<<"Liste bos...."<<endl;                    // ilk kromozomun ilk adresi null ise liste boş demektir
    }
    else
    {
        cout<<"--------------Ilk genden kucuk gen (var ise) yazdiriliyor-----------"<<endl;
        while (ilkKromozom!=nullptr)
        {
            Gen* gec=ilkKromozom->son;                      // ilk ve son genlerin adresleri yedeklenir
            Gen* kucukGen=ilkKromozom->ilk;
            while(gec!=nullptr)
            {
                if (gec -> veri < kucukGen -> veri)       // son genin verisi ilk geninkinden küçük ise kucukGeni yazdırır ve diğer kromozoma geçer değilse küçük gen aramaya devam eder
                {
                    kucukGen=gec;
                    break;
                }
                gec=gec->onceki;
            }
            
            cout<<kucukGen->veri<< ' ';                // küçük geni yazdırır ve sonraki kromozoma geçer
            ilkKromozom=ilkKromozom->sonraki;

        }
        cout<<endl;
        
        
    }
    
}

Kromozom *Kromozom::kromozomGetir(Kromozom* ilkKromozom, int satir)  // istenilen satırdaki kromozoma ulaşmak için fonksiyon
{
    Kromozom* gec = ilkKromozom;                         // ilk adres kaybetmemek için yedeklenir 

    for (int i = 0; i < satir && gec != nullptr; i++)       // istenilen satıra gelene kadar kromozomlar geçilir
    {     
        gec = gec->sonraki;
    }
    return gec;                         // istenen satıra gelindiğinde döngüden çıkar ve o anki bağlı liste elemanını döndürür
}
void Kromozom::mutasyon(Kromozom* ilkKromozom, int satir, int index) // kullanıcıdan alınan satır ve index e göre mutasyon işlemi yapar
{
    Kromozom* gec = kromozomGetir(ilkKromozom, satir);       // kromozom getir fonksiyonunun getirdiği kromozomun adresini yedekledik

    if (gec != 0) 
    {
        Gen* gen = gec->ilk;                         // seçilen kromozomun ilk geninin adresi yedeklendi
        for (int i = 0; i < index && gen != nullptr; i++)       
        {
            gen = gen->sonraki;                     // istenen index e gelinene kadar genler geçilir
        }
        
        if (gen != 0) 
        {
            gen->veri = 'X';         // aranan gen bulunduğunda o genin verisi X yapılır
        }

        cout<<"Mutasyon islemi basarili.."<<endl;
    }
    else
    {
        cout<<"Mutasyon islemi basarisiz.."<<endl;
    }
}

void Kromozom::caprazlama(Kromozom* ilkKromozom, int satir1, int satir2) 
{
    Kromozom* kromozom1 = kromozomGetir(ilkKromozom, satir1);
    Kromozom* kromozom2 = kromozomGetir(ilkKromozom, satir2);

    if (kromozom1 != nullptr && kromozom2 != nullptr) 
    {    
        // İlk kromozomun ortası bulunur
        Gen* gec1 = kromozom1->ilk;         // kromozom1 in ilk adresi kaybedilmemek için yedeklendi
        int uzunluk1 = 0;
        while (gec1!=nullptr)                  
        {                       
            uzunluk1++;                     // genler gezilerek kromozomun uzunluğu hesaplandı
            gec1 = gec1->sonraki;
        }
        int ortaNokta1 = uzunluk1 / 2;      // bulunan uzunluğun yarısı alındı ve orta nokta olarak işaretlendi 


        int sayac1=0;
        Gen* part1 = kromozom1-> ilk ;
        while(sayac1 < ortaNokta1)           // orta noktadaki gene git  
        {
            part1 = part1->sonraki;
            sayac1++;
        }

        // İkinci kromozomun ortası bulunur
        Gen* gec2 = kromozom2->ilk;          
        int uzunluk2 = 0;                         
        while (gec2!=nullptr) 
        {                          
            uzunluk2++;                    // uzunluk hesaplandı 
            gec2 = gec2->sonraki;
        }
        int ortaNokta2 = uzunluk2 / 2;     // orta nokta hesaplandı

                              
        int sayac2=0;
        Gen* part2 = kromozom2-> ilk ;
        while(sayac2 < ortaNokta2)           // orta noktadaki gene git 
        {
            part2 = part2->sonraki;
            sayac2++;
        }
        
        // Yeni kromozomlar oluşturulur
        Kromozom* yenikromozom1 = new Kromozom();         
        Kromozom* yenikromozom2 = new Kromozom();   

        Gen* gec = kromozom1->ilk;
        for (int i = 0; i < ortaNokta1; i++) 
        {
            yenikromozom1->genEkle(gec->veri);         // orta noktaya gelene kadar 1.kromozomun genlerini alıp yeni oluşan 1.kromozoma ekler
            gec = gec -> sonraki;
        }
        gec = part2;
        while (gec != nullptr) {
            yenikromozom1->genEkle(gec->veri);      // 2.kromozomun ortasından başlayarak sona gelene kadar genleri alır ve 1.kromozomun sonuna ekler
            gec = gec->sonraki;
        }


        gec = part1;
        while (gec != nullptr) 
        {
            yenikromozom2->genEkle(gec->veri);      // 1.kromozomun ortasından başlayarak sona kadar gider ve genleri 2.kromozomun başından başlayarak yazar
            gec = gec->sonraki;
        }

        gec = kromozom2->ilk;
        for (int i = 0; i < ortaNokta2; i++) 
        {
            yenikromozom2->genEkle(gec->veri);     // orta noktaya gelene kadar 2.kromozomun genlerini alıp yeni oluşan 2.kromozoma ekler
            gec = gec -> sonraki;
        }

        // Yeni kromozomları popülasyona ekler
        while (ilkKromozom->sonraki != nullptr) 
        {
            ilkKromozom = ilkKromozom->sonraki;              // listenin sonuna git 
        }
        ilkKromozom->sonraki = yenikromozom1;           // son elemandan sonrakine yeni oluşan ilk kromozomu ekle
        yenikromozom1->sonraki = yenikromozom2;  // sonra da sonuna ikinci kromozomu ekle

        cout<<" Caprazlama islemi basariyla tamamlandi.."<<endl;
    }
    else
    {
        cout<<"Caprazlama islemi basarisiz.."<<endl;
    }
}


