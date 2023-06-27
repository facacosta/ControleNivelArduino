void setup() {
Serial.begin(115200);
Serial3.begin(115200);//15(RX), 14(TX)

pinMode(pinoBomPc, OUTPUT);
pinMode(pinoBomCis, OUTPUT);

pinMode(pinoSemFx, INPUT_PULLUP);
attachInterrupt(digitalPinToInterrupt(pinoSemFx), contador, RISING);
}
