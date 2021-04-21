/**
    Header que contiene constantes relevantes para el accionar del programa principal.
    @file constants.h
    @author Franco Abosso
    @author Julio Donadello
    @version 1.0 29/03/2021
*/

#define DEBUG_LEVEL 5				// Nivel de debug (0 inhabilita el puerto serial).
#define SERIAL_BPS 9600				// Bitrate de las comunicaciones por puerto serial.

#define LORA_FREQ 433175000 		// Frecuencia de la transmisión LoRa (en Hz).
#define DEVICE_ID 10009 			// Identificador del nodo.
      
#define LORA_TIMEOUT 20			    // Tiempo entre cada mensaje LoRa.
#define LORA_SYNC_WORD 0x34			// Palabra de sincronización LoRa.



#define TIMING_SLOTS 3 				// Cantidad de slots necesarios de timing (ver timing_helpers.h)

#define TENSION_MOCK 223.11         // Valor de sensado falso.
// #define TEMPERATURA_MOCK 23.11   // Valor de sensado falso.
