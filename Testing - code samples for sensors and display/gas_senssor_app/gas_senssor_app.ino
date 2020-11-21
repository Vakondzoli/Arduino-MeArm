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

#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

const int AOUTpin=15;


int value;

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
  }else if(identifier == 0x7575) {
    Serial.println(F("Found HX8347G LCD driver"));
  } else if(identifier == 0x9341) {
    Serial.println(F("Found ILI9341 LCD driver"));
  } else if(identifier == 0x8357) {
    Serial.println(F("Found HX8357D LCD driver"));
  } else if(identifier==0x0101)
  {     
      identifier=0x9341;
       Serial.println(F("Found 0x9341 LCD driver"));
  }else {
    Serial.print(F("Unknown LCD driver chip: "));
    Serial.println(identifier, HEX);
    identifier=0x9341;
  }
  tft.begin(identifier);
  tft.setRotation(2);


#define MINPRESSURE 10
#define MAXPRESSURE 1000
}
void loop()
{
  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);
  p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
  p.y = (tft.height()-map(p.y, TS_MINY, TS_MAXY, tft.height(), 0));
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  value= analogRead(AOUTpin);


  tft.fillScreen(BLACK);    
  tft.setCursor(30,50);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print("alcohol: ");
  tft.print (value);
  

}
