
#include <ESPAsyncWebSrv.h>

#include <WiFi.h>




const char *ssid = "Vodafone-SMMF";
const char *password = "Malloppo1980$";
IPAddress staticIP(192, 168, 1, 52);   // Imposta l'indirizzo IP statico desiderato
IPAddress gateway(192, 168, 1, 1);      // Gateway predefinito della tua LAN
IPAddress subnet(255, 255, 255, 0);     // Maschera di sottorete della tua LAN


const int ledPin = 21; // Definisci il pin del LED
bool ledState = false; // Stato corrente del LED
bool isBlinking = false; // Stato corrente del lampeggio del LED
unsigned long previousMillis = 0;
const long interval = 500;

// Crea un'istanza del server web Async
AsyncWebServer server(80);

void setup() {
  // Inizializza il LED come output
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // Spegni il LED all'avvio

  // Connetti l'ESP32 alla rete WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connessione WiFi in corso...");
  }
  Serial.println("Connesso alla rete WiFi");

  // Gestione delle richieste HTTP
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    String html = "<html><head><style>";
    html += "body { font-family: Arial, sans-serif; margin: 20px; }";
    html += "button { padding: 10px 20px; font-size: 16px; }";
    html += "</style></head><body>";
    html += "<h1>Controllo LED</h1>";
    html += "<p>Stato del LED: <span id='ledStatus'>" + String(ledState ? "Acceso" : "Spento") + "</span></p>";
    html += "<button onclick='toggleLED()'>Cambia Stato LED</button>";
    html += "<button onclick='blinkLED()'>Lampeggia LED</button>";
    html += "<script>";
    html += "function toggleLED() {";
    html += "  fetch('/toggle')";
    html += "    .then(response => response.text())";
    html += "    .then(data => {";
    html += "      document.getElementById('ledStatus').innerText = data;";
    html += "    });";
    html += "}";
    html += "function blinkLED() {";
    html += "  fetch('/blink')";
    html += "    .then(response => response.text())";
    html += "    .then(data => {";
    html += "      document.getElementById('ledStatus').innerText = data;";
    html += "    });";
    html += "}";
    html += "</script>";
    html += "</body></html>";
    request->send(200, "text/html", html);
  });

  // Funzione per cambiare lo stato del LED
  server.on("/toggle", HTTP_GET, [](AsyncWebServerRequest *request){
    toggleLED();
    String response = ledState ? "Acceso" : "Spento";
    request->send(200, "text/plain", response);
  });

  // Funzione per far lampeggiare il LED
  server.on("/blink", HTTP_GET, [](AsyncWebServerRequest *request){
    blinkLED();
    String response = "LED sta lampeggiando";
    request->send(200, "text/plain", response);
  });

  // Avvia il server web
  server.begin();
}

void loop() {
  unsigned long currentMillis = millis();

  if (isBlinking && currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    digitalWrite(ledPin, !digitalRead(ledPin)); // Inverti lo stato del LED
  }
}

void toggleLED() {
  isBlinking = false; // Ferma il lampeggio del LED
  ledState = !ledState;
  digitalWrite(ledPin, ledState ? HIGH : LOW);
}

void blinkLED() {
  isBlinking = true; // Inizia il lampeggio del LED
  previousMillis = millis();
}
