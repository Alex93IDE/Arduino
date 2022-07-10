
#ifndef GPS_H
#define GPS_H

class GPS
{
public:
  GPS();

  typedef struct
  {
    unsigned char hora;
    unsigned char minuto;
    unsigned char segundo;
    unsigned char dia;
    unsigned char mes;
    unsigned char anno;
    unsigned char dia_week;

  } HoraDecGPS;

  HoraDecGPS horagps;

  char sentencia_gga[83];
  char sentencia_gsa[83];
  char sentencia_gps[83];
  double velocidad;

  void agregando_buffer_gps(char caracter_recibido);
  void enviarSerie();
  void decodificar_trama_gps();
  void cargar_reloj_GPS();
  void convirtiendo_trama_gps();

private:
  typedef struct
  {
    char fix;
    char PDOP[5];
    char HDOP[5];
    char VDOP[5];
  } GSA;
  typedef struct
  {
    char msl[10]; //altitud con respecto al nivel del mar
    char nosv[3]; //satÃƒÂ©lites en uso
    char umsl;    //
  } GGA;

  typedef struct
  {

    struct
    {
      char value[14];
      char length;
      char orientacion;
    } latitud, longitud;
    char fecha[7];
    char horas[7];

    struct
    {
      char value[8];
      char length;
    } velocidad;

    struct
    {
      char value[7];
      char length;
    } spin;
    char estado;
  } RMC;

  RMC gps;
  GGA gga;
  GSA gsa;

  char datos_gps_preparados;
  char datos_gga_adquiridos;
  char datos_rmc_adquiridos;
  char datos_gsa_adquiridos;
  char datos_gps_adquiridos;
  char trama_activa;
  char bufer_gps[83];
  unsigned char contador_sentencia_gps;
  unsigned char contador_sentencia_gsa;
  unsigned char contador_comas_gsa;
  unsigned char contador_bufer_gps;
  unsigned char contador_sentencia_gga;
  unsigned char contador_comas_gga;
  unsigned char contador_campo_altitud;
  char usohorario;
  bool tipo_anno;

  void correccion_usohorario();
  void adquiriendo_bufer_gps_rmc();
  void adquiriendo_bufer_gps_gga();
  void adquiriendo_bufer_gps_gsa();
  void DatosGPSAdquiridos();
  void analizar_bufer_gps();
  void ajuste_de_calendario();
  void calcular_tipo_dia();
  
};

extern GPS mi_gps;

#endif
