//the baud rate of the Bluetooth module set to 38400
//tp reduce servo jittering. 
#include <SoftwareSerial.h>
#include <Servo.h>
const int Laser_PIN = 8;
Servo PanServo;
Servo TiltServo;
Servo bowservo;
SoftwareSerial Bluetooth(0, 1); // Arduino(RX, TX)-BT (TX, RX)
int PantServoCurrent, TiltServoCurrent; // current position
int PanServPrevious, TiltServPrevious; // previous position
int index = 0;
String dataIn = "";

void setup() {
  Serial.begin(9600);
  pinMode (Laser_PIN, OUTPUT); 
  bowservo.attach(9);  
  PanServo.attach(10);
  TiltServo.attach(11);
  Bluetooth.begin(38400); //baud rate of the Bluetooth module
  Bluetooth.setTimeout(1);
  delay(20);
  PanServPrevious = 90;// servo initial position
  PanServo.write(PanServPrevious);
  TiltServPrevious = 90;
  TiltServo.write(TiltServPrevious);
}

void loop() {
  // Check for incoming data
  if (Bluetooth.available() > 0) {// Check for incoming data
    dataIn = Bluetooth.readString();  // Read the data as string
    // If "Waist" slider has changed value - Move Servo 1 to position
    if (dataIn.startsWith("s1")) {
      String dataInS = dataIn.substring(2, dataIn.length()); // Extract "120" from "s1120"
      PantServoCurrent = dataInS.toInt();  // Convert the string into integer
      Serial.print("Pan Servo =");
      Serial.println(PantServoCurrent);
      // We use for loops so we can control the speed of the servo
      // If previous position is bigger then current position
      if (PanServPrevious > PantServoCurrent) {
        for ( int j = PanServPrevious; j >= PantServoCurrent; j--) {   // Run servo down
          PanServo.write(j);
          delay(0);    // defines the speed at which the servo rotates
        }
      }
      // If previous position is smaller then current position
      if (PanServPrevious < PantServoCurrent) {
        for ( int j = PanServPrevious; j <= PantServoCurrent; j++) {   // Run servo up
          PanServo.write(j);
          delay(0);
        }
      }
      PanServPrevious = PantServoCurrent;   // set current position as previous position
    }
    
    // Move Servo 2
    if (dataIn.startsWith("s2")) {
      String dataInS = dataIn.substring(2, dataIn.length());
      TiltServoCurrent = dataInS.toInt();
      Serial.print("Tilt Servo =");
      Serial.println(TiltServoCurrent);
      if (TiltServPrevious > TiltServoCurrent) {
        for ( int j = TiltServPrevious; j >= TiltServoCurrent; j--) {
          TiltServo.write(j);
          delay(0);
        }
      }
      if (TiltServPrevious < TiltServoCurrent) {
        for ( int j = TiltServPrevious; j <= TiltServoCurrent; j++) {
          TiltServo.write(j);
          delay(0);
        }
      }
      TiltServPrevious = TiltServoCurrent;
    }
    if (dataIn.startsWith("LASER")) { // If button "LASER" is pressed
      digitalWrite (Laser_PIN, HIGH); // Turn Laser On
      delay (1);               
    }
    else {
      digitalWrite (Laser_PIN, LOW); // Turn Laser Off
      delay (1);  
    }
    if (dataIn.startsWith("FIRE")) {// If button "FIRE" is pressed
        bowservo.write(155);
        delay(1000);
        bowservo.write(20);
        delay(500);
      }    
  }
}
