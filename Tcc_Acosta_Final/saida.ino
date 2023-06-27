void SaiAutBom(){
int StAutBomPcLDAnt = StAutBomPcLD;    // verifica o status atual da bomba do poço e carrega em staus anterior
int StAutBomCisLDAnt = StAutBomCisLD;  // verifica o status atual da bomba da cisterna e carre em staus anterior
if(StNivCis < 2 ){ // se o nivel da cisterna estiver baixo 
digitalWrite(pinoBomPc, HIGH);
StAutBomPcLD = 1;
//Serial.println("A bomba do poço foi ligada em automatico");
} else if(StNivCis > 2 ){
digitalWrite(pinoBomPc, LOW);
StAutBomPcLD = 0;
//Serial.println("A bomba desligada em foi desligada em automatico");
  }
if((StNivCis > 1 ) && (StNivCx < 2 )){
digitalWrite(pinoBomCis, HIGH);
StAutBomCisLD = 1;
} else if((StNivCx > 2 )||(StNivCis < 2 )){
digitalWrite(pinoBomCis, LOW);
StAutBomCisLD = 0;
  }

if(StAutBomPcLDAnt != StAutBomPcLD){
  EnviarStBomPc = "#" + EndStBomPc + String(StAutBomPcLD) + "#";
  Serial3.println(EnviarStBomPc);
   if(StAutBomPcLD == 0){
    Serial.print("A bomba do poço foi mudou de status para desligada: ");
  } else if(StAutBomPcLD == 1){
    Serial.print("A bomba do poço foi mudou de status para ligada: ");
  }
}

if(StAutBomCisLDAnt != StAutBomCisLD){
  EnviarStBomCis = "#" + EndStBomPc + String(StAutBomCisLD) + "#";
  Serial3.println(EnviarStBomCis);
   if(StAutBomCisLD == 0){
    Serial.print("A bomba da cisterna foi mudou de status para desligada: ");
  } else if(StAutBomCisLD == 1){
    Serial.print("A bomba da cisterna foi mudou de status para ligada: ");
  }
}

}


