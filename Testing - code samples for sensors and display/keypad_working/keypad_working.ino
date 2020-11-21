/* @file CustomKeypad.pde
|| @version 1.0
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Demonstrates changing the keypad size and key values.
|| #
*/
#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads

char* password ="1234"; //create a password
int pozisyon = 0; //keypad position
int setLocked;
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'},
};
byte rowPins[ROWS] = {35, 37, 39, 41}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {43, 45, 47, 49}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup(){
  Serial.begin(9600);
  setLocked =0;; //state of the password
}
  
void loop(){
  char whichKey = customKeypad.getKey();
  
  if (whichKey){
    Serial.println(whichKey);


  if(whichKey == '*'){
    Serial.println("reset");
    }

  if(whichKey == '#' || whichKey == 'A' ||       //define invalid keys
  whichKey == 'B' || whichKey == 'C' || whichKey == 'D'){
    Serial.println("invalid key");
    pozisyon=0;
    setLocked =0;
    
  }
  if(whichKey == password [pozisyon]){

    pozisyon ++;
  }
  if(pozisyon == 4){
    setLocked =1;
    Serial.println("Valid key");
    
    
    
  }
  delay(100);
  }
}
