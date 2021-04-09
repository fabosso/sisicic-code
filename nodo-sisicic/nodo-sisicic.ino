/**
    Rutina principal que obtiene los valores sensados y los modula
    y transmite sobre LoRa@433MHz en una string especialmente diseñada.
    @file nodo-sisicic.ino
    @author Franco Abosso
    @author Julio Donadello
    @version 1.1 29/03/2021
*/


// Header que contiene constantes relevantes al accionar de este programa.
#include "constants.h"          // Biblioteca propia.

// Bibliotecas necesarias para manejar al SX1278.
#include <SPI.h>                // https://www.arduino.cc/en/reference/SPI
#include <LoRa.h>               // https://github.com/sandeepmistry/arduino-LoRa

// Bibliotecas necesarias para manejar al DS18B20.
#include <OneWire.h>            // https://www.pjrc.com/teensy/td_libs_OneWire.html
#include <DallasTemperature.h>  // https://www.milesburton.com/Dallas_Temperature_Control_Library

// Biblioteca utilizada para manejar al HC-SR04.
#include <NewPing.h>            // https://bitbucket.org/teckel12/arduino-new-ping/wiki/Home

// Biblioteca utilizada para calcular los valores RMS de los sensores de tensión y corriente.
#include <EmonLib.h>            // https://learn.openenergymonitor.org/electricity-monitoring/ctac/how-to-build-an-arduino-energy-monitor

/**
    currentStates contiene 6 strings que representan el valor actual 
    de la medición de cada uno de los sensores. Estos tienen un orden arbitrario:
    { Corriente, Tensión, Fuego, Temperatura, Lluvia, Combustible }
    Estos valores se refrescan cuando sea requerido, y retienen el valor anterior
    hasta entonces.
*/
String currentStates[6] = {"0.0", "0.0", "0", "0.0", "0", "0.0"};

/**
    refreshRequest contiene 6 variables booleanas que representan la necesidad 
    de refrescar los valores de currentStates. Estos tienen un orden arbitrario:
    { Corriente, Tensión, Fuego, Temperatura, Lluvia, Combustible }
    Una vez refrescado, cada uno de estos booleanos vuelve a ponerse en false.
*/
bool refreshRequested[6] = {false, false, false, false, false, false};

/**
    initiateAlert es un flag que, de ser evaluado a true, dispara una
    alerta con valores preconfigurados. Al finalizar este evento, se
    pone en false automáticamente.
*/ 
bool initiateAlert = true;  

/**
    LoRaPayload es una string que contiene el mensaje preformateado especialmente
    para que, posteriormente, el concentrador LoRa pueda decodificarla.
*/
String LoRaPayload = "";            

// Bibliotecas que agregan funcionalidades.
#include "pinout.h"             // Biblioteca propia.
#include "timing_helpers.h"     // Biblioteca propia.
#include "sensors.h"            // Biblioteca propia.
#include "actuators.h"          // Biblioteca propia.
#include "LoRa_helpers.h"       // Biblioteca propia.

/**
    setup() inicializa el puerto serial, setea el pinout e inicializa 
    los sensores y el SX1278. Esta función se invoca una única vez en el programa.
*/
void setup() {
    #if DEBUG_LEVEL >= 1
        Serial.begin(SERIAL_BPS);
    #endif
    setupPinout();
    LoRaInitialize();
    startAlert(133, 3);
}

/**
    loop() determina las tareas que cumple el programa:
        - cada LORA_TIMEOUT segundos, envía un payload LoRa.
        - si no está ocupado con eso:
            - se ocupa de disparar las alertas preestablecidas.
            - cada 2 segundos, refresca el estado de los sensores.
    Esta función se repite hasta que se le dé un reset al programa.
*/
void loop() {
    if (runEvery(sec2ms(LORA_TIMEOUT), 1)) {
        // Deja de refrescar TODOS los sensores.
        stopRefreshingAllSensors();

        // Compone la carga útil de LoRa.
        LoRaPayload = composeLoRaPayload(currentStates);
        
        #if DEBUG_LEVEL >= 1
            Serial.print("Payload LoRa encolado!: ");
            Serial.println(LoRaPayload);
        #endif

        // Componer y enviar paquete.
        LoRa.beginPacket();
        LoRa.print(LoRaPayload);
        LoRa.endPacket();

        // Inicia la alerta preestablecida.
        startAlert(133, 3);

        LoRa.receive();
    } else {
        callbackAlert();
        
        if(runEvery(sec2ms(2), 2)) {
            // Refresca TODOS los sensores.
            refreshAllSensors();
        }
     
        if (refreshRequested[0] && pitidosRestantes == 0) {
            // Calcula el valor RMS de V e I, y refresca el estado de la corriente
            eMon.calcVI(20,1000);
            refreshCurrent();
        }
        if (refreshRequested[1]) 
            refreshVoltage();
        if (refreshRequested[2]) 
            refreshFlame();
        if (refreshRequested[3]) 
            refreshTemperature();
        if (refreshRequested[4]) 
            refreshRaindrops();
        if (refreshRequested[5]) 
            refreshGas();
    }
}
