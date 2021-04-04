#include <Adafruit_NeoPixel.h>//Neopixelという種類のLEDを光らせるためのライブラリ

#define PIN 0 //PIN 0からLEDに信号が送られる,ここではPIN 0に指定すると書かれている
#define NUM_LEDS 10 //LEDの数を指定している,ここでは１10個のLEDを指定すると書かれている
// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
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

  rainbow(20);//虹色
  rainbowCycle(20);//虹色
  theaterChaseRainbow(50);//虹色
}
///////////////////////ここまでがloop関数///////////////////////////////////


//光り方の関数1 rainbow  ここから
void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

/////////////////ここまでが光かたの関数 rainbow //////////////////////////



//光り方の関数2 rainbowCycle  ここから
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}
/////////////////ここまでが光かたの関数 rainbowCycle //////////////////////////

//光り方の関数3 theaterChase,theaterChaseRainboここから
//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
        }
        strip.show();

        delay(wait);

        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}

/////////////////ここまでが光かたの関数 theaterChase,theaterChaseRainbo/////////////////////////
