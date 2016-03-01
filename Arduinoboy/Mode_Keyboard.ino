void modeKeyboardSetup() {
  DDRC  = B00000000; // Set analog pins as inputs so we don't interfere with the PS/2 data
  modeKeyboard();
}

void modeKeyboard() {
  while(1) {
    setMode();                // Check if mode button was depressed
  }
}
