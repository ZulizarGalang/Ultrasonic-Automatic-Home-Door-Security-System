#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>
Servo myservo;
int pos=0; // LCD Connections
LiquidCrystal lcd(A0,A1,A2,A3,A4,A5);


const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};



byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2};//connect to the column pinouts of the keypad
int LCDRow = 0;


Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

char* password="2001";
int currentposition=0;
int trigPin = 12;
int echoPin = 11;
int buzz=10;
int invalidcount=12;


void setup()
{
 
displayscreen();
Serial.begin(9600); 
pinMode(trigPin,OUTPUT);
pinMode(echoPin,INPUT);
pinMode(10,INPUT);
pinMode(buzz, OUTPUT);
myservo.attach(13); //SERVO ATTACHED//
 
lcd.begin(16,2);
 
}
 
void loop()
{
if( currentposition==0)
{
displayscreen();
 
}
int l ;
char code=keypad.getKey();
if(code!=NO_KEY)
{
lcd.clear();
lcd.setCursor(0,0);
lcd.print("PASSWORD:");
lcd.setCursor(7,1);
lcd.print(" ");
lcd.setCursor(7,1);
for(l=0;l<=currentposition;++l)
{
 
lcd.print("*");
keypress();
}
 
if (code==password[currentposition])
{
++currentposition;
if(currentposition==4)
{
 
unlockdoor();
currentposition=0;
 
}
 
}
 
else
{
++invalidcount;
incorrect();
currentposition=0;
 
}
if(invalidcount==5)
{
 
++invalidcount;
torture1();
 
}
if(invalidcount==8)
{
torture2();
}
 
}
// LOOP ENDS!!!//
}
 
//********OPEN THE DOOR FUNCTION!!!!***********//
 
