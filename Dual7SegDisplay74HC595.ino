#define clockPin A2

//Pins used for the tens digit
#define latchPin1 A1
#define dataPin1 A0

//Pins used for the ones digit
#define dataPin2 A3
#define latchPin2 A4

// binary code to shift out for each segment with MSBFIRST
//    ______
//   |   A  |
//  F|______|B
//   |   G  |
//  E|______|C
//       D

//Save the byte code that turns on each segment
byte A = 1 << 1;
byte B = 1 << 2;
byte C = 1 << 3;
byte D = 1 << 4;
byte E = 1 << 5;
byte F = 1 << 6;
byte G = 1 << 7;

byte empty = 00000000;

//Create the bytes for each number by combining the
// above bytes through bit masking
byte zero = A | B | C | D | E | F;
byte one = B | C;
byte two = A | B | D | E | G;
byte three = A | B | C | D | G;
byte four = B | C | F | G;
byte five = A | C | D | F | G;
byte six = A | C | D | E | F | G;
byte seven = A | B | C;
byte eight = A | B | C | D | E | F | G;
byte nine = A | B | C | D | F | G;


void setup() {

  pinMode(clockPin, OUTPUT);
  
  pinMode(dataPin1, OUTPUT);
  pinMode(dataPin2, OUTPUT);

  pinMode(latchPin1, OUTPUT);
  pinMode(latchPin2, OUTPUT);

  //Ensure all the segments are unlit when we start
  digitalWrite(latchPin1, LOW);
  shiftOut(dataPin1, clockPin, MSBFIRST, empty);
  digitalWrite(latchPin1, HIGH);

  digitalWrite(latchPin2, LOW);
  shiftOut(dataPin2, clockPin, MSBFIRST, empty);
  digitalWrite(latchPin2, HIGH);

  Serial.begin(9600);
  Serial.println("Enter a two digit number");
}

void loop() {

  //Read input 
  if (Serial.available())
  {
    int num = Serial.parseInt();

    Serial.println(num);

    displayNum(num);

    //discard any leftover input after the 
    // num has been read in. This is typically 
    // the new line character.
    if(Serial.available()) Serial.read();
  }

}

void displayNum(int num) {

  int tensDigit = num / 10;
  int onesDigit = num % 10;

  displayDigit(tensDigit, latchPin1, dataPin1);
  displayDigit(onesDigit, latchPin2, dataPin2);
}

void displayDigit(int digit, int latchPin, int dataPin)
{
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, intToByteSeg(digit));
  digitalWrite(latchPin, HIGH);
}

//Given a single digit, returns the appropriate byte to represent it.
byte intToByteSeg(int digit)
{
  switch (digit)
  {
    case 0:
      return zero;
      break;
    case 1:
      return one;
      break;
    case 2:
      return two;
      break;
    case 3:
      return three;
      break;
    case 4:
      return four;
      break;
    case 5:
      return five;
      break;
    case 6:
      return six;
      break;
    case 7:
      return seven;
      break;
    case 8:
      return eight;
      break;
    case 9:
      return nine;
      break;
  }

}

