#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>

ros::NodeHandle  nh;

//Ecoder
int rawsensorValue_M1 = 0; // variable to store the value coming from the sensor
int sensorcount0_M1 = 0;
int sensorcount1_M1 = 0;
long count_M1 = 0;

int rawsensorValue_M2 = 0; // variable to store the value coming from the sensor
int sensorcount0_M2 = 0;
int sensorcount1_M2 = 0;
long count_M2 = 0;

int rawsensorValue_M3 = 0; // variable to store the value coming from the sensor
int sensorcount0_M3 = 0;
int sensorcount1_M3 = 0;
long count_M3 = 0;

int rawsensorValue_M4 = 0; // variable to store the value coming from the sensor
int sensorcount0_M4 = 0;
int sensorcount1_M4 = 0;
long count_M4 = 0;
//Front motors
int E1 = 10 ; //M1 Speed Control
int E2 = 11; //M2 Speed Control
int M1 = 12; //M1 Direction Control
int M2 = 13; //M2 Direction Control
//Rear motors
int E3 = 6; //M1 Speed Control
int E4 = 5; //M2 Speed Control
int M3 = 8; //M1 Direction Control
int M4 = 7; //M2 Direction Control

int leftspeed = 255; //255 is maximum speed
int rightspeed = 255;
bool f = false;
std_msgs::String str_msg;

void messageCb( const std_msgs::String& toggle_msg){
  //Serial.printf(toggle_msg.data);
  str_msg.data = toggle_msg.data;
  if(strcmp(toggle_msg.data,"a") == 0){
      //digitalWrite(13, HIGH);
      left(leftspeed,rightspeed);
      //Serial.println(toggle_msg.data);
  }
  else if(strcmp(toggle_msg.data,"d") == 0) {
      right(leftspeed,rightspeed);
  }
  else if(strcmp(toggle_msg.data,"w") == 0) {
      forward (leftspeed,rightspeed);
  }
  else if(strcmp(toggle_msg.data,"stop") == 0) {
      stop();
  }
  else if(strcmp(toggle_msg.data,"s") == 0) {
      reverse(leftspeed,rightspeed);
  }
}

ros::Subscriber<std_msgs::String> sub("chatter", &messageCb );


