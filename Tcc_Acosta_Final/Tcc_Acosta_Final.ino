#include <ResponsiveAnalogRead.h> // incluir biblioteca ResponsiveAnalogRead

/**********************************************************************************************************************
Variável de loop 
**********************************************************************************************************************/
long ciclo = 0;
int cont60seg = 0;
unsigned long tempoSeg = 0;
unsigned long tempoSegAnt = 0;
long tempo = 0;
int cicloAnalog= 0;
int teste = 500;
/****************************************************************************************
configuração entrada analogica
******************************************************************************************/

/**********Sensor de  nivel da Cisterna**************/
int pinoSenNivCis = A0; // pino da entrada 
int analogico01 = 0;// variavel para receber a entrada analogica do sensor de nível
ResponsiveAnalogRead analogOne(pinoSenNivCis, true);// cria uma instancia para ResponsiveAnalogRead
int analog1[10]; // vetor utilizado para media movel
int somaSensor1 = 0; // soma  utilizada para calculo a media movel
int sensor1 = 0; // media
int NivCis = 0; // valor do nível
String NivCisStr; // string do nível para cálculo 
int StNivCis = 0; // status do nível da cisterna
float setLNivCis = 120; // setpoit de nível baixo cisterna
float setHNivCis = 130; // setpoit de nível alto cisterna
float histNivCis = 5; // histerese cisterna

/**********Sensor de  nivel da Caixa**************/
int pinoSenNivCx = A8; // pino da entrada analógica
int analogico02 = 0; // variavel para receber a entrada analogica do sensor de nível
ResponsiveAnalogRead analogTwo(pinoSenNivCx, true); // cria uma instancia para ResponsiveAnalogRead
int analog2[10]; // vetor utilizado para media movel
int somaSensor2 = 0; // soma  utilizada para cálculo a media movel
int sensor2 = 0; // media
int NivCx = 0; //valor do nível
String NivCxStr; // string do nível para cálculo 
int StNivCx = 0; // status do nível da cisterna
float setLNivCx = 135; // setpoit de nível baixo caixa
float setHNivCx = 145; // setpoit de nível alto caixa
float histNivCx = 5; // histerese caixa

int varFor = 0;


/**********************************************************************************************************************
Variável de fluxo 
**********************************************************************************************************************/

volatile int pulso = 0; // contagem de pulso para fluxo
volatile int pulsoTotal = 0; // contagem de pulso para volume 1 minuto
float fluxo = 0; //Converte para Litros/segundo
float volumeMin = 0; // volume a cada 1 minuto
const byte pinoSemFx = 2;// entrada de pulso sensor de fluxo

/**********************************************************************************************************************
Configurações de pinos específicos 
**********************************************************************************************************************/

/*****************************************Saídas*********************************************************************/
const byte pinoBomPc = 25;// saída para bomba do poço
const byte pinoBomCis = 24;// saída para bomba da cisterna


/***************entradas Discretas***********************************/

/*****Monitoração de Status e led de Builtin****/

bool StComAutBomPcLD = 0;             // status liga desliga da bomba do poço em automatico "0" desliga "1" liga
bool StComAutBomCisLD = 0;            // status liga desliga da bomba da cisterna automatico "0" desliga "1" liga
bool StAutBomPcLD = 0;             // status liga desliga da bomba do poço em automatico "0" desliga "1" liga
bool StAutBomCisLD = 0;            // status liga desliga da bomba da cisterna automatico "0" desliga "1" liga
String EnviarStBomPc;
String EnviarStBomCis;
/*
Variaveis de indentificação de variaveis para transmissão serial e wifi
*/

String EndSenNivCis = "00";
String EndSenNivCx = "01";
String EndFx = "02";
String EndVol = "03";
String EndStNivCis = "04";
String EndStNivCx = "05";
String EndStBomPc = "06";
String EndStBomCis = "07";

String separador = "#"; // caracter indicativo de inicio e fim de menssagem
