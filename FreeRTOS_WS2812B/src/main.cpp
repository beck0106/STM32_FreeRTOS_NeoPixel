#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN   PB6
#define LED_COUNT 16

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void ledTask(void *pvParameters) {
    uint8_t hue = 0;

    while (1) {
        for (int i = 0; i < strip.numPixels(); i++) {
            uint32_t color = strip.ColorHSV((hue + (i * 65536L / strip.numPixels())) % 65536, 255, 255);
            strip.setPixelColor(i, color);
        }
        strip.show();
        hue += 256;
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void setup() {
    strip.begin();
    strip.show(); // apaga todos los LEDs
    xTaskCreate(ledTask, "LEDTask", 128, NULL, 1, NULL);
}

void loop() {
    // Nada que hacer aquí
}
