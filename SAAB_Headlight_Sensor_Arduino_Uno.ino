int Mosfet = 4; //Pin number 9 on the Arduino UNO
int potval = 0;
int oposite = 0;
int lastval = 0;

///////////////////////For mosfet usage need to opposite the HIGH and LOW.
uint8_t HIGH_O = LOW;
uint8_t LOW_O = HIGH;

void setup() 
{
  Serial.begin(115200);
  pinMode(Mosfet,OUTPUT);
  pinMode(A0, INPUT); //Potentiometer is connected on PIN A0
}

void loop() 
{
  read_potentionmeter();
    delay(20);
}

void start_of_transmition()
{
  digitalWrite(Mosfet, HIGH_O);
  delay(2);
  digitalWrite(Mosfet, LOW_O);
  delay(5);
  digitalWrite(Mosfet, HIGH_O);
  delayMicroseconds(1000);

}

void data_of_transmissino()
{
  digitalWrite(Mosfet, HIGH_O);
  delayMicroseconds(potval);
  digitalWrite(Mosfet, LOW_O);
  delayMicroseconds(oposite);
}

void end_of_transmission()
{
  digitalWrite(Mosfet, LOW_O);
  delayMicroseconds(1000);
  digitalWrite(Mosfet, HIGH_O);
  delayMicroseconds(1000);
  digitalWrite(Mosfet, LOW_O);
  delayMicroseconds(500);
  digitalWrite(Mosfet, HIGH_O);
  delayMicroseconds(500);
  digitalWrite(Mosfet, LOW_O);
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
