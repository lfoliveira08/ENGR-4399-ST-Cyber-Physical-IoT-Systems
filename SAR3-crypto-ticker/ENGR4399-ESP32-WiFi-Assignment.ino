/*
 * ENGR 4399 - Simulation Assignment 3: ESP32 WiFi, APIs, and Cloud Data
 * Project: ESP32 Cryptocurrency Price Ticker (Wokwi)
 *
 * - Connects to the Wokwi-GUEST WiFi network (no password)
 * - HTTPS GET to the free CoinGecko API (no key) -> JSON prices + 24 h change
 * - Parses JSON with ArduinoJson, builds a JSON status report
 * - Input : push button (cycle coin: BTC -> ETH -> SOL)
 * - Output: 16x2 I2C LCD, green/red LEDs, Serial Monitor
 *
 * Pins: BTN=GPIO15 (INPUT_PULLUP), GREEN=GPIO26, RED=GPIO27, SDA=GPIO21, SCL=GPIO22
 * Libraries (Wokwi libraries.txt): ArduinoJson, LiquidCrystal I2C
 */
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const char* WIFI_SSID = "Wokwi-GUEST";
const char* WIFI_PASS = "";

// One request returns all three coins
const char* API_URL =
  "https://api.coingecko.com/api/v3/simple/price"
  "?ids=bitcoin,ethereum,solana&vs_currencies=usd&include_24hr_change=true";

const int PIN_BTN   = 15;
const int PIN_GREEN = 26;
const int PIN_RED   = 27;

const int NUM_COINS = 3;
const char* COIN_ID[NUM_COINS]  = {"bitcoin", "ethereum", "solana"};
const char* COIN_SYM[NUM_COINS] = {"BTC", "ETH", "SOL"};

float price[NUM_COINS];
float change24h[NUM_COINS];
bool  haveData = false;
int   selected = 0;

const unsigned long AUTO_REFRESH_MS = 60000;  // respect API rate limit
const unsigned long DEBOUNCE_MS     = 50;
unsigned long lastFetch = 0, lastPress = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void connectWiFi() {
  lcd.clear(); lcd.print("WiFi connecting");
  Serial.printf("Connecting to %s", WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASS, 6);  // channel 6 speeds up Wokwi connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
  }
  Serial.printf("\nConnected! IP: %s\n", WiFi.localIP().toString().c_str());
  lcd.clear(); lcd.print("WiFi connected");
}

void showCoin() {
  if (!haveData) return;
  char l1[17], l2[17];
  snprintf(l1, sizeof(l1), "%s $%.2f", COIN_SYM[selected], price[selected]);
  snprintf(l2, sizeof(l2), "24h %+.2f%% %s", change24h[selected],
           change24h[selected] >= 0 ? "UP" : "DN");
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print(l1);
  lcd.setCursor(0, 1); lcd.print(l2);
  bool up = change24h[selected] >= 0;
  digitalWrite(PIN_GREEN, up ? HIGH : LOW);
  digitalWrite(PIN_RED,   up ? LOW : HIGH);
}

bool fetchPrices() {
  if (WiFi.status() != WL_CONNECTED) connectWiFi();

  WiFiClientSecure client;
  client.setInsecure();  // simulation only: skips certificate validation
  HTTPClient http;
  http.begin(client, API_URL);

  Serial.println("\n[HTTP] GET CoinGecko ...");
  int code = http.GET();
  Serial.printf("[HTTP] Status code: %d\n", code);
  if (code != HTTP_CODE_OK) {
    Serial.println("[HTTP] Request failed (rate limit or network).");
    http.end();
    return false;
  }
  String payload = http.getString();
  http.end();

  // ---- Parse incoming JSON ----
  JsonDocument doc;
  DeserializationError err = deserializeJson(doc, payload);
  if (err) {
    Serial.printf("[JSON] Parse error: %s\n", err.c_str());
    return false;
  }
  for (int i = 0; i < NUM_COINS; i++) {
    price[i]     = doc[COIN_ID[i]]["usd"];
    change24h[i] = doc[COIN_ID[i]]["usd_24h_change"];
  }
  haveData = true;

  // ---- Construct outgoing JSON (what would be pushed to a cloud service) ----
  JsonDocument out;
  out["device"] = "esp32-ticker-01";
  out["uptime_s"] = millis() / 1000;
  JsonArray arr = out["coins"].to<JsonArray>();
  for (int i = 0; i < NUM_COINS; i++) {
    JsonObject c = arr.add<JsonObject>();
    c["symbol"]     = COIN_SYM[i];
    c["usd"]        = price[i];
    c["change_24h"] = change24h[i];
    c["trend"]      = change24h[i] >= 0 ? "up" : "down";
  }
  Serial.println("[JSON] Parsed prices:");
  for (int i = 0; i < NUM_COINS; i++)
    Serial.printf("  %s : $%.2f (%+.2f%% 24h)\n", COIN_SYM[i], price[i], change24h[i]);
  Serial.print("[JSON] Report: ");
  serializeJson(out, Serial);
  Serial.println();
  return true;
}

void setup() {
  Serial.begin(115200);
  pinMode(PIN_BTN, INPUT_PULLUP);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_RED, OUTPUT);
  Wire.begin(21, 22);
  lcd.init(); lcd.backlight();
  lcd.print("Crypto Ticker");
  connectWiFi();
  if (fetchPrices()) showCoin();
  lastFetch = millis();
}

void loop() {
  // Debounced button: press = next coin
  if (digitalRead(PIN_BTN) == LOW && millis() - lastPress > DEBOUNCE_MS) {
    lastPress = millis();
    selected = (selected + 1) % NUM_COINS;
    Serial.printf("[BTN] Selected %s\n", COIN_SYM[selected]);
    showCoin();
    while (digitalRead(PIN_BTN) == LOW) delay(5);
  }
  if (millis() - lastFetch >= AUTO_REFRESH_MS) {
    lastFetch = millis();
    if (fetchPrices()) showCoin();
  }
}
