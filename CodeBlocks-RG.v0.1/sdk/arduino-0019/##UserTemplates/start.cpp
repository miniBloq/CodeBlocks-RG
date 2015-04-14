/*





 */

extern "C" void __cxa_pure_virtual(void); //for C++ defines

void __cxa_pure_virtual(void) {};
#include <WProgram.h>

void setup()
{

   Serial.begin(9600);
   Serial.println("Hello from Arduino Code::Blocks template");

}


void loop()
{


}
