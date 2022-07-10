#include <Arduino.h>
#include "gps.h"
#include <stdint.h>
#include <stdio.h>

GPS mi_gps;

GPS::GPS()
{
  char datos_gps_preparados = 0;
  char datos_gga_adquiridos = 0;
  char datos_rmc_adquiridos = 0;
  char datos_gsa_adquiridos = 0;
  char datos_gps_adquiridos = 0;
  char trama_activa = 0;
  unsigned char contador_bufer_gps = 0;
  unsigned char contador_comas_gga = 0;
  unsigned char contador_campo_altitud = 0;
  unsigned char contador_comas_gsa = 0;
  char usohorario = 0;
  float velocidad = 0;
}

void GPS::adquiriendo_bufer_gps_rmc()
{
  unsigned char i;
  unsigned char b;

  for (i = 7, b = 0; i < contador_bufer_gps; i++, b++)
  {
    sentencia_gps[b] = bufer_gps[i];
  }
  contador_sentencia_gps = contador_bufer_gps - 7;
  sentencia_gps[contador_sentencia_gps] = '\0';
  datos_rmc_adquiridos = 1;
}

void GPS::adquiriendo_bufer_gps_gga()
{
  unsigned char i;
  unsigned char b;
  for (i = 7, b = 0; i < contador_bufer_gps; i++, b++)
  {
    sentencia_gga[b] = bufer_gps[i];
  }
  contador_sentencia_gga = contador_bufer_gps - 7;
  sentencia_gga[contador_sentencia_gga] = '\0';
  datos_gga_adquiridos = 1;
}

void GPS::adquiriendo_bufer_gps_gsa()
{
  unsigned char i;
  unsigned char b;
  for (i = 7, b = 0; i < contador_bufer_gps; i++, b++)
  {
    sentencia_gsa[b] = bufer_gps[i];
  }
  contador_sentencia_gsa = contador_bufer_gps - 7;
  sentencia_gsa[contador_sentencia_gsa] = '\0';
  datos_gsa_adquiridos = 1;
}

void GPS::DatosGPSAdquiridos()
{
  if (datos_gga_adquiridos && datos_rmc_adquiridos && datos_gsa_adquiridos)
  {
    datos_gps_adquiridos = 1;
    datos_gga_adquiridos = 0;
    datos_rmc_adquiridos = 0;
    datos_gsa_adquiridos = 0;
  }
}

void GPS::analizar_bufer_gps()
{
#ifdef TXSERIE
  led_AMARILLO = APAGAR_LED;
  printf(ToBufferLOG, "%s\r\n", bufer_gps);
#endif

#ifndef TXSERIE
  if ((bufer_gps[3] == 'R') && (bufer_gps[4] == 'M') && (bufer_gps[5] == 'C'))
  {
    adquiriendo_bufer_gps_rmc();
    DatosGPSAdquiridos();
    contador_bufer_gps = 0;
    return;
  }
  if ((bufer_gps[3] == 'G') && (bufer_gps[4] == 'G') && (bufer_gps[5] == 'A'))
  {
    adquiriendo_bufer_gps_gga();
    DatosGPSAdquiridos();
    contador_bufer_gps = 0;
    return;
  }
  if ((bufer_gps[3] == 'G') && (bufer_gps[4] == 'S') && (bufer_gps[5] == 'A'))
  {
    adquiriendo_bufer_gps_gsa();
    DatosGPSAdquiridos();
    contador_bufer_gps = 0;
    return;
  }
#endif
  contador_bufer_gps = 0;
}

void GPS::agregando_buffer_gps(char caracter_recibido)
{
  if (!(caracter_recibido == 13))
  {
    //   if ((!(isalnum(caracter_recibido)||caracter_recibido=='.'||
    //           caracter_recibido==','||caracter_recibido=='*'||
    //           caracter_recibido=='-'||caracter_recibido=='$'||
    //           caracter_recibido==' ')))
    //           {
    //           contador_bufer_gps=0;
    //           return 0;
    //           }
    if (caracter_recibido == '$')
    {
      contador_bufer_gps = 0;
    }

    bufer_gps[contador_bufer_gps] = caracter_recibido;
    contador_bufer_gps++;
    if (contador_bufer_gps == 83)
      contador_bufer_gps = 0;
  }
  else
  {
    analizar_bufer_gps();
  }
}

void GPS::enviarSerie()
{
// cuando todas las tramsa sean adquiridas y la bandera 
//principal degps adquirida sea 1 crear otra bander que sea enviar por serie y ejecutarla y limpiarla aqui 
  
}

