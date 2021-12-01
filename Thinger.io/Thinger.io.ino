#define _DISABLE_TLS_

#define THINGER_SERIAL_DEBUG
#include <ThingerESP32.h>
#include <EmonLib.h>
#include "arduino_secrets.h"

ThingerESP32 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

#define VOLT_CAL 83.65
EnergyMonitor emon1;
EnergyMonitor emon2;
EnergyMonitor emon3;

EnergyMonitor SCT1;
EnergyMonitor SCT2;
EnergyMonitor SCT3;

float faseR = 34, faseS = 35, faseT = 32;
int correnteR= 15, correnteS= 2, correnteT= 0; 
double Irms1, Irms2, Irms3;

void setup() {
  Serial.begin(115200);
  pinMode(16, OUTPUT);
  thing.add_wifi(SSID, SSID_PASSWORD);

  emon1.voltage(34, VOLT_CAL, 1.7);
  emon2.voltage(35, VOLT_CAL, 1.7);
  emon3.voltage(32, VOLT_CAL, 1.7);

  SCT1.current(correnteR, 1.362 );
  SCT2.current(correnteS, 1.362 );
  SCT3.current(correnteT, 1.362 );

    thing["dados"] >> [] (pson & out) {
    out["faseR"] = faseR;
    out["faseS"] = faseS;
    out["faseT"] = faseT;
    out["Irms1"] = Irms1;
    out["Irms2"] = Irms2;
    out["Irms3"] = Irms3;
  };
}

void loop() {
  emon1.calcVI(60, 2000);
  emon2.calcVI(60, 2000);
  emon3.calcVI(60, 2000);
  
  faseR = emon1.Vrms;
  faseS = emon2.Vrms;
  faseT = emon3.Vrms;

  Irms1 = SCT1.calcIrms ( 1480 ); 
  Irms2 = SCT2.calcIrms ( 1480 );
  Irms3 = SCT3.calcIrms ( 1480 ); 
  
  thing.handle();
}
