int intA = 11, intB = 7, intC = 4, intD = 2, intE = 1, intF = 10;
int intDP = 3, intG = 5, intDig1 = 12, intDig2 = 9, intDig3 = 8, intDig4 = 6;
int intNumberToDisplay = 0;
long lngDelayAccumulatedMicro = 0;

void setup() {
  // Pins do arduino correspondentes aos segmentos e digitos
  // Inicializar pins de output
  for (int intPinNumber = 1; intPinNumber <= 12; intPinNumber++) {
    pinMode(intPinNumber, OUTPUT);
  }
}

// Esquema do display visto de cima:
/*
                                            12  11  10  9   8   7
                                            |   |   |   |   |   |
                                            |   |   |   |   |   |
 ______________________________________________________________________________________________________
 |---------a---------|      |---------a---------|      |---------a---------|      |---------a---------|                 
 |                   |      |                   |      |                   |      |                   |
 f                   b      f                   b      f                   b      f                   b
 |                   |      |                   |      |                   |      |                   |
 |---------g---------|      |---------g---------|      |---------g---------|      |---------g---------|    
 |                   |      |                   |      |                   |      |                   |
 e                   c      e                   c      e                   c      e                   c
 |                   |      |                   |      |                   |      |                   |
 |---------d---------| [dp] |---------d---------| [dp] |---------d---------| [dp] |---------d---------| [dp]
 ______________________________________________________________________________________________________
                                            |   |   |   |   |   |
                                            |   |   |   |   |   |
                                            1   2   3   4   5   6
*/

void turn_off() {
  int i = 1; // Pin number
  while(i <= 12) {
    // Turn off every pin
    digitalWrite(i, LOW);
    i++;
  }
}

void turn_on() {
  int i = 1; // Pin number
  while(i <= 13) {
    // Turn off every pin
    digitalWrite(i, HIGH);
    i++;
  }
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void disp(int in_intNumber, int in_intDigit) {
  turn_off();
  if (in_intDigit == 4) digitalWrite(intDig4, HIGH);
  if (in_intDigit == 3) digitalWrite(intDig3, HIGH);
  if (in_intDigit == 2) digitalWrite(intDig2, HIGH);
  if (in_intDigit == 1) digitalWrite(intDig1, HIGH);
  // ======================================================
  switch (in_intNumber) {
    case 0:
      digitalWrite(intE, HIGH); // e
      digitalWrite(intD, HIGH); // d
      digitalWrite(intC, HIGH); // c
      digitalWrite(intG, LOW); // g
      digitalWrite(intB, HIGH); // b
      digitalWrite(intF, HIGH); // f
      digitalWrite(intA, HIGH); // a
      break; // End case 0
    // ====================================================
    case 1:
      digitalWrite(intB, HIGH);
      digitalWrite(intC, HIGH);
      break;
    // ====================================================
    case 2:
      digitalWrite(intA, HIGH);
      digitalWrite(intB, HIGH);
      digitalWrite(intG, HIGH);
      digitalWrite(intE, HIGH);
      digitalWrite(intD, HIGH);
      break; // End case 2
    // ====================================================
    case 3:
      digitalWrite(intA, HIGH);
      digitalWrite(intB, HIGH);
      digitalWrite(intC, HIGH);
      digitalWrite(intD, HIGH);
      digitalWrite(intG, HIGH);
      break;
    // ====================================================
    case 4:
      digitalWrite(intF, HIGH);
      digitalWrite(intG, HIGH);
      digitalWrite(intB, HIGH);
      digitalWrite(intC, HIGH);
      break;
    // ====================================================
    case 5:
      digitalWrite(intA, HIGH);
      digitalWrite(intF, HIGH);
      digitalWrite(intG, HIGH);
      digitalWrite(intC, HIGH);
      digitalWrite(intD, HIGH);
      break;
    // ====================================================
    case 6:
      digitalWrite(intA, HIGH);
      digitalWrite(intF, HIGH);
      digitalWrite(intG, HIGH);
      digitalWrite(intC, HIGH);
      digitalWrite(intD, HIGH);
      digitalWrite(intE, HIGH);
      break;
    // ====================================================
    case 7:
      digitalWrite(intA, HIGH);
      digitalWrite(intB, HIGH);
      digitalWrite(intC, HIGH);
      break;
    // ====================================================
    case 8:
      digitalWrite(intA, HIGH);
      digitalWrite(intB, HIGH);
      digitalWrite(intC, HIGH);
      digitalWrite(intD, HIGH);
      digitalWrite(intE, HIGH);
      digitalWrite(intF, HIGH);
      digitalWrite(intG, HIGH);
      break;
    // ====================================================
    case 9:
      digitalWrite(intA, HIGH);
      digitalWrite(intB, HIGH);
      digitalWrite(intG, HIGH);
      digitalWrite(intC, HIGH);
      digitalWrite(intD, HIGH);
      digitalWrite(intF, HIGH);
      break;
    // ====================================================
  } // End switch
} // End
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void disp_dp() {
  turn_off();
  digitalWrite(5, HIGH);
}

void loop() {
  int intDelayMicro = 2000, intResto = 0;
 
  int intMilhares = intNumberToDisplay / 1000;

  intResto = intNumberToDisplay % 1000;

  int intCentenas = intResto / 100;

  intResto %= 100;

  int intUnidades = intResto % 10;

  int intDezenas = intResto / 10;
  
  disp(intUnidades, 4);
  delayMicroseconds(intDelayMicro);
  lngDelayAccumulatedMicro += intDelayMicro;
  if ( intNumberToDisplay >= 10 ) disp(intDezenas, 3);
  delayMicroseconds(intDelayMicro);
  lngDelayAccumulatedMicro += intDelayMicro;
  if ( intNumberToDisplay >= 100 ) disp(intCentenas, 2);
  delayMicroseconds(intDelayMicro);
  lngDelayAccumulatedMicro += intDelayMicro;
  if ( intNumberToDisplay >= 1000) disp(intMilhares, 1);
  delayMicroseconds(intDelayMicro);
  lngDelayAccumulatedMicro += intDelayMicro;

  if (lngDelayAccumulatedMicro == 1000000) {
    lngDelayAccumulatedMicro = 0;
    intNumberToDisplay += 1;
  }

  if ( intNumberToDisplay >= 9999 ) intNumberToDisplay = 0;
} // End loop()
