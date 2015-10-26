#include <Servo.h>
#define SERVO 1
Servo rightServo;
#define SERVO 2
Servo leftServo;

String message;
//Drive settings for motor
const int Neutral = 1500;
const int Up = 1960;
const int Down = 1000;
String state = "UP";


void setup()
{
  Serial.begin(9600); //set baud rate
  pinMode (SERVO, OUTPUT); //want servo pin to be an output
  rightServo.attach(1); //attach the pin to the servo
  rightServo.writeMicroseconds(Neutral); //set servo to mid-point
  leftServo.attach(2);
  leftServo.writeMicroseconds(Neutral);
}
 
void loop(){

  //while there is data available on the serial monitor
  while(Serial.available() && (message != "DOWN\r" || message != "UP\r")){
    //store string from serial command
    message+=char(Serial.read());
    Serial.println(message);
  }
  Serial.println(message);
  if(!Serial.available()){
    //if up signal is received
    if(message.equalsIgnoreCase("UP\r") && state != "UP"){
      
      leftServo.writeMicroseconds(Up);
      rightServo.writeMicroseconds(Up);
      delay(5000);
      
      message ="";
      state = "UP";

      }
    //if down signal is received
    else if(message.equalsIgnoreCase("DOWN\r") && state != "DOWN"){
  
      leftServo.writeMicroseconds(Down);
      rightServo.writeMicroseconds(Down);
      delay(5000);
      
      message="";
      state = "DOWN";

    }
    //otherwise keep the motor in neutral
    else{
      leftServo.writeMicroseconds(Neutral);
      rightServo.writeMicroseconds(Neutral);
    }
  message="";
  }
  delay(500); //delay
}
