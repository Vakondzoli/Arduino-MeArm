#include <Keypad.h>
#include <Elegoo_GFX.h>    
#include <Elegoo_TFTLCD.h> 
#include <TouchScreen.h>

#define YP A3  
#define XM A2  
#define YM 9   
#define XP 8   

#define TS_MINX 120
#define TS_MAXX 900
#define TS_MINY 70
#define TS_MAXY 920

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4

#define MINPRESSURE 10
#define MAXPRESSURE 1000

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

#define BOXSIZE 40
#define PENRADIUS 3

int oldcolor, currentcolor, randNumber,unit;

const int DigiOutToUno12=41;
const int AOUTpinAlc=7;
const int AOUTpinGas=8;

int tft_page, alcohol_value, gas_value;

const byte keypad_rows = 4;
const byte keypad_cols = 4;

char* password ="8474";
int passwordPosition = 0;

char hexaKeys[keypad_rows][keypad_cols] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'},
};
byte rowPins[keypad_rows] = {34, 36, 38, 40};
byte colPins[keypad_cols] = {42, 44, 46, 48};

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, keypad_rows, keypad_cols); 

void main_menu0(){  
    tft.fillScreen(BLACK);
    tft.drawRoundRect(10, 30, 220, 280, 20, BLUE);
    tft.drawRoundRect(11, 31, 222, 282, 20, BLUE);
    tft.drawRoundRect(12, 32, 224, 284, 20, BLUE);
    
    tft.fillRoundRect(20, 250, 200, 50, 10, RED);
    tft.drawRoundRect(21, 251, 202, 52, 10, RED);
    tft.drawRoundRect(22, 252, 204, 54, 10, RED);
    tft.setCursor(30,255);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.print("BREATHALYZER");
    tft.setCursor(31,256);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.print("BREATHALYZER");
    
    tft.fillRoundRect(20, 180, 200, 50, 10, GREEN);
    tft.drawRoundRect(21, 181, 202, 52, 10, GREEN);
    tft.drawRoundRect(22, 182, 204, 54, 10, GREEN);
    tft.setCursor(30,190);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.print("XYZ");
    tft.setCursor(31,191);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.print("XYZ");
  
    tft.fillRoundRect(20, 110, 200, 50, 10, MAGENTA);
    tft.drawRoundRect(21, 111, 202, 52, 10, MAGENTA);
    tft.drawRoundRect(22, 112, 204, 54, 10, MAGENTA);
    tft.setCursor(30,120);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.print("CLOCK-IN");
    tft.setCursor(31,121);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.print("CLOCK-IN");
  
    tft.fillRoundRect(20, 40, 200, 50, 10, YELLOW);
    tft.drawRoundRect(21, 41, 202, 52, 10, YELLOW);
    tft.drawRoundRect(22, 42, 204, 54, 10, YELLOW);
    tft.setCursor(30,50);
    tft.setTextColor(CYAN);
    tft.setTextSize(2);
    tft.print("GAS SENSOR");
    tft.setCursor(31,51);
    tft.setTextColor(CYAN);
    tft.setTextSize(2);
    tft.print("GAS SENSOR");
}
void return_to_mainmenu(){
    tft.drawRoundRect(20, 250, 200, 50, 10, WHITE);
    delay(100);
    tft_page=0;
    main_menu0();
}
void exit_menu(){
    tft.fillScreen(BLACK);    
    tft.fillRoundRect(20, 250, 200, 50, 10, RED);
    tft.setCursor(30,255);
    tft.setTextColor(WHITE);
    tft.setTextSize(3);
    tft.print("Exit");
}

void exit_menu_breath(){
    tft.fillScreen(BLACK);    
    tft.fillRoundRect(20, 250, 200, 50, 10, RED);
    tft.setCursor(30,255);
    tft.setTextColor(WHITE);
    tft.setTextSize(3);
    tft.print("DONE");
}


