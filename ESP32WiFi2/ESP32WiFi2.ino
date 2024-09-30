#include <ESPAsyncWebSrv.h>

#include <WiFi.h>

const char *ssid = "TIM-18417049";
const char *password = "aN5GXwlef2uCEG6s0VO2Kk9t";

//const char *ssid = "WiFi Nonna";
//const char *password = "lenticchiaefagiolo21$";

//const char *ssid = "Vodafone-SMMF";
//const char *password = "Malloppo1980$";
IPAddress staticIP(192, 168, 1, 52);   // Imposta l'indirizzo IP statico desiderato
IPAddress gateway(192, 168, 1, 1);      // Gateway predefinito della tua LAN
IPAddress subnet(255, 255, 255, 0);     // Maschera di sottorete della tua LAN

const int ledPins[] = {27, 26, 25, 33};
int currentStep = 0;

AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);
  // Inizializza i pin dei LED come OUTPUT
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  // Connetti ESP32 alla rete WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connessione WiFi in corso...");
  }
  Serial.println("Connessione WiFi stabilita");
  WiFi.config(staticIP, gateway, subnet);
  // Visualizza l'indirizzo IP assegnato
  Serial.print("Indirizzo IP: ");
  Serial.println(WiFi.localIP());

  // Gestione delle richieste HTTP
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    String html = "<html><head>";
    html += "<style>";
    html += "body { display: flex; justify-content: center; align-items: center; height: 100vh; margin: 0; }";
    html += "h1 { text-align: center; }";
    html += "a { text-decoration: none; }";
    html += "button { font-size: 24px; }";
    html += "div.progress-container { width: 300px; height: 30px; border: 1px solid black;}";
    html += "div.progress-bar { height: 100%; background-color: green; transition: width 0.5s; }";
    html += "</style>";
    html += "</head><body>";
    html += "<h1>Controllo LED</h1>";
    html += "<a href='/left'><button><-</button></a>";
    html += "<div class='progress-container'>";
    html += "<div class='progress-bar' style='width: " + String(currentStep * 25) + "%;'></div>";
    html += "</div>";
    html += "<a href='/right'><button>-></button></a>";
    html += "</body></html>";
    request->send(200, "text/html", html);
  });

  server.on("/right", HTTP_GET, [](AsyncWebServerRequest *request){
    if (currentStep < 4) {
      currentStep++;
      updateLEDs();
    }
    request->redirect("/");
  });

  server.on("/left", HTTP_GET, [](AsyncWebServerRequest *request){
    if (currentStep > 0) {
      currentStep--;
      updateLEDs();
    }
    request->redirect("/");
  });

  // Inizia il server
  server.begin();
}

void loop() {
}


void updateLEDs() {
  static unsigned long previousMillis = 0;
  static int step = -1;
  static bool ledState = LOW;
  unsigned long currentMillis = millis();
  const unsigned long interval = 500;

  if (step != currentStep) {
    step = currentStep;
    previousMillis = currentMillis;
    ledState = LOW;
  }

  for (int i = 0; i < 4; i++) {
    digitalWrite(ledPins[i], i < currentStep ? HIGH : LOW);
  }

  if ((currentStep == 0 || currentStep == 4) && (currentMillis - previousMillis >= interval)) {
    previousMillis = currentMillis;
    ledState = !ledState;
    for (int j = 0; j < 4; j++) {
      digitalWrite(ledPins[j], ledState);
    }
  }
}




//void updateLEDs() {
//  for (int i = 0; i < 4; i++) {
//    digitalWrite(ledPins[i], i < currentStep ? HIGH : LOW);
//  }
//  if (currentStep == 0) {
//    // Lampeggia tutti i LED
//    for (int i = 0; i < 2; i++) {
//      for (int j = 0; j < 4; j++) {
//        digitalWrite(ledPins[j], HIGH);
//      }
//      delay(500);
//      for (int j = 0; j < 4; j++) {
//        digitalWrite(ledPins[j], LOW);
//      }
//      delay(500);
//    }
//  }
//  if (currentStep == 4) {
//    // Lampeggia tutti i LED
//    for (int i = 0; i < 2; i++) {
//      for (int j = 0; j < 4; j++) {
//        digitalWrite(ledPins[j], HIGH);
//      }
//      delay(500);
//      for (int j = 0; j < 4; j++) {
//        digitalWrite(ledPins[j], LOW);
//      }
//      delay(500);
//    }
//    for (int i = 0; i < 4; i++) {
//      digitalWrite(ledPins[i], HIGH);
//    }
//  }
//}