void unlockdoor()
{
delay(900);
 
lcd.setCursor(0,0);
lcd.println(" ");
lcd.setCursor(1,0);
lcd.print("Akses Diterima");
lcd.setCursor(0,1);
lcd.println("Selamat Datang!!");
lcd.println(" ");
unlockbuzz();
 myservo.write(0);
delay(5); // waits 15ms for the servo to reach the position

delay(2000);
 
 
 
delay(1000);
counterbeep();
delay(1000);

  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  int duration = pulseIn(echoPin,HIGH);
  int distance = duration / 58;
  
   if(distance < 100)
  {
     lcd.clear();
    lcd.setCursor(3,0);
lcd.print("TERDETEKSI");
     digitalWrite(buzz, HIGH);
	 tone(11, 440, 50);
     delay (1000);
     digitalWrite(buzz, HIGH);
	 tone(11, 440, 50);
     myservo.write(0);
     delay(10000);
     digitalWrite(buzz, HIGH);
	 tone(11, 220, 100);
     lcd.setCursor(1,0);
	 lcd.println("Terkunci dalam:");
	 lcd.setCursor(4,1); //3
	 lcd.print("3");
	 delay(100);
	 lcd.clear();
	 lcd.setCursor(1,0);
	 lcd.println("Terkunci dalam:");
	 digitalWrite(buzz,LOW);
	 delay(1000);
	 digitalWrite(buzz, HIGH);
	 tone(11, 220, 100);
     lcd.setCursor(1,0);
	 lcd.println("Terkunci dalam:");
	 lcd.setCursor(4,1); //4
	 lcd.print("2");
	 delay(100);
	 lcd.clear();
	 lcd.setCursor(1,0);
	 lcd.println("Terkunci dalam:");
	 digitalWrite(buzz,LOW);
	 delay(1000);
	 digitalWrite(buzz, HIGH);
	 tone(11, 220, 100);
     lcd.setCursor(4,1);
	 lcd.print("1");
	 delay(100);
	 lcd.clear();
	 lcd.setCursor(1,0);
	 lcd.println("Terkunci dalam:");
	 digitalWrite(buzz,LOW);
	 delay(1000); 
   }
  else if(distance > 100 )
  {
   lcd.clear();
    lcd.setCursor(1,0);
	lcd.print("TDK TERDETEKSI");
    digitalWrite(buzz, HIGH);
	 tone(11, 440, 100);
    myservo.write(90);
    delay(5000);
  }
  
  else if(distance < 100 && distance > 0){
   lcd.clear();
   lcd.setCursor(3,0);
	lcd.print("TERDETEKSI"); 
    digitalWrite(buzz, HIGH);
	 tone(11, 440, 50);
     delay (500);
     digitalWrite(buzz, HIGH);
	 tone(11, 440, 50);
	myservo.write(0);
	delay(10000);
	digitalWrite(buzz, HIGH);
	tone(11, 220, 100);
	lcd.setCursor(1,0);
	lcd.println("Terkunci dalam:");
	lcd.setCursor(4,1); //3
	lcd.print("3");
	delay(100);
	lcd.clear();
	lcd.setCursor(1,0);
	lcd.println("Terkunci dalam:");
	digitalWrite(buzz,LOW);
	delay(1000);
	digitalWrite(buzz, HIGH);
	tone(11, 220, 100);
    lcd.setCursor(1,0);
	lcd.println("Terkunci dalam:");
	lcd.setCursor(4,1); //4
	lcd.print("2");
	delay(100);
	lcd.clear();
	lcd.setCursor(1,0);
	lcd.println("Terkunci dalam:");
	digitalWrite(buzz,LOW);
	delay(1000);
	digitalWrite(buzz, HIGH);
	tone(11, 220, 100);
    lcd.setCursor(4,1);
	lcd.print("1");
	delay(100);
	lcd.clear();
	lcd.setCursor(1,0);
	lcd.println("Terkunci dalam:");
	digitalWrite(buzz,LOW);
	delay(1000);
  	}
digitalWrite(buzz, HIGH);
	tone(11, 550, 100);  	 
myservo.write(90);
currentposition=0; 
lcd.clear();
displayscreen();
}

 
//************WRONG CODE FUNCTION********//
void incorrect()
{
          
delay(500);
lcd.clear();
lcd.setCursor(1,0);
lcd.print("KODE");
lcd.setCursor(6,0);
lcd.print("SALAH");
lcd.setCursor(15,1);
lcd.println(" ");
lcd.setCursor(3,1);
lcd.println("*COBA LAGI*");
 delay(3000);
lcd.clear();
displayscreen();

}    

     
//************** CLEAR THE SCREEN!!!*************//
void clearscreen()
{
lcd.setCursor(0,0);
lcd.println(" ");
lcd.setCursor(0,1);
lcd.println(" ");
lcd.setCursor(0,2);
lcd.println(" ");
lcd.setCursor(0,3);
lcd.println(" ");
}
//**************KEYPRESS********************//
void keypress()
{
 
 
 
digitalWrite(buzz, HIGH);
  tone(11, 330, 30);

digitalWrite(buzz, LOW);
}
//********DISPLAY FUNCTION!!!*************//
void displayscreen()
{
 
lcd.setCursor(0,0);
  lcd.println("(MASUKKAN KODE)");
lcd.setCursor(0 ,1);
 
lcd.println("*SILAHKAN KETIK*");
}

//**********UNLOCK BUZZ*************//
void unlockbuzz()
{
 
digitalWrite(buzz, HIGH);
 tone(11, 220, 100); 
delay(80);
digitalWrite(buzz, LOW);
delay(80);
digitalWrite(buzz, HIGH);
tone(11, 220, 100);
 delay(80);
digitalWrite(buzz, LOW);
delay(200);
digitalWrite(buzz, HIGH);
tone(11, 220, 100);
  delay(80);
digitalWrite(buzz, LOW);
delay(80);
digitalWrite(buzz, HIGH);
tone(11, 220, 100);
  delay(80);
digitalWrite(buzz, LOW);
delay(80);
}
 
