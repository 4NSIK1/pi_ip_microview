#include <MicroView.h>

String incoming = "";  // the message sent from the computer over to the microview
const byte numChars = 60;
char receivedChars[numChars];
char tempChars[numChars];
char parsed_string[numChars]; 
boolean newData = false;

void setup() // this only runs once
{
  Serial.begin(9600); // open the serial port on the arduino
  uView.begin();    // start the screen on the Microview
  uView.clear(PAGE);  // clear the screen in case anything was being displayed
  uView.setFontType(0);
  uView.print("Pi IP");
  uView.display();  
  Serial.println("READY!"); // tell user when the device is ready to recieve data, this will only show up if the serial port
  // is expecting a packet, as in the arduino IDE or codebender
}

void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;
 
    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}
void loop() {
  int j=0;
  parsed_string[0]='\0';
  delay(1000);
  recvWithStartEndMarkers();
  if (newData == true) {
    strcpy(tempChars, receivedChars);
    uView.clear(PAGE);  // clear the screen in case anything was being displayed
    uView.setCursor(0,0);
    for (byte i=0; i < 60; i++) {   // data comes in the format of a string of the interfaces with start and end delimiters <lo=127.0.0.0,eth0=192.168.0.17,wlan0=123.456.789.321>
      if (tempChars[i] == ',') { //splits on comma
        
        if (i>0){
          parsed_string[j]='\0';
          Serial.println(parsed_string);
          uView.print(parsed_string);
          uView.print('\n');
          j=0;      
        }
       }
      else{
         parsed_string[j]=tempChars[i];
         j++;    
      }
    }
  Serial.println(parsed_string);
  uView.print(parsed_string); 
  uView.display(); 
  newData=false;
  }
}
