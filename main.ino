#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid     = "mobile_hotspot";
const char* password = "pineapple-pen-strawberry-785";

const char* url = "https://smsapi.free-mobile.fr/sendmsg?&user=123456789&pass=PassFree&msg=sms";

void setup() {

    Serial.begin(115200);
    delay(4000);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print("Connecting to WiFi..");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void loop() {
      if (WiFi.status() == WL_CONNECTED) {
          HTTPClient http;
          http.begin(url);
          int r = http.GET();

          if (r > 0) {
            String payload = http.getString();
            Serial.println(r);
            Serial.println(payload);
          } else {
            Serial.println("Error on HTTP request");
          }
          http.end();
      }
      delay(1000);
}