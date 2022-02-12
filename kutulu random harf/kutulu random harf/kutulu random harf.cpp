// kutulu random harf.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>         //standart giris cikis kutuphanesi
#include <windows.h>        //windows kutuphanesi konsoldaki harf islemleri icin
#include <ctime>            //random renk ve harf almak icin gerekli kutuphane

using namespace std;        //standart isim uzayi

class karakter {             //karakter adli sinif olusturuldu
public:                     //tum kullanicilara acik
    karakter();             //karakter fonksiyonu
    char harf;              //harf tanimlandi
    int color;              //renk icin tamsayi degiskeni tanimlandi
};

class katar {                //katar adli sinif olusturuldu
public:                     //tum kullanicilara acik
    katar();                //katar fonksiyonu
    void karakterEkle();    //karakter ekleme fonksiyonu
    void karakterCikar();   //karakter cikarma fonksiyonu
    void yazdir();          //yazdir fonksiyonu
private:                    //tum kullanicilara acik olmayan
    int karakterSayisi;     //karakter sayisi adli tamsayi degiskeni tanimlandi
    karakter karakterler[50];   //karakterler adli 50 elemanli karakter sinifina bagli dizi olusturuldu
};

enum colors {                //renklerin kodlari verildi
    LIGHTBLUE = 9,          //acik mavinin karsiligi 9
    LIGHTGREEN = 10,        //acik yesilin karsiligi 10
    LIGHTCYAN = 11,         //turkuazin karsiligi 11
    LIGHTRED = 12,          //acik kirmizinin karsiligi 12
    LIGHTMAGENTA = 13,      //morun karsiligi 13
    YELLOW = 14,            //sarinin karsiligi 14
};

struct Color {               //renk adli yapi olusturuldu
    int color;              //renk adli tamsayi degiskeni tanimlandi

    Color(int color_) : color(color_) {} //renk adli tamsayi degiskenini renge donusturdu

    Color operator + (const Color& other) const { return Color(this->color | other.color); }   //renk operatoru ile rengi dondurur
};

#define FORE_LIGHT(color) const Color cfl##color##_ = FOREGROUND_##color | FOREGROUND_INTENSITY;    //acik renk tanimlandi
#define BACK_LIGHT(color) const Color cbl##color##_ = BACKGROUND_##color | BACKGROUND_INTENSITY;    //acik renk tanimlandi
#define FORE_DARK(color)  const Color cfd##color##_ = FOREGROUND_##color;                           //koyu renk tanimlandi
#define BACK_DARK(color)  const Color cbd##color##_ = BACKGROUND_##color;                           //koyu rnek tanimlandi

FORE_LIGHT(RED) FORE_LIGHT(GREEN) FORE_LIGHT(BLUE)      //acik kirmizi, yesil, mavi renkler tanimlandi
BACK_LIGHT(RED) BACK_LIGHT(GREEN) BACK_LIGHT(BLUE)      //acik kirmizi, yesil, mavi renkler tanimlandi
FORE_DARK(RED) FORE_DARK(GREEN) FORE_DARK(BLUE)      //koyu kirmizi, yesil, mavi renkler tanimlandi
BACK_DARK(RED) BACK_DARK(GREEN) BACK_DARK(BLUE)      //koyu kirmizi, yesil, mavi renkler tanimlandi

const Color cdefault_ = cfdRED_ + cfdGREEN_ + cfdBLUE_; //varsayilan renk kirmizi yesil ve mavinin karisimi olarak tanimlandi

std::ostream& operator << (std::ostream& os, Color c) //yukaridaki renk tanimlarini kullanarak konsola renkli yazdirma
{
    return SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c.color), os;   //konsola renkli yazdirma komutunu dondurur
}

