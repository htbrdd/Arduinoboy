void modeKeyboardSetup() {
   // Set analog pins as inputs so we don't interfere with the PS/2 data
   pinMode(pinGBClock,INPUT);
   pinMode(pinGBSerialIn,INPUT);
   pinMode(pinGBSerialOut,INPUT);
   modeKeyboard();
 }

 void modeKeyboard() {
   while(1) {
     setMode();                // Check if mode button was depressed
   }
 }