//**********COUNTER BEEP**********//
//**********COUNTER BEEP**********//
void counterbeep()
{
delay(1200);
 
 
lcd.clear();
digitalWrite(buzz, HIGH);
tone(11, 220, 100);
lcd.setCursor(2,15);
lcd.println(" ");
lcd.setCursor(2,14);
lcd.println(" ");
lcd.setCursor(2,0);
delay(200);
lcd.println("Checking:::");
 
lcd.setCursor(4,1);
lcd.print("5");
delay(200);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("Checking:");
digitalWrite(buzz,LOW);
delay(1000);
//2
digitalWrite(buzz, HIGH);
tone(11, 220, 100);
  lcd.setCursor(2,0);
lcd.println("Checking:");
lcd.setCursor(4,1); //2
lcd.print("4");
delay(100);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("Checking:");
digitalWrite(buzz,LOW);
delay(1000);
//3
digitalWrite(buzz, HIGH);
tone(11, 220, 100);
  lcd.setCursor(2,0);
lcd.println("Checking:");
lcd.setCursor(4,1); //3
lcd.print("3");
delay(100);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("Checking:");
digitalWrite(buzz,LOW);
delay(1000);
//4
digitalWrite(buzz, HIGH);
tone(11, 220, 100);
  lcd.setCursor(2,0);
lcd.println("Checking:");
lcd.setCursor(4,1); //4
lcd.print("2");
delay(100);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("Checking:");
digitalWrite(buzz,LOW);
delay(1000);
//
digitalWrite(buzz, HIGH);
tone(11, 220, 100);
  lcd.setCursor(4,1);
lcd.print("1");
delay(100);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("Checking::");
digitalWrite(buzz,LOW);
delay(1000);
//5
digitalWrite(buzz, HIGH);
tone(11, 220, 100);
  delay(40);
digitalWrite(buzz,LOW);
delay(40);
digitalWrite(buzz, HIGH);
tone(11, 220, 100);
  delay(40);
digitalWrite(buzz,LOW);
delay(40);
digitalWrite(buzz, HIGH);
tone(11, 220, 100);
  delay(40);
digitalWrite(buzz,LOW);
delay(40);
digitalWrite(buzz, HIGH);
tone(11, 220, 100);
  delay(40);
digitalWrite(buzz,LOW);
lcd.clear();
lcd.setCursor(2,0);
lcd.print("RE-CHECK");
delay(500);
lcd.setCursor(12,0);
lcd.print(".");
delay(500);
lcd.setCursor(13,0);
lcd.print(".");
delay(500);
lcd.setCursor(14,0);
lcd.print(".");
delay(400);
lcd.clear();
lcd.setCursor(4,0);
lcd.print("Result!");
delay(440);
}
//*********TORTURE1***********//
void torture1()
{
delay(1000);
lcd.clear();
lcd.setCursor(2,0);
lcd.print("WAIT FOR ");
lcd.setCursor(5,1);
lcd.print("15 SECONDS");
digitalWrite(buzz, HIGH);
tone(11, 220, 100);
  delay(15000);
digitalWrite(buzz, LOW);
lcd.clear();
lcd.setCursor(2,0);
lcd.print("LOL..");
lcd.setCursor(1,1);
lcd.print(" HOW WAS THAT??");
delay(3500);
lcd.clear();
 
}
//*****TORTURE2*****//
void torture2()
{
delay(1000);
lcd.setCursor(1,0);
lcd.print(" ");
lcd.setCursor(2,0);
lcd.print("EAR DRUMS ARE");
lcd.setCursor(0,1);
lcd.print(" PRECIOUS!! ");
delay(1500);
lcd.clear();
lcd.setCursor(1,0);
lcd.print(" WAIT FOR");
lcd.setCursor(4,1);
lcd.print(" 1 MINUTE");
digitalWrite(buzz, HIGH);
tone(11, 220, 100);
  delay(55000);
counterbeep();
lcd.clear();
digitalWrite(buzz, LOW);
lcd.setCursor(2,0);
lcd.print("WANT ME TO");
lcd.setCursor(1,1);
lcd.print("REDICULE MORE??");
delay(2500);
lcd.clear();
lcd.setCursor(2,0);
lcd.print("Ha Ha Ha Ha");
delay(1700);
lcd.clear();
}
  
