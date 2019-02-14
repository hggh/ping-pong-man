#include <Arduino.h>
#include <FastLED.h>

const static CRGB::HTMLColorCode colors[35] = {
  CRGB::Crimson,
  CRGB::Red,
  CRGB::DarkRed,
  CRGB::DeepPink,
  CRGB::OrangeRed,
  CRGB::Orange,
  CRGB::Gold,
  CRGB::Yellow,
  CRGB::Violet,
  CRGB::Navy,
  CRGB::RosyBrown,
  CRGB::Fuchsia,
  CRGB::MediumOrchid,
  CRGB::BlueViolet,
  CRGB::Purple,
  CRGB::Indigo,
  CRGB::DarkSlateBlue,
  CRGB::GreenYellow,
  CRGB::Lime,
  CRGB::MediumSpringGreen,
  CRGB::ForestGreen,
  CRGB::DarkGreen,
  CRGB::LightSeaGreen,
  CRGB::Teal,
  CRGB::Cyan,
  CRGB::CadetBlue,
  CRGB::SteelBlue,
  CRGB::SkyBlue,
  CRGB::Blue,
  CRGB::DarkBlue,
  CRGB::Chocolate,
  CRGB::SaddleBrown,
  CRGB::Maroon,
  CRGB::DarkSlateGray,
  CRGB::Brown
};


CRGB leds[1];
#define DIRECTION_UP 1
#define DIRECTION_DOWN 0

volatile uint8_t brightness = 0;
volatile uint8_t hold = 0;
volatile short direction = DIRECTION_UP;

ISR(TIMER1_COMPA_vect) {
	if (brightness < 10 && hold < 2) {
		hold++;
		return;
	}
	hold = 0;
	if (brightness > 200) {
		direction = DIRECTION_DOWN;
	}
	if (brightness < 10) {
		direction = DIRECTION_UP;
	}

	if (direction == DIRECTION_UP) {
		if (brightness > 140) {
			brightness +=5;
		}
		else {
			brightness += 2;
		}
	}
	else {
		if (brightness > 140) {
			brightness -=5;
		}
		else {
			brightness -= 2;
		}
	}
}


void setup() {
	FastLED.addLeds<PL9823, 3>(leds, 1);
	FastLED.setBrightness(0);
	FastLED.clear(true);
	FastLED.show();

	leds[0] = colors[random(34)];

	TCCR1 |= (1 << CTC1);
	TCCR1 |= (1 << CS13) | (1 << CS11) | (1 << CS10);
	OCR1C = 280;
	TIMSK |= (1 << OCIE1A);
}



void loop() {
	FastLED.setBrightness(brightness);
	FastLED.show();
}
