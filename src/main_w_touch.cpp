#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>
#include "kafkar_logo.h"

// Instancias
TFT_eSPI tft = TFT_eSPI();

#define XPT2046_IRQ 36
#define XPT2046_MOSI 32
#define XPT2046_MISO 39
#define XPT2046_CLK 25
#define XPT2046_CS 33

SPIClass touchscreenSPI = SPIClass(VSPI);
XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320
#define FONT_SIZE 2

// Estados de pantalla
enum PantallaEstado {
  PANTALLA_BIENVENIDA,
  PANTALLA_PRINCIPAL
};
PantallaEstado pantallaActual = PANTALLA_BIENVENIDA;

// Variables globales
int posX, posY, pressure;
int centerX, centerY;

void logTouchData(int posX, int posY, int pressure)
{
  Serial.print("X = ");
  Serial.print(posX);
  Serial.print(" | Y = ");
  Serial.print(posY);
  Serial.print(" | Pressure = ");
  Serial.print(pressure);
  Serial.println();
}

void displayTouchData(int posX, int posY, int pressure)
{
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  int textY = 100;
  String text = "X = " + String(posX) + " Y = " + String(posY);
  tft.drawCentreString(text, centerX, textY, FONT_SIZE);

  textY += 20;
  text = "Pressure = " + String(pressure);
  tft.drawCentreString(text, centerX, textY, FONT_SIZE);

  tft.drawCentreString("Prueba TOUCH", centerX, 280, FONT_SIZE);

  tft.fillSmoothCircle(posX, posY, pressure / 200, TFT_RED);
}

void mostrarPantallaPrincipal()
{
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.drawCentreString("Pantalla Principal", centerX, 30, FONT_SIZE);

  // Aquí podés dibujar elementos propios del modo principal
}

void setup()
{
  Serial.begin(115200);

  touchscreenSPI.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
  touchscreen.begin(touchscreenSPI);
  touchscreen.setRotation(2);

  tft.init();
  tft.setRotation(2);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  centerX = SCREEN_WIDTH / 2;
  centerY = SCREEN_HEIGHT / 2;

  // Pantalla de bienvenida
  tft.drawCentreString("Hola perrito!", centerX, 30, FONT_SIZE);
  tft.drawCentreString("Toca para comenzar", centerX, 280, FONT_SIZE);

  int x = (tft.width() - 116) / 2;
  int y = (tft.height() - 110) / 2;
  tft.drawBitmap(x, y, bitmap_kafkar_logo, 116, 100, TFT_WHITE);
}

void loop()
{
  if (pantallaActual == PANTALLA_BIENVENIDA)
  {
    if (touchscreen.tirqTouched() && touchscreen.touched())
    {
      TS_Point p = touchscreen.getPoint();
      posX = map(p.x, 200, 3700, 1, SCREEN_WIDTH);
      posY = map(p.y, 240, 3800, 1, SCREEN_HEIGHT);
      pressure = p.z;

      logTouchData(posX, posY, pressure);

      pantallaActual = PANTALLA_PRINCIPAL;
      mostrarPantallaPrincipal();

      delay(100);
    }
  }
  else if (pantallaActual == PANTALLA_PRINCIPAL)
  {
    // Aquí podés seguir desarrollando la lógica de la pantalla principal
    // Por ejemplo, detectar toques para botones, mostrar datos, etc.
  }
}