int alcohol_read(){
    alcohol_value = analogRead(AOUTpinAlc);      
    return (alcohol_value);      
}
int units(){
    if (alcohol_read()<60){
      unit=0;
      return unit;
      }
    else{
      unit=(alcohol_read()-60)/25;
      return unit;
      } 
} 
void been_drinking(){
    tft.fillRoundRect(20, 150, 200, 50, 10, YELLOW);
    tft.setCursor(30,155);
    tft.setTextColor(RED);
    tft.setTextSize(2);
    tft.print("You've been");
    tft.print('\n');
    tft.setCursor(30,180);  
    tft.println("drinking"); 
      
    digitalWrite(DigiOutToUno12,LOW); 
}
void breath_menu1(){
    exit_menu_breath();
    
    tft.setCursor(30,50);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.print("ALCOHOL LEVEL: ");
}
void print_alcohol_readings(){
    if (alcohol_read()<60){
      tft.fillRoundRect(20, 90, 200, 50, 10, YELLOW);
      tft.fillRoundRect(20, 150, 200, 50, 10, BLACK);
      tft.setCursor(30,100);
      tft.setTextColor(GREEN);
      tft.setTextSize(2); 
      tft.print (alcohol_read());
      tft.print(" = ");
      tft.print(units());
      tft.print(" unit(s)");
}   
   else if (alcohol_read()>100){  
      tft.fillRoundRect(20, 90, 200, 50, 10, YELLOW);
      tft.setCursor(30,100);
      tft.setTextColor(RED);
      tft.setTextSize(2); 
      tft.print (alcohol_read());
      tft.print(" = ");
      tft.print(units());
      tft.print(" unit(s)");
          
      been_drinking();
} 
    delay(500);
}


int gas_read(){
    gas_value = analogRead(AOUTpinGas);
    return gas_value;
}
void mq2_menu4(){
    exit_menu();
        
    tft.setCursor(30,50);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.print("GAS LEVEL: ");   
}
void print_gas_readings(){
    if (gas_read()<300){
      tft.fillRoundRect(20, 90, 100, 50, 10, YELLOW);
      tft.setCursor(30,100);
      tft.setTextColor(GREEN);
      tft.setTextSize(3); 
      tft.print (gas_read());
}   else if (gas_read()>300){  
      tft.fillRoundRect(20, 90, 100, 50, 10, YELLOW);
      tft.setCursor(30,100);
      tft.setTextColor(RED);
      tft.setTextSize(3); 
      tft.print (gas_read());
      tft.fillRoundRect(20, 150, 200, 50, 10, YELLOW);
      tft.setCursor(30,155);
      tft.setTextColor(RED);
      tft.setTextSize(2);
      tft.print("DANGEROUS");
      tft.print('\n');
      tft.setCursor(30,180);  
      tft.println("GAS LEVELS");    
} 
    delay(200);
}


