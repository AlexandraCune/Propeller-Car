/*
  Alexandra-Ioana Cune
  336CC
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>


#define servo_pin A2
#define CE A0
#define CSN A1

int motor1pin1 = 2;
int motor1pin2 = 3;

int enA = 10;
int enB = 9;

int motor2pin1 = 4;
int motor2pin2 = 5;



RF24 radio(CE, CSN); // CE, CSN
const byte address[6] = "00001";
Servo myServo;

struct Data_Package {
  int dir = 0;
  int power = 0;
};

Data_Package data;


void setup() {
  Serial.begin(9600);
  radio.begin();
  myServo.attach(servo_pin);

  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);

  pinMode(enB, OUTPUT); 
  pinMode(enA, OUTPUT);
  
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {

  if (radio.available()) {
    int x_pos = 0;
    while( radio.available()){
      radio.read(&data, sizeof(Data_Package));
      Serial.println(data.dir);
      Serial.println(data.power);
    }
    x_pos = map(data.dir, 0, 1023, 0, 180);
    myServo.write(x_pos);

  analogWrite(enA, data.power); //ENA pin
  analogWrite(enB,  data.power); //ENB pin

//Controlling spin direction of motors:
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);

  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);



  }
}
