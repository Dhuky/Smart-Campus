int pino_sensor = 35;
float tensao_rms;
float tensao_pico;
double menor_valor = 0;
float valor_inst;

void setup() {
  Serial.begin(9600);
  pinMode(pino_sensor,INPUT);
}

void loop() {
  menor_valor = 4095;
  for(int i = 0; i< 2000; i++){
    valor_inst = analogRead(pino_sensor);
    if(menor_valor > valor_inst){
    menor_valor = valor_inst;
    }
  delayMicroseconds(10);
  }
  Serial.print("Menor Valor:");
  Serial.println(menor_valor);
  delay(5000);

  tensao_pico = map(menor_valor, 3250,2760,0,315);
  tensao_rms = tensao_pico/1.4;
  Serial.print("Tensão da rede elétrica: ");
  Serial.println(tensao_rms);
}
