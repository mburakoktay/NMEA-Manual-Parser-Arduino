#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Değişkenler
uint8_t veri, eskiveri;
uint8_t dizi[80]; 
int8_t kalan = -1;
int saat; 

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600); 

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("GPS Bekleniyor..");
}

void loop() {
  if(Serial1.available())
  {
    veri = Serial1.read();
    
    // "G" ve ardından "A" gelirse paket başlar
    if(veri == 'A' && eskiveri == 'G')
    {
      kalan = 60; 
    }
    else
    {
      if(kalan > 0)
      {
        // Veriyi diziye sırayla yerleştir
        dizi[60 - kalan] = veri;
        kalan--;
      }
      else if(kalan == 0)
      {
        kalan = -1; // Kilitleme
        
        // --- 1. SAAT HESAPLAMA (TÜRKİYE UTC+3) ---
      
        saat = (dizi[1] - '0') * 10 + (dizi[2] - '0');
        saat = (saat + 3) % 24; 

        // --- EKRANA SAAT YAZDIRMA ---
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Sa:");
        if (saat < 10) lcd.print("0"); 
        lcd.print(saat);
        lcd.print(":");
        lcd.write(dizi[3]); lcd.write(dizi[4]); // Dakika
        lcd.print(":");
        lcd.write(dizi[5]); lcd.write(dizi[6]); // Saniye

        // --- 2. KOORDİNAT HESAPLAMA ---
        // KUZEY 
        float kuzeyDerece = (dizi[11]-'0')*10 + (dizi[12]-'0');
        float kuzeyDakika = (dizi[13]-'0')*10 + (dizi[14]-'0') + 
                            (dizi[16]-'0')*0.1 + (dizi[17]-'0')*0.01 + 
                            (dizi[18]-'0')*0.001 + (dizi[19]-'0')*0.0001;
        
        float enlemSonuc = kuzeyDerece + (kuzeyDakika / 60.0);

        // DOĞU 
        float doguDerece = (dizi[24]-'0')*100 + (dizi[25]-'0')*10 + (dizi[26]-'0');
        float doguDakika = (dizi[27]-'0')*10 + (dizi[28]-'0') + 
                           (dizi[30]-'0')*0.1 + (dizi[31]-'0')*0.01 + 
                           (dizi[32]-'0')*0.001 + (dizi[33]-'0')*0.0001;
                           
        float boylamSonuc = doguDerece + (doguDakika / 60.0);

        // --- EKRANA KOORDİNAT YAZDIRMA ---
        lcd.setCursor(0, 1);
        lcd.print("N:"); lcd.print(enlemSonuc, 3);
        lcd.print(" E:"); lcd.print(boylamSonuc, 3);

        // Serial Monitör Kontrolü
        Serial.print("Enlem: "); Serial.print(enlemSonuc, 5);
        Serial.print(" Boylam: "); Serial.println(boylamSonuc, 5);

        // Bir sonraki paket için diziyi temizle 
        for(int i=0; i<80; i++) dizi[i] = 0;
      }
    }
    eskiveri = veri;
  }
}
