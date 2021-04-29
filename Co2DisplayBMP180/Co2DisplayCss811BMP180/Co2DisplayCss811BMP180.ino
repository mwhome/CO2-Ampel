
/*********
CO2 Luftqualität mit Arduino Nano, ccs811, ws2812, BMP180  und OLED Display 128*32
*********/
//Anschluss am Arduino Nano
//SDA an A4, SCL an A5, Vcc an 3,3V und GND an GND
//WS2812 an 5V (Vin), GND und Data an A1
//
#include "SparkFunCCS811.h" 
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>


#define CCS811_ADDR 0x5A //Alternative I2C Addresse des CCS811 Sensors
#define NUM_PIXEL 19    //Anzahl der WS2812 LEDs
#define PIN 15          // Data Anschluss des WS2812 Wemos D8
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXEL, PIN, NEO_GRB + NEO_KHZ800);
CCS811 mySensor(CCS811_ADDR);     //CCS811 Sensorlibrary von Sparkfun
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);

float TEMP = 0;

int P = NUM_PIXEL/2;
unsigned int CO2 = 400;
unsigned int TVOC = 0;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;



void setup() {
 Serial.begin(115200);
    Wire.begin();
    //bmp.begin();
 
   strip.begin();
  clearStrip();
  strip.show();
  strip.setBrightness(200);
  
  //Serial.println("Pressure Sensor Test"); Serial.println("");
  
  /* Initialise the sensor */
if(!bmp.begin())
{
  /* There was a problem detecting the BMP085 ... check your connections */
  Serial.print("Ooops, no BMP085 detected ... Check your wiring or I2C ADDR!");
  while(1);
}
  
  /* Display some basic information on this sensor */
  displaySensorDetails();


  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

if (mySensor.begin() == false)
  {
    Serial.print("CCS811 error. Please check wiring. Freezing...");
    while (1)
      ;
  }


  // Clear the buffer
  display.clearDisplay();

  // text display tests
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
    display.print(F("CO"));
    display.setTextSize(1);
    display.setCursor(23,10);
    display.print(F("2"));
    display.setTextSize(2);
    display.setCursor(28,0);
  display.println("-Ampel");
  display.setTextSize(1);
    display.setCursor(0,20);
  display.println("Markus Weber");
  display.display();
  delay(4000);
  
  display.clearDisplay();
  
}
 
void loop() {
   //Check to see if data is ready with .dataAvailable()
  if (mySensor.dataAvailable())
  {
    //If so, have the sensor read and calculate the results.
    //Get them later
    mySensor.readAlgorithmResults();

    Serial.print("CO2: ");
    //Returns calculated CO2 reading
    Serial.print(mySensor.getCO2());
    Serial.print(" ppm  tVOC: ");
    //Returns calculated TVOC reading
    Serial.print(mySensor.getTVOC());
     Serial.print(" ppb");
    
    Serial.println();
  }

  delay(10); //Don't spam the I2C bus

sensors_event_t event;
  bmp.getEvent(&event);
 
  /* Display the results (barometric pressure is measure in hPa) */
  if (event.pressure)
  {
    /* Display atmospheric pressue in hPa */
    Serial.print("Pressure:    ");
    Serial.print(event.pressure);
    Serial.println(" hPa");
    
    /* Calculating altitude with reasonable accuracy requires pressure    *
     * sea level pressure for your position at the moment the data is     *
     * converted, as well as the ambient temperature in degress           *
     * celcius.  If you don't have these values, a 'generic' value of     *
     * 1013.25 hPa can be used (defined as SENSORS_PRESSURE_SEALEVELHPA   *
     * in sensors.h), but this isn't ideal and will give variable         *
     * results from one day to the next.                                  *
     *                                                                    *
     * You can usually find the current SLP value by looking at weather   *
     * websites or from environmental information centers near any major  *
     * airport.                                                           *
     *                                                                    *
     * For example, for Paris, France you can check the current mean      *
     * pressure and sea level at: http://bit.ly/16Au8ol                   */
     
    /* First we get the current temperature from the BMP085 */
    float temperature;
    bmp.getTemperature(&temperature);
    Serial.print("Temperatur: ");
    Serial.print(temperature-4);
    TEMP = temperature-4;
    Serial.println(" C");
    Serial.println("");
  }
  else
  {
    Serial.println("Sensor error");
  }


CO2 = mySensor.getCO2();
TVOC = mySensor.getTVOC();

  if ((CO2) < 2100) {
    { int t = map(CO2, 400, 2100, 1, NUM_PIXEL);int f = map(CO2, 400, 2100, 0, 255);
       
        clearStrip();
        strip.setPixelColor((t-1),f,255-f,0); 
     
      
      strip.show(); //Output on strip
 
  display.clearDisplay();
  display.setTextSize(2);
    display.setCursor(0,0);
    display.print(F("CO"));
    display.setTextSize(1);
    display.setCursor(23,10);
    display.print(F("2"));
    display.setTextSize(2);
    display.setCursor(28,0);
    display.print(F(":"));
    display.print(mySensor.getCO2());
    display.setCursor(50,20);
    display.setTextSize(1);
    display.println(F("ppm"));

     // text display 

  display.display();
    delay(2000);
  
  display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0,20);
    display.print(F("tVOC:"));
    display.print(mySensor.getTVOC());
    display.println(F("ppb"));
      display.setCursor(60,20);
    display.print(F(":"));
    display.print(event.pressure);
    display.println(F("hPa"));
    display.setCursor(0,0);
    display.setTextSize(2);
    display.print(TEMP);
    display.print((char)247);
    display.print(F("C"));
  
  // text display 

  display.display();
    delay(2000);

      
     }
  }
  else {
    (CO2) = 2100;
        clearStrip();
        strip.setPixelColor(NUM_PIXEL-1,255,0,0); 
        strip.show(); //Output on strip
        display.clearDisplay();
    
    display.setTextSize(2);
    display.setCursor(0,0);
    display.print(F("CO"));
    display.setTextSize(1);
    display.setCursor(23,10);
    display.print(F("2"));
    display.setTextSize(2);
    display.setCursor(28,0);
    display.print(F(":"));
    display.print(mySensor.getCO2());
    display.setCursor(50,20);
    display.setTextSize(1);
    display.println(F("ppm"));
        
    display.display();
  delay(750);  
   
      clearStrip();
      strip.show(); //Output on strip
  delay(750);
     

        clearStrip();
        strip.setPixelColor(NUM_PIXEL-1,255,0,0); 
        strip.show(); //Output on strip
      
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(15,5);
    display.print(F("FENSTER AUF !"));
    display.setCursor(15,20);
    display.print(F("Sauerstoff !"));
    display.display();
  delay(750);   
      clearStrip();
      strip.show(); //Output on strip
  delay(750);

     }

}

void clearStrip() {
  for (int i = 0; i < NUM_PIXEL; i++) {
    strip.setPixelColor(i, 0);
  }
}

void displaySensorDetails(void)
{
  sensor_t sensor;
  bmp.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" hPa");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" hPa");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" hPa");  
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}