void keypad_menu3(){  
    exit_menu();    
    tft.setCursor(30,50);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.print("ACCESS: ");   
}
void keypad_reading(){  
    char whichKey = customKeypad.getKey();
      
    if (whichKey){
      Serial.println(whichKey);
      tft.fillRoundRect(20, 90, 150, 50, 10, YELLOW);
      tft.setCursor(30,100);
      tft.setTextColor(GREEN);
      tft.setTextSize(3); 
      tft.print (whichKey);
}  
    if(whichKey == '*'){
      Serial.println("reset");
      passwordPosition=0;
      
      tft.fillRoundRect(20, 90, 150, 50, 10, YELLOW);
      tft.setCursor(30,100);
      tft.setTextColor(GREEN);
      tft.setTextSize(3); 
      tft.print ("RESET");
      return;
}  
    if(whichKey == password [passwordPosition]){
      passwordPosition ++;
        if(passwordPosition == 4){    
        Serial.println("Valid key");
        tft.fillRoundRect(20, 90, 150, 50, 10, YELLOW);
        tft.setCursor(30,100);
        tft.setTextColor(GREEN);
        tft.setTextSize(3); 
        tft.print ("GRANTED");
        delay(1000);
        randNumber = 0;
           if (randNumber==0){
              tft.fillRoundRect(20, 160, 150, 50, 10, YELLOW);
              tft.setCursor(30,170);
              tft.setTextColor(GREEN);
              tft.setTextSize(2); 
              tft.print ("RANDOM TEST");
              delay(1000);
              breath_menu1();
              tft_page=1;
 } 
          else if (randNumber==1){
              tft.fillRoundRect(20, 160, 200, 50, 10, YELLOW);
              tft.setCursor(30,170);
              tft.setTextColor(GREEN);
              tft.setTextSize(2); 
              tft.print ("ARM ACTIVATED!");
              
              delay(1000);
              digitalWrite(DigiOutToUno12, HIGH);
              main_menu0();
              tft_page=0;
      } 
    }
  }
}
  


  
void paint_menu5(){
    tft.fillScreen(BLACK);
    tft.fillRect(0, 0, BOXSIZE, BOXSIZE, RED);
    tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, YELLOW);
    tft.fillRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, GREEN);
    tft.fillRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, CYAN);
    tft.fillRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE, BLUE);
    tft.fillRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, MAGENTA);
   
    tft.drawRect(0, 0, BOXSIZE, BOXSIZE, WHITE);
    currentcolor = RED; 
}
void paint(){  
    TSPoint p = ts.getPoint();
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
  
    if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
      /*
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z);
      */
      if (p.y < (TS_MINY-5)) {
        Serial.println("erase");
        // press the bottom of the screen to erase 
        tft.fillRect(0, BOXSIZE, tft.width(), tft.height()-BOXSIZE, BLACK);
      }
      p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
      p.y = (tft.height()-map(p.y, TS_MINY, TS_MAXY, tft.height(), 0));     
      /*
      Serial.print("("); Serial.print(p.x);
      Serial.print(", "); Serial.print(p.y);
      Serial.println(")");
      */
      if (p.y < BOXSIZE) {
         oldcolor = currentcolor;
         if (p.x < BOXSIZE) { 
           currentcolor = RED; 
           tft.drawRect(0, 0, BOXSIZE, BOXSIZE, WHITE);
         } else if (p.x < BOXSIZE*2) {
           currentcolor = YELLOW;
           tft.drawRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, WHITE);
         } else if (p.x < BOXSIZE*3) {
           currentcolor = GREEN;
           tft.drawRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, WHITE);
         } else if (p.x < BOXSIZE*4) {
           currentcolor = CYAN;
           tft.drawRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, WHITE);
         } else if (p.x < BOXSIZE*5) {
           currentcolor = BLUE;
           tft.drawRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE, WHITE);
         } else if (p.x < BOXSIZE*6) {
           currentcolor = MAGENTA;
           tft.drawRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, WHITE);
         }
         if (oldcolor != currentcolor) {
            if (oldcolor == RED) tft.fillRect(0, 0, BOXSIZE, BOXSIZE, RED);
            if (oldcolor == YELLOW) tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, YELLOW);
            if (oldcolor == GREEN) tft.fillRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, GREEN);
            if (oldcolor == CYAN) tft.fillRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, CYAN);
            if (oldcolor == BLUE) tft.fillRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE, BLUE);
            if (oldcolor == MAGENTA) tft.fillRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, MAGENTA);
         }
      }
      if (((p.y-PENRADIUS) > BOXSIZE) && ((p.y+PENRADIUS) < tft.height())) {
        tft.fillCircle(p.x, p.y, PENRADIUS, currentcolor);
    }
  }
}

