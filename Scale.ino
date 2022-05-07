#include <HX711_ADC.h> 
#include <Wire.h>
#include <LiquidCrystal_I2C.h>              // LiquidCrystal_I2C library
#include <Keypad.h>

HX711_ADC LoadCell(12, 13);                 // parameters: dt pin, sck pin
LiquidCrystal_I2C lcd(0x27, 20, 4);         // Set the LCD address to 0x27 for a 16 chars and 2 line display

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
char line[20];
char temp1[20];
char temp2[20];
byte rowPins[ROWS] = {2, 3, 4, 5};          // connect to the row pinouts of the keypad
byte colPins[COLS] = {6,7,8};               // connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
int led = 11;
int taree = 10;
int a = 0;
float b = 0;
int c = 0;
int Num1,Num2,Number;
void setup() 
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode (taree, INPUT_PULLUP);
  LoadCell.begin();                         // start connection to HX711
  LoadCell.start(1000);                     // load cells gets 1000ms of time to stabilize
  LoadCell.setCalFactor(103);               // calibration factor for load cell
  lcd.begin();                              // connect to the LCD module
  lcd.backlight();                    
}
void loop() 
{
  char key = keypad.getKey();
  if ((key)&&(c<4))
  { 
    if (key == '1')                         //If Button 1 is pressed
    { 
      if (Number==0)
        Number=1;
      else
        Number = (Number*10) + 1;           //Pressed twice
     }
    if (key == '2') 
    { 
      if (Number==0)
        Number=2;
      else
        Number = (Number*10) + 2; 
    }
    if (key == '3')
    { 
      if (Number==0)
        Number=3;
      else
        Number = (Number*10) + 3; 
    }    
    if (key == '4') 
    { 
      if (Number==0)
        Number=4;
      else
        Number = (Number*10) + 4; 
    }
    if (key == '5')
    { 
      if (Number==0)
        Number=5;
      else
        Number = (Number*10) + 5; 
    }
    if (key == '6')
    {
      if (Number==0)
        Number=6;
      else
        Number = (Number*10) + 6; 
    }     
    if (key == '7') 
    { 
      if (Number==0)
        Number=7;
      else
        Number = (Number*10) + 7; 
    } 
    if (key == '8')
    { 
      if (Number==0)
        Number=8;
      else
        Number = (Number*10) + 8; 
    }   
    if (key == '9')
    {
      if (Number==0)
        Number=9;
      else
        Number = (Number*10) + 9; 
    }
    if (key == '0')
    {
      if (Number==0)
      {
        Number=0;
        c = c - 1;
      }
      else
        Number = (Number*10) + 0;     
    } 
      c = c + 1;
  }
  if (key=='*')                       //reset
  {
   Number=0;
   c = 0;
   lcd.setCursor(15, 1); 
   lcd.print("0    ");
  }
  LoadCell.update();                  // get data from the load cell
  float i = LoadCell.getData();       // get output value
  lcd.setCursor(15, 1);   
  lcd.print(Number);                  // Price that we entered 
  delay(1);
  lcd.setCursor(0, 3); 
  lcd.print("Price = ");
  b = (i* Number/1000); 
  if(b<0)
  {
    b=0; 
  }
  lcd.setCursor(10, 3); 
  lcd.print(b, 3);                    // total price
  lcd.print("   ");
  lcd.setCursor(0, 0); 
  lcd.print("   Digital Scale ");     // print out to LCD
  lcd.setCursor(0, 1); 
  lcd.print("Price per KG = ");
  float k = i/1000;
  lcd.setCursor(9, 2); 
  lcd.print(k, 3);                    // print out the retrieved value to the second row
  lcd.print(" KG ");
  lcd.setCursor(0, 2); 
  lcd.print("Weight = ");
  if (k>=10)
  {
    digitalWrite(led, HIGH);
    lcd.setCursor(0, 2); 
    lcd.print("Over Loaded         "); 
    delay(100);
  }
  digitalWrite(led, LOW);
  if (key=='#')
  {
    digitalWrite(led, HIGH);
    lcd.setCursor(0, 2); 
    lcd.print("Calibrate...        ");
    LoadCell.start(1000);
  }
  dtostrf(k,4,2,temp1);
  dtostrf(b,4,2,temp2);
  sprintf(line,"%s,%s",temp1,temp2);
  Serial.println(line);
  delay(100);
}
