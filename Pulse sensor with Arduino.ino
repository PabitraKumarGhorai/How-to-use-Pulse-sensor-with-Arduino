#include<Wire.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display = Adafruit_SSD1306();

int sensorPin = A0;
float sensorValue= 0;
int count = 9;
unsigned long starttime = 0;

int heartrate = 0;

boolean counted = false;

void setup()
{
  Serial.begin(9600); // If you use nodeMCU then this value is change to 115200
  
 
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Display Address
  display.clearDisplay();

  display.setTextColor(WHITE);
}
void loop()
{
  starttime = millis();

  while(millis()<starttime+10000) // Reading the pulse for 10 sec.
  {
    sensorValue = analogRead(sensorPin);
    if(sensorValue > 550 && counted==false) //Checking whether the thresold value is 550 (2.7v)
    {
      count++;
      Serial.print("count =");
      Serial.println(count);
      

      
      counted = true;
    }
    else if(sensorValue<550)
    {

      counted = false;
      
    }
  }

  heartrate = count*6; // Multiply the count by 6 to get beats per minute
  Serial.println();
  Serial.print("BPM =");
  Serial.println(heartrate);
  Serial.println();
  count = 0;
  display.setCursor(6,10);
   display.setTextSize(2);
  display.print(heartrate);
  display.display();
  display.clearDisplay();


  

}
