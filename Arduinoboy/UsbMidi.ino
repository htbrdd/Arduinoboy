
#ifndef MIDI_INTERFACE
void usbMidiSendTwoByteMessage(uint8_t b1, uint8_t b2) {};
void usbMidiSendThreeByteMessage(uint8_t b1, uint8_t b2, uint8_t b3) {};
void usbMidiSendRTMessage(uint8_t b) {};
void usbMidiHandleSysEx(const uint8_t *data, uint16_t length, bool complete) {};
void usbMidiInit() {};
#else

void usbMidiSendTwoByteMessage(uint8_t b1, uint8_t b2)
{
    uint8_t stat = b1 & 0xf0;
    uint8_t chan = (b1 & 0x0f)+1;
    if(stat == 0xC0) {
        usbMIDI.sendProgramChange(b2, chan);
    } else if (stat == 0xD0) {
        usbMIDI.sendAfterTouch(b2, chan);
    }
}

void usbMidiSendThreeByteMessage(uint8_t b1, uint8_t b2, uint8_t b3)
{
    uint8_t channel = (b1&0x0F)+1;

    switch(midiData[0] & 0xF0) {
        case 0x80:
          usbMIDI.sendNoteOff(b2, b3, channel);
          usbMIDI.send_now();
          break;
        case 0x90:
          usbMIDI.sendNoteOn(b2, b3, channel);
          usbMIDI.send_now();
          break;
        case 0xA0:
          usbMIDI.sendPolyPressure(b2, b3, channel);
          break;
        case 0xB0:
          usbMIDI.sendControlChange(b2, b3, channel);
          usbMIDI.send_now();
          break;
        case 0xE0:
          unsigned short v = (unsigned short)b3;
          v<<=7;
          v|=(unsigned short)b2;
          usbMIDI.sendPitchBend(v, channel);
          break;
    }
}

void usbMidiSendRTMessage(uint8_t b)
{
    usbMIDI.sendRealTime(b);
}

void usbMidiHandleSysEx(const uint8_t *data, uint16_t length, bool complete)
{
    // @TODO this is broken, at least on OSX - Cannot receive any sysex message.
    if(sysexPosition + length > longestSysexMessage) {
        //wrapped!
        sysexPosition = 0;
        return ;
    }
    memcpy(&sysexData[sysexPosition],data,length);
    sysexPosition += length;

    if(complete) {
        sysexPosition = 0;
        getSysexData();
    }
}

void usbMidiInit()
{
    usbMIDI.setHandleSysEx(usbMidiHandleSysEx);
}

#endif
