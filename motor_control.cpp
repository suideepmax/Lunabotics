void sendMotorCommand(uint8_t address, uint8_t command, uint8_t data) {
  uint8_t checksum = (address + command + data) & 0x7F;
  Serial1.write(address);
  Serial1.write(command);
  Serial1.write(data);
  Serial1.write(checksum);
}

void setMotors(int speed1, int speed2) {
  // Motor 1
  if (speed1 > 0) {
    sendMotorCommand(128, 0, speed1);
  } else if (speed1 < 0) {
    sendMotorCommand(128, 1, -speed1);
  } else {
    sendMotorCommand(128, 0, 0);
  }

  // Motor 2
  if (speed2 > 0) {
    sendMotorCommand(128, 4, speed2);
  } else if (speed2 < 0) {
    sendMotorCommand(128, 5, -speed2);
  } else {
    sendMotorCommand(128, 4, 0);
  }
}

void runFor(int speed1, int speed2, int duration_ms) {
  unsigned long start = millis();
  while (millis() - start < duration_ms) {
    setMotors(speed1, speed2);
    delay(10);
  }
}

void setup() {
  Serial1.begin(9600);
  delay(2000);
  setMotors(0, 0);
}

void loop() {
  runFor(64, 64, 5000);   // both forward 50% - 5s
  runFor(0, 0, 3000);     // both stop - 3s
}