int main()      //ilk calisacak fonksiyon
{
    char harfler[50] = {};    //harfler adli harflerin tutuldugu 50 elemanli dizi tanimlandi
    int renkler[50] = {};     //renkler adli renklerin tamsayi olarak tutuldugu 50 elemanli tamsayi dizisi tanimlandi

    srand(time(0));         //programin her calismasinda farkli rastgele harfler ve renkler almamizi saglayan islev

    char duzCizgi = 205;      //hucrenin bir parcasi icin gereken cizgi tanimlandi
    char solUstKose = 201;    //hucrenin bir parcasi icin gereken cizgi tanimlandi
    char sagUstKose = 187;    //hucrenin bir parcasi icin gereken cizgi tanimlandi
    char dikeyCizgi = 186;    //hucrenin bir parcasi icin gereken cizgi tanimlandi
    char asagiAyrac = 203;    //hucrenin bir parcasi icin gereken cizgi tanimlandi
    char solAltKose = 200;    //hucrenin bir parcasi icin gereken cizgi tanimlandi
    char sagAltKose = 188;    //hucrenin bir parcasi icin gereken cizgi tanimlandi
    char yukariAyrac = 202;   //hucrenin bir parcasi icin gereken cizgi tanimlandi

    int rastgeleHarfinKodu;     //rastgele harfin kodu tamsayi degiskeni olarak tanimlandi
    int rastgeleRenginKodu;     //rastgele rengin kodu tamsayi degiskeni olarak tanimlandi

    for (int i = 0; i < 50; i++) {      //i degerini 0'dan 50'ye kadar gezdirir
        rastgeleHarfinKodu = rand() % 26 + 65;      //50 tane rastgele harf icin tamsayi degeri alir
        harfler[i] = (char)rastgeleHarfinKodu;  //rastgele harf icin aldigi 50 tane tamsayiyi ASCI tablosuna gore harfe cevirir
        rastgeleRenginKodu = rand() % 6 + 9;        //50 tane rastgele renk icin tamsayi degeri alir
        renkler[i] = rastgeleRenginKodu;        //rastgele renk icin aldigi 50 tane tamsayiyi renkler adli tamsayi dizisine atar
    }

    int karakterSayisi = 0;   //karakter sayisi adli tamsayi degiskeni tanimlar ve 0 olarak deger verir

    while (1)       //1 oldugu surece yani surekli giris yapmamizi saglar
    {
        int cevap;                  //menuden sececegimiz islemi tamsayi olarak alacagimiz degisken tanimlandi
        cout << endl << "Yapmak istediginiz islemi seciniz..." << endl;     //kullaniciya mesaj verir
        cout << "1-) Karakter Ekle" << endl;        //kullaniciya karakter ekleme mesajini verir
        cout << "2-) Karakter Cikar" << endl;       //kulaniciya karakter cikarma mesajini veir
        cout << "3-) Programdan Cikis" << endl;     //kullaniciya programdan cikis mesajini verir
        cin >> cevap;       //kullanicidan tamsayi degeri alir

        switch (cevap) {      //kullanicidan aldigi tamsayi degerine gore cesitli secenekler sunar
        case 1:             //cevap degiskeni 1 ise bu bolume girer
            if (karakterSayisi >= 0 && karakterSayisi < 50) {     //eger karakter sayisi 0'a esit veya buyukse ve 50'den kucukse
                karakterSayisi++;       //karakter sayisi degiskenini 1 arttirir
            }
            else {       //eger yukaridaki sart saglanmazsa
                cout << cflRED_ << "Ekleme yapilamaz." << cdefault_ << endl;    //kullaniciya mesaj verir
            }
            break;  //case'i kirar
        case 2:        //cevap degiskeni 2 ise bu bolume girer
            if (karakterSayisi <= 0) {          //eger karakter sayisi 0'dan kucuk veya esitse
                cout << cflRED_ << "Cikarma yapilamaz." << cdefault_ << endl;   //kullaniciya mesaj verir
            }
            else {       //yukaridaki sart saglanmazsa
                karakterSayisi--;       //karakter sayisi degiskenini 1 eksiltir
            }
            break;      //case'i kirar
        case 3:         //cevap degiskeni 3 ise bu bolume girer
            cout << "Onceki durumun eleman sayisi: " << karakterSayisi - 1 << endl;    //onceki durumun eleman sayisini kullaniciya yazdirir
            cout << "Sonraki durumun eleman sayisi: " << karakterSayisi << endl;      //sonraki durumun eleman sayisini kullaniciya yazdirir
            cout << "Programdan cikiliyor..." << endl;              //kullaniciya programdan cikildigina dair mesaj verir
            return 0;           //programdan cikmak icin gereken islev yazildi
            break;              //case'i kirar
        default:                //yukaridaki 3 case'e girmezse buraya girer
            cout << "Lutfen 1,2 ya da 3 degerini giriniz." << endl;    //kullaniciya ne yapmasi gerektigi hakkinda bilgi verir
        }
        //-------------------------------------------------------------------------------------------------------------------------
        if (karakterSayisi > 0)             //karakter sayisi 0'dan buyuk ise
        {
            cout << "Onceki durumun eleman sayisi: " << karakterSayisi - 1 << endl;     //onceki durumun eleman sayisini yazdirir
            cout << solUstKose;                 //hucrenin parcasini olusturur
            for (int i = 0; i < karakterSayisi - 1; i++)    //i degiskenini 0'dan karakter sayisinin bir eksigine kadar gezdirir
            {
                cout << duzCizgi << duzCizgi << asagiAyrac;     //hucrenin ust kismini olusturur
            }
            cout << duzCizgi << duzCizgi << sagUstKose << endl;     //hucrenin ust kismini olusturur
            cout << dikeyCizgi;     //hucre icin gereken cizgiyi yazdirir

            for (int i = 0; i < karakterSayisi; i++) {      //i degiskenini 0'dan karakter sayisina kadar gezdirir
                switch (renkler[i]) {                 //renkler dizisinin elemaninin durumuna gore
                case 9:         //renkler adli dizinin elemani 9 ise
                    cout << cflRED_ << harfler[i - 1];       //varsayilan renkte hucrenin dikey cizgisini ve kirmizi renkte bir onceki harfleri olusturur
                    break;       //case'i kirar
                case 10:        //renkler adli dizinin elemani 10 ise
                    cout << cflGREEN_ << harfler[i - 1];       //varsayilan renkte hucrenin dikey cizgisini ve yesil renkte bir onceki harfleri olusturur
                    break;       //case'i kirar
                case 11:        //renkler adli dizinin elemani 11 ise
                    cout << cflBLUE_ << harfler[i - 1];       //varsayilan renkte hucrenin dikey cizgisini ve mavi renkte bir onceki harfleri olusturur
                    break;       //case'i kirar
                case 12:        //renkler adli dizinin elemani 12 ise
                    cout << cflRED_ + cflGREEN_ << harfler[i - 1];       //varsayilan renkte hucrenin dikey cizgisini ve sari renkte bir onceki harfleri olusturur
                    break;       //case'i kirar
                case 13:        //renkler adli dizinin elemani 13 ise
                    cout << cflRED_ + cflBLUE_ << harfler[i - 1];       //varsayilan renkte hucrenin dikey cizgisini ve magenta(mor) renkte bir onceki harfleri olusturur
                    break;       //case'i kirar
                case 14:        //renkler adli dizinin elemani 14 ise
                    cout << cflGREEN_ + cflBLUE_ << harfler[i - 1];       //varsayilan renkte hucrenin dikey cizgisini ve cyan(turkuaz) renkte bir onceki harfleri olusturur
                    break;       //case'i kirar
                default:         //yukaridaki case kisimlarina girmezse buraya girer
                    cout << cdefault_;    //varsayilan renge doner
                    cout << harfler[i - 1] << endl;     //kullaniciya harfler dizisinden bir harf yazdirir
                }
                cout << cdefault_ << " " << dikeyCizgi;     //varsayilan renkte dikey cizgi olusturur
            }
            cout << endl << solAltKose;     //hucre icin gereken cizgiyi yazdirir
            for (int i = 0; i < karakterSayisi - 1; i++)        //i degiskenini 0'dan karakter sayisina kadar gezdirir
            {
                cout << cdefault_ << "" << duzCizgi << duzCizgi << yukariAyrac << "";       //varsayilan renkye hucrenin ust kismini olusturur
            }

            cout << cdefault_ << duzCizgi << duzCizgi << sagAltKose;                   //varsayilan renkte dikey cizgi olusturur
            cout << endl;       //alt satira gecer
        }
        //----------------------------------------------------------------------------------------------------------------------------------
        if (karakterSayisi > 0) {       //karakter sayisi 0'dan buyuk ise
            cout << "Sonraki durumun eleman sayisi: " << karakterSayisi << endl;    //sonrak durumun eleman sayisini yazdirir
            cout << solUstKose;     //hucra icin gereken cizgiyi yazdirir
            for (int i = 0; i < karakterSayisi - 1; i++)        //i degiskenini 0'dan karakter sayisinin bir eksigine kadar gezdirir
            {
                cout << duzCizgi << duzCizgi << asagiAyrac;     //hcrenin ust kismini olusturur
            }
            cout << duzCizgi << duzCizgi << sagUstKose << endl;     //hucrenin ust kismini olusturur
            cout << dikeyCizgi;         //hucre icin gereken cizgiyi yazdirir

            for (int i = 0; i < karakterSayisi; i++) {      //i degiskenini 0'dan baslatarak karakter sayisina kadar gezdirir
                switch (renkler[i]) {                 //renkler dizisinin elemaninin durumuna gore
                case 9:         //renkler adli dizinin elemani 9 ise
                    cout << cflRED_ << harfler[i];       //varsayilan renkte hucrenin dikey cizgisini ve kirmizi renkte harfleri olusturur
                    break;       //case'i kirar
                case 10:        //renkler adli dizinin elemani 10 ise
                    cout << cflGREEN_ << harfler[i];       //varsayilan renkte hucrenin dikey cizgisini ve yesil renkte harfleri olusturur
                    break;       //case'i kirar
                case 11:        //renkler adli dizinin elemani 11 ise
                    cout << cflBLUE_ << harfler[i];       //varsayilan renkte hucrenin dikey cizgisini ve mavi renkte harfleri olusturur
                    break;       //case'i kirar
                case 12:        //renkler adli dizinin elemani 12 ise
                    cout << cflRED_ + cflGREEN_ << harfler[i];       //varsayilan renkte hucrenin dikey cizgisini ve sari renkte harfleri olusturur
                    break;       //case'i kirar
                case 13:        //renkler adli dizinin elemani 13 ise
                    cout << cflRED_ + cflBLUE_ << harfler[i];       //varsayilan renkte hucrenin dikey cizgisini ve magenta(mor) renkte harfleri olusturur
                    break;       //case'i kirar
                case 14:        //renkler adli dizinin elemani 14 ise
                    cout << cflGREEN_ + cflBLUE_ << harfler[i];       //varsayilan renkte hucrenin dikey cizgisini ve cyan(turkuaz) renkte harfleri olusturur
                    break;       //case'i kirar
                default:         //yukaridaki case kisimlarina girmezse buraya girer
                    cout << cdefault_;    //varsayilan renge doner
                    cout << harfler[i] << endl;     //kullaniciya harfler dizisinden bir harf yazdirir
                }
                cout << cdefault_ << " " << dikeyCizgi;     //hucre icin varsayilan renkte dikey cizgi olusturur
            }
            cout << endl << solAltKose;             //alt satira gereken cizgiyi ekler
            for (int i = 0; i < karakterSayisi - 1; i++)        //i degiskenini 0'dan baslatarak karakter sayisinin bir eksigine kadar gezdirir
            {
                cout << cdefault_ << "" << duzCizgi << duzCizgi << yukariAyrac << "";       //varsayilan renkte gereken hucre parcalari olusturulur
            }

            cout << cdefault_ << duzCizgi << duzCizgi << sagAltKose;                   //varsayilan renkte dikey cizgi olusturur
            cout << endl;       //alt satira gecer
        }
        cout << cdefault_ << "Cikmak icin ENTER'a basiniz...";      //varsayilan renkte cikis islemi icin gereken mesaji kullaniciya verir
        cin.get();          //kullanicidan bir tusa basmasini ister.
    }


}