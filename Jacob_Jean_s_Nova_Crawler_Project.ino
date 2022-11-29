#include <Servo.h>   //makes servo library
Servo right;      //servo named right
Servo left;     //servo named left
int trig = 2; // attach pin 2 to Trig
int echo = 3; //attach pin 3 to Echo
int rightPin = 4; //attach pin 4 to rightPin servo
int leftPin = 5;  //attach pin 5 to leftPin servo
void setup() 
{
Serial.begin(9600);   //serial monitor with a refresh rate of 9600
right.attach(rightPin);   //attaches right servo pin
left.attach(leftPin);   //attaches left servo pin
}

void loop() 
{
 // establish variables for duration of the ping,
  // and the distance result in inches and centimeters:
  long duration, inches, cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(trig, OUTPUT);      
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echo, INPUT);
  duration = pulseIn(echo, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  Serial.print(inches);
  Serial.print("in, ");
  Serial.println();

  delay(100);
      //range of less than 30 inches right and left turn by 90 degrees with a delay of 500 and 100
  if (inches <30)
  {
  right.write(90);
  delay(500);
  left.write(90);   
  delay(100);
  }
  else  //if not less than 30 inches right and left servo turn back to 0 degrees with a delay of 500 and 50 
  {
    right.write(0);
    delay(500);
    left.write(0);
    delay(50);
  }

}

long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second). This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PI...
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
