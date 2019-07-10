
#include<Adafruit_GFX.h>
#include<MCUFRIEND_kbv.h>
#include<Fonts/FreeSansBold12pt7b.h>
#include <SoftwareSerial.h>

SoftwareSerial SIM900(50,52);

MCUFRIEND_kbv tft;

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin
#define LCD_CS A3   // Chip Select goes to Analog 3
#define LCD_CD A2  // Command/Data goes to Analog 2
#define LCD_WR A1  // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0


#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF





// Variable to store text message
String textMessage="";
String msg="";String a1="";String b1="";
String message="";
// Relay connected to pin 12
const int relay1 = 51;
const int relay2 =53;
String tim="";

void setup() {
  // Automatically turn on the shield
  digitalWrite(50, HIGH);
  delay(1000);
  digitalWrite(50, LOW);
  delay(5000);
  
  // Set relay as OUTPUT
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  // By default the relay is off
  digitalWrite(relay1, HIGH);
    digitalWrite(relay2, HIGH);
  // Initializing serial commmunication
  Serial.begin(9600); 
  SIM900.begin(9600);

  // Give time to your GSM shield log on to network
  delay(1000);
  SIM900.print("AT+GSMBUSY=1\r"); 
  delay(1000);
  // AT command to set SIM900 to SMS mode
 
  // Set module to send SMS data to serial out upon receipt
   SIM900.print("AT+CMGF=1\r"); 
  delay(100); 
  SIM900.print("AT+CNMI=2,2,0,0,0\r");
  delay(100);
   SIM900.print("AT+CMGD=1,1\r"); 
  delay(100);
  tft.reset();
 
  
  tft.begin(tft.readID()); 
  tft.setRotation(4);
  tft.fillScreen(BLACK);
  tft.fillRoundRect(20, 215, 100, 80, 10, WHITE);
  tft.fillRoundRect(20, 337, 100, 80, 10, WHITE);
  tft.setFont(&FreeSansBold12pt7b);
   tft.drawFastHLine(130,30,320,RED);
  tft.setCursor(5,30);
  tft.setTextColor(YELLOW);
  tft.setTextSize(1);
  tft.println("Technovia");
     tft.setCursor(7,200);
  tft.setTextColor(WHITE);
   tft.setTextSize(1);
   tft.println("DEVICE1");
    tft.setCursor(7,325);
  tft.setTextColor(WHITE);
   tft.setTextSize(1);
   tft.println("DEVICE2");
   
}

void loop(){
  
 

 while (SIM900.available()>0) {
    msg = SIM900.readString();
    if(msg.indexOf("iri")>=0) 
      textMessage=msg;  
    delay(10);
   }

  Serial.println("txt="+textMessage);
  
  
  if(textMessage.indexOf("ON1")>=0){
    // Turn on relay and save current state
    digitalWrite(relay1, LOW);
   
    tft.fillRoundRect(20, 215, 100, 80, 10, WHITE);
    tft.setCursor(30,270);
  tft.setTextColor(BLACK);
   tft.setTextSize(2);
   tft.println("ON");
   tft.fillRect(130, 222, 150, 80, BLACK);  
   tft.setCursor(140,240);
  tft.setTextColor(WHITE);
   tft.setTextSize(1);
   tft.println("Was OFF at");tft.setCursor(140,260);
  tft.setTextColor(WHITE);
   tft.setTextSize(1);
   tft.println(a1);sendSMS("Device1 is on");
     a1=tim;
 
  }else if(textMessage.indexOf("OFF1")>=0){
    // Turn on relay and save current state
    digitalWrite(relay1, HIGH);
    tft.fillRoundRect(20, 215, 100, 80, 10, WHITE);
    tft.setCursor(22,270);
  tft.setTextColor(BLACK);
   tft.setTextSize(2);
   tft.println("OFF");  
   tft.fillRect(140, 222, 150, 80, BLACK);  
   tft.setCursor(140,240);
  tft.setTextColor(WHITE);
   tft.setTextSize(1);
   tft.println("Was ON at");
   tft.setCursor(140,260);
  tft.setTextColor(WHITE);
   tft.setTextSize(1);
   tft.println(a1);
  sendSMS("Device1 is off");
   a1=tim;
  }
  else if(textMessage.indexOf("ON2")>=0){
    // Turn on relay and save current state
    digitalWrite(relay2, LOW);
   
    
  tft.fillRoundRect(20, 337, 100, 80, 10, WHITE);
    tft.setCursor(30,390);
  tft.setTextColor(BLACK);
   tft.setTextSize(2);
   tft.println("ON");  
    
  tft.fillRect(140, 343, 150, 80, BLACK);  
   tft.setCursor(140,360);
  tft.setTextColor(WHITE);
   tft.setTextSize(1);
   tft.println("Was OFF at");
   tft.setCursor(140,380);
  tft.setTextColor(WHITE);
   tft.setTextSize(1);
   tft.println(b1);
   sendSMS("Device2 is on");
   b1=tim;
  }
  else if(textMessage.indexOf("OFF2")>=0){
    // Turn on relay and save current state
    digitalWrite(relay2, HIGH);
  tft.fillRoundRect(20, 337, 100, 80, 10, WHITE); 
    tft.setCursor(22,390);
  tft.setTextColor(BLACK);
   tft.setTextSize(2);
   tft.println("OFF"); 
   tft.fillRect(140, 343, 150, 80, BLACK);  
   tft.setCursor(140,360);
  tft.setTextColor(WHITE);
   tft.setTextSize(1);
   tft.println("Was ON at");
   tft.setCursor(140,380);
  tft.setTextColor(WHITE);
   tft.setTextSize(1);
   tft.println(b1);
   sendSMS("Device2 is off");
   b1=tim;
  }
  
 
  
  textMessage = "";
dateTime();
}  

// Function that sends SMS
void sendSMS(String message){
  // AT command to set SIM900 to SMS mode
 

  // REPLACE THE X's WITH THE RECIPIENT'S MOBILE NUMBER
  // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS
  SIM900.println("AT + CMGS = \"+918825272821\""); 
  delay(1000);
  // Send the SMS
  SIM900.println(message); 
  delay(1000);

  // End AT command with a ^Z, ASCII code 26
  SIM900.println((char)26); 
  delay(1000);
  SIM900.println();
  // Give module time to send SMS
  delay(1000);  
}
void dateTime(){
  String mystr="";
  int i = 0;
  SIM900.println("AT+CCLK?");
  delay (1000);
  while (SIM900.available()>0) {
    mystr += char(SIM900.read());
  }

Serial.println(SIM900.read());
  int x = mystr.indexOf(String('"'));// Find the first occurance of an open quotation.  This is where we begin to read from
  int y = mystr.lastIndexOf(String(',')); // Find the last occurance of an open quotation. This is where we end.
  int z = mystr.lastIndexOf(String(':'));   tft.setCursor(240,60);
tim=mystr.substring(y+1,z);
  tft.setTextColor(BLACK);
   tft.setTextSize(1);
   tft.fillRect(230, 40,80, 22, WHITE);
   tft.print(mystr.substring(y+1,z));Serial.println("TIME= "+mystr.substring(y+1,z));
   tft.setCursor(200,100);
  tft.setTextColor(BLACK);
   tft.setTextSize(1); tft.fillRect(200,80,95, 22, WHITE);
   tft.print(mystr.substring(x+1,y));Serial.println("DATE= "+mystr.substring(x+1,y));
   delay(2000);
   }
