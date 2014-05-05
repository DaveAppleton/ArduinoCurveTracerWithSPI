#include <SPI.h>
#include <MCP4131.h>
float r1 = 100104.0;
float r2 = 984.0;

//setup an intance of MCP4131
MCP4131 MCP4131(10); // with a CS pin of 10

void setup() {
  Serial.begin(9600);
  MCP4131.setTap(MCP4131_MIN); //Sets the pot to 0.
  
  if (MCP4131.initTCON())  //init the pot, connect wiper0, and turn ON pot
  {
    Serial.println("Init Error!");
  }
  
}

int tapValue = 1;
 
void loop() {
  if (MCP4131.setTap(tapValue))
  {
    Serial.println("setTap Error!");
  }
  else
  {
    tapValue++;    
    if (tapValue > 128)
    {
      while (Serial.available()) {
        char c = Serial.read();
        if (c == 'G') {
          tapValue = 0;
          return;
        }
      }
      tapValue = 129;
      return;
    }
  }
  delay(20);
  float bvc  = analogRead(A0);
  float bvb = analogRead(A2);
  float bvs = analogRead(A3);
  
  float vc = 5.0*bvc/1024.0;
  float vb = 5.0*bvb/1024.0;
  float vs = 5.0*bvs/1024.0;
  //Serial.println("============");

  Serial.print(vc);
  Serial.print(",");
  Serial.print(vb);
  Serial.print(",");
  Serial.print(vs);
  Serial.print(",");
  Serial.println(tapValue);
  delay(100);
}
