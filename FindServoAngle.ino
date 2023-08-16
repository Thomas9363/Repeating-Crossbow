//run servo by inputing an angle from serial monitor 
//no line ending in monitor
#include <Servo.h>
Servo myservo;
void setup(){
  Serial.begin(9600);
  myservo.attach(10);
  myservo.write(90);
  Serial.println("");
  Serial.println("Input an angle between 0 and 180 degree > ");
}
void loop() {
  while (Serial.available()){
    int angle = Serial.parseInt();
    if (angle >= 0 && angle <= 180){
      Serial.print("> turning servo to ");
      Serial.print(angle);
      Serial.println(" degrees");
      myservo.write(angle);
      Serial.println("Input an angle between 0 and 180 degree > ");
    }
  }
}
