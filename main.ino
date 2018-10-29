
#include <SoftwareSerial.h>
#include <Servo.h>

const byte rxPin = 11; // Wired this to Tx Pin of ESP8266
const byte txPin = 10; // Wired this to Rx Pin of ESP8266

// We had used a software serial interface to connect to ESP8266
SoftwareSerial esp8266 (rxPin, txPin);

Servo myservo1;
Servo myservo2;

int servo_position1 , servo_position2 ;

void setup() {
  
  Serial.begin(9600);
  esp8266.begin(9600); // Esp8266 WiFi Module default baud rate
  
  Serial.println("Working...");

  pinMode(2,OUTPUT);
  digitalWrite(2,LOW);
  
  pinMode(4,OUTPUT);
  digitalWrite(4,LOW);

  pinMode(7,OUTPUT);
  digitalWrite(7,LOW);
  
  pinMode(8,OUTPUT);
  digitalWrite(8,LOW);
  
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);

  pinMode(12,OUTPUT);
  digitalWrite(12,HIGH);

  pinMode(3,OUTPUT);
  digitalWrite(3,LOW);

  pinMode(5,OUTPUT);
  digitalWrite(5,LOW);

  sendCommand("AT+RST\r\n"); // reset module
  delay(1000);
  sendCommand("AT+CWMODE=3\r\n"); // configure as access point
  delay(1000);
  sendCommand("AT+CWJAP=\"HAWKER\",\"12344321\"\r\n");
  delay(5000);
 
  sendCommand("AT+CIFSR\r\n"); // get ip address
  delay(1000);
  sendCommand("AT+CIPMUX=1\r\n"); // configure for multiple connections
  delay(5000);
  sendCommand("AT+CIPSERVER=1,80\r\n"); // turn on server on port 80 
  delay(5000);
  
  Serial.println("Server Ready");

    myservo1.attach(6);
  myservo2.attach(9);

  servo_position1 = 90 ;
  servo_position2 = 50 ;

  myservo1.write(servo_position1);
  myservo2.write(servo_position2);

  delay(500);

  myservo1.detach();
  myservo2.detach();


}

void loop() {
  

  if(esp8266.available())
  {
    if(esp8266.find("+IPD"))
    {
      process();
    }
  }
}
void sendCommand(String command){
  Serial.println(command);
  esp8266.print(command);
}
void process(){
      Serial.println("COMMAND RECEIVED..");
      Serial.println(esp8266.read());
      Serial.println(esp8266.read());
      Serial.println(esp8266.read());
      Serial.println(esp8266.read());
      Serial.println(esp8266.read());
      Serial.println(esp8266.read());
      Serial.println(esp8266.read());
      Serial.println(esp8266.read());
      Serial.println(esp8266.read());
      Serial.println(esp8266.read());
      Serial.println(esp8266.read());
      Serial.println(esp8266.read());
      char function = (esp8266.read());      
      char value = (esp8266.read()); 
      Serial.println(function);
      Serial.println(value);

      if(function == 'M'){
        switch(value){
        case 'F':
                    digitalWrite(3,HIGH); digitalWrite(5,HIGH);
                    digitalWrite(2, HIGH); digitalWrite(4, LOW); 
                    digitalWrite(7, HIGH);digitalWrite(8, LOW);  
                    break;

        case 'B':
                    digitalWrite(3,HIGH); digitalWrite(5,HIGH);
                    digitalWrite(2, LOW); digitalWrite(4, HIGH); 
                    digitalWrite(7, LOW);digitalWrite(8, HIGH);  
                    break;

        case 'L':
                    analogWrite(3,150); analogWrite(5,150);
                    digitalWrite(2, LOW); digitalWrite(4, HIGH); 
                    digitalWrite(7, HIGH);digitalWrite(8, LOW); 
                    break;

        case 'R':
                    analogWrite(3,150); analogWrite(5,150);                    
                    digitalWrite(2, HIGH); digitalWrite(4, LOW); 
                    digitalWrite(7, LOW);digitalWrite(8, HIGH);  
                    break;

        case 'S':
                    digitalWrite(3,LOW); digitalWrite(5,LOW);
                    digitalWrite(2, LOW); digitalWrite(4, LOW); 
                    digitalWrite(7, LOW);digitalWrite(8, LOW);  
                    break;

       default:
                   Serial.println("Motor Command Error...");
      }
        
      
      }else if(function == 'S'){
        Serial.println("servo");
        switch(value){
          
          case 'L':
                      if(servo_position1 < 155){
                          servo_func('L');
                      }
                      break;

          case 'R':
                      servo_func('R');
                      break;

          case 'U':
                      servo_func('U');
                      break;

          case 'D':
                      servo_func('D');
                      break;

          case 'S':
                      servo_func('S');
                      break;                      

          default:
                      Serial.println("Servo Command Error...");
        }
      }else{
        Serial.println("Command Error...");
      }
}

void servo_func(char a){
  switch(a){
    case'L':
        Serial.println("left");
        if(servo_position1 == 40){
          myservo1.attach(6);
          servo_position1 = 85;
          Serial.println(servo_position1);
          myservo1.write(servo_position1);
        }else if(servo_position1 == 85 || servo_position1 == 90){
          myservo1.attach(6);
          servo_position1 = 145;
          Serial.println(servo_position1);
          myservo1.write(servo_position1);
        }
        delay(1000);
        myservo1.detach();
        break;

    case'R':
        Serial.println("right");
        myservo1.attach(6);
        if(servo_position1 == 145){
          servo_position1 = 90;
          Serial.println(servo_position1);
          myservo1.write(servo_position1);
        }else if(servo_position1 == 90 || servo_position1 == 85){
          servo_position1 = 40;
          Serial.println(servo_position1);
          myservo1.write(servo_position1);
        }
        delay(1000);
        myservo1.detach();
        break;


    case'U':
        Serial.println("up");
        myservo2.attach(9);
        if(servo_position2 == 120){
          servo_position2 = 50;
          Serial.println(servo_position2);
          myservo2.write(servo_position2);
        }
        break; 

    case'D':
        Serial.println("down");
        myservo2.attach(9);
        if(servo_position2 == 50){
          servo_position2 = 120;
          Serial.println(servo_position2);
          myservo2.write(servo_position2);
        }
        break; 

    case'S':
        Serial.println("stop");
        break; 

    
  }
}

