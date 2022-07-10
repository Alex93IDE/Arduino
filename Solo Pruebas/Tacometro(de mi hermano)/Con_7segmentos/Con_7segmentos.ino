/*
28 de Julio de 2018
Antonio Dos Santos López
Tacómetro
Mapa de los números del 0 al 9 de un 7 segmentos
 numero_0={1,1,1,1,1,1,0}      ---------a-------- 
 numero_1={0,1,1,0,0,0,0}      ----///////////---
 numero_2={1,1,0,1,1,0,1}      --f-//-------//-b-
 numero_3={1,1,1,1,0,0,1}      ----//---g---//---
 numero_4={0,1,1,0,0,1,1}      ----///////////---
 numero_5={1,0,1,1,0,1,1}      ----//-------//---
 numero_6={1,0,1,1,1,1,1}      --e-//-------//-c-
 numero_7={1,1,1,0,0,0,0}      ----///////////---
 numero_8={1,1,1,1,1,1,1}      ---------d--------
 numero_9={1,1,1,1,1,1,0}
 */
bool numero[]={0,0,0,0,0,0,0};
//Declaración de pines
int pin_in=A3;//pin de entrada del sensor
int pin_a=2;
int pin_b=3;
int pin_c=4;
int pin_d=5;
int pin_e=6;
int pin_f=7;
int pin_g=8;
int pin_millar=9;
int pin_centenas=10;
int pin_decenas=11;
int pin_unidades=12;

//Variables utilizadas
long muestreo_anterior=20000;
int active_screen=1;
boolean bandera=HIGH;
int disparo=90;//Valor para reconocer el paso del reflector
int histeresis=20;//Valor para reconocer cuando ha pasado el reflector
long tiempo=0;//variable que guarda el tiempo de la última revolución
int sensor;
long periodo=0;
long frecuencia=0;
long frecuencia_muestra=0;
int millar;
int centenas;
int decenas;
int unidades;
long tiempo_de_muestra=1000;
long tiempo_transcurrido=0;
bool numero_millar[]={0,0,0,0,0,0,0};
bool numero_centenas[]={0,0,0,0,0,0,0};
bool numero_decenas[]={0,0,0,0,0,0,0};
bool numero_unidades[]={0,0,0,0,0,0,0};
int microsegundos=50;// microsegundos de pausa para mostrar en los 7seg
void setup() {
  Serial.begin(250000);
  pinMode(pin_in,INPUT);
  pinMode(pin_a,OUTPUT);
  pinMode(pin_b,OUTPUT);
  pinMode(pin_c,OUTPUT);
  pinMode(pin_d,OUTPUT);
  pinMode(pin_e,OUTPUT);
  pinMode(pin_f,OUTPUT);
  pinMode(pin_g,OUTPUT);
  pinMode(pin_millar,OUTPUT);
  pinMode(pin_centenas,OUTPUT);
  pinMode(pin_decenas,OUTPUT);
  pinMode(pin_unidades,OUTPUT);
}

