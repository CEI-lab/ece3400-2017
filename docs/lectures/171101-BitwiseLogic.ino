
//uint8_t *heapptr, *stackptr; // global variable
//#include <FFT.h> // include the library

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {

  /*Type declaration, to port between operating systems*/
  /*0b means binary, print a binary number with BIN*/
  uint8_t var_o = 0b11000000;
  uint8_t var_t = 0b01111110;
  Serial.print(var_o,BIN);

  /*Bitwise operators*/
  /*Negated*/
  var_o = ~var_o;   
  Serial.print(" negated");
  /*And*/
  /*Short hand operator*/
  //var_o &= var_t;
  //Serial.print(" & "); Serial.print(var_t,BIN); 
  /*OR*/
  //var_o |= var_t;
  //Serial.print(" | "); Serial.print(var_t,BIN); 
  /*XOR*/
  //var_o ^= var_t;
  //Serial.print(" ^ "); Serial.print(var_t,BIN); 
  /*Bit shift*/
  //var_o = var_o>>2;
  //Serial.print(">>2");
  /*Bit shift signed*/
  //int8_t var_f = 0b11000000;
  //var_o=var_f>>2;
  //Serial.print(">>2");
  /*Setting bits*/
  //var_o |= (1<<3);
  //Serial.print(", Set bit 3");
  /*Toggling bits*/
  //var_o ^= (1<<6);   
  //Serial.print(" ^ (1<<6)");
  Serial.print(": "); Serial.println(var_o,BIN);

  /*Program storage, 1,728 bytes (5%)
    Dynamic memory, 200 bytes 
    Declared 3 integers...
    And some text!
    Add F() around text. Explain how this is stored in Flash, not RAM*/

  /*What about libraries?...
    Comment out Serial and save 186 bytes*/

  /*Can we track how much memory we use during run time?*/

  /*
  //Debugging
  check_mem(); 
  Serial.write("heapptr: "); Serial.print((int)heapptr);
  Serial.write(", stackptr: "); Serial.println((int)stackptr);
  //SP should always be larger than HP 
  */
  
  /*But this is weird, our program says that we use 234 bytes, but our heap pointer 
    is already at 492! Why??
    Check data sheet: http://www.atmel.com/Images/Atmel-42735-8-bit-AVR-Microcontroller-ATmega328-328P_Datasheet.pdf 
    page 35. Use scientific calculator to confirm the number: 490. */

  /*Should this be cause for concern?
   * #include <FFT.h>
   * Maybe try to change the standard buffer size in here!
   */
   
  /*You can also see the change in the stack pointer. Right now it is pointing to the top of your memory.
   * But if you add a function call
    stupid_function();
    When it shifts from stupid_function to mem, it adds the address to the stack and the pointer decrements.
    If there had been variables in here, it would have decremented more.
    What does this mean for recursive functions?
   */
  while(1){}
}

/*
void check_mem() {
  stackptr = (uint8_t *)malloc(4);  // use stackptr temporarily
  heapptr = stackptr;               // save value of heap pointer
  free(stackptr);                   // free up the memory again (sets stackptr to 0)
  stackptr =  (uint8_t *)(SP);      // save value of stack pointer
}
*/
/*
void stupid_function(void)
{
  //Debugging
  check_mem(); 
  Serial.write("heapptr: "); Serial.print((int)heapptr);
  Serial.write(", stackptr: "); Serial.println((int)stackptr);

  //volatile is a variable qualifier, means that the variable will be loaded from RAM, not storage. 
  // This is beneficial to use, if several functions may change it at the same time, e.g. because of interrupts
  //Static local variables are only visible to the function in which they are created, but they don't loose 
  //their value between function calls
}
*/

