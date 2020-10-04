#include <attiny85_ir_send.h>
IRsend irsend;
enum tipologie{
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
    mandaSegnale(codec, 0x212FD02F, 32);
  }
  else if (digitalRead(A2) == LOW) {
    mandaSegnale(codec, 0x212F34CB, 32);
  }
  else if (digitalRead(A3) == LOW) {
    mandaSegnale(codec, 0x212F34CB, 32);
  }
}
void mandaSegnale(int tipo, unsigned long int valore, int bits) {
  switch (tipo){
    case NEC:irsend.sendNEC(valore, bits);break;
    case SONY:irsend.sendSony(valore, bits);break;
    case RC5:irsend.sendRC5(valore, bits);break;
    case RC6:irsend.sendRC6(valore, bits);break;
  }
  delay(500);
}
void segnaleManuale(unsigned long int valore, int bits, int frequenza){
  for(int i = bits; i > 0; i--){
    if (valore % 2 == 1){
      digitalWrite(PB1, HIGH);
    }
    delay
  }
}
