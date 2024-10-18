#include "FastLED.h"

#define NUM_LEDS 13    // Set the number of LEDs to 13
#define LED_PIN 5      // LED strip connected to pin 5
#define BRIGHTNESS 50  // Set brightness to 50

CRGB leds[NUM_LEDS];

// State variable to track the current mode (color transitions)
char currentMode = 'b';  // 'b' for blue, 'r' for red, 'g' for green, 't' for turquoise, 'o' for orange, 'y' for yellow, 's' for rainbow

// Number of LEDs to light up (initially all 13)
int ledsToLight = NUM_LEDS;

void setup() {
    Serial.begin(115200);  // Initialize serial communication
    FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(BRIGHTNESS);

    Serial.println("Type 'b' for blue, 'r' for red, 'g' for green, 't' for turquoise, 'o' for orange, 'y' for yellow, 's' for rainbow effect");
    Serial.println("Also type a number from 1 to 13 to set how many LEDs are lit.");
}

// Function to transition from any color to white and back
void colorToWhiteTransition(CRGB color, float speedFactor) {
    unsigned long currentTime = millis();
    float progress = (sin(currentTime / speedFactor * PI) + 1.0) / 2.0;
    CRGB currentColor = blend(color, CRGB(255, 255, 255), progress * 255);

    for (int i = 0; i < ledsToLight; i++) {
        leds[i] = currentColor;
    }

    // Turn off the rest of the LEDs
    for (int i = ledsToLight; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Black;
    }

    FastLED.show();
}

// Function to display rainbow colors across all LEDs
void rainbowEffect() {
    // Step through the rainbow for each LED one at a time
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CHSV((i * 256 / NUM_LEDS), 255, 255);  // Set each LED to a rainbow color
        FastLED.show();
        delay(200);  // Delay to give a nice effect as each LED lights up
    }
}

// Function to switch modes based on input
void loop() {
    // Check if there's serial input available
    if (Serial.available() > 0) {
        // Read the incoming input
        String input = Serial.readStringUntil('\n');  // Read the entire input until newline

        // Check if the input is a number to set the number of LEDs to light up
        int inputNumber = input.toInt();  // Convert input to an integer
        if (inputNumber >= 1 && inputNumber <= 13) {
            ledsToLight = inputNumber;
            Serial.print("Now lighting ");
            Serial.print(ledsToLight);
            Serial.println(" LEDs.");
        } else {
            // Change the mode based on the input (color change or rainbow effect)
            char mode = input.charAt(0);  // Take the first character
            if (mode == 'b') {
                currentMode = 'b';  // Blue to white
                Serial.println("Switched to blue-to-white transition.");
            } else if (mode == 'r') {
                currentMode = 'r';  // Red to white
                Serial.println("Switched to red-to-white transition.");
            } else if (mode == 'g') {
                currentMode = 'g';  // Green to white
                Serial.println("Switched to green-to-white transition.");
            } else if (mode == 't') {
                currentMode = 't';  // Turquoise to white
                Serial.println("Switched to turquoise-to-white transition.");
            } else if (mode == 'o') {
                currentMode = 'o';  // Orange to white
                Serial.println("Switched to orange-to-white transition.");
            } else if (mode == 'y') {
                currentMode = 'y';  // Yellow to white
                Serial.println("Switched to yellow-to-white transition.");
            } else if (mode == 's') {
                currentMode = 's';  // Rainbow effect
                Serial.println("Switched to rainbow effect.");
                rainbowEffect();  // Start the rainbow effect
            }
        }
    }

    // Perform the transition based on the current mode
    if (currentMode == 'b') {
        colorToWhiteTransition(CRGB(0, 0, 255), 4000.0);  // Blue to white
    } else if (currentMode == 'r') {
        colorToWhiteTransition(CRGB(255, 0, 0), 4000.0);  // Red to white
    } else if (currentMode == 'g') {
        colorToWhiteTransition(CRGB(0, 255, 0), 4000.0);  // Green to white
    } else if (currentMode == 't') {
        colorToWhiteTransition(CRGB(64, 224, 208), 4000.0);  // Turquoise to white
    } else if (currentMode == 'o') {
        colorToWhiteTransition(CRGB(255, 165, 0), 4000.0);  // Orange to white
    } else if (currentMode == 'y') {
        colorToWhiteTransition(CRGB(255, 255, 0), 4000.0);  // Yellow to white
    }

    // Small delay for smooth animation
    delay(10);
}