void setup() { 
  Serial.begin(9600); 
  Serial.println(F("Rock and Roll!"));
  
  pinMode(AOUTpinAlc, INPUT);
  pinMode(AOUTpinGas, INPUT);  
  pinMode(DigiOutToUno12, OUTPUT);
  tft.reset();  
  
  uint16_t identifier = tft.readID();
  if(identifier == 0x9325) {
    Serial.println(F("Found ILI9325 LCD driver"));
  } else if(identifier == 0x9328) {
    Serial.println(F("Found ILI9328 LCD driver"));
  } else if(identifier == 0x4535) {
    Serial.println(F("Found LGDP4535 LCD driver"));
  } else if(identifier == 0x7575) {
    Serial.println(F("Found HX8347G LCD driver"));
  } else if(identifier == 0x9341) {
    Serial.println(F("Found ILI9341 LCD driver"));
  } else if(identifier == 0x8357) {
    Serial.println(F("Found HX8357D LCD driver"));
  } else if(identifier==0x0101){     
    identifier=0x9341;
    Serial.println(F("Found 0x9341 LCD driver"));
  } else {
    Serial.print(F("Unknown LCD driver chip: "));
    Serial.println(identifier, HEX);
    identifier=0x9341;
  }
  tft.begin(identifier);
  tft.setRotation(2);
  main_menu0();
  tft_page=0;  
}
  
void loop() {

  TSPoint p = ts.getPoint();
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
  p.y = (tft.height()-map(p.y, TS_MINY, TS_MAXY, tft.height(), 0));
  
  if (tft_page==0){      
        if (p.y < 300 && p.y > 250) {       
          tft.drawRoundRect(20, 250, 200, 50, 10, WHITE);
          delay(100);          
          tft_page=1;      
          breath_menu1();
        }/*
        else if (p.y < 230 && p.y > 180 && p.x < 120 && p.x >0) {       
          tft.drawRoundRect(20, 180, 200, 50, 10, WHITE);
          delay(100);          
          tft_page=1;      
          game_menu2();                 
        } */ 
        else if (p.y < 160 && p.y > 110) {       
          tft.drawRoundRect(20, 110, 200, 50, 10, WHITE);
          delay(100);          
          tft_page=3;      
          keypad_menu3();        
      }
        else if (p.y < 90 && p.y > 40) {       
          tft.drawRoundRect(20, 40, 200, 50, 10, WHITE);
          delay(100);          
          tft_page=4;      
          mq2_menu4();        
      }
        else if (p.y < 20 && p.y > 0) {       
          tft.fillRoundRect(20, 0, 200, 15, 10, WHITE);
          tft.setCursor(20,0);
          tft.setTextColor(RED);
          tft.setTextSize(2);
          tft.print("_____PAINT_____");
          delay(200);          
          tft_page=5;      
          paint_menu5();        
      }
    }  
     
  else if (tft_page==1){    
    print_alcohol_readings();
    if (p.y < 300 && p.y > 250) {  
      return_to_mainmenu();     
  }
 }
/*
  else if (tft_page==2){    
    game();
    if (p.y < 300 && p.y > 250) {  
      return_to_mainmenu();   
  }
 }*/
   else if (tft_page==3){    
   keypad_reading();
   if (p.y < 300 && p.y > 250) {  
      return_to_mainmenu();     
  }
 }
  else if (tft_page==4){    
    print_gas_readings();
    if (p.y < 300 && p.y > 250) {  
      return_to_mainmenu();   
  }
 }
 else if (tft_page==5){    
    paint();
    tft.drawRoundRect(0, 310, 10, 10, 10, RED);
    tft.setCursor(1,311);
    tft.setTextColor(RED);
    tft.setTextSize(1);
    tft.print("x");
    if (p.y < 320 && p.y > 310 && p.x < 10 && p.x >0) {  
      tft.drawRoundRect(0, 310, 10, 10, 10,WHITE);
      delay(100);
      tft_page=0;
      main_menu0();    
  }
 }
 else {
 Serial.print('WTF!!!');
 }
}
   
  