void GPS::decodificar_trama_gps()
{

  if (datos_gps_adquiridos == 1)
  {
    unsigned char a;
    unsigned char b;
    unsigned char cont = 0;
    //uint8 fin;
    a = 5;
    cont = 0;

    do
    {
      a++;
      if (sentencia_gps[a] == ',')
        cont++;
    } while (cont < 1);
    a++; //encontre la coma anterior a estado

    if (sentencia_gps[0] != ',' && sentencia_gps[a] == 'A')
    {
      trama_activa = 1;
      gps.horas[0] = sentencia_gps[0];
      gps.horas[1] = sentencia_gps[1];
      gps.horas[2] = sentencia_gps[2];
      gps.horas[3] = sentencia_gps[3];
      gps.horas[4] = sentencia_gps[4];
      gps.horas[5] = sentencia_gps[5];
      gps.horas[6] = '\0';
      gps.estado = 'A';
      a += 2;
      cont = 0;
      while (sentencia_gps[a] != ',')
      {
        gps.latitud.value[cont] = sentencia_gps[a];
        a++;
        if (cont > 12)
          break;
        cont++;
      }
      gps.latitud.value[cont] = '\0';
      gps.latitud.length = cont;
      cont = 0;
      a++;
      gps.latitud.orientacion = sentencia_gps[a];
      a += 2;
      while (sentencia_gps[a] != ',')
      {
        gps.longitud.value[cont] = sentencia_gps[a];
        a++;
        if (cont > 12)
          break;
        cont++;
      }

      gps.longitud.value[cont] = '\0';
      gps.longitud.length = cont;
      cont = 0;
      a++;
      gps.longitud.orientacion = sentencia_gps[a];
      a += 2;
      cont = 0;

      while (sentencia_gps[a] != ',')
      {
        gps.velocidad.value[cont] = sentencia_gps[a];
        a++;
        if (cont > 6)
          break;
        cont++;
      }

      gps.velocidad.value[cont] = '\0';
      gps.velocidad.length = cont;
      a++;
      cont = 0;
      while (sentencia_gps[a] != ',')
      {
        gps.spin.value[cont] = sentencia_gps[a];
        a++;
        if (cont > 5)
          break;
        cont++;
      }

      gps.spin.value[cont] = '\0';
      gps.spin.length = cont;
      a++;
      gps.fecha[0] = sentencia_gps[a];
      gps.fecha[1] = sentencia_gps[a + 1];
      gps.fecha[2] = sentencia_gps[a + 2];
      gps.fecha[3] = sentencia_gps[a + 3];
      gps.fecha[4] = sentencia_gps[a + 4];
      gps.fecha[5] = sentencia_gps[a + 5];
      gps.fecha[6] = '\0';

      //atendiendo gga

      a = contador_sentencia_gga - 4;
      contador_campo_altitud = 0;
      contador_comas_gga = 0;
      while (contador_comas_gga < 6)
      {
        if (sentencia_gga[a] == ',')
          contador_comas_gga++;
        else
        {
          if (contador_comas_gga == 4)
            gga.umsl = sentencia_gga[a];
          if (contador_comas_gga == 5)
          {
            contador_campo_altitud++;
          }
        }
        a--;
      }

      for (cont = a + 2, b = 0; cont < a + 2 + contador_campo_altitud; cont++, b++)
      {
        gga.msl[b] = sentencia_gga[cont];
      }
      gga.msl[b] = '\0';
      contador_campo_altitud = 0;
      contador_comas_gga = 0;
     
      // atendiendo gsa

      a = 2;
      gsa.fix = sentencia_gsa[a];
      while (contador_comas_gsa < 13)
      {
        if (sentencia_gsa[a] == ',')
        {
          contador_comas_gsa++;
        }
        a++;
      }
      gsa.PDOP[0] = sentencia_gsa[a];
      gsa.PDOP[1] = sentencia_gsa[a + 1];
      gsa.PDOP[2] = sentencia_gsa[a + 2];
      gsa.PDOP[3] = sentencia_gsa[a + 3];
      gsa.PDOP[4] = '\0';
      gsa.HDOP[0] = sentencia_gsa[a + 5];
      gsa.HDOP[1] = sentencia_gsa[a + 6];
      gsa.HDOP[2] = sentencia_gsa[a + 7];
      gsa.HDOP[3] = sentencia_gsa[a + 8];
      gsa.HDOP[4] = '\0';
      gsa.VDOP[0] = sentencia_gsa[a + 10];
      gsa.VDOP[1] = sentencia_gsa[a + 11];
      gsa.VDOP[2] = sentencia_gsa[a + 12];
      gsa.VDOP[3] = sentencia_gsa[a + 13];
      gsa.VDOP[4] = '\0';

      contador_comas_gsa = 0;
      datos_gps_preparados = 1;
	  //Lammar a la funcion de convertir los valores 
    }
    else
    {
      trama_activa = 0;
      gps.horas[0] = '\0';
      gps.fecha[0] = '\0';
      gps.latitud.value[0] = '\0';
      gps.latitud.orientacion = 'x';
      gps.longitud.value[0] = '\0';
      gps.longitud.orientacion = 'x';
      gps.velocidad.value[0] = '\0';
      gps.spin.value[0] = '\0';
      gps.latitud.length = 0;
      gps.longitud.length = 0;
      gps.velocidad.length = 0;
      gps.spin.length = 0;
      gps.estado = 'V';
      gga.msl[0] = '\0';
      gga.umsl = 'x';
      gga.nosv[0] = '\0';
      gsa.fix = '1';
      gsa.HDOP[0] = '\0';
      gsa.PDOP[0] = '\0';
      gsa.VDOP[0] = '\0';
      datos_gps_preparados = 0;
    }
    datos_gps_adquiridos = 0;
  }
}

