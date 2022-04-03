/** Beispiel Abfrage Cloud Dienst Sunrise / Sunset
 */
#include "MFRC522.h"
#include "MbedJSONValue.h"
#include "OLEDDisplay.h"
#include "http_request.h"
#include "mbed.h"
#include <cstdio>
#include <cstring>
#include <string>

#define SS_PIN 10
#define RST_PIN 9

// UI
OLEDDisplay oled(MBED_CONF_IOTKIT_OLED_RST, MBED_CONF_IOTKIT_OLED_SDA,
                 MBED_CONF_IOTKIT_OLED_SCL);

MFRC522 rfidReader(MBED_CONF_IOTKIT_RFID_MOSI, MBED_CONF_IOTKIT_RFID_MISO,
                   MBED_CONF_IOTKIT_RFID_SCLK, MBED_CONF_IOTKIT_RFID_SS,
                   MBED_CONF_IOTKIT_RFID_RST);

// I/O Buffer
char message[6000];

char body[1024];

// DigitalOut myled(MBED_CONF_IOTKIT_LED1);

int main() {
  oled.clear();

  oled.printf("Starting Wifi Interface\n");
  WiFiInterface *network = WiFiInterface::get_default_instance();
  if (!network) {
    printf("ERROR: No WiFiInterface found.\n");
    return -1;
  }

  printf("\nConnecting to %s...\n", MBED_CONF_APP_WIFI_SSID);
  int ret =
      network->connect(MBED_CONF_APP_WIFI_SSID, MBED_CONF_APP_WIFI_PASSWORD,
                       NSAPI_SECURITY_WPA_WPA2);

  if (ret != 0) {
    printf("\nConnection error: %d\n", ret);
    return -1;
  }

  printf("Success\n\n");
  printf("MAC: %s\n", network->get_mac_address());
  SocketAddress a;
  network->get_ip_address(&a);
  printf("IP: %s\n", a.get_ip_address());

  oled.clear();
  oled.printf("RFID Scanner\n");
  rfidReader.PCD_Init();

  while (1) {
    if (rfidReader.PICC_IsNewCardPresent()) {
      if (rfidReader.PICC_ReadCardSerial()) {
        oled.cursor(1, 0);
        oled.printf("UID: ");
        
        char buf[1024];

        for (int i = 0; i < rfidReader.uid.size; i++){
            oled.printf("%02X:", rfidReader.uid.uidByte[i]);
            }
        oled.printf("\r\n");

        // Print Card type
        int piccType = rfidReader.PICC_GetType(rfidReader.uid.sak);
        oled.printf("PICC Type: %s \r\n", rfidReader.PICC_GetTypeName(piccType));

        HttpRequest *post_req = new HttpRequest(network, HTTP_POST, "http://104.238.130.64:5000/");
        post_req->set_header("Content-Type", "application/json");
         
        sprintf(body, "{\"uid\": \"%02X:%02X:%02X:%02X:\"}", rfidReader.uid.uidByte[0], rfidReader.uid.uidByte[1], rfidReader.uid.uidByte[2], rfidReader.uid.uidByte[3]);

        HttpResponse *get_res = post_req->send(body, strlen(body));

       if (get_res) {
          MbedJSONValue parser;
          
          parse(parser, get_res->get_body_as_string().c_str());

        } else {
          printf("HttpRequest failed (error code %d)\n", post_req->get_error());
          return 1;
        }
        delete post_req;
      }
    }
    thread_sleep_for(200);
  }
}
