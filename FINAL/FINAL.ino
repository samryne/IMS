#include <AFMotor.h>
// Motor Library add
#define lights_green 46

#include <NewPing.h>

#define TRIGGER_PIN_F  44//BROWN
#define ECHO_PIN_F     45//ORANGE
#define MAX_DISTANCE_F 200


#define TRIGGER_PIN_R  9//BLACK
#define ECHO_PIN_R     13//BROWN
#define MAX_DISTANCE_R 50
NewPing sonar_R(TRIGGER_PIN_R, ECHO_PIN_R, MAX_DISTANCE_R);

AF_DCMotor motor(2,MOTOR12_64KHZ); //Left MOTOR-reset button of motor driver as a reference
AF_DCMotor motor2(4,MOTOR12_64KHZ); //Right MOTOR

int left_brown = 8; //Start from left sense pin
int blue = 9;
int yellow = 10;
int grey = 11;
int right_white = 12;
int value_brown, value_blue,value_yellow, value_grey, value_white;
int convalue1, convalue2,convalue3, convalue4,convalue5;
int leftOffset,rightOffset,xright,xleft,centre;
int distance_R;
int stop=0;


void calibrate() {
for (int x=0; x<10; x++) { // run this 10 times to obtain average
digitalWrite(lights_green, HIGH); // lights on
value_brown = analogRead(left_brown);//Name of color indicates the colors of the wires 
value_blue = analogRead(blue); 
value_yellow = analogRead(yellow); 
value_grey = analogRead(grey); 
value_white = analogRead(right_white);
leftOffset = leftOffset + value_brown;// add value of left sensor to total
xleft=xleft+value_blue;
centre = centre + value_yellow;// add value of centre sensor to total
xright=xright+value_grey;
rightOffset = rightOffset + value_white; // add value of right sensor to total
digitalWrite(lights_green, LOW); // lights off

}
// obtain average for each sensor
leftOffset = leftOffset / 10;
xleft=xleft/10;
centre = centre /10;
xright=xright/10;
rightOffset = rightOffset / 10;
}
int stop_2=2;
void setup()
{ 
  Serial.begin(9600);
  pinMode(value_brown, INPUT);
  pinMode(value_blue, INPUT);
  pinMode(value_yellow, INPUT);
  pinMode(value_grey, INPUT);
  pinMode(value_white, INPUT);
  pinMode(lights_green, OUTPUT);
  calibrate();
  digitalWrite(lights_green, HIGH); // lights on
  motor.run(RELEASE);
  motor2.run(RELEASE);
}
void loop()
{ 
  delay(500);// Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int uS = sonar_R.ping(); // Send ping, get ping time in microseconds (uS).
  Serial.print("Ping R: ");
  distance_R = uS / US_ROUNDTRIP_CM;
  // Convert ping time to distance in cm and print result (0 = outside set distance range)
  Serial.print(distance_R);
  Serial.println("cm");
 
value_brown = analogRead(left_brown);
value_blue = analogRead(blue);
value_yellow = analogRead(yellow); 
value_grey = analogRead(grey); 
value_white = analogRead(right_white);
Serial.print("value_brown");
Serial.println(analogRead(value_brown));
Serial.print("value_blue");
Serial.println(analogRead(value_blue));
Serial.print("value_yellow");
Serial.println(analogRead(value_yellow));
Serial.print("value_grey");
Serial.println(analogRead(value_grey));
Serial.print("value_white");
Serial.println(analogRead(value_white));
{
{if ( value_brown >=490 && value_brown <= 1022 )
convalue1 = 0 ; //Black

else if ( value_brown >= 15 && value_brown <= 620)
convalue1 = 1 ;
} //; //White
{if ( value_blue >= 620 && value_blue <= 1022)
convalue2 = 0 ;  //Black
else if ( value_blue >=15 && value_blue <= 620)
convalue2 = 1 ;
} //White
{if ( value_yellow >= 620 && value_yellow <= 1022)
convalue3 = 0 ;  //Black
else if ( value_yellow >= 15 && value_yellow <= 620)
convalue3 = 1 ;
} //White
{if ( value_grey >= 620 && value_grey <= 1022)
convalue4 = 0 ;  //Black
else if ( value_grey >= 15 && value_grey <=620 )
convalue4 = 1 ;} //White
{if ( value_white >= 620 &&value_white <= 1022)
convalue5 = 0 ;  //Black
else if (value_white >= 15 && value_white <= 620)
convalue5 = 1 ;} //White
}

if(convalue1== 1 && convalue2== 1 && convalue3== 1 && convalue4== 1 && convalue5== 1)
{
  stop = 1;
  /*delay(200);
  motor.run(FORWARD);
  motor2.run(RELEASE);
  delay(150);
  motor.run(FORWARD);
  motor2.run(RELEASE);
  delay(150);
  motor.run(FORWARD);
  motor2.run(FORWARD);
  delay(100);*/
  motor.run(BACKWARD);
  motor2.run(BACKWARD);
  delay(500);
  motor2.run(FORWARD);
  motor.run(RELEASE);
  motor2.run(FORWARD);
  motor.run(RELEASE);
  delay(200);
}
else 
{
  motor.setSpeed(150);
  motor2.setSpeed(150);
  motor.run(FORWARD);
  motor2.run(FORWARD);
  stop =0;
}


 
if((distance_R==20||distance_R==21||distance_R==22||distance_R==23||distance_R==24||distance_R==25||distance_R==26||distance_R==27||distance_R==28||distance_R==29) && stop == 0)
{
  Serial.print("GO TO STATION-1");
  motor.setSpeed(150);
  motor2.setSpeed(150);
  motor.run(FORWARD);
  motor2.run(FORWARD);
  //delay(150);
 
  
}
else{
  motor.run(RELEASE);
  motor2.run(RELEASE);
}



}

