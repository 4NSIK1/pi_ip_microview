#include <MicroView.h>
String incoming = "";  // the message sent from the computer over to the microview
void setup() // this only runs once
{
  Serial.begin(9600); // open the serial port on the arduino
  uView.begin();    // start the screen on the Microview
  uView.clear(PAGE);  // clear the screen in case anything was being displayed
  uView.print("PiSound IP");
  uView.print("IP Address");
  uView.display();  
}

void readSerial() // this is where the input from the serial port is initially processed
{
  if (Serial.available())
  {
    delay(100);
    while(Serial.available() > 0)
    {
      incoming = Serial.readString();
      Serial.println(incoming);
    }
  }
}

void loop()
{
  delay(1000);
  readSerial();
  uView.clear(PAGE);  // clear the screen in case anything was being displayed
  uView.setCursor(0,0);
  uView.print("PiSound IP");
  uView.print(incoming);   // display string
  uView.display(); 
}
