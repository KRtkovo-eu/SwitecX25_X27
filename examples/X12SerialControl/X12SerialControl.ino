//----------------------------------------------------------------------
// https://github.com/clearwater/SwitecX25
// 
// This is an example of using the SwitchX12 library.
// It zero's the motor, sets the position to mid-range
// and waits for serial input to indicate new motor positions.
// 
// Open the serial monitor and try entering values 
// between 0 and 3779.
// 
// Note that the maximum speed of the motor will be determined
// by how frequently you call update().  If you put a big slow
// serial.println() call in the loop below, the motor will move
// very slowly!
//----------------------------------------------------------------------

#include <SwitecX12.h>

#define pinStep   21
#define pinDir    20
#define pinReset  19

// standard X25.168 range 315 degrees at 1/12 degree steps
#define STEPS (315*12)

// 5 letters, a-e
#define LETTERS 9

//    SwitecX12(unsigned int steps, unsigned char pinStep, unsigned char pinDir);
//SwitecX12 motor1(STEPS,21, 20, 19);
SwitecX12 motor1(STEPS, pinStep, pinDir, pinReset);

void setup(void)
{   
  // run the motor against the stops
  motor1.zero();
  delay(200);
  motor1.full();

  // start moving towards the center of the range
  motor1.setPosition(STEPS/2);
  
  Serial.begin(115200);
  // Wait for serial monitor
  while (!Serial) ;
  Serial.print("Enter a step position from 0 through ");
  Serial.print(STEPS-1);
  Serial.println(".");
  
  Serial.println("Or use letters:");
  for (int i=0; i < LETTERS; i++) {
      Serial.write('a'+i);
      Serial.print(": ");
      Serial.println(i * STEPS / (LETTERS-1));    
  }  
}

void loop(void)
{
  static int nextPos = 0;
  // the motor only moves when you call update
  motor1.update();
  
  if (Serial.available()) {
    char c = Serial.read();
    if (c==10 || c==13) {
      motor1.setPosition(nextPos);
      Serial.print("Moving to: ");
      Serial.println(nextPos);
      nextPos = 0;
    } else if (c>='0' && c<='9') {
      nextPos = 10*nextPos + (c-'0');
    } else if (c>='a' && c < ('a'+LETTERS) ) {
      nextPos = (c-'a') * STEPS / (LETTERS-1);
    } else if (c==']' ) {
      motor1.debug = true;
    } else if (c=='[' ) {
      motor1.debug = false;
    } else if (c=='z' ) {
      motor1.zero();
  delay(200);
      motor1.full();
    }
  }
}
