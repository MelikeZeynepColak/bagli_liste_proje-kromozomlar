#ifndef Gen_hpp
#define Gen_hpp

class Gen {
public:
    char veri;
    Gen* sonraki;     // sonraki elemanın adresini tutan sonraki işaretçisi ve öncekinin adresini tutan onceki işaretçisi tanımlandı 
    Gen* onceki;

    Gen(char veri); // kurucu fonksiyon
    ~Gen();  //yıkıcı fonksiyon ile bellekte kendini temizler
};

#endif 
