#include <SwitecX12.h>

const int STEPS = 315 * 12;
const int A_STEP = 21;
const int A_DIR = 20;
const int A_RESET = 19;

SwitecX12 motor1(STEPS, A_STEP, A_DIR, A_RESET);


void setup() {
//  digitalWrite(RESET, HIGH);
//  Serial.begin(9600);
  motor1.zero();
  motor1.setPosition(STEPS/2);
}

void loop() {
  static bool forward = true;
  static int position1 = STEPS * 3/4;
  static int position2 = STEPS * 1/4;
  if (motor1.stopped) {
    motor1.setPosition(forward ? position1 : position2);
    forward = !forward;
  }
  motor1.update();
}