void GPS::cargar_reloj_GPS()
{
  if (trama_activa == 1)
  {
    horagps.hora = (gps.horas[0] - 0x30) * 10 + gps.horas[1] - 0x30;
    horagps.minuto = (gps.horas[2] - 0x30) * 10 + gps.horas[3] - 0x30;
    horagps.segundo = (gps.horas[4] - 0x30) * 10 + gps.horas[5] - 0x30;
    horagps.dia = (gps.fecha[0] - 0x30) * 10 + gps.fecha[1] - 0x30;
    horagps.mes = (gps.fecha[2] - 0x30) * 10 + gps.fecha[3] - 0x30;
    horagps.anno = (gps.fecha[4] - 0x30) * 10 + gps.fecha[5] - 0x30;

    if (horagps.hora < usohorario)
    {
      horagps.hora = horagps.hora - usohorario + 24;
      horagps.dia = horagps.dia - 1;
    }
    else
    {
      horagps.hora = horagps.hora - usohorario;
      horagps.dia = horagps.dia;
    }
  }
  if (trama_activa == 0 && horagps.dia != 0)
  {
    horagps.segundo = horagps.segundo + 1;
    if (horagps.segundo > 59)
    {
      horagps.minuto++;
      horagps.segundo = 0;
    }
    if (horagps.minuto > 59)
    {
      horagps.hora++;
      horagps.minuto = 0;
    }
    if (horagps.hora > 23)
    {
      horagps.dia++;
      horagps.hora = 0;
    }
    if (horagps.dia > 31)
    {
      horagps.mes++;
      horagps.dia = 1;
    }
    if (horagps.mes > 12)
    {
      horagps.anno++;
      horagps.mes = 1;
    }
  }
  ajuste_de_calendario();
  calcular_tipo_dia();
  correccion_usohorario();
}

void GPS::calcular_tipo_dia()
{
  char regular[] = {0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5};
  char bisiestro[] = {0, 3, 4, 0, 2, 5, 0, 3, 6, 1, 4, 6};
  int res1, res2, res3, res4, res5;
  int d, m, a;

  d = horagps.dia;
  m = horagps.mes;
  a = horagps.anno;

  if ((a % 4 == 0) && !(a % 100 == 0))
  {
    m = bisiestro[m - 1];
    tipo_anno = 0;
  }
  else if (a % 400 == 0)
  {
    m = bisiestro[m - 1];
    tipo_anno = 0;
  }
  else
  {
    m = regular[m - 1];
    tipo_anno = 1;
  }

  res1 = (a - 1) % 7;
  res2 = (a - 1) / 4;
  res3 = (3 * (((a - 1) / 100) + 1)) / 4;
  res4 = (res2 - res3) % 7;
  res5 = d % 7;
  d = (res1 + res4 + m + res5) % 7;

  switch (d)
  {
  case 0:
    horagps.dia_week = d;
    break;
  case 1:
    horagps.dia_week = d;
    break;
  case 2:
    horagps.dia_week = d;
    break;
  case 3:
    horagps.dia_week = d;
    break;
  case 4:
    horagps.dia_week = d;
    break;
  case 5:
    horagps.dia_week = d;
    break;
  case 6:
    horagps.dia_week = d;
    break;
  }
}

