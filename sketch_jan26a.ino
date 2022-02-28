#include <SoftwareSerial.h>


int state = 0;
int flag = 0;
String message;
unsigned long timeMS = 0;

SoftwareSerial bt05(10,11);

void setup() {
  Serial.begin(9600);
  bt05.begin(9600);
}

int loopNumber = 0;
#define MAX_LOOP 10
char lastRateChange = '-';
void loop() {
  if(bt05.available()) {
    String recv = bt05.readString();
    Serial.println("Recv from device: " + recv);
    
  }

  if(loopNumber++ == MAX_LOOP) {
    loopNumber = 0;
    lastRateChange = (lastRateChange == '+') ? '-' : '+';
    String outMessage = String(lastRateChange) + String("1000");
    Serial.println(outMessage);
    bt05.println(outMessage);
  } else {
     String outMessage = String("{\"battery\":{\"percent\":30},\"heart\":{\"rate\":120}, \"time\":") + String(timeMS += 1000) + String("}");
     Serial.println(outMessage);
     bt05.println(String(timeMS));
  }

  delay(1000);
}
