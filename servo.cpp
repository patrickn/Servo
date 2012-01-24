// 
// 

#include <WProgram.h>
#include <Servo.h>

#ifdef __cplusplus
extern "C" {
   #include "uart.h"
}
#endif


void toggleState(void);

Servo pan;
Servo tilt;
volatile int state = LOW;


// Program entry point
int main(void)
{
	init();
	setup();

   int analogValue = 0;
   int outputValue = 0;
   int analogIn = 0;
    
   for (;;)
	{
      analogValue = analogRead(analogIn);
   
      if (!state) {
         outputValue = map(analogValue, 0, 1023, 1, 180);
         printf("Pan: %d\n", outputValue);
         pan.write(outputValue);
      } else {
         outputValue = map(analogValue, 0, 1023, 1, 130);
         printf("Tilt: %d\n", outputValue);
         tilt.write(outputValue);
      }
      delay(15); // time for the servo to reach position
   }

	return 0;
}

void setup()
{
   attachInterrupt(0, toggleState, RISING);

   uart_init();
   stdout = &uart_output;
   stdin  = &uart_input;

   pan.attach(9);  // attaches the pan servo to pin 9 to the servo object
   tilt.attach(8);  // attaches the tilt servo to pin 9 to the servo object
}

void toggleState(void)
{
   state = !state;
}

void loop()
{
}