void GPS::ajuste_de_calendario()
{
  if (horagps.dia == 0)
  {
    switch (horagps.mes)
    {
    case 1:
      horagps.dia = 31;
      horagps.mes = 12;
      horagps.anno -= 1;
      break;
    case 2:
      horagps.dia = 31;
      horagps.mes -= 1;
      break;
    case 3:
      if (tipo_anno == 1)
      {
        horagps.dia = 28;
      }
      else if (tipo_anno == 0)
      {
        horagps.dia = 29;
      }
      horagps.mes -= 1;

      break;
    case 4:
      horagps.dia = 31;
      horagps.mes -= 1;
      break;
    case 5:
      horagps.dia = 30;
      horagps.mes -= 1;
      break;
    case 6:
      horagps.dia = 31;
      horagps.mes -= 1;
      break;
    case 7:
      horagps.dia = 30;
      horagps.mes -= 1;
      break;
    case 8:
      horagps.dia = 31;
      horagps.mes -= 1;
      break;
    case 9:
      horagps.dia = 31;
      horagps.mes -= 1;
      break;
    case 10:
      horagps.dia = 30;
      horagps.mes -= 1;
      break;
    case 11:
      horagps.dia = 31;
      horagps.mes -= 1;
      break;
    case 12:
      horagps.dia = 30;
      horagps.mes -= 1;
      break;
    }
  }
}

void GPS::correccion_usohorario()
{
  if (usohorario == 0)
  {
    if (horagps.mes >= 3 && horagps.mes < 11)
      usohorario = 4;
    if (horagps.mes >= 11 || horagps.mes == 1 || horagps.mes == 2)
      usohorario = 5;
      }
  if (horagps.mes == 3 && horagps.dia > 7 && horagps.dia_week == 0)
    usohorario = 4;
  if (horagps.mes == 11 && horagps.dia_week == 0)
    usohorario = 5;
}

void GPS::convirtiendo_trama_gps()
{
  unsigned long a, b, c;
  double valor = 0;
  double angulo, longitud, latitud, altura;
  b = 0;
  c = 10;
  if (datos_gps_preparados == 1)
  {
    //calculos del spin
    b = 0;
    c = 10;
    for (a = 0; a < gps.spin.length; a++)
    {
      if (gps.spin.value[a] == '.')
      {
        c = 1;
      }
      else
      {
        b = b * 10 + gps.spin.value[a] - 0x30;
        c *= 10;
      }
    }
    valor = b / 1.0 / c;
    angulo = valor;
    //////////////////////////////////////////////////////////////////////////
    b = 0;
    c = 10;
    for (a = 0; a < gps.latitud.length; a++)
    {
      if (gps.latitud.value[a] == '.')
      {
        c = 1;
      }
      else
      {
        b = b * 10 + gps.latitud.value[a] - 0x30;
        c *= 10;
      }
    }
    valor = b / c;
    latitud = valor;
    int temp;
    temp = latitud / 100;
    if (gps.latitud.orientacion == 'N')
      latitud = temp + (latitud - temp * 100.0) / 60;
    else
      latitud = (temp + (latitud - temp * 100.0) / 60) * (-1);
    ////////////////////////////////////////////////////////////////////////
    b = 0;
    c = 10;
    for (a = 0; a < gps.longitud.length; a++)
    {
      if (gps.longitud.value[a] == '.')
      {
        c = 1;
      }
      else
      {
        b = b * 10 + gps.longitud.value[a] - 0x30;
        c *= 10;
      }
    }
    valor = b / 1.0 / c;
    longitud = valor;

    int temp2;
    temp2 = longitud / 100;
    if (gps.longitud.orientacion == 'E')
      longitud = temp2 + (longitud - temp2 * 100.0) / 60;
    else
      longitud = (temp2 + (longitud - temp2 * 100.0) / 60) * (-1);

    b = 0;
    c = 10;
    for (a = 0; a < 10; a++)
    {
      if (gga.msl[a] == '.')
      {
        c = 1;
      }
      else
      {
        b = b * 10 + gga.msl[a] - 0x30;
        c *= 10;
      }
    }
    valor = b / 1.0 / c;
    altura = valor;

    //calculos de la velocidad
    b = 0;
    c = 10;
    for (a = 0; a < gps.velocidad.length; a++)
    {
      if (gps.velocidad.value[a] == '.')
      {
        c = 1;
      }
      else
      {
        b = b * 10 + gps.velocidad.value[a] - 0x30;
        c *= 10;
      }
    }
    valor = b / 1.0 / c;
    //velocidad = valor * 1.85184;  //nudos a km/h
    //velocidad = valor * 0.5144;   //nudos a m/s
  }
}
