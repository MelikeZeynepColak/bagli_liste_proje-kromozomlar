/**       
* @file           Gen.cpp
* @description    Gen sınıfındaki kurucu ve yıkıcı fonksiyonların gövdelerinin bulunduğu dosya
* @course         1.Öğretim C grubu
* @assignment     1.Ödev
* @date           09.11.2024
* @author         Melike Zeynep Çolak(melike.colak3@ogr.sakarya.edu.tr)
*/ 
#include "Gen.hpp"

Gen::Gen(char veri) : veri(veri), sonraki(nullptr), onceki(nullptr) {} // kurucu fonksiyon
Gen::~Gen(){} // kendini serbest bırakır