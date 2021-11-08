#include <EmonLib.h> //INCLUSÃO DE BIBLIOTECA

#define VOLT_CAL 83.65 //VALOR DE CALIBRAÇÃO (DEVE SER AJUSTADO EM PARALELO COM UM MULTÍMETRO)


 
EnergyMonitor emon1;
EnergyMonitor emon2;
EnergyMonitor emon3; //CRIA UMA INSTÂNCIA PARA OS SENSORES DE TENSÃO

EnergyMonitor SCT1;
EnergyMonitor SCT2;
EnergyMonitor SCT3; // CRIA UMA INSTÂNCIA PARA OS SENSORES DE CORRENTE

int pinSCT1= 15 ;   // DEFINE OS PINOS ANALÓGICOS AO QUAIS ESTÃO CONECTADOS OS SENSORES DE CORRENTE
int pinSCT2= 2 ;
int pinSCT3= 0 ;

void setup()
{  
  Serial.begin(9600); //INICIALIZA A SERIAL
  emon1.voltage(34, VOLT_CAL, 1.7);
  emon2.voltage(35, VOLT_CAL, 1.7);
  emon2.voltage(32, VOLT_CAL, 1.7); //PASSA PARA A FUNÇÃO OS PARÂMETROS (PINO ANALÓGIO / VALOR DE CALIBRAÇÃO / MUDANÇA DE FASE)

  
  SCT1.current(pinSCT1, 1.362 );
  SCT2.current(pinSCT2, 1.362 );
  SCT3.current(pinSCT3, 1.362 );
  Serial.begin ( 9600 );

}

void loop(){
  emon1.calcVI(60,2000); //FUNÇÃO DE CÁLCULO (60 SEMICICLOS, TEMPO LIMITE PARA FAZER A MEDIÇÃO)    
   emon2.calcVI(60,2000);
    emon3.calcVI(60,2000);

   double Irms1 = SCT1.calcIrms ( 1480 ); 
   double Irms2 = SCT2.calcIrms ( 1480 );
   double Irms3 = SCT3.calcIrms ( 1480 );// Calcula o valor da Corrente
    
  float supplyVoltage   = emon1.Vrms; //VARIÁVEL RECEBE O VALOR DE TENSÃO RMS OBTIDO
  float supplyVoltage2  = emon2.Vrms;
  float supplyVoltage3  = emon3.Vrms; 
  Serial.print("Tensão medida na rede AC: "); //IMPRIME O TEXTO NA SERIAL
  Serial.print(supplyVoltage, 2); //IMPRIME NA SERIAL O VALOR DE TENSÃO MEDIDO E REMOVE A PARTE DECIMAL
  Serial.println("V");
  Serial.print("Tensão medida na rede AC: "); //IMPRIME O TEXTO NA SERIAL
  Serial.print(supplyVoltage2, 2); //IMPRIME NA SERIAL O VALOR DE TENSÃO MEDIDO E REMOVE A PARTE DECIMAL
  Serial.println("V"); //IMPRIME O TEXTO NA SERIAL
  Serial.print("Tensão medida na rede AC: "); //IMPRIME O TEXTO NA SERIAL
  Serial.print(supplyVoltage3, 2); //IMPRIME NA SERIAL O VALOR DE TENSÃO MEDIDO E REMOVE A PARTE DECIMAL
  Serial.println("V");
  Serial.print ( " Corrente = " );
  Serial.print (Irms1);
  Serial. println ( " A " );
  Serial.print ( " Corrente = " );
  Serial.print (Irms2);
  Serial. println ( " A " );
  Serial.print ( " Corrente = " );
  Serial.print (Irms3);
  Serial. println ( " A " );
  delay(1000);
}