void loop() {
  for(int i= 0;i<30;i++){
sensor+=analogRead(pin_in);
  }//lee el pin
  sensor = sensor/30;
Serial.println(sensor);
delay(1000);
/*
if (sensor>disparo){//¿Está pasando el reflector?
  if (bandera==HIGH){//¿Es la 1ra vez que lo detecto en esta revolución?
   periodo=millis()-tiempo;
   tiempo=millis();
   frecuencia=60000/periodo;
   Serial.print(sensor);
   Serial.println(" rpm");
   bandera=LOW;
  }
}
if (sensor<histeresis){//ha pasado ya el reflector
    bandera=HIGH;
  }
//Actualizar datos
tiempo_transcurrido=millis()-muestreo_anterior;
if (tiempo_transcurrido>tiempo_de_muestra){
  muestreo_anterior=millis();
  frecuencia_muestra=frecuencia;
  //
  millar=frecuencia_muestra/1000;
  centenas=(frecuencia_muestra-millar*1000)/100;
  decenas=(frecuencia_muestra-millar*1000-centenas*100)/10;
  unidades=(frecuencia_muestra-millar*1000-centenas*100-decenas*10);
  //

  switch(millar){
    case 1:
    numero_millar[0]=0;numero_millar[1]=1;numero_millar[2]=1;
    numero_millar[3]=0;numero_millar[4]=0;numero_millar[5]=0;
    numero_millar[6]=0;
    break;
    case 2:
    numero_millar[0]=1;numero_millar[1]=1;numero_millar[2]=0;
    numero_millar[3]=1;numero_millar[4]=1;numero_millar[5]=0;
    numero_millar[6]=1;
    break;
    case 3:
    numero_millar[0]=1;numero_millar[1]=1;numero_millar[2]=1;
    numero_millar[3]=1;numero_millar[4]=0;numero_millar[5]=0;
    numero_millar[6]=1;
    break;
    case 4:
    numero_millar[0]=0;numero_millar[1]=1;numero_millar[2]=1;
    numero_millar[3]=0;numero_millar[4]=0;numero_millar[5]=1;
    numero_millar[6]=1;
    break;
    case 5:
    numero_millar[0]=1;numero_millar[1]=0;numero_millar[2]=1;
    numero_millar[3]=1;numero_millar[4]=0;numero_millar[5]=1;
    numero_millar[6]=1;
    break;
    case 6:
    numero_millar[0]=1;numero_millar[0]=1;numero_millar[2]=1;
    numero_millar[3]=1;numero_millar[4]=1;numero_millar[5]=1;
    numero_millar[6]=1;
    break;
    case 7:
    numero_millar[0]=1;numero_millar[1]=1;numero_millar[2]=1;
    numero_millar[3]=0;numero_millar[4]=0;numero_millar[5]=0;
    numero_millar[6]=0;
    break;
    case 8:
    numero_millar[0]=1;numero_millar[1]=1;numero_millar[2]=1;
    numero_millar[3]=1;numero_millar[4]=1;numero_millar[5]=1;
    numero_millar[6]=1;
    break;
    case 9:
    numero_millar[0]=1;numero_millar[1]=1;numero_millar[2]=1;
    numero_millar[3]=1;numero_millar[4]=0;numero_millar[5]=1;
    numero_millar[6]=1;
    break;
    default:
    numero_millar[0]=0;numero_millar[1]=0;numero_millar[2]=0;
    numero_millar[3]=0;numero_millar[4]=0;numero_millar[5]=0;
    numero_millar[6]=0;
    break;
  }
  switch(centenas){
    case 1:
    numero_centenas[0]=0;numero_centenas[1]=1;numero_centenas[2]=1;
    numero_centenas[3]=0;numero_centenas[4]=0;numero_centenas[5]=0;
    numero_centenas[6]=0;
    break;
    case 2:
    numero_centenas[0]=1;numero_centenas[1]=1;numero_centenas[2]=0;
    numero_centenas[3]=1;numero_centenas[4]=1;numero_centenas[5]=0;
    numero_centenas[6]=1;
    break;
    case 3:
    numero_centenas[0]=1;numero_centenas[1]=1;numero_centenas[2]=1;
    numero_centenas[3]=1;numero_centenas[4]=0;numero_centenas[5]=0;
    numero_centenas[6]=1;
    break;
    case 4:
    numero_centenas[0]=0;numero_centenas[1]=1;numero_centenas[2]=1;
    numero_centenas[3]=0;numero_centenas[4]=0;numero_centenas[5]=1;
    numero_centenas[6]=1;
    break;
    case 5:
    numero_centenas[0]=1;numero_centenas[1]=0;numero_centenas[2]=1;
    numero_centenas[3]=1;numero_centenas[4]=0;numero_centenas[5]=1;
    numero_centenas[6]=1;
    break;
    case 6:
    numero_centenas[0]=1;numero_centenas[0]=1;numero_centenas[2]=1;
    numero_centenas[3]=1;numero_centenas[4]=1;numero_centenas[5]=1;
    numero_centenas[6]=1;
    break;
    case 7:
    numero_centenas[0]=1;numero_centenas[1]=1;numero_centenas[2]=1;
    numero_centenas[3]=0;numero_centenas[4]=0;numero_centenas[5]=0;
    numero_centenas[6]=0;
    break;
    case 8:
    numero_centenas[0]=1;numero_centenas[1]=1;numero_centenas[2]=1;
    numero_centenas[3]=1;numero_centenas[4]=1;numero_centenas[5]=1;
    numero_centenas[6]=1;
    break;
    case 9:
    numero_centenas[0]=1;numero_centenas[1]=1;numero_centenas[2]=1;
    numero_centenas[3]=1;numero_centenas[4]=0;numero_centenas[5]=1;
    numero_centenas[6]=1;
    break;
     case 0:
    numero_centenas[0]=1;numero_centenas[1]=1;numero_centenas[2]=1;
    numero_centenas[3]=1;numero_centenas[4]=1;numero_centenas[5]=1;
    numero_centenas[6]=0;
    break;
    default:
    numero_centenas[0]=0;numero_centenas[1]=0;numero_centenas[2]=0;
    numero_centenas[3]=0;numero_centenas[4]=0;numero_centenas[5]=0;
    numero_centenas[6]=0;
    break;
  }
  switch(decenas){
    case 1:
    numero_decenas[0]=0;numero_decenas[1]=1;numero_decenas[2]=1;
    numero_decenas[3]=0;numero_decenas[4]=0;numero_decenas[5]=0;
    numero_decenas[6]=0;
    break;
    case 2:
    numero_decenas[0]=1;numero_decenas[1]=1;numero_decenas[2]=0;
    numero_decenas[3]=1;numero_decenas[4]=1;numero_decenas[5]=0;
    numero_decenas[6]=1;
    break;
    case 3:
    numero_decenas[0]=1;numero_decenas[1]=1;numero_decenas[2]=1;
    numero_decenas[3]=1;numero_decenas[4]=0;numero_decenas[5]=0;
    numero_decenas[6]=1;
    break;
    case 4:
    numero_decenas[0]=0;numero_decenas[1]=1;numero_decenas[2]=1;
    numero_decenas[3]=0;numero_decenas[4]=0;numero_decenas[5]=1;
    numero_decenas[6]=1;
    break;
    case 5:
    numero_decenas[0]=1;numero_decenas[1]=0;numero_decenas[2]=1;
    numero_decenas[3]=1;numero_decenas[4]=0;numero_decenas[5]=1;
    numero_decenas[6]=1;
    break;
    case 6:
    numero_decenas[0]=1;numero_decenas[0]=1;numero_decenas[2]=1;
    numero_decenas[3]=1;numero_decenas[4]=1;numero_decenas[5]=1;
    numero_decenas[6]=1;
    break;
    case 7:
    numero_decenas[0]=1;numero_decenas[1]=1;numero_decenas[2]=1;
    numero_decenas[3]=0;numero_decenas[4]=0;numero_decenas[5]=0;
    numero_decenas[6]=0;
    break;
    case 8:
    numero_decenas[0]=1;numero_decenas[1]=1;numero_decenas[2]=1;
    numero_decenas[3]=1;numero_decenas[4]=1;numero_decenas[5]=1;
    numero_decenas[6]=1;
    break;
    case 9:
    numero_decenas[0]=1;numero_decenas[1]=1;numero_decenas[2]=1;
    numero_decenas[3]=1;numero_decenas[4]=0;numero_decenas[5]=1;
    numero_decenas[6]=1;
    break;
    default:
    numero_decenas[0]=0;numero_decenas[1]=0;numero_decenas[2]=0;
    numero_decenas[3]=0;numero_decenas[4]=0;numero_decenas[5]=0;
    numero_decenas[6]=0;
    break;
  }
  switch(unidades){
    case 1:
    numero_unidades[0]=0;numero_unidades[1]=1;numero_unidades[2]=1;
    numero_unidades[3]=0;numero_unidades[4]=0;numero_unidades[5]=0;
    numero_unidades[6]=0;
    break;
    case 2:
    numero_unidades[0]=1;numero_unidades[1]=1;numero_unidades[2]=0;
    numero_unidades[3]=1;numero_unidades[4]=1;numero_unidades[5]=0;
    numero_unidades[6]=1;
    break;
    case 3:
    numero_unidades[0]=1;numero_unidades[1]=1;numero_unidades[2]=1;
    numero_unidades[3]=1;numero_unidades[4]=0;numero_unidades[5]=0;
    numero_unidades[6]=1;
    break;
    case 4:
    numero_unidades[0]=0;numero_unidades[1]=1;numero_unidades[2]=1;
    numero_unidades[3]=0;numero_unidades[4]=0;numero_unidades[5]=1;
    numero_unidades[6]=1;
    break;
    case 5:
    numero_unidades[0]=1;numero_unidades[1]=0;numero_unidades[2]=1;
    numero_unidades[3]=1;numero_unidades[4]=0;numero_unidades[5]=1;
    numero_unidades[6]=1;
    break;
    case 6:
    numero_unidades[0]=1;numero_unidades[0]=1;numero_unidades[2]=1;
    numero_unidades[3]=1;numero_unidades[4]=1;numero_unidades[5]=1;
    numero_unidades[6]=1;
    break;
    case 7:
    numero_unidades[0]=1;numero_unidades[1]=1;numero_unidades[2]=1;
    numero_unidades[3]=0;numero_unidades[4]=0;numero_unidades[5]=0;
    numero_unidades[6]=0;
    break;
    case 8:
    numero_unidades[0]=1;numero_unidades[1]=1;numero_unidades[2]=1;
    numero_unidades[3]=1;numero_unidades[4]=1;numero_unidades[5]=1;
    numero_unidades[6]=1;
    break;
    case 9:
    numero_unidades[0]=1;numero_unidades[1]=1;numero_unidades[2]=1;
    numero_unidades[3]=1;numero_unidades[4]=0;numero_unidades[5]=1;
    numero_unidades[6]=1;
    break;
     case 0:
    numero_unidades[0]=1;numero_unidades[1]=1;numero_unidades[2]=1;
    numero_unidades[3]=1;numero_unidades[4]=1;numero_unidades[5]=1;
    numero_unidades[6]=0;
    break;
    default:
    numero_unidades[0]=0;numero_unidades[1]=0;numero_unidades[2]=0;
    numero_unidades[3]=0;numero_unidades[4]=0;numero_unidades[5]=0;
    numero_unidades[6]=0;
    break;
  }
}
    digitalWrite(pin_unidades,0);//Deben ir a bases de BJTs para dar la 
    digitalWrite(pin_decenas,0); //tierra a los 7 segmentos y así 
    digitalWrite(pin_centenas,0);//activarlos
    digitalWrite(pin_millar,1);
  digitalWrite(pin_a,numero_millar[0]);
  digitalWrite(pin_b,numero_millar[1]);
  digitalWrite(pin_c,numero_millar[2]);
  digitalWrite(pin_d,numero_millar[3]);
  digitalWrite(pin_e,numero_millar[4]);
  digitalWrite(pin_f,numero_millar[5]);
  digitalWrite(pin_g,numero_millar[6]);
  delayMicroseconds(microsegundos);
  //
    digitalWrite(pin_unidades,0);//Deben ir a bases de BJTs para dar la 
    digitalWrite(pin_decenas,0); //tierra a los 7 segmentos y así 
    digitalWrite(pin_centenas,1);//activarlos
    digitalWrite(pin_millar,0);
  digitalWrite(pin_a,numero_centenas[0]);
  digitalWrite(pin_b,numero_centenas[1]);
  digitalWrite(pin_c,numero_centenas[2]);
  digitalWrite(pin_d,numero_centenas[3]);
  digitalWrite(pin_e,numero_centenas[4]);
  digitalWrite(pin_f,numero_centenas[5]);
  digitalWrite(pin_g,numero_centenas[6]);
  delayMicroseconds(microsegundos);
 //
  digitalWrite(pin_unidades,0);//Deben ir a bases de BJTs para dar la 
    digitalWrite(pin_decenas,1); //tierra a los 7 segmentos y así 
    digitalWrite(pin_centenas,0);//activarlos
    digitalWrite(pin_millar,0);
  digitalWrite(pin_a,numero_decenas[0]);
  digitalWrite(pin_b,numero_decenas[1]);
  digitalWrite(pin_c,numero_decenas[2]);
  digitalWrite(pin_d,numero_decenas[3]);
  digitalWrite(pin_e,numero_decenas[4]);
  digitalWrite(pin_f,numero_decenas[5]);
  digitalWrite(pin_g,numero_decenas[6]);
  delayMicroseconds(microsegundos);
  //
   digitalWrite(pin_unidades,1);//Deben ir a bases de BJTs para dar la 
    digitalWrite(pin_decenas,0); //tierra a los 7 segmentos y así 
    digitalWrite(pin_centenas,0);//activarlos
    digitalWrite(pin_millar,0);
  digitalWrite(pin_a,numero_unidades[0]);
  digitalWrite(pin_b,numero_unidades[1]);
  digitalWrite(pin_c,numero_unidades[2]);
  digitalWrite(pin_d,numero_unidades[3]);
  digitalWrite(pin_e,numero_unidades[4]);
  digitalWrite(pin_f,numero_unidades[5]);
  digitalWrite(pin_g,numero_unidades[6]);
  //delayMicroseconds(microsegundos);*/
}
