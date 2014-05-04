/*
 ================== DROduino v1.0 =====================
 ...need desrciption 
 
 A special thanks to Dr. Rainer Hessmer for quadrature encoder code 
 adapted for this project. His blog entry with code and explanation
 can be found at:
 http://www.hessmer.org/blog/2011/01/30/quadrature-encoder-too-fast-for-arduino/
 
 ...need license info
*/

// include the library code:
  #include <LiquidCrystal.h>

// initialize the library with the numbers of the Arduino interface pins
  LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// Quadrature encoders
// X-axis encoder
  #define encoderXInterruptA 0
  #define encoderXPinA 2
  #define encoderXPinB 4
  volatile int encoderXPos = 0;
  int Xtmp = 0;
  int XAold = 0;
  int XBnew = 0;
  float XReal = 0.000;
// Z-axis encoder
  #define encoderZInterruptA 1
  #define encoderZPinA 3
  #define encoderZPinB 5
  volatile int encoderZPos = 0;
  int Ztmp = 0;
  int ZAold = 0;
  int ZBnew = 0;
  float ZReal = 0.000;

void setup() {
  // Quadrature encoders
  // X-axis encoder
    pinMode(encoderXPinA, INPUT); 
    pinMode(encoderXPinB, INPUT);
    attachInterrupt(encoderXInterruptA, doXEncoderA, CHANGE);
  // Z-axis encoder
    pinMode(encoderZPinA, INPUT); 
    pinMode(encoderZPinB, INPUT);
    attachInterrupt(encoderZInterruptA, doZEncoderA, CHANGE);
  // set up the LCD's number of columns and rows 
    lcd.begin(8, 2);
}

void loop(){
  //Check each change in position
  if (Xtmp != encoderXPos) {
    //XReal variable calibrates encoderXPos to actual length
    XReal = float(encoderXPos)*.0005;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("X:");
    lcd.print(XReal, 3);
    lcd.setCursor(0, 1);
    lcd.print("Z:");
    lcd.print(ZReal, 3);
    Xtmp = encoderXPos;
  }
  if (Ztmp != encoderZPos) {
    //ZReal variable calibrates encoderZPos to actual length
    ZReal = float(encoderZPos)*.0005;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("X:");
    lcd.print(XReal, 3);
    lcd.setCursor(0, 1);
    lcd.print("Z:");
    lcd.print(ZReal, 3);
    Ztmp = encoderZPos;
  }
  delay(250);
}

// X Axis Interrupt on A changing state
void doXEncoderA(){
  XBnew^XAold ? encoderXPos++:encoderXPos--;
  XAold=digitalRead(encoderXPinA);
  XBnew=digitalRead(encoderXPinB);
  XBnew^XAold ? encoderXPos++:encoderXPos--;
}

// Z Axis Interrupt on A changing state
void doZEncoderA(){
  ZBnew^ZAold ? encoderZPos++:encoderZPos--;
  ZAold=digitalRead(encoderZPinA);
  ZBnew=digitalRead(encoderZPinB);
  ZBnew^ZAold ? encoderZPos++:encoderZPos--;
}
