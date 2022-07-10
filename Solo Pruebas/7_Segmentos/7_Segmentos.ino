# include "SevenSeg.h" // incluimos la librería para nuestro display

float numeros, x;  // en esta variable se almacenan los numero a mostrar o letras.

SevenSeg disp(2, 3, 4, 5, 6, 7, 8); //declaramos nuestro display y definimos sus pines
//                     A, B ,C, D, E, F, G

const int numOfDigits = 4; // definimos el numero de dígitos de nuestro display

int digitPins [numOfDigits] = {12 , 11 , 10 , 9}; // los pines para cada Digito
//                                       D1,D2,D3,D4

void setup() {
  disp.setCommonAnode();
  disp.setDigitPins (numOfDigits , digitPins); //Configuramos el display
  disp . setDPPin (1) ;

}

void loop () {
  numeros++;

  disp.write(x,0);  // mostramos los números o letras en el display
if (numeros == 9999){
  numeros = 0;
  x++;
}
}
