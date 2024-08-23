int buzzer = 3;
int Vibration_signal = A0; 
int Sensor_State = 1;

int leftirpin = 13;
int rightirpin = 4;

int leftstatus;
int rightstatus;

//ultrasonic pins
const int triggerpin = 8;
const int echopin = 7;

//variables for duaration and distance
long duaration_us; //microseconds
long distance_cm; //centimeters

//Threshold distance in cm
const int threshold_cm = 20;

//motor direction control pins
int leftforwardpin = 11;
int leftbackwardpin = 12;
int rightforwardpin = 9;
int rightbackwardpin = 10;

//motor speed control pins; pwm pins are used
int leftmotorspeedpin = 6;
int rightmotorspeedpin = 5;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(Vibration_signal, INPUT); //Set pin as input
  pinMode(buzzer, OUTPUT);  

  pinMode(leftirpin,INPUT);
  pinMode(rightirpin,INPUT);
  
  pinMode(triggerpin,OUTPUT); //since 10 us trigger is given from arduino to ultrasonic sensor 
  pinMode(echopin,INPUT); //echo is received in sensor and high duaration given to arduino
  
  pinMode(leftforwardpin,OUTPUT);
  pinMode(leftbackwardpin,OUTPUT);
  pinMode(rightforwardpin,OUTPUT);
  pinMode(rightbackwardpin,OUTPUT);
  pinMode(leftmotorspeedpin,OUTPUT);
  pinMode(rightmotorspeedpin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  leftstatus = digitalRead(leftirpin); // or use analog read and threshold
  rightstatus = digitalRead(rightirpin);
  
  digitalWrite(triggerpin,LOW);
  delayMicroseconds(2); //low to high pulse
  digitalWrite(triggerpin,HIGH);
  delayMicroseconds(10); //high part is 10 us ;sensor transmitts ultrasound
  digitalWrite(triggerpin,LOW);

  duaration_us = pulseIn(echopin,HIGH); // duaration received signal in microseconds
  distance_cm = 0.017*duaration_us; // finding distance; dis = speed*time/2; 343 m/s to cm/s

   Sensor_State = digitalRead(Vibration_signal);
  if (Sensor_State == 1) {
    //Serial.println("Sensing vibration");
    stopdriving(0);
    for(int i=0;i<5;i++){
    tone(buzzer,500);
    delay(500);
    noTone(buzzer);
    delay(500);
    }
  }

   if(distance_cm < threshold_cm){
    stopdriving(1);
  }
  else{

    if((leftstatus == HIGH) && (rightstatus == HIGH)){
    driveforward(0,130,130);
  }
  else if((leftstatus == LOW) && (rightstatus == HIGH)){
    turnright(0,80,70);
  }
  else if((leftstatus == HIGH) && (rightstatus == LOW)){
    turnleft(0,70,80);
  }
  else{
    stopdriving(2000);
  }
    
  }

}
void stopdriving(int delay_time){//time is in microseconds
  digitalWrite(leftforwardpin,LOW);
  digitalWrite(leftbackwardpin,LOW);
  digitalWrite(rightforwardpin,LOW);
  digitalWrite(rightbackwardpin,LOW);
  delay(delay_time);
}
void driveforward(int delay_time,int leftspeed,int rightspeed){//speed can be 0 - 255
  analogWrite(leftmotorspeedpin,leftspeed);
  analogWrite(rightmotorspeedpin,rightspeed);
  digitalWrite(leftforwardpin,HIGH);
  digitalWrite(leftbackwardpin,LOW);
  digitalWrite(rightforwardpin,HIGH);
  digitalWrite(rightbackwardpin,LOW);
  delay(delay_time);
}
void drivebackward(int delay_time,int leftspeed,int rightspeed){
  analogWrite(leftmotorspeedpin,leftspeed);
  analogWrite(rightmotorspeedpin,rightspeed);
  digitalWrite(leftforwardpin,LOW);
  digitalWrite(leftbackwardpin,HIGH);
  digitalWrite(rightforwardpin,LOW);
  digitalWrite(rightbackwardpin,HIGH);
  delay(delay_time);
}
void turnright(int delay_time,int leftspeed,int rightspeed){
  analogWrite(leftmotorspeedpin,leftspeed);
  analogWrite(rightmotorspeedpin,rightspeed);
  digitalWrite(leftforwardpin,HIGH);
  digitalWrite(leftbackwardpin,LOW);
  digitalWrite(rightforwardpin,LOW);
  digitalWrite(rightbackwardpin,HIGH);
  delay(delay_time);
}
void turnleft(int delay_time,int leftspeed,int rightspeed){
  analogWrite(leftmotorspeedpin,leftspeed);
  analogWrite(rightmotorspeedpin,rightspeed);
  digitalWrite(leftforwardpin,LOW);
  digitalWrite(leftbackwardpin,HIGH);
  digitalWrite(rightforwardpin,HIGH);
  digitalWrite(rightbackwardpin,LOW);
  delay(delay_time);
}
