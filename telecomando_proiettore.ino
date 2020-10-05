#include <attiny85_ir_send.h>
IRsend irsend;
enum tipologie {
  nec,
  sony,
  rc5,
  rc6
};
#define codec nec
void setup() {
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(PB1, OUTPUT);
}

void loop() {
  if (digitalRead(A1) == LOW) {
    mandaSegnale(codec, 0x212FD02F, 32);
  }
  else if (digitalRead(A2) == LOW) {
    mandaSegnale(codec, 0x212F34CB, 32);
  }
  else if (digitalRead(A3) == LOW) {
    mandaSegnale(codec, 0x212F34CB, 32);
  }
  while(bottoniPremuti);
}
void mandaSegnale(int tipo, unsigned long int valore, int bits) {
  switch (tipo) {
    case nec: irsend.sendNEC(valore, bits); break;
    case sony: irsend.sendSony(valore, bits); break;
    case rc5: irsend.sendRC5(valore, bits); break;
    case rc6: irsend.sendRC6(valore, bits); break;
    default:break;
  }
}
void mandaSegnale(unsigned long int valore, int frequenza) {
  while (valore > 0) {
    if (valore % 2 == 1) {
      analogWrite(PB1, 255);
    }
    else {
      analogWrite(PB1, 0);
    }
    valore /= 2;
    delayMicroseconds(1000 / frequenza);
  }
  digitalWrite(PB1, LOW);
  delay(500);
}
boolean bottoniPremuti(){
  if(digitalRead(A1) == LOW || digitalRead(A2) == LOW || digitalRead(A3) == LOW){
    return true;
  }
  delay(500);
  return false;
}
