// Versión histórica del prototipo (agosto de 2026).
// Incluye LCD 16x2 y buzzer, retirados del montaje el 21/10/2026.

#include <WiFi.h>
#include <WebServer.h>
#include <LiquidCrystal.h>

const char* ssid = "CuradoLadrillos";
const char* password = "12345678";

WebServer server(80);
LiquidCrystal lcd(19, 23, 18, 21, 22, 13);

const int HUMIDITY_PIN = 34;
const int RELAY_PIN = 26;
const int BUTTON_ON_PIN = 25;
const int BUTTON_OFF_PIN = 27;
const int RED_LED_PIN = 32;
const int GREEN_LED_PIN = 33;
const bool RELAY_ACTIVE_LOW = true;
const int VALOR_SECO = 2463;
const int VALOR_HUMEDO = 959;

bool pumpOn = false;
unsigned long pumpStartTime = 0;
unsigned long pumpDuration = 0;
unsigned long lastLcdUpdate = 0;
unsigned long lastButtonRead = 0;

int readHumidityPercent() {
  int raw = analogRead(HUMIDITY_PIN);
  return constrain(map(raw, VALOR_SECO, VALOR_HUMEDO, 0, 100), 0, 100);
}

void writeRelay(bool on) {
  digitalWrite(RELAY_PIN, RELAY_ACTIVE_LOW ? (on ? LOW : HIGH) : (on ? HIGH : LOW));
}

void setPump(bool on) {
  pumpOn = on;
  writeRelay(on);
  digitalWrite(RED_LED_PIN, on ? LOW : HIGH);
  digitalWrite(GREEN_LED_PIN, on ? HIGH : LOW);
  Serial.println(on ? "Rele ACTIVADO" : "Rele APAGADO");
}

unsigned long getRemainingSeconds() {
  if (!pumpOn || pumpDuration == 0) return 0;
  unsigned long elapsed = millis() - pumpStartTime;
  if (elapsed >= pumpDuration) return 0;
  return (pumpDuration - elapsed + 999) / 1000;
}

void updateLcd() {
  lcd.setCursor(0, 0);
  lcd.print("Hum: ");
  lcd.print(readHumidityPercent());
  lcd.print("%       ");
  lcd.setCursor(0, 1);
  if (pumpOn) {
    lcd.print("Riego: ");
    lcd.print(getRemainingSeconds());
    lcd.print("s       ");
  } else {
    lcd.print("Bomba: OFF      ");
  }
}

void startIrrigation(unsigned long durationMs) {
  pumpStartTime = millis();
  pumpDuration = durationMs;
  setPump(true);
  Serial.print("Riego iniciado por ");
  Serial.print(durationMs / 1000);
  Serial.println(" segundos");
}

void stopIrrigation() {
  pumpDuration = 0;
  setPump(false);
  Serial.println("Riego detenido");
}

String htmlPage() {
  int humedad = readHumidityPercent();
  String estado = pumpOn ? "ENCENDIDA" : "APAGADA";
  unsigned long restante = getRemainingSeconds();
  String page = "<!DOCTYPE html><html><head>";
  page += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  page += "<meta http-equiv='refresh' content='1'><title>Curado de Ladrillos</title>";
  page += "<style>body{font-family:Arial;background:#f2f2f2;margin:20px;color:#222;}";
  page += ".box{max-width:420px;margin:auto;background:white;padding:20px;border-radius:8px;}";
  page += "h1{font-size:22px;margin-top:0;}.dato{font-size:20px;margin:12px 0;}";
  page += "button{width:100%;padding:14px;margin:8px 0;font-size:18px;border:0;border-radius:6px;}";
  page += ".on{background:#1f8f4d;color:white;}.off{background:#b3261e;color:white;}";
  page += "</style></head><body><div class='box'><h1>Riego para curado</h1>";
  page += "<div class='dato'>Humedad: <b>" + String(humedad) + "%</b></div>";
  page += "<div class='dato'>Bomba: <b>" + estado + "</b></div>";
  if (pumpOn) page += "<div class='dato'>Tiempo restante: <b>" + String(restante) + " s</b></div>";
  page += "<form action='/regar5'><button class='on'>Regar 5 segundos</button></form>";
  page += "<form action='/regar10'><button class='on'>Regar 10 segundos</button></form>";
  page += "<form action='/regar20'><button class='on'>Regar 20 segundos</button></form>";
  page += "<form action='/apagar'><button class='off'>Apagar ahora</button></form>";
  page += "<p>Boton fisico ON: riego 5s</p><p>Boton fisico OFF: apagado inmediato</p>";
  return page + "</div></body></html>";
}

void handleRoot() { server.send(200, "text/html", htmlPage()); }

void redirectHome() {
  server.sendHeader("Location", "/");
  server.send(303);
}

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUTTON_ON_PIN, INPUT_PULLUP);
  pinMode(BUTTON_OFF_PIN, INPUT_PULLUP);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  setPump(false);

  lcd.begin(16, 2);
  lcd.print("Curado ladrillo");
  lcd.setCursor(0, 1);
  lcd.print("Iniciando...");

  WiFi.softAP(ssid, password);
  Serial.print("IP: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);
  server.on("/regar5", []() { startIrrigation(5000); redirectHome(); });
  server.on("/regar10", []() { startIrrigation(10000); redirectHome(); });
  server.on("/regar20", []() { startIrrigation(20000); redirectHome(); });
  server.on("/apagar", []() { stopIrrigation(); redirectHome(); });
  server.begin();
  updateLcd();
}

void loop() {
  server.handleClient();

  if (pumpOn && pumpDuration > 0 && millis() - pumpStartTime >= pumpDuration) stopIrrigation();

  if (millis() - lastButtonRead > 250) {
    if (digitalRead(BUTTON_ON_PIN) == LOW) {
      lastButtonRead = millis();
      if (!pumpOn) startIrrigation(5000);
    }
    if (digitalRead(BUTTON_OFF_PIN) == LOW) {
      lastButtonRead = millis();
      if (pumpOn) stopIrrigation();
    }
  }

  if (millis() - lastLcdUpdate >= 1000) {
    lastLcdUpdate = millis();
    updateLcd();
  }
}
