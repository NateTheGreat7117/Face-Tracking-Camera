#include <IRremote.hpp>
#include <Servo.h>

Servo servo1;
Servo servo2;

int servo1_pos = 40;
int servo2_pos = 70;

void setup() {
  Serial.begin(9600);
  servo1.attach(6); // Bottom
  servo2.attach(7); // Top
  servo1.write(0);
  servo2.write(0);
  servo1.write(servo1_pos);
  servo2.write(servo2_pos);

  IrReceiver.begin(2, ENABLE_LED_FEEDBACK);
  printActiveIRProtocols(&Serial);
}

void loop() {
  if (IrReceiver.decode())
  {
    IrReceiver.printIRResultShort(&Serial);
    IrReceiver.printIRSendUsage(&Serial);
    if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
        Serial.println(F("Received noise or an unknown (or not yet enabled) protocol"));
        // We have an unknown protocol here, print more info
        IrReceiver.printIRResultRawFormatted(&Serial, true);
    }
    Serial.println();
    IrReceiver.resume();

    if (IrReceiver.decodedIRData.command == 0x9) {
        // Rotate right along z axis
        if (servo1_pos > 20)
        {
          servo1_pos -= 5;
        }
        servo1.write(servo1_pos);
        Serial.print(servo1_pos);
        delay(200);
    } else if (IrReceiver.decodedIRData.command == 0x15) {
        // Rotate left along z axis
        if (servo1_pos < 140)
        {
          servo1_pos += 5;
        }
        servo1.write(servo1_pos);
        Serial.print(servo1_pos);
        delay(200);
    } else if (IrReceiver.decodedIRData.command == 0x40) {
      // Rotate down
        if (servo2_pos > 20)
        {
          servo2_pos -= 5;
        }
        servo2.write(servo2_pos);
        Serial.print(servo2_pos);
        delay(200);
    } else if (IrReceiver.decodedIRData.command == 0x43)
    {
      // Rotate up
        if (servo2_pos < 140)
        {
          servo2_pos += 5;
        }
        servo2.write(servo2_pos);
        Serial.print(servo2_pos);
        delay(200);
    }
  }
}
