/*
  Alexandra-Ioana Cune
  336CC
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define x_key A0
#define pin_Pot A1

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";


struct Data_Package {
  int dir = 0;
  int power = 0;
};

Data_Package data;

void setup() {

  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  pinMode (x_key, INPUT) ;  
  pinMode (pin_Pot, INPUT);  
}

void loop() {
  data.dir = analogRead (x_key);
  int data_pot = analogRead(pin_Pot);
  int percentage = map(data_pot, 0, 1023, 0, 100);
  data.power = percentage; 
  Serial.println(data.dir); 
  Serial.println(data.power);
  radio.write(&data, sizeof(Data_Package));

  delay(1000);
}