void setup()
{
int i;
for(i=3;i<=13;i++)
pinMode(i, OUTPUT);
Serial.begin(576000);

nh.initNode();
nh.subscribe(sub);
}
void loop()
{
  nh.spinOnce();
  delay(0);
/*while (Serial.available() < 1) {
encoder();
} // Wait until a character is received
char val = Serial.read();
int leftspeed = 255; //255 is maximum speed
int rightspeed = 255;
switch(val) // Perform an action depending on the command
{
case 'w'://Move Forward
forward (leftspeed,rightspeed);
break;
case 's'://Move Backwards
reverse (leftspeed,rightspeed);
break;
case 'a'://Turn Left
left (leftspeed,rightspeed);
break;
case 'd'://Turn Right
right (leftspeed,rightspeed);
break;
case 'q'://rotate ccw
ccw (leftspeed,rightspeed);
break;
case 'e'://rotate cw
cw (leftspeed,rightspeed);
break;
case 'z'://move at 45 degrees
fortyfive (leftspeed,rightspeed);
break;
case 'x'://move at 135 degrees
onethirtyfive (leftspeed,rightspeed);
break;
// to move at 225 and 315, use the 45 degree and 135 degree code but reverse motor direction.
default:
stop();
break;
}
*/
}
void stop(void) //Stop
{
digitalWrite(E1,LOW);
digitalWrite(E2,LOW);
digitalWrite(E3,LOW);
digitalWrite(E4,LOW);
}
void forward(char a,char b)
{
analogWrite (E1,a);
digitalWrite(M1,LOW);
analogWrite (E2,b);
digitalWrite(M2,HIGH);
analogWrite (E3,a);
digitalWrite(M3,LOW);
analogWrite (E4,b);
digitalWrite(M4,HIGH);
}
void reverse (char a,char b)
{
analogWrite (E1,a);
digitalWrite(M1,HIGH);
analogWrite (E2,b);
digitalWrite(M2,LOW);
analogWrite (E3,a);
digitalWrite(M3,HIGH);
analogWrite (E4,b);
digitalWrite(M4,LOW);
}
void ccw (char a,char b)
{
analogWrite (E1,a);
digitalWrite(M1,HIGH);
analogWrite (E2,b);
digitalWrite(M2,HIGH);
analogWrite (E3,a);
digitalWrite(M3,HIGH);
analogWrite (E4,b);
digitalWrite(M4,LOW);
}
void cw (char a,char b)
{
analogWrite (E1,a);
digitalWrite(M1,LOW);
analogWrite (E2,b);
digitalWrite(M2,LOW);
analogWrite (E3,a);
digitalWrite(M3,LOW);
analogWrite (E4,b);
digitalWrite(M4,HIGH);
}
void left (char a,char b)
{
analogWrite (E1,a);
digitalWrite(M1,HIGH);
analogWrite (E2,b);
digitalWrite(M2,HIGH);
analogWrite (E3,a);
digitalWrite(M3,LOW);
analogWrite (E4,b);
digitalWrite(M4,LOW);
}
void right (char a,char b)
{
analogWrite (E1,a);
digitalWrite(M1,LOW);
analogWrite (E2,b);
digitalWrite(M2,LOW);
analogWrite (E3,a);
digitalWrite(M3,HIGH);
analogWrite (E4,b);
digitalWrite(M4,HIGH);
}
void fortyfive (char a,char b)
{
analogWrite (E1,a);
digitalWrite(M1,LOW);
analogWrite (E3,a);
digitalWrite(M3,LOW);
}
void onethirtyfive (char a,char b)
{
analogWrite (E2,b);
digitalWrite(M2,HIGH);
analogWrite (E4,b);
digitalWrite(M4,HIGH);
}
void encoder(){
rawsensorValue_M1 = analogRead(0);
if (rawsensorValue_M1 < 600){ //Min value is 400 and max value is 800, so state chance can be done at 600.
sensorcount1_M1 = 1;
}
else {
sensorcount1_M1 = 0;
}
if (sensorcount1_M1 != sensorcount0_M1){
count_M1 ++;
}
sensorcount0_M1 = sensorcount1_M1;

rawsensorValue_M2 = analogRead(1);
if (rawsensorValue_M2 < 600){ //Min value is 400 and max value is 800, so state chance can be done at 600.
sensorcount1_M2 = 1;
}
else {
sensorcount1_M2 = 0;
}
if (sensorcount1_M2 != sensorcount0_M2){
count_M2 ++;
}
sensorcount0_M2 = sensorcount1_M2;

rawsensorValue_M3 = analogRead(2);
if (rawsensorValue_M3 < 600){ //Min value is 400 and max value is 800, so state chance can be done at 600.
sensorcount1_M3 = 1;
}
else {
sensorcount1_M3 = 0;
}
if (sensorcount1_M3 != sensorcount0_M3){
count_M3 ++;
}
sensorcount0_M3 = sensorcount1_M3;

rawsensorValue_M4 = analogRead(3);
if (rawsensorValue_M4 < 600){ //Min value is 400 and max value is 800, so state chance can be done at 600.
sensorcount1_M4 = 1;
}
else {
sensorcount1_M4 = 0;
}
if (sensorcount1_M4 != sensorcount0_M4){
count_M4 ++;
}
sensorcount0_M4 = sensorcount1_M4;

Serial.print("M1:");
Serial.print(count_M1);

Serial.print(" M2:");
Serial.print(count_M2);

Serial.print(" M3:");
Serial.print(count_M3);

Serial.print(" M4:");
Serial.print(count_M4);

Serial.println(" ");
}
