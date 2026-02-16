# NMEA-Manual-Parser-Arduino

# Manual NMEA GPS Parser 

Bu proje, bir GPS modülünden gelen ham  NMEA verilerini, herhangi bir dış kütüphane  kullanmadan, manuel olarak ayrıştıran  ve I2C LCD ekrana yansıtan bir gömülü sistem uygulamasıdır.

##  Teknik Detaylar
Mekatronik mühendisliği perspektifiyle hazırlanan bu projede, veriler doğrudan seri porttan karakter karakter okunur ve bir  dizi içerisinde işlenir. 

### Öne Çıkan Özellikler:
* **Manuel Parsing:** `$GPGGA` veya `$GNGGA` cümle yapısı manuel olarak çözümlenmiştir.
* **UTC+3 Adaptasyonu:** Global saat verisi, Türkiye yerel saatine matematiksel olarak dönüştürülür.
* **Koordinat Dönüşümü:** Ham koordinat verileri (DDMM.MMMM), standart ondalık derece (DD.DDDD) formatına dönüştürülür.

#### Donanım
* **MCU:** Arduino Mega 
* **GPS:** NEO-6M veya benzeri NMEA destekli modüller
* **Ekran:** 16x2 I2C LCD Display

##### Kod Yapısı
Algoritma, seri porttan gelen her karakteri `eskiveri` ve `veri` kontrolü ile takip eder. `G` ve `A` karakter dizilimi yakalandığında paket alımı başlar ve önceden belirlenen indisler üzerinden veri ayrıştırma işlemi gerçekleştirilir.
