#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DFRobot_MLX90614.h>
#include <Wire.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
DFRobot_MLX90614_I2C sensor;   // instantiate an object to drive our sensor
int buzzer=6;
void setup()
{
  Serial.begin(115200);
  pinMode(buzzer,OUTPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  delay(2000);
  display.clearDisplay();
  display.setTextColor(WHITE);
  // initialize the sensor
  while( NO_ERR != sensor.begin() ){
    Serial.println("Communication with device failed, please check connection");
    delay(3000);
  }
  Serial.println("Begin ok!");

  /**
   * adjust sensor sleep mode
   * mode select to enter or exit sleep mode, it's enter sleep mode by default
   *      true is to enter sleep mode
   *      false is to exit sleep mode (automatically exit sleep mode after power down and restart)
   */
  sensor.enterSleepMode();
  delay(50);
  sensor.enterSleepMode(false);
  delay(200);

sensor.setEmissivityCorrectionCoefficient(0.91);
float ambientTemp = sensor.getAmbientTempCelsius();
float objectTemp = sensor.getObjectTempCelsius();
 
}

void loop()
{

  float ambientTemp = sensor.getAmbientTempCelsius();  
  float temp = sensor.getObjectTempCelsius();
display.clearDisplay();
  display.setTextSize(3);
  display.setCursor(0, 20);
  display.print(temp);
   display.print((char)247);
  display.print("C");
display.display();
if(temp>45)
{
  digitalWrite(buzzer,HIGH);
  delay(1000);
  digitalWrite(buzzer,LOW);
  }
delay(1000);

}
