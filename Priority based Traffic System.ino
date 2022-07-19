//ports for the two sensors
const int Ir_1 = 7;   //first sensor
const int Ir_2 = 13;  //second sensor

//ports for the first set of traffic lights(Churchill Ave)
const int amber_1 = 3;
const int red_1 = 5;
const int green_1 = 6;
//ports for the second setof traffic lights(UZ Gate)
const int amber_2 = 8;
const int red_2 = 9;
const int green_2 = 10;

int flag = 0;  // counter variable to keep track of time


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(Ir_1,INPUT);
  pinMode(Ir_2,INPUT);
  pinMode(red_1,OUTPUT);
  pinMode(amber_1,OUTPUT);
  pinMode(green_1,OUTPUT);
  pinMode(red_2,OUTPUT);
  pinMode(amber_2,OUTPUT);
  pinMode(green_2,OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  int val_1 = (digitalRead(Ir_1)); //Converting output from IR Sensor to digital input
  
  
  init_state();  //initial state of the program

  if(val_1 == LOW){
    
    priority();  //if there's a car at the gate
    init_state(); //return to init state after traffic clears
    }
  
  
 
}

//Defining normal traffic light sequence if the density of traffic is almost the same
void normal(){
  //digitalWrite(red_1,LOW);
   digitalWrite(red_2,HIGH);
  digitalWrite(green_1,HIGH);
 delay(10000);
  digitalWrite(green_1,LOW);
  digitalWrite(amber_1,HIGH);
  delay(5000);
  digitalWrite(amber_1,LOW);
  digitalWrite(red_1,HIGH);
   digitalWrite(red_2,LOW);
  digitalWrite(green_2,HIGH);
  delay(10000);
  digitalWrite(green_2,LOW);
  digitalWrite(amber_2,HIGH);
  delay(5000);
  digitalWrite(amber_2,LOW);
  digitalWrite(red_1,LOW);
  
  }

  //priority sequence 
  void priority(){

    digitalWrite(green_1,LOW);
    digitalWrite(red_2,HIGH);
    digitalWrite(amber_1,HIGH);
    delay(3000);

    digitalWrite(amber_1,LOW);
    digitalWrite(red_1,HIGH);
    digitalWrite(red_2,LOW);
    digitalWrite(green_2,HIGH);
    delay(5000);
 
    //to determine time for the priority sequence
    delay(check());

    digitalWrite(green_2,LOW);
    digitalWrite(amber_2,HIGH);
    delay(3000);
    
    digitalWrite(amber_2,LOW);
    digitalWrite(red_1,LOW);
     
     
 }

//initial program state 
void init_state(){
  digitalWrite(green_1,HIGH);
  digitalWrite(red_2,HIGH);
  }

 //method for determining the time needed priority sequence
 int check(){
    
    int val_2 = (digitalRead(Ir_2)); //Convert output of IR sensor to digital input
    int time_delay;
    
      if(val_2 == LOW){  //if there's a car at the checkpoint
      flag++; //determine the number of times the method check() has been recursively called
      Serial.println(flag);
      if(flag<600){ 
        check();
        }else{ // if a certain amount of time has passed, switch to normal sequence
          digitalWrite(green_2,LOW);
          digitalWrite(amber_2,HIGH);
          delay(3000);
    
          digitalWrite(amber_2,LOW);
          digitalWrite(red_1,LOW);
          normal();
          flag = 0;
          }
      
      }else{
        time_delay = 5000; //time delay for one car to clear the intersection
        return time_delay;
        }
      }
