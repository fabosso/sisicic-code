/**
    Header que contiene constantes relevantes para el accionar del programa principal.
    @file constants.h
    @author Franco Abosso
    @author Julio Donadello
    @version 1.0 29/03/2021
*/

#define DEBUG						// Imprime mensajes por el puerto serial.
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

#define TIEMPO_PITIDO 133			// Tiempo de cada pitido del buzzer [ms].
#define TOTAL_PITIDOS 3				// Total de pitidos por alarma.

#define TIMING_SLOTS 3 				// Cantidad de slots necesarios de timing (ver timing_helpers.h)

#define CORRIENTE_MOCK "0.26"       // Valores de sensado falsos.
// #define TENSION_MOCK "223.11"    // Valores de sensado falsos.
// #define FLAME_MOCK "0"           // Valores de sensado falsos.
// #define TEMPERATURA_MOCK "23.11" // Valores de sensado falsos.
// #define LLUVIA_MOCK "0"          // Valores de sensado falsos.
#define NAFTA_MOCK "128.22"         // Valores de sensado falsos.
