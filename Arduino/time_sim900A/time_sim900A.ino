#include <SoftwareSerial.h>

SoftwareSerial mySerial(50,52);

void setup()
{
  mySerial.begin(9600);               // the GPRS baud rate   
  Serial.begin(9600);   
   mySerial.println("AT+CCLK?");// the GPRS baud rate   
}

void loop()
{
/* if (mySerial.available())     Serial.write(mySerial.read());
if (Serial.available())       mySerial.write(Serial.read());  
*/
  String mystr="";
  int i = 0;
  mySerial.println("AT+CCLK?");
  delay (2000);
  while (mySerial.available()>0) {
    mystr += char(mySerial.read());
  }

Serial.println(mySerial.read());
  int x = mystr.indexOf(String('"'))+1;   // Find the first occurance of an open quotation.  This is where we begin to read from
  int y = mystr.lastIndexOf(String('+')); // Find the last occurance of an open quotation. This is where we end.
  Serial.println(mystr.substring(x,y));   // This is the time string yy/mm/dd,hh:mm:ss-tz (tz in qtrs)

 
  
}
