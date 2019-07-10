#include<Adafruit_GFX.h>
#include<MCUFRIEND_kbv.h>
#include<Fonts/FreeSansBold12pt7b.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(50,52);

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


void setup() {
  // put your setup code here, to run once:
  mySerial.begin(9600);
  Serial.begin(9600);
  tft.reset();
 
  
  tft.begin(tft.readID()); 
  tft.setRotation(4);
  tft.fillScreen(BLACK);
  tft.fillRoundRect(20, 215, 100, 80, 10, WHITE);
  tft.fillRoundRect(20, 337, 100, 80, 10, WHITE);
  tft.setFont(&FreeSansBold12pt7b);
}

void loop() {
   
  timeDate();

  
  tft.drawFastHLine(130,30,320,RED);
  tft.setCursor(5,30);
  tft.setTextColor(YELLOW);
  tft.setTextSize(1);
  tft.println("Technovia");
  tft.setCursor(240,60);
  tft.setTextColor(GREEN);
   tft.setTextSize(1);
   tft.fillRect(230, 40,80, 22, BLACK);
   tft.println(tim);delay(10000);
  tft.setCursor(165,90);
  tft.setTextColor(CYAN);
   tft.setTextSize(1);
   tft.println(dat);
  
  
   tft.setCursor(7,200);
  tft.setTextColor(WHITE);
   tft.setTextSize(1);
   tft.println("DEVICE1");
   tft.setCursor(30,270);
  tft.setTextColor(BLACK);
   tft.setTextSize(2);
   tft.println("ON");
   tft.setCursor(165,250);
  tft.setTextColor(WHITE);
   tft.setTextSize(1);
   tft.println("Sarthak has");
   tft.setCursor(165,270);
  tft.setTextColor(WHITE);
   tft.setTextSize(1);
   tft.print("turned ON");
   
   tft.setCursor(7,325);
  tft.setTextColor(WHITE);
   tft.setTextSize(1);
   tft.println("DEVICE2");
   tft.setCursor(30,390);
  tft.setTextColor(BLACK);
   tft.setTextSize(2);
   tft.println("ON");
   tft.setCursor(165,360);
  tft.setTextColor(WHITE);
   tft.setTextSize(1);
   tft.println("Ambi has");
   tft.setCursor(165,380);
  tft.setTextColor(WHITE);
   tft.setTextSize(1);
   tft.print("turned ON");
  
  
}
void timeDate(){
  String mystr="";
  int i = 0;
  mySerial.println("AT+CCLK?");
  delay (500);
  while (mySerial.available()>0) {
    mystr += char(mySerial.read());
  }


  int x = mystr.indexOf(String('"'));   // Find the first occurance of an open quotation.  This is where we begin to read from
  int y = mystr.lastIndexOf(String(','));
  int z = mystr.lastIndexOf(String(':'));// Find the last occurance of an open quotation. This is where we end.
  String dat= mystr.substring(x+1,y);   // This is the time string yy/mm/dd,hh:mm:ss-tz (tz in qtrs)
  String tim= mystr.substring(y+1,z);
}
}
