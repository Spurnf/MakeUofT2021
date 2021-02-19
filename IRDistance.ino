/*
 * Code Written By: Maxim Radulovic & Christopher Mountain
 * Date: 15/02/2021
 * Description: Simple code using an IR sensor to get an analog value for distance, 
 * then mapping said values to a servo output for haptic distance feedback.
 */
 
#include <Servo.h>

#define IRPIN 0 //the analog pin with the Sharp Infrared sensor 
float distanceVal;
int servoVal;
float voltVal;
float distance;
Servo servoDist;

void setup() 
{
  Serial.begin(9600); //begin serial instance at 9600 baud
  servoDist.attach(9); // attach servo to digital pin 9
}

void loop() 
{
  Serial.print("Sharp = ");
  distanceVal = analogRead(IRPIN); //read sensor value
  Serial.print(distanceVal); //display IR sensor value
  Serial.println();

  voltVal = mapf(distanceVal, 0, 1023, 0, 3); //map float from input to the voltage being inputted

  distance = log((voltVal-0.4905445)/3.521161)/-0.07; //use function from curve fit to determine distance

  servoVal = map(distance, 10, 50, 10, 170); //map the values of the distance to the servo, had to mess with it to get it reliable up to about a meter
  servoDist.write(servoVal); //write value to servo
  
  delay(100); //pause for 1/10th of a second
}

float mapf(float var, float min1, float max1, float min2, float max2) //map float function for voltage as map does not work for floats
{
    return (var-min1)*(max2-min2)/(max1-min1) + min2; //basically map function using floats instead
}
