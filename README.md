# CO2-Ampel
Eine CO2 Ampel mit esp8266, ccs811 Sensor, beliebig vielen WS2812 LEDs und OLED Display 128x32

Im Code die Anzahl der WS2812 LEDs anpassen, sollte kein DHT-Sensor verwendet werden die entsprechende Zeile "#define DHTSENSOR" auskommentieren.
Nach dem erstmaligen Einschalten sich mit dem Accesspoint "CO2 Ampel" und dem Passwort "12345678" verbinden und das eigene Wifi auswählen.
Nach kurzem Aufleuchten aller LEDs in grün wird die IP-Adresse durch die LEDs ausgegeben.
Die 17. LED blinkt entsprechend, blau bedeutet nächste Zahl, rot bedeutet Punkt (also 192.168.0.25 wäre also 1 mal grün, blau, 9mal grün, blau, 2mal grün, blau, rot, 1mal grün, blau 6mal grün, blau, 8mal grün, blau, rot, blau, blau, blau, rot, blau, 2mal grün,blau, 5mal grün, blau, rot)

Verdrahtung:
Data des WS2812 auf D8 des ESP
VCC (WS2812) auf 5V (ESP)
SDA (CCS811) auf D2 des ESP
SDL (CCS811) auf D1 des ESP
WAK (CCS811) auf GND !!!!!
VCC (CSS811) auf 3,3V(ESP)
GND ....



Benötigte libraries:

- unter “Datei”, “Voreinstellungen” folgende zusätzliche Boardverwalter-URL hinzufügen: http://arduino.esp8266.com/stable/package_esp8266com_index.json
- unter "Werkzeuge" >> "Board" >> "Boardverwalter" >>"ESP8266 Boards" den WeMos D1 R1 auswählen
- Sparkfun CCS811 Arduino Library  ("Werkzeuge" >> "Bibliotheken verwalten" nach Sparkfun CCS811 suchen und installieren)
- Adafruit NeoPixel by Adafruit ("Werkzeuge" >> "Bibliotheken verwalten" nach Adafruit Neopixel suchen und installieren)
- Adafruit SSD1306  ("Werkzeuge" >> "Bibliotheken verwalten" nach Adafruit SSD1306 suchen und installieren)



Das Gehäuse mit den Buchstaben CO2 findet man hier:

https://www.tinkercad.com/things/ipEyfYHhAQ5

https://www.tinkercad.com/things/5hAtBOBWlKD

Die Buchstaben mit transparentem Filament und 3% Füllung drucken, damit sie durchscheinend sind und die Beleuchtung von unten gut gelingt. Die drei LEDs unter den Buchstaben werden nur als eine LED angesteuert (im Code eine WS2812b LED angeben), alle drei Datenleitungen der LEDs werden mit D8 am WEMOS verbunden.
