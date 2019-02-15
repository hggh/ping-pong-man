#include <Arduino.h>
#include <FastLED.h>
#include <Bounce2.h>

const static CRGB::HTMLColorCode colors[35] = {
  CRGB::Crimson,
  CRGB::Red,
  CRGB::DeepPink,
  CRGB::OrangeRed,
  CRGB::SkyBlue,
  CRGB::Orange,
  CRGB::Gold,
  CRGB::Yellow,
  CRGB::DarkRed,
  CRGB::Violet,
  CRGB::Navy,
  CRGB::Fuchsia,
  CRGB::RosyBrown,
  CRGB::MediumOrchid,
  CRGB::BlueViolet,
  CRGB::Indigo,
  CRGB::DarkSlateBlue,
  CRGB::GreenYellow,
  CRGB::Purple,
  CRGB::Lime,
  CRGB::MediumSpringGreen,
  CRGB::ForestGreen,
  CRGB::CadetBlue,
  CRGB::DarkGreen,
  CRGB::LightSeaGreen,
  CRGB::Teal,
  CRGB::Cyan,
  CRGB::SteelBlue,
  CRGB::Blue,
  CRGB::Brown,
  CRGB::DarkBlue,
  CRGB::Chocolate,
  CRGB::SaddleBrown,
  CRGB::Maroon,
  CRGB::DarkSlateGray
};


CRGB leds[1];
Bounce debouncer = Bounce();
#define DIRECTION_UP 1
#define DIRECTION_DOWN 0
#define PIN_RGB_LED 0
#define PIN_BUTTON 2

volatile uint8_t brightness = 0;
volatile uint8_t hold = 0;
volatile short direction = DIRECTION_UP;
volatile uint8_t color_index = 0;

// called every ~ 35ms
ISR(TIMER1_COMPA_vect) {
	if (brightness < 5 && hold < 6) {
		hold++;
		return;
	}
	hold = 0;
	if (brightness > 200) {
		direction = DIRECTION_DOWN;
	}
	if (brightness < 5) {
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
	FastLED.addLeds<PL9823, PIN_RGB_LED>(leds, 1);
	leds[0] = CRGB::Blue;
	for (short i = 255; i > 0; i--) {
		FastLED.setBrightness(i);
		FastLED.show();
		delay(10);
	}
	delay(15);
	FastLED.setBrightness(0);
	FastLED.clear(true);
	FastLED.show();

	leds[0] = CRGB::Red;
	TCCR1 |= (1 << CTC1);
	TCCR1 |= (1 << CS13) | (1 << CS11) | (1 << CS10);
	OCR1C = 280;
	TIMSK |= (1 << OCIE1A);

	pinMode(PIN_BUTTON, INPUT_PULLUP);

	debouncer.attach(PIN_BUTTON);
	debouncer.interval(20);
}



void loop() {
	debouncer.update();
	FastLED.setBrightness(brightness);
	FastLED.show();

	if (debouncer.fell()) {
		color_index += 1;
		if (color_index > 34) {
			color_index = 0;
		}
		leds[0] = colors[color_index];
	}
}
