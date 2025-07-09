
#include <TFT_eSPI.h>
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI();  // Usa la configuración de User_Setup.h

void setup() {
  tft.init();
  tft.setRotation(2);  // Ajustá según la orientación de tu pantalla

  // Colores pastel definidos en formato RGB565
  uint16_t pastelPink = tft.color565(255, 182, 193);   // Light pink
  uint16_t pastelGreen = tft.color565(152, 251, 152);  // Pale green
  uint16_t pastelBlue = tft.color565(173, 216, 230);   // Light blue
  uint16_t pastelYellow = tft.color565(255, 255, 204); // Light yellow

  // Fondo
  tft.fillScreen(pastelYellow);

  // Texto principal
  tft.setTextColor(TFT_BLACK, pastelYellow);
  tft.setTextSize(2);
  tft.setCursor(20, 30);
  tft.println("Hola Pomodoro!");

  // Dibujar cuadros de colores pastel
  tft.fillRoundRect(10, 70, 100, 40, 10, pastelPink);
  tft.setTextColor(TFT_BLACK, pastelPink);
  tft.setCursor(20, 85);
  tft.println("Inicio");

  tft.fillRoundRect(130, 70, 100, 40, 10, pastelGreen);
  tft.setTextColor(TFT_BLACK, pastelGreen);
  tft.setCursor(140, 85);
  tft.println("Pausa");

  tft.fillRoundRect(70, 130, 100, 40, 10, pastelBlue);
  tft.setTextColor(TFT_BLACK, pastelBlue);
  tft.setCursor(80, 145);
  tft.println("Reset");
}

void loop() {
  // Por ahora vacío
}
