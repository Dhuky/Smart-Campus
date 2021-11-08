#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ssl_client.h>
#include <EmonLib.h>
#include <WiFi.h>

const char* ssid = "Newbie-on_2.4 GHz";
const char* password = "9373Aa@3";

#define ORG "o17xcd"
#define DEVICE_TYPE "esp32s-teste"
#define DEVICE_ID "ID001"
#define TOKEN "tFg9T-SbK*(AD-0Ex)"

char Server[] = ORG ".messaging.internetofthings.ibmcloud.com";
char pubTopic1[] = "iot-2/evt/status/fmt/json";
char pubTopic2[] = "iot-2/evt/status/fmt/json";
char pubTopic3[] = "iot-2/evt/status/fmt/json";
char pubTopic4[] = "iot-2/evt/status/fmt/json";
char pubTopic5[] = "iot-2/evt/status/fmt/json";
char pubTopic6[] = "iot-2/evt/status/fmt/json";
char AuthMethod[] = "use-token-auth";
char Tokem[] = TOKEN;
char ClientId[] = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;

int intervalo_medidas = 60000;
long proxima_medida;

#define VOLT_CAL 83.65
EnergyMonitor emon1;
EnergyMonitor emon2;
EnergyMonitor emon3;

EnergyMonitor SCT1;
EnergyMonitor SCT2;
EnergyMonitor SCT3;

float faseR = 34;
float faseS = 35;
float faseT = 32;

int correnteR= 15; 
int correnteS= 2;
int correnteT= 0;

WiFiClient wifiClient;
PubSubClient client (Server, 1883, NULL, wifiClient);

void setup() {

  emon1.voltage(34, VOLT_CAL, 1.7);
  emon2.voltage(35, VOLT_CAL, 1.7);
  emon3.voltage(32, VOLT_CAL, 1.7);

  SCT1.current(correnteR, 1.362 );
  SCT2.current(correnteS, 1.362 );
  SCT3.current(correnteT, 1.362 );
  
  Serial.begin(115200);
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Wifi connected, IP address: ");
  Serial.print(WiFi.localIP());
  Serial.println();

  if (!!!client.connected()) {
    Serial.print("Reconnecting client to ");
    Serial.println (Server);
    while (!!!client.connect(ClientId, AuthMethod, Tokem)) {
      Serial.print (".");
      delay(500);
    }
    Serial.println();
  }
}

void loop() {
  client.loop();
  emon1.calcVI(60, 2000);
  emon2.calcVI(60, 2000);
  emon3.calcVI(60, 2000);
  
  faseR = emon1.Vrms;
  faseS = emon2.Vrms;
  faseT = emon3.Vrms;

  double Irms1 = SCT1.calcIrms ( 1480 ); 
  double Irms2 = SCT2.calcIrms ( 1480 );
  double Irms3 = SCT3.calcIrms ( 1480 ); 

if (millis() > proxima_medida) {
  
  String payload = "{\"d\":{\"Name\":\"" DEVICE_ID "\"";
  payload += ",\"Fase_R\":";
  payload += faseR;
  payload += "}}";
  Serial.print("Sending payload: ");
  Serial.println(payload);
  if (client.publish(pubTopic1, (char*) payload.c_str())) {
    Serial.println("Publish ok");
  } else {
    Serial.println("Publish failed");
  }
  
  String payload1 = "{\"d\":{\"Name\":\"" DEVICE_ID "\"";
  payload1 += ",\"Fase_S\":";
  payload1 += faseS;
  payload1 += "}}";
  Serial.print("Sending payload1: ");
  Serial.println(payload1);
  if (client.publish(pubTopic2, (char*) payload1.c_str())) {
    Serial.println("Publish ok");
  } else {
    Serial.println("Publish failed");
  }
  
  String payload2 = "{\"d\":{\"Name\":\"" DEVICE_ID "\"";
  payload2 += ",\"Fase_T\":";
  payload2 += faseT;
  payload2 += "}}";
  Serial.print("Sending payload2: ");
  Serial.println(payload2);
  if (client.publish(pubTopic3, (char*) payload2.c_str())) {
    Serial.println("Publish ok");
  } else {
    Serial.println("Publish failed");
  }

  String payload3 = "{\"d\":{\"Name\":\"" DEVICE_ID "\"";
  payload3 += ",\"Corrente_R\":";
  payload3 += correnteR;
  payload3 += "}}";
  Serial.print("Sending payload3: ");
  Serial.println(payload3);
  if (client.publish(pubTopic4, (char*) payload3.c_str())) {
    Serial.println("Publish ok");
  } else {
    Serial.println("Publish failed");
  }
  
  String payload4 = "{\"d\":{\"Name\":\"" DEVICE_ID "\"";
  payload4 += ",\"Corrente_S\":";
  payload4 += correnteS;
  payload4 += "}}";
  Serial.print("Sending payload4: ");
  Serial.println(payload4);
  if (client.publish(pubTopic5, (char*) payload4.c_str())) {
    Serial.println("Publish ok");
  } else {
    Serial.println("Publish failed");
  }
  
  String payload5 = "{\"d\":{\"Name\":\"" DEVICE_ID "\"";
  payload5 += ",\"Corrente_T\":";
  payload5 += correnteT;
  payload5 += "}}";
  Serial.print("Sending payload5: ");
  Serial.println(payload5);
  if (client.publish(pubTopic6, (char*) payload5.c_str())) {
    Serial.println("Publish ok");
  } else {
    Serial.println("Publish failed");
  }
   proxima_medida = millis() + intervalo_medidas;
 }
}
