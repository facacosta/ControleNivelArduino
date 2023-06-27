void contador(){
  pulso ++;
  pulsoTotal ++;
}

void Fluxo(){
  
cli();      //Disable interrupts
fluxo = (pulso/55); //calcula o fluxo sem divisão por numero fracionário
imprimirfluxo();
pulso = 0;
sei();      //Enables interrupts
String enviarfluxo = "#" + EndFx + String(fluxo, 2) + "#";
Serial3.println(enviarfluxo);

}

int ChaveVirtual(int valor, int setL, int setH, int hist){

int StatusValor; // valor de retorno com status do sensor
int histL = setL + hist;// calcula a histerese do valor baixo 
int histH = setH - hist;// calcula a histerese do valor alto

// verifica se o status estiver diferente de alto e o valor maior que o setpoit alto seta o status como alto "3"
if ((StatusValor < 3)&&(valor > setH)){ 
  StatusValor = 3;
 }
 // verifica se o status está alto porem o valor ja diminuiu abaixo da histerese ou
 // se o status esta baixo porem o valor já almentou acima da histeres  seta o status como normal "2"
 if(((StatusValor > 2)&&(valor < histH))||((StatusValor < 2)&&(valor > histL))){
  StatusValor = 2;
}
// verifica se o status estiver diferente de baixo e o valor menor que o setpoit baixo seta o status como baixo "1"
if((StatusValor > 1)&&(valor < setL)){
  StatusValor = 1;
}
return StatusValor;
}

void SensorAnalogico(){
/**************************************************************************************
 retira a media dos dez ultimos valores lidos para todos os sensores
**************************************************************************************/
// update the ResponsiveAnalogRead objects every loop
analogOne.update(); // executa o ResponsiveAnalogRead
analogTwo.update(); // executa o ResponsiveAnalogRead

int analogico01 = analogOne.getValue(); // atualiza o valor da entrada analógica
int analogico02 = analogTwo.getValue(); // atualiza o valor da entrada analógica

//imprimirEntAnalogBruta();

analog1[cicloAnalog] = analogico01; // alimenta o arrey sensor0 a cada ciclo com a leitura atual
analog2[cicloAnalog] = analogico02; // alimenta o arrey sensor0 a cada ciclo com a leitura atual

for(int i = 0; i <= 9; i  ++){ // laço for para somar todos os 10 valores lidos dos sensores
somaSensor1 = somaSensor1 + analog1[i]; //soma os valores da matriz para gerar a media de valores 
somaSensor2 = somaSensor2 + analog2[i]; //soma os valores da matriz para gerar a media de valores 
varFor = i; // variavel global varFor para ser utilizada na função imprimirEntAnalogFor()
//imprimirEntAnalogFor();
  }

NivCis = somaSensor1/10; // media das dez ultimas leituras para o sensor1
NivCx = somaSensor2/10; // media das dez ultimas leituras para o sensor2

somaSensor1 = 0; // zera o valor da soma dos valores do sensor
somaSensor2 = 0; // zera o valor da soma dos valores do sensor

imprimirAnalogFinal();

NivCisStr = "#" + EndSenNivCis + String(NivCis) + "#"; // transforma a variável para string concatenada com o indentificador da variável
Serial3.println(NivCisStr); // envio de variável para o esp32
Serial.println(NivCisStr);
delay(50);
// imprime o nível da cisterna
Serial.print("O valor do nivel da Cisterna é: ");
Serial.print(NivCis);
Serial.print(" - status: ");            // imprime na porta serial para debug
Serial.println(StNivCis);
int StNivCisAnt = 0; // cria uma variável com status do nível da cistena anterior
StNivCisAnt = StNivCis; // passa o status atual para o stats anterior
StNivCis = ChaveVirtual(NivCis, setLNivCis, setHNivCis, histNivCis); // verifica o novo status
if(StNivCisAnt != StNivCis){ // verifica se houve mudança do status, caso tenha havido diferença executa as intruções do if
String EnvStNivCis = "#" + EndStNivCis + String(StNivCis) + "#"; // prepara a string do envio
Serial3.println(EnvStNivCis);
Serial.print("O valor do status Anterior do nivel da cisterna é: ");            // imprime na porta serial para debug
Serial.print(StNivCisAnt);                                               // entra na função de envio de rede
Serial.print(" - status: ");            // imprime na porta serial para debug
Serial.println(StNivCis);
}

NivCxStr = "#" + EndSenNivCx + String(NivCx) + "#";
Serial3.println(NivCxStr); // envio de variável para o esp32
Serial.println(NivCxStr);
delay(50);
Serial.print("O valor do nivel da Caixa é: ");
Serial.print(NivCx);
Serial.print(" - status é: ");   
Serial.println(StNivCx);
int StNivCxAnt = 0;
StNivCxAnt = StNivCx; 
StNivCx = ChaveVirtual(NivCx, setLNivCx, setHNivCx, histNivCx);
if(StNivCxAnt != StNivCx){   // toda vez que houver mudança de status é enviado para o supervisorio o novo status
String EnvStNivCx = "#" + EndStNivCx + String(StNivCx) + "#"; 
 Serial3.println(EnvStNivCx);
Serial.print("O valor do statusAnterior do nivel da caixa é: ");           // imprime na porta serial para debug
Serial.print(StNivCxAnt);                                                 // entra na função de envio de rede
Serial.print(" - status é: ");           // imprime na porta serial para debug
Serial.println(StNivCx);
  }
cicloAnalog ++;
if(cicloAnalog > 9){
  cicloAnalog = 0;
  }
}

void imprimirEntAnalogBruta(){
Serial.print("Valor analogico1 sem correção: ");
Serial.println(analogRead(pinoSenNivCis));
Serial.print("Valor analogic2 sem correção: ");
Serial.println(analogRead(pinoSenNivCx));
}

void imprimirEntAnalogFor(){
Serial.print("Posição i: ");
Serial.println(varFor); 
Serial.print(" - somaSensor1: ");
Serial.println(somaSensor1);    
Serial.print(" - somaSensor2: ");
Serial.println(somaSensor2);
}

void imprimirAnalogFinal(){
Serial.print("Nível da Cisterna - Valor Bruto: ");
Serial.print(analogOne.getRawValue());
Serial.print(" - Valor Corrigido : ");
Serial.print(analogico01);
Serial.print(" - Após a Media : ");
Serial.println(NivCis);

Serial.print("Nível da Caixa - Valor Bruto: ");
Serial.print(analogTwo.getRawValue());
Serial.print(" - Valor Corrigido : ");
Serial.print(analogico02);
Serial.print(" - Após a Media : ");
Serial.println(NivCx);
}

void imprimirfluxo(){
Serial.print("A quantidade de pulso");
Serial.print(pulso);
Serial.print(" - o valor do fluxo é: ");
Serial.println(fluxo); // indica o valor do fluxo em litros por minuto
Serial.print(" - a quantidade de pulso total é: ");
Serial.println(pulsoTotal);
}
//calculo de media movel
//https://blog.eletrogate.com/filtro-digital-no-arduino/


