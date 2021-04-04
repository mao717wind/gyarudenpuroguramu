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
  Sparkle(0xff, 0xff, 0xff, 50);//白
  Sparkle(0xff, 0x00, 0xff, 50);//ピンク
  Sparkle(0x00, 0xff, 0xff, 50);//ブルー
  Sparkle(0xff, 0xff, 0x00, 50);//黄色
 }
///////////////////////ここまでがloop関数///////////////////////////////////

//光り方の関数1 Sparkle ここから

void Sparkle(byte red, byte green, byte blue, int SpeedDelay) {
  int Pixel = random(NUM_LEDS);
  setPixel(Pixel,red,green,blue);
  showStrip();
  delay(SpeedDelay);
  setPixel(Pixel,0,0,0);
}


/////////////////ここまでが光かたの関数 Sparkle//////////////////////////



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
