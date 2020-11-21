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

#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

const int AOUTpin=7;
int page;
int value;

void main_menu0(){
  tft.fillScreen(BLACK);
  tft.fillRect(20, 250, 200, 50, RED);
  tft.setCursor(30,255);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print("Breathalyzer");
  
  tft.fillRect(20, 180, 200, 50, BLUE);
  tft.setCursor(30,190);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print("Gas Sensor");

  tft.fillRect(20, 110, 200, 50, MAGENTA);
  tft.setCursor(30,120);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print("Clock-in");

  tft.fillRect(20, 40, 200, 50, YELLOW);
  tft.setCursor(30,50);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print("Game");
}
int alcohol_read(){
  value = analogRead(AOUTpin);
  return value;
}
void breath_menu1(){
  tft.fillScreen(BLACK);    
  tft.setCursor(30,50);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print("Alcohol level: ");
  tft.fillRect(20, 250, 200, 50, RED);
  tft.setCursor(30,255);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.print("Exit"); 
}
void print_readings(){
  if (alcohol_read()<100){
    tft.fillRect(20, 90, 100, 50, YELLOW);
    tft.setCursor(30,100);
    tft.setTextColor(GREEN);
    tft.setTextSize(3); 
    tft.print (alcohol_read());
} else if (alcohol_read()>100){  
    tft.fillRect(20, 90, 100, 50, YELLOW);
    tft.setCursor(30,100);
    tft.setTextColor(RED);
    tft.setTextSize(3); 
    tft.print (alcohol_read());
    tft.fillRect(20, 150, 200, 50, YELLOW);
    tft.setCursor(30,155);
    tft.setTextColor(RED);
    tft.setTextSize(2);
    tft.print("You've been");
    tft.print('\n');
    tft.setCursor(30,180);  
    tft.println("drinking");    
  } 
  delay(200);
}
void setup() {
  Serial.begin(9600);
  Serial.println(F("Rock and Roll!"));
  pinMode(AOUTpin, INPUT);
  pinMode(13, OUTPUT);
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
  page=0;  
}
void loop(){
  digitalWrite(13, HIGH);  
  digitalWrite(13, LOW);
  TSPoint p = ts.getPoint();
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
  p.y = (tft.height()-map(p.y, TS_MINY, TS_MAXY, tft.height(), 0));
  
  if(page==0){      
    if (p.y < 300 && p.y > 250) {       
      tft.drawRect(20, 250, 200, 50, WHITE);
      delay(100);          
      page=1;      
      breath_menu1();      
  }
}      
  else if(page==1){    
    print_readings();
    if (p.y < 300 && p.y > 250) {  
      tft.drawRect(20, 250, 200, 50, WHITE);
      delay(100);
      page=0;
      main_menu0();    
  }
 }
}
