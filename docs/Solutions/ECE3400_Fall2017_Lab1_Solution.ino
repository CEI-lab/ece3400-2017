#include <Servo.h>

int ledPin = 9;                 // LED connected to digital pin 8
int potmeter = 0;
Servo myservo;

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(A0, INPUT);
  Serial.begin(9600);
  myservo.attach(11);
}

// the loop function runs over and over again forever
void loop() {
/*   
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(ledPin, HIGH);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
*/
/*
  Serial.print("Alpha team!");
  Serial.println("");
  delay(500);
  */
  potmeter = analogRead(A0); //Reads an ADC conversion from pin A0 using default settings for the ADC (10 bit conversion).
  Serial.println(potmeter>>2);  //Send the potmeter value to the screen
  analogWrite(ledPin, potmeter>>2); //The analog write function only takes 8bits, so we have to divide our value by 4
  delay(100);
}
