#include <SoftwareSerial.h> 
#define RFID_READ 0x01
#define txPin 6 // transmition pin (kan ændres) - SIN på RFID
#define rxPin 8 // Receive pin (kan ændres) - SOUT på RIFD
#include <Servo.h> // servo lel... 
Servo servoMain; // lav et servo objekt
SoftwareSerial mySerial(rxPin, txPin);
int val; // val=mySerial.read(); 
int prevval; // bruges til ikke at læse 2x

void setup()
{
  Serial.begin(9600);
  Serial.write(1);
//  Serial.println("RFID Read/Write Test");
  mySerial.begin(9600);
  pinMode(txPin, OUTPUT);    
  pinMode(rxPin, INPUT);
  servoMain.attach(9);  // tilknytter DIGITAL 9 til SERVO motoren
  
}

void suppressAll()                                // Forhindre NULL resultat i at blive printet.
{
    if(mySerial.available() > 0)
    { mySerial.read();
      suppressAll();
    }
}

void servo_left()
{
  // servoMain.write(90);  
  // delay(2000);          
   servoMain.write(170);
   delay(2000);         
   servoMain.write(90); 
   delay(1000);    
}

void servo_right()
{
 //  servoMain.write(90);
   //delay(2000);     
   servoMain.write(18); 
   delay(2000);      
   servoMain.write(90);  
   delay(1000);  
}


void loop()
{
  int val;
  mySerial.print("!RW");
  mySerial.write(byte(RFID_READ));
  mySerial.write(byte(32));
  

  if(mySerial.available() > 0)
  {      
    val = mySerial.read();                        //The mySerial.read() procedure is called, but the result is not printed because I don't want the "error message: 1" cluttering up the serial monitor
      if (val != 1)                                   //If the error code is anything other than 1, then the RFID tag was not read correctly and any data collected is meaningless. In this case since we don't care about the resultant values they can be suppressed
       {suppressAll();}                              
  }      
 

if(mySerial.available() > 0) { 
  
    val = mySerial.read();
    val = mySerial.read();
    val = mySerial.read();
    val = mySerial.read(); // vi læser 2 bytes * 4
    
    
    // Hvis koden ikke virker, kan dette benyttes. lav til loop.
    while ( val == prevval )
    {
     val = 0;
     val = mySerial.read();
     val = mySerial.read();
     val = mySerial.read();
     val = mySerial.read(); // vi læser 2 bytes * 4
    }
    
    if (val == 0X96){
        //   Serial.print("1");
           Serial.println(1);
           servo_right();
           delay(2000);
          
    }
    else if (val == 0X12){
         //  Serial.print("2");
           Serial.println(2);
           servo_left();
           delay(2000);
    }
    else {
        Serial.println("kunne ikke genkende.");
        delay(1000);
    }
    prevval=val;
    val = 0;
    
  }  
delay(750);
}
