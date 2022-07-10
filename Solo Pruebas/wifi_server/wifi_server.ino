#include <OneWire.h>
#include <DallasTemperature.h>
#include <SoftwareSerial.h>

const int pin =9;
 
SoftwareSerial BT1(2, 3); // RX | TX
OneWire objeto(pin);
DallasTemperature sensor(&objeto);
int n1 = 0;


void setup()
{ Serial.begin(9600);
  BT1.begin(9600);
  sensor.begin();
  
}

void loop()
{ sensor.requestTemperatures();
  while (BT1.available() > 0 )
  { char c = BT1.read();
    if (c == 71)
    { Serial.println("peticion web enviada");
      delay(500);
      servidor();
    }
  }

}


void escribir(String text)
{ BT1.print("AT+CIPSEND=0,");
  BT1.println(text.length());
  if (BT1.find(">"))             // Si se recibe el mensaje
  { Serial.println(text);
    BT1.println(text);            //mandamos el mensaje por el wifi
    delay(10);
    while ( BT1.available() > 0 )
    { if (  BT1.find("SEND OK") )  //buscamos "ok" y luego salimos
        break;
    }
  }
}

void servidor(void)
{ escribir("<!DOCTYPE HTML>");
  escribir("<html>");                                                  //una pagina web necesita esto <HTML> y </HTML> es el inicio y fin del documento
  escribir("<head><title>Prueba arduino esp8266 html :)</title>");    //nombre de la pestaña que llevara la pagina
  escribir("<meta http-equiv=\"refresh\" content=\"10\"></head>");    //tiempo para refrescar la pagina web
  escribir("<body><h1> <FONT SIZE=\"5\" COLOR=\"red\"> ADSF </h1>");                              //titulo del inicio de la pagina
  escribir(" <BODY BGCOLOR=\"black\"> ");
 

   
   float lectura = sensor.getTempCByIndex(0);
    escribir("<FONT FACE=\"Arial\" SIZE=\"5\" COLOR=\"blue\"> entrada del sensor </FONT>"); //escribimos y cambiamos el tamaño, letra y color
   
    escribir(" es ");
    escribir(String(lectura));  //imprimimos la variable
    escribir("<br />");
    escribir("<br />");
 
  delay(1);
  BT1.println("AT+CIPCLOSE=0");
  //delay(500);
}
