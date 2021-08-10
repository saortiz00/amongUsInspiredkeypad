/*
Created on August 10 2021 
by Sean Ortiz with help from:
https://www.circuitbasics.com/how-to-set-up-a-keypad-on-an-arduino/
*/

#include <Keypad.h>
#include <LiquidCrystal.h>

#define Password_Length 5 
int motorPin = 2;   

char Data[Password_Length]; 
char Master[Password_Length] = "3456"; 
byte data_count = 0, master_count = 0;
bool Pass_is_good;
char customKey;

const byte ROWS = 2; //2 rows
const byte COLS = 5; //5 columns
char buttons[ROWS][COLS] =  {{'1', '2', '3', '4', '5'},
                              {'6', '7', '8', '9', '0'}};
byte rowPins[ROWS] =  {14,15}; //pins for rows
byte colPins[COLS] = {3,4,5,6,7};//pins to each column
                 
const int rs = 12, en = 13, d4 = 11, d5 = 10, d6 = 9, d7 = 8;    //Pins for LCD; D14 = A0, D15 = A1             
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

Keypad customKeypad = Keypad(makeKeymap(buttons), rowPins, colPins, ROWS, COLS);



void setup(){
  Serial.begin(9600);
  shuffle();
  lcd.begin(16,2);
   lcd.print(" Among Us Keypad");
   lcd.setCursor(0,1);
   lcd.print(" V1.2");
   delay(2000);
   lcd.clear();
  pinMode(motorPin, OUTPUT);
}

void loop(){  
print();
  customKey = customKeypad.getKey();
  if (customKey){
    Data[data_count] = customKey; 
    lcd.setCursor(data_count,1); 
    lcd.print(Data[data_count]); 
    data_count++; 
    }

  if(data_count == Password_Length-1)//-1 to remove null character at end of string
  {
    lcd.clear();

    if(!strcmp(Data, Master)){
     lcd.begin(16,2);
      lcd.print(" Access ");
      lcd.setCursor(0,1);
       lcd.print(" Granted");
      digitalWrite(motorPin, HIGH); 
      delay(3500);
      digitalWrite(motorPin, LOW);
      }
    else{
       lcd.begin(16,2);
      lcd.print(" Access ");
      lcd.setCursor(0,1);
       lcd.print(" Denied");
      delay(1000);
      }
    
    lcd.clear();
    clearData();
    shuffle();  
  }
}

void clearData()
{
  while(data_count !=0)
  {
    Data[data_count--] = 0; 
  }
  return;
}

void shuffle()
{
for (int i=0; i < 2; i++) 
{
for (int j=0; j < 5; j++) 
{
   int m = random(0, 2); 
   int n = random(0, 5);
   int temp = buttons[i][j];
   buttons[i][j] =  buttons[m][n];
  buttons[m][n] = temp;
}
}
return;
}

void print()
{
for (int i=0; i < 2; i++) 
{
for (int j=0; j < 5; j++) 
{
  if(j<5)
  {
    if(j==0)
  lcd.setCursor(j, i); 
  else
   lcd.setCursor(3*j, i); 

  lcd.print(" "); 
  lcd.print(buttons[i][j]);
  lcd.print(", ");
  }
  else
   lcd.println(buttons[i][j]);
}
}
return;
}
