#include <attiny85_ir_send.h>
IRsend irsend;
enum tipologie {
  nec,
  sony,
  rc5,
  rc6,
  raw
};
#define codec nec
#define rawlen 68
unsigned int powerRAW[]{
  15900, 9000, 4500, 
  550, 550, 550, 550, 550, 1700, 550, 550, 
  550, 550, 500, 600, 500, 600, 500, 1700, 
  500, 600, 550, 550, 550, 1650, 550, 550, 
  550, 1650, 500, 1700, 550, 1650, 550, 1700, 
  450, 1750, 550, 1650, 500, 550, 550, 1700, 
  500, 550, 600, 500, 600, 500, 550, 550, 
  550, 550, 550, 550, 550, 1700, 500, 600, 
  550, 1650, 550, 1650, 550, 1650, 550, 1650, 
  560};
void setup() {
  pinMode(4, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(1, OUTPUT);
  delay(500);
  mandaSegnale(codec, powerRAW, 32);
}

void loop() {
  if (digitalRead(2) == LOW) {
    mandaSegnale(codec, 0x212FD02F, 32);
  }
  else if (digitalRead(4) == LOW) {
    mandaSegnale(codec, 0x212F34CB, 32);
  }
  else if (digitalRead(3) == LOW) {
    mandaSegnale(codec, 0x212F34CB, 32);
  }
  while(bottoniPremuti);
}
void mandaSegnale(int tipo, long int valore, int bits) {
  switch (tipo) {
    case nec: irsend.sendNEC(valore, bits); break;
    case sony: irsend.sendSony(valore, bits); break;
    case rc5: irsend.sendRC5(valore, bits); break;
    case rc6: irsend.sendRC6(valore, bits); break;
    case raw: irsend.sendRaw(valore, rawlen, 76 /* kHz */);
    default:digitalWrite(PB1, LOW);break;
  }
}
boolean bottoniPremuti(){
  if(digitalRead(A1) == LOW || digitalRead(A2) == LOW || digitalRead(A3) == LOW){
    return true;
  }
  delay(500);
  return false;
}
