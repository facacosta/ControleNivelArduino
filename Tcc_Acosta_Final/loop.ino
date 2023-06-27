void loop() {
  ciclo ++; // contador de ciclo do Arduino
  SaiAutBom(); // chamada da função que liga e desliga as bombas
  if((millis() - tempoSegAnt) > 1000){ // a cada 1 segundo executa as tarefas abaixo
  tempoSegAnt = millis(); // armazena o tempo ataula para a base de tempo 
  tempo ++; // variavel de diagnóstico a quanto tempo o arduino esta ativo
  cont60seg ++; // conta 60 segundos para a tarefa de volume 
  Serial3.println("estou funcionando"); // 
  Fluxo(); // executa a tarefa de calcular o fluxo por minuto a cada segundo
  SensorAnalogico(); // entra na função das entrasa analogicas
  Serial.print("o tempo de inicilaização aproximado em segundos: ");
  Serial.print(tempo);
  Serial.print(" e a quantidade de cilos: ");
  Serial.println(ciclo);
  }
if(cont60seg > 59){
cont60seg = 0; // reinicia o contador de 60 segundos 
cli(); // desabilita a interrupção
volumeMin = pulsoTotal/300; //calcula o volume de 1 minuto 

pulsoTotal = 0; //zera a quantidade de pulsos de 1 minuto
sei(); //habilita a interrupção  
Serial.print("O volume total: ");
Serial.println(volumeMin);
String VolumeStr = "#" + EndVol + String(volumeMin, 2) + "#"; //prepara a string de envia para o esp32 
Serial3.println(VolumeStr); // envia para o esp32 a string
  }
}
