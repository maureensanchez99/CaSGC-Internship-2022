/*
  Created by Maureen Sanchez, Andres Zamudio, and Manuel Aboite
  Reference Code is cited in the README file of the repository
  Purpose: needs to measure heart rate, blood oxygen levels, and recored the ECG/EKG
*/

#include <SPI.h>  // incluye libreria SPI para comunicacion con el modulo
#include <RH_NRF24.h> // incluye la seccion NRF24 de la libreria RadioHead
#include <DHT.h>  // incluye libreria necesaria para el uso del sensor DHT11
//#include <DHT_U.h>  // incluye libreria necesaria para el uso del sensor DHT11

RH_NRF24 nrf24(9,10);   // crea objeto con valores por defecto para bus SPI
      // y pin digital numero 8 para CE

#define SENSOR  4 // establece a SENSOR con numero 4, pin de senal del DHT11
DHT dht(SENSOR, DHT22); // crea objeto dht

int TEMPERATURA;  // variable para almacenar valor de temperatura
int HUMEDAD;    // variable para almacenar valor de humedad
 
String str_humedad; // string para almacenar valor de humedad
String str_temperatura; // string para almacenar valor de temperatura
String str_datos; // string para almacenar valores separados por coma

void setup() 
{
  Serial.begin(9600);   // inicializa monitor serie a 9600 bps
  if (!nrf24.init())    // si falla inicializacion de modulo muestra texto
    Serial.println("fallo de inicializacion");
  if (!nrf24.setChannel(2)) // si falla establecer canal muestra texto
    Serial.println("fallo en establecer canal");
  if (!nrf24.setRF(RH_NRF24::DataRate250kbps, RH_NRF24::TransmitPower0dBm)) // si falla opciones 
    Serial.println("fallo en opciones RF");           // RF muestra texto

    dht.begin();  // inicializa sensor 
    delay(2000);  // demora de 2 segundos para estabilizar lectura de sensor
}

void loop()
{
    TEMPERATURA = dht.readTemperature();  // obtiene y almacena temperatura
    HUMEDAD = dht.readHumidity();   // obtiene y almacena humedad
    
    str_temperatura = String(TEMPERATURA);  // convierte a string valor entero de temperatura
    str_humedad = String(HUMEDAD);    // convierte a string valor entero de humedad
 
    str_datos = str_temperatura + "," + str_humedad;  // concatena valores separados mediante una coma
    
    static char *datos = str_datos.c_str();   // convierte a string en formato de lenguaje C
    
    nrf24.send((uint8_t *)datos, strlen(datos));  // envia datos
    nrf24.waitPacketSent();       // espera hasta realizado el envio
    delay(1000);          // demora de 1 segundo entre envios
}
