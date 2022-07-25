/*
Created by Maureen Sanchez, Andres Zamudio, and Manuel Aboite
Reference Code is cited in the README file of the repository
Purpose: receives data from transmitter Arduino, measures data from attached sensors, displays data onto LCD display 
*/

#include <SPI.h>  // incluye libreria SPI para comunicacion con el modulo
#include <RH_NRF24.h> // incluye la seccion NRF24 de la libreria RadioHead

RH_NRF24 nrf24(9,10);   // crea objeto con valores por defecto para bus SPI
      // y pin digital numero 8 para CE

String str_datos; // string para almacenar valores separados por coma
String str_temperatura; // string para almacenar valor individual de temperatura
String str_humedad; // string para almacenar valor individual de humedad  

void setup() 
{
  Serial.begin(9600);   // inicializa monitor serie a 9600 bps
  if (!nrf24.init())    // si falla inicializacion de modulo muestra texto
    Serial.println("fallo de inicializacion");
  if (!nrf24.setChannel(2)) // si falla establecer canal muestra texto
    Serial.println("fallo en establecer canal");
  if (!nrf24.setRF(RH_NRF24::DataRate250kbps, RH_NRF24::TransmitPower0dBm)) // si falla opciones 
    Serial.println("fallo en opciones RF");             // RF muestra texto
     
    Serial.println("Base iniciada");  // texto para no comenzar con ventana vacia
}

void loop()
{
    uint8_t buf[5];     // buffer de 5 posiciones
    uint8_t buflen = sizeof(buf); // obtiene longitud del buffer
    
    if (nrf24.recv(buf, &buflen)) // si hay informacion valida disponible
    { 
      str_datos = String((char*)buf); // almacena en str_datos datos recibidos
      
      for (int i = 0; i < str_datos.length(); i++) {  // bucle recorre str_datos desde el inicio
        if (str_datos.substring(i, i+1) == ",") { // si en el indice hay una coma
          str_temperatura = str_datos.substring(0, i);  // obtiene desde indice 0 hasta una posicion anterior
          str_humedad = str_datos.substring(i+1); // obtiene desde indice posterior a la coma
          break;          // hasta el final del string y sale del bucle
      }
    }
    Serial.print("Temperatura: ");  // muestra texto
    Serial.print(str_temperatura);  // muestra valor de la variable
    Serial.print(" Humedad: "); // muestra texto
    Serial.println(str_humedad);  // muestra valor de la variabl
    }
}
