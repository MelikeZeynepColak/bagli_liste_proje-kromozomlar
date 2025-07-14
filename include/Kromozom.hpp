#ifndef Kromozom_hpp
#define Kromozom_hpp

#include "Gen.hpp"

class Kromozom 
{
public:
    Gen* ilk;
    Gen* son;                   // ilk geni tutan işaretçi ve son geni tutan işaretçi tanımlandı
    Kromozom* sonraki;          // sonraki kromozomun adresini tutan işaretçi

    Kromozom(); //kurucu fonksiyon
    ~Kromozom(); // yıkıcı fonksiyon 
    void genEkle(char veri);                                       // dosyadan okunan kromozomları teker teker bağlı listeye aktarmakta kullandığım fonksiyon
    void mutasyon(Kromozom* ilkKromozom, int satir, int index);    // kullanıcıdan alınan satır ve indekse göre ilgili genin verisini "X" yapar
    void caprazlama(Kromozom* ilkKromozom, int satir1, int satir2);// kullanıcıdan alınan iki kromozom satırına göre o satırdaki kromozomları uygun şekilde çaprazlayan fonksiyon
    void kromozomlariYazdir(Kromozom* ilkKromozom);                // oluşan değişiklikleri görebilmek için tüm kromozomları ekrana yazdırma fonksiyonu
    void ekranaYazdir(Kromozom* ilkKromozom);                      // kromozomların ilk geninden daha küçük genini yazdırma fonksiyonu
    Kromozom* kromozomGetir(Kromozom* ilkKromozom, int satir);     // her seferinde aynı kodlarla istenilen kromozomu bulmak yerine istenen kromozomu getiren fonksiyon kurdum bununla kolayca istediğimiz satırdaki kromozoma erişebiliriz
    
};

#endif 
