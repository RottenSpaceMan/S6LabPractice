#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

#define DHTPIN 4

DHT dht(DHTPIN, DHT11);
const char* ssid = "WiFi_Name";
const char* pass = "12345678";
String apikey = "Your_API_Key";
const char* server = "http://api.thingspeak.com/update";

void setup() {
  Serial.begin(115200);
  dht.begin();
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
}

void SendDataToThingSpeak(float t, float h){
    if(WiFi.status() == WL_CONNECTED){
        HTTPClient http;
        String postStr = "apikey=" + apikey + "&field1=" + String(t) + "&field2=" + String(h);
        http.begin(server);
        http.addHeader("Content-Type", "application/x-www-form-urlencoded");
        int httpResponseCode = http.POST(postStr);
        Serial.printf("Temperature: %.2f, Humidity: %.2f\n", t, h);
        Serial.printf("Data sent to ThingSpeak");
        Serial.printf("HTTP Response code: %d\n", httpResponseCode);
        http.end();
    } else{
        Serial.println("WiFi not connected");
    }
}

void loop(){
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    if(isnan(h) || isnan(t)){
        Serial.println("Failed to read from DHT sensor!");
        return;
    }
    SendDataToThingSpeak(t, h);
    delay(15000);
}