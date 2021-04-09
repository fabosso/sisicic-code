/**
    Header que contiene constantes relevantes para el accionar del programa principal.
    @file constants.h
    @author Franco Abosso
    @author Julio Donadello
    @version 1.0 29/03/2021
*/

#define DEBUG_LEVEL 1				// Imprime mensajes por el puerto serial.
#define SERIAL_BPS 9600				// Bitrate de las comunicaciones por puerto serial.

#define LORA_FREQ 433175000 		// Frecuencia de la transmisión LoRa (en Hz).
#define DEVICE_ID 10009 			// Identificador del nodo.
#define LORA_TIMEOUT 30			    // Tiempo entre cada mensaje LoRa.
#define LORA_SYNC_WORD 0x34			// Palabra de sincronización LoRa.

#define MAX_DISTANCE 50         	// Distancia al fondo del tanque [F].
#define MIN_DISTANCE 5          	// Distancia al borde del tanque [B].
#define CAPACIDAD_COMBUSTIBLE 150   // Capacidad del tanque (en L).
#define PI_TIMES_R_SQUARED (CAPACIDAD_COMBUSTIBLE) / (MAX_DISTANCE - MIN_DISTANCE)
#define PING_SAMPLES 5				// Cantidad de muestras ultrasónicos.

#define TIMING_SLOTS 3 				// Cantidad de slots necesarios de timing (ver timing_helpers.h)

#define CORRIENTE_MOCK "0.26"       // Valor de sensado falso.
// #define TENSION_MOCK "223.11"    // Valor de sensado falso.
// #define FLAME_MOCK "0"           // Valor de sensado falso.
// #define TEMPERATURA_MOCK "23.11" // Valor de sensado falso.
// #define LLUVIA_MOCK "0"          // Valor de sensado falso.
#define NAFTA_MOCK "128.22"         // Valor de sensado falso.
