#include "LedControl.h"
/* pin 12 is connected to the DataIn
   pin 11 is connected to the CLK
   pin 10 is connected to LOAD
   syntax- LedControl(dataPin,clockPin,csPin,number of MAX7219 Devices) */

LedControl lc=LedControl(12,11,10,1);

//Ultrasonic Sensor pin declarations
const int trigPin = 8;
const int echoPin = 9;

long duration;   //  to calculate the time taken to receive the signal
int distance;    //to calculate the distance from the obstacle

void setup()
{
  /* The MAX72XX is in power-saving mode on startup,
   * we have to do a wakeup call  */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values
   * SYNTAX lc.setIntensity(address of LED matrix, brightness from 0 to 15) */
  lc.setIntensity(0,5);
  /* and clear the display 
   * SYNTAX lc.clearDisplay(address of the LED MATRIX number) */
  lc.clearDisplay(0);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
}

void loop()
{
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
   // Sets the trigPin on HIGH state for 10 micro seconds to send 8 cycles of sonic
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  /* Reads the echoPin, returns the sound wave travel time in microseconds pulsIn() 
  function will wait for the pin to go HIGH caused by the bounced sound wave and it will start timing,
  then it will wait for the pin to go LOW when the sound wave will end which will stop the timing.
  At the end the function will return the length of the pulse in microseconds.*/
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance= duration*0.034/2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  if (distance> 10)
  {
    Serial.println("Off");
    displayoff();
  }
  else
  {
    Serial.println("On");
    displayon();  
  }
  delay(1000);
}

void displayon()
{
  /*to display 'ON' character by character on LED MATRIX */
  /* here is the data for the characters */
  byte o[8]={B00000000,B01111110,B01000010, B01000010, B01000010, B01000010 , B01111110, B0000000};
  byte n[8]={B00000000,B01000010,B01100010,B01010010, B01001010, B01000110,B01000010,B0000000};
  /* now display them one by one with a small delay 
   *  setRow(addr,row, array value)  */
  lc.setRow(0,0,o[0]);
  lc.setRow(0,1,o[1]);
  lc.setRow(0,2,o[2]);
  lc.setRow(0,3,o[3]);
  lc.setRow(0,4,o[4]);
  lc.setRow(0,5,o[5]);
  lc.setRow(0,6,o[6]);
  lc.setRow(0,7,o[7]);
  delay(2000);
  lc.setRow(0,0,n[0]);
  lc.setRow(0,1,n[1]);
  lc.setRow(0,2,n[2]);
  lc.setRow(0,3,n[3]);
  lc.setRow(0,4,n[4]);
  lc.setRow(0,5,n[5]);
  lc.setRow(0,6,n[6]);
  lc.setRow(0,7,n[7]);
  delay(2000); 
  lc.clearDisplay(0);
  delay(2000);
}

void displayoff()
{
  /*to display 'OFF' character by character on LED MATRIX */
 byte o[8]={B00000000,B01111110,B01000010, B01000010, B01000010, B01000010 , B01111110, B0000000};
 byte f[8]={B00000000,B01111110,B01000000, B01111000, B01000000, B01000000,  B01000000, B0000000};
  lc.setRow(0,0,o[0]);
  lc.setRow(0,1,o[1]);
  lc.setRow(0,2,o[2]);
  lc.setRow(0,3,o[3]);
  lc.setRow(0,4,o[4]);
  lc.setRow(0,5,o[5]);
  lc.setRow(0,6,o[6]);
  lc.setRow(0,7,o[7]);
  delay(2000);
  lc.setRow(0,0,f[0]);
  lc.setRow(0,1,f[1]);
  lc.setRow(0,2,f[2]);
  lc.setRow(0,3,f[3]);
  lc.setRow(0,4,f[4]);
  lc.setRow(0,5,f[5]);
  lc.setRow(0,6,f[6]);
  lc.setRow(0,7,f[7]);
  delay(2000);
  lc.clearDisplay(0);
  delay(100);
  lc.setRow(0,0,f[0]);
  lc.setRow(0,1,f[1]);
  lc.setRow(0,2,f[2]);
  lc.setRow(0,3,f[3]);
  lc.setRow(0,4,f[4]);
  lc.setRow(0,5,f[5]);
  lc.setRow(0,6,f[6]);
  lc.setRow(0,7,f[7]);
  delay(2000);
  lc.clearDisplay(0);
  delay(2000); 
}
