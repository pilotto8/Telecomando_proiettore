#include <attiny85_ir_send.h>
IRsend irsend;
enum tipologie {
  NEC,
  SONY,
  RC5,
  RC6
};
#define codec RC5
void setup() {
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(PB1, OUTPUT);
}

void loop() {

  if (digitalRead(A1) == LOW) {
    mandaSegnale(0x212FD02F, 8);
  }
  else if (digitalRead(A2) == LOW) {
    mandaSegnale(0x212F34CB, 8);
  }
  else if (digitalRead(A3) == LOW) {
    mandaSegnale(0x212F34CB, 8);
  }
}
void mandaSegnale(int tipo, unsigned long int valore, int bits) {
  switch (tipo) {
    case NEC: irsend.sendNEC(valore, bits); break;
    case SONY: irsend.sendSony(valore, bits); break;
    case RC5: irsend.sendRC5(valore, bits); break;
    case RC6: irsend.sendRC6(valore, bits); break;
  }
  delay(500);
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
