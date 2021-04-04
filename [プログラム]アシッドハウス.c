#include <Adafruit_NeoPixel.h> //Neopixelという種類のLEDを光らせるためのライブラリ
#define PIN 0 //PIN 0からLEDに信号が送られる,ここではPIN 0に指定すると書かれている
#define NUM_LEDS 10 //LEDの数を指定している,ここでは１10個のLEDを指定すると書かれている
// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);



//setupする関数,主にマイコンの部分に電源を入れた時やリセットした時の,ピンのモードの初期化など,ハードウェア側の設定
void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}
///////////////////////ここまでがsetup関数///////////////////////////////////



//loop関数の中のは実行したいプログラムを書く,マイコンの動きをコントロールする,この部分は繰り返し実行される
//この関数内では下記で示されている光り方の関数1,2を動作させたいので,loop関数内に記述している
void loop() {
  Strobe(0xff, 0xff, 0xff, 10, 50, 100); //白
  meteorRain(0xff, 0xff, 0xff,10, 64, true, 15);//白

  Strobe(0xff, 0x00, 0xff, 10, 50, 100); //ピンク
  meteorRain(0xff, 0x00, 0xff,10, 64, true, 15);//ピンク

  Strobe(0xFF, 0xFF, 0x00, 10, 50, 100);//黄色
  meteorRain(0xff, 0xff, 0x00,10, 64, true, 15);//黄色

  Strobe(0x0A, 0x0A, 0x2A, 10, 50, 100);//青
  meteorRain(0x0A, 0x0A, 0x2A,10, 64, true, 15);//青

  Strobe(0x29, 0x08, 0x8A, 10, 50, 100);//紫
  meteorRain(0x29, 0x08, 0x8A,10, 64, true, 15);//紫
 }
///////////////////////ここまでがloop関数///////////////////////////////////

//光り方の関数1 meteorRaine ここから
void meteorRain(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay) {
  setAll(0,0,0);

  for(int i = 0; i < NUM_LEDS+NUM_LEDS; i++) {


    // fade brightness all LEDs one step
    for(int j=0; j<NUM_LEDS; j++) {
      if( (!meteorRandomDecay) || (random(10)>5) ) {
        fadeToBlack(j, meteorTrailDecay );
      }
    }

    // draw meteor
    for(int j = 0; j < meteorSize; j++) {
      if( ( i-j <NUM_LEDS) && (i-j>=0) ) {
        setPixel(i-j, red, green, blue);
      }
    }

    showStrip();
    delay(SpeedDelay);
  }
}

void fadeToBlack(int ledNo, byte fadeValue) {
 #ifdef ADAFRUIT_NEOPIXEL_H
    // NeoPixel
    uint32_t oldColor;
    uint8_t r, g, b;
    int value;

    oldColor = strip.getPixelColor(ledNo);
    r = (oldColor & 0x00ff0000UL) >> 16;
    g = (oldColor & 0x0000ff00UL) >> 8;
    b = (oldColor & 0x000000ffUL);

    r=(r<=10)? 0 : (int) r-(r*fadeValue/256);
    g=(g<=10)? 0 : (int) g-(g*fadeValue/256);
    b=(b<=10)? 0 : (int) b-(b*fadeValue/256);

    strip.setPixelColor(ledNo, r,g,b);
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   leds[ledNo].fadeToBlackBy( fadeValue );
 #endif
}
/////////////////ここまでが光かたの関数 meteorRain//////////////////////////


//光り方の関数2 Strobe ここから

void Strobe(byte red, byte green, byte blue, int StrobeCount, int FlashDelay, int EndPause){
  for(int j = 0; j < StrobeCount; j++) {
    setAll(red,green,blue);
    showStrip();
    delay(FlashDelay);
    setAll(0,0,0);
    showStrip();
    delay(FlashDelay);
  }

 delay(EndPause);
}
////////////////////////光り方の関数Strobe ここまで///////////////////////////



//値を0-255で入力して,色の値を取得する
//色はred-green-blue-redでサイクルしてる
byte * Wheel(byte WheelPos) {
  static byte c[3];

  if(WheelPos < 85) {
   c[0]=WheelPos * 3;
   c[1]=255 - WheelPos * 3;
   c[2]=0;
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   c[0]=255 - WheelPos * 3;
   c[1]=0;
   c[2]=WheelPos * 3;
  } else {
   WheelPos -= 170;
   c[0]=0;
   c[1]=WheelPos * 3;
   c[2]=255 - WheelPos * 3;
  }

  return c;
}
////////////////////////色と値の関係性の関数記述はここまで//////////////////////


//Neopixelという種類のLEDを使うためおのセットアップ
void showStrip() {
 #ifdef ADAFRUIT_NEOPIXEL_H
   // NeoPixel
   strip.show();
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   FastLED.show();
 #endif
}

void setPixel(int Pixel, byte red, byte green, byte blue) {
 #ifdef ADAFRUIT_NEOPIXEL_H
   // NeoPixel
   strip.setPixelColor(Pixel, strip.Color(red, green, blue));
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   leds[Pixel].r = red;
   leds[Pixel].g = green;
   leds[Pixel].b = blue;
 #endif
}

void setAll(byte red, byte green, byte blue) {
  for(int i = 0; i < NUM_LEDS; i++ ) {
    setPixel(i, red, green, blue);
  }
  showStrip();
}
//////////////////////NeopixelというLEDのセットアップここまで////////////////////
