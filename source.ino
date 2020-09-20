
/*
 * This code is implemented on Arduino 2560
 * Sensors work on 5V input
 * Input from ultrasonic sensor on pins 1(front), 2(left), 3(right)
 * DC motor on pins 11 (left), 12 (right)
 */
const float anPin1 = 0;
const float anPin2 = 1;
const float anPin3 = 2;
const int anPin4 = 3;
int triggerPin1 = 1;
int triggerPin2 = 2;
int triggerPin3 = 3;
float distance1, distance2, distance3, sensor_front , sensor_left, sensor_right;

void setup() {
  Serial.begin(9600);  // sets the serial port to 9600
}

void start_sensor(){
  digitalWrite(triggerPin1,HIGH);
  delay(1);
  digitalWrite(triggerPin1,LOW);

  digitalWrite(triggerPin2,HIGH);
  delay(1);
  digitalWrite(triggerPin2,LOW);

 digitalWrite(triggerPin3,HIGH);
 delay(1);
 digitalWrite(triggerPin3,LOW);
}
void start_motor_left(){
  analogWrite(12,253);
delay(300);
analogWrite(12,0);
delay(300);
}
void start_motor_right(){
  analogWrite(11,253);
delay(300);
analogWrite(11,0);
delay(300);
}

void read_sensors(){
  distance1 = analogRead(anPin1)*5;
  distance2 = analogRead(anPin2)*5;
  distance3 = analogRead(anPin3)*5;          
  mts1=distance1/10;
  mts2=distance2/10;
  mts3=distance3/10;

  if((sensor_front&&sensor_left&&sensor_right)<15)
  {
    Serial.println("Stop");  
    Serial.println("P2\r"); // 2.WAV AUDIO FOR STOP!
    delay(2500);
    Serial.println("S"); 
    start_motor_right();
    start_motor_left();
    break;
    }
  
  else if(((sensor_front&&sensor_left)<60)&&(sensor_right>60))
  {
    Serial.println("SLIGHT RIGHT");  
    Serial.println("P3\r"); // 3.WAV AUDIO FOR SLIGHT RIGHT
    delay(2500);
    Serial.println("S");
    start_motor_right();
    break;
    }
    
    else if((sensor_front&&sensor_right<60)&&(sensor_left>60))
    {
    Serial.println("SLIGHT LEFT");  
    Serial.println("P4\r"); // 4.WAV AUDIO FOR SLIGHT LEFT
    delay(2500);
    Serial.println("S");
    start_motor_left();
    break;
      }
      
  else if(((sensor_left&&sensor_right)<60)&&sensor_front>60)
  {
    Serial.println("Straight");  
    Serial.println("P1\r");
    delay(2500);
    Serial.println("S");
    delay(500); 
    break;
    }
  
  else if(sensor_front<100)
  {
    if(sensor_left>sensor_right)
    {
     Serial.println("LEFT");  
     Serial.println("P5\r"); // 5.WAV AUDIO FOR  LEFT
     delay(2500);
     Serial.println("S");
     start_motor_left();
     break;
      
      }
      else if (sensor_right>sensor_left)
      {
       Serial.println("RIGHT");  
       Serial.println("P6\r"); // 6.WAV AUDIO FOR  RIGHT
       delay(2500);
       Serial.println("S");
       start_motor_right();
        break;
        }
         break;
    }
  else if(sensor_left<60)
  {
    if(sensor_front>60)
     {
       Serial.println("Straight");  
       Serial.println("P1\r");
       delay(2500);
       Serial.println("S");
       delay(500); 
       return 0;
      }
   else if(sensor_right>60)
    {
       Serial.println("RIGHT");  
       Serial.println("P6\r"); // 6.WAV AUDIO FOR  RIGHT
       delay(2500);
       Serial.println("S");
       start_motor_right();
    
    }
     break;
     
  }
 else if(sensor_right<60)
    {
      
    if(sensor_front>60)
     {
       Serial.println("Straight");  
       Serial.println("P1\r");
       delay(2500);
       Serial.println("S");
       delay(500); 
       break;
      }
      else if(sensor_left>60)
      {
        Serial.println("LEFT");  
        Serial.println("P5\r"); // 5.WAV AUDIO FOR  LEFT
        delay(2500);
        Serial.println("S");
        start_motor_left();
        break;
      }
 break;
      
      }
     
}

void print_all(){
 Serial.print("S1=");
 Serial.print(sensor_front);
 Serial.print("m");
 Serial.print(" S2=");
 Serial.print(sensor_left);
 Serial.print("m");
 Serial.print(" S3=");
 Serial.print(sensor_right);
 Serial.print("m");
 delay(1000);
}

void loop() {
  start_sensor();
  read_sensors();
  print_all();
  delay(10000);
}
