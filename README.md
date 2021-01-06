# CO2-Ampel
Eine CO2 Ampel mit esp8266, ccs811 Senso, WS2812 und OLED Display 128x32

Im Code die wlan Zugangsdaten eintragen.
Nach dem Einschalten blinkt die 17. LED rot bis eine Verbindung aufgebaut ist.
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
