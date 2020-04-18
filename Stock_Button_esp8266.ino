////This is used with the "Original" halogen height adjust switch instead of a potentiometer.

int MOSFET = 4;
int potval = 0;
int oposite = 0;
int lastval = 0;
int stored_time = 0;
int elapsed_time = 0;
int reapets = 1;
int current_height = 1500;

#include "ESP8266WiFi.h"


///////////////////////For mosfet usage need to opposite the HIGH and LOW.
uint8_t HIGH_O = LOW;
uint8_t LOW_O = HIGH;

void setup() 
{
  WiFi.mode(WIFI_OFF);
  WiFi.forceSleepBegin();                  // turn off ESP8266 RF
  delay(1);                                // give RF section time to shutdown
  Serial.begin(115200);
  pinMode(MOSFET,OUTPUT);
  pinMode(A0, INPUT);
  stored_time = millis();
}

void loop() 
{
  read_potentionmeter();
  lastval = current_height;
}

void start_of_transmition()
{
  digitalWrite(MOSFET, HIGH_O);
  delay(2);
  digitalWrite(MOSFET, LOW_O);
  delay(5);
  digitalWrite(MOSFET, HIGH_O);
  delayMicroseconds(1000);

}

void data_of_transmissino()
{
  digitalWrite(MOSFET, HIGH_O);
  delayMicroseconds(current_height);
  digitalWrite(MOSFET, LOW_O);
  delayMicroseconds(oposite);
}

void end_of_transmission()
{
  digitalWrite(MOSFET, LOW_O);
  delayMicroseconds(1000);
  digitalWrite(MOSFET, HIGH_O);
  delayMicroseconds(1000);
  digitalWrite(MOSFET, LOW_O);
  delayMicroseconds(500);
  digitalWrite(MOSFET, HIGH_O);
  delayMicroseconds(500);
  digitalWrite(MOSFET, LOW_O);
  delay(4);
}

void read_potentionmeter()
{
  ///Reading potentiometer
      potval = analogRead(A0);
      
     //Check Saab switch
     //MODE 0
     if (potval > 150 && potval < 250)
         {
            current_height = 1500;
         }
     //MODE 1
     else if (potval > 300 && potval < 400)
         {
            if(current_height <= 300)
            {
              current_height = 100;
            }
            else
            {
            current_height -= 50;
            }
         }
     //MODE 2
     else if (potval > 450 && potval < 510)
         {
          
         }
     //MODE 3
     else if (potval > 510)
         {
          if(current_height >= 2700)
          {
            current_height = 2900;
          }
          else
          {
          current_height += 50;
          }
         }
      //Serial.println(current_height);
         
      //debug////////////////////
      Serial.println(potval);//
      Serial.println(current_height);
      ///////////////////////////
      
      oposite = 3000 - current_height;
  
      ///Contiue transmittion for 3 seconds after changed.
      if (reapets == 0)
          {
              if (lastval < current_height + 10 && lastval > current_height - 10)
                  {
                     delay(500);
                  }
              else
                  {
                    reapets = 1;
                    stored_time = millis();
                  }
           }
        else
        {
          ////Transmition start here - send 5 times each signal
           for (int i = 0; i <= 5; i++) {
           send_signal();
        }

        }
}

//void checktime()
//   {
//     elapsed_time = millis() - stored_time;
//      if(elapsed_time >= 2000)
//      {
//        reapets = 0;
//      }
//   }

void send_signal()
{
    start_of_transmition();
    data_of_transmissino();
    end_of_transmission();
    //checktime();
}
