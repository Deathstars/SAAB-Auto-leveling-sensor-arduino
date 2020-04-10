#include "ESP8266WiFi.h"
int LED = 4; //Pin D2 on the esp8266
int potval = 0;
int oposite = 0;
int lastval = 0;

///////////////////////For mosfet usage need to opposite the HIGH and LOW.
uint8_t HIGH_O = LOW;
uint8_t LOW_O = HIGH;

void setup() 
{
  WiFi.mode(WIFI_OFF);
  WiFi.forceSleepBegin();                  // turn off ESP8266 RF
  delay(1);                                // give RF section time to shutdown
  Serial.begin(115200);
  pinMode(LED,OUTPUT);
  pinMode(A0, INPUT);
}

void loop() 
{
  read_potentionmeter();
    delay(20);
}

void start_of_transmition()
{
  digitalWrite(LED, HIGH_O);
  delay(2);
  digitalWrite(LED, LOW_O);
  delay(5);
  digitalWrite(LED, HIGH_O);
  delayMicroseconds(1000);

}

void data_of_transmissino()
{
  digitalWrite(LED, HIGH_O);
  delayMicroseconds(potval);
  digitalWrite(LED, LOW_O);
  delayMicroseconds(oposite);
}

void end_of_transmission()
{
  digitalWrite(LED, LOW_O);
  delayMicroseconds(1000);
  digitalWrite(LED, HIGH_O);
  delayMicroseconds(1000);
  digitalWrite(LED, LOW_O);
  delayMicroseconds(500);
  digitalWrite(LED, HIGH_O);
  delayMicroseconds(500);
  digitalWrite(LED, LOW_O);
  delay(4);
}

void read_potentionmeter()
{
  potval = analogRead(A0);
  potval = potval * 2.92;
  oposite = 3000 - potval;
  if (potval <= 0)
  {
    potval = 0;
  }
  if (oposite <= 0)
  {
    oposite = 0;
  }
      lastval = potval;
      Serial.println(potval);
      Serial.println(oposite);
      start_of_transmition();
      data_of_transmissino();
      end_of_transmission();
}
