//#include <Arduino.h>
#include <U8x8lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif

#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid     = "mobile_hotspot";
const char* password = "pineapple-pen-strawberry-785";

const char* url = "https://smsapi.free-mobile.fr/sendmsg?&user=123456789&pass=PassFree&msg=sms";

U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock=*/ 15, /* data=*/ 4, /* reset=*/ 16);

void setup() {
    u8x8.begin();
    u8x8.setPowerSave(0);
    u8x8.setFont(u8x8_font_chroma48medium8_r);

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
    u8x8.setFont(u8x8_font_chroma48medium8_r);
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin(url);
        int r = http.GET();

        if (r > 0) {
            String payload = http.getString();
            String stringR = String(r);
            Serial.println(r);
            Serial.println(payload);
            u8x8.drawString(1,1, stringR.c_str());	// write something to the internal memory

        } else {
            u8x8.drawString(0,0, "Error on HTTP request");
            Serial.println("Error on HTTP request");
        }
        http.end();
        u8x8.refreshDisplay();		// only required for SSD1606/7
    }
    delay(1000);
}