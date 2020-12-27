# CO2-Ampel
Eine CO2 Ampel mit esp8266, ccs811 Sensor und WS2812

Im Code die wlan Zugangsdaten eintragen.
Nach dem Einschalten blinkt die 10. LED rot bis eine Verbindung aufgebaut ist.
Nach kurzem Aufleuchten aller LEDs in grün wird die IP-Adresse durch die LEDs ausgegeben.
Anzahl der grün leuchtenden LEDs entspricht der Zahl (Erst die Hunderter, dann die Zehner und zuletzt die Einer), eine blaue LED stellt den Punkt dar, eine rote LED steht für die Null.

Verdrahtung:
Data des WS2812 auf D8 des ESP
VCC (WS2812) auf 5V (ESP)
SDA (CCS811) auf D2 des ESP
SDL (CCS811) auf D1 des ESP
WAK (CCS811) auf GND !!!!!
VCC (CSS811) auf 3,3V(ESP)
GND ....
