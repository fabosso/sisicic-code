/**
    Header que indica el pinout de los nodos LoRa.
    @file pinout.h
    @author Franco Abosso
    @author Julio Donadello
    @version 1.6 29/03/2021
*/

// Pinout RA-02.
#define NSS_PIN 10
#define RESET_PIN -1
#define DIO0_PIN 2
#define DIO1_PIN 3
#define DIO2_PIN 4
#define RXTX_PIN -1

// Pinout sensores y actuadores.
#define TENSION_PIN A1
#define BUZZER_PIN 9
#define TEMPERATURA_PIN 8
#define RELE_PIN 7

// Definición de modo de trabajo.
#define BUZZER_ACTIVO LOW
#define BUZZER_INACTIVO HIGH

// Instanciamiento de objetos relacionados al pinout.
EnergyMonitor eMon;
OneWire oneWireObjeto(TEMPERATURA_PIN);
DallasTemperature sensorDS18B20(&oneWireObjeto);
/**
    setupPinout() determina las I/Os digitales, inicializa al DS18B20
    y calibra el módulo sensor de tensión.
*/
void setupPinout() {
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(TEMPERATURA_PIN, INPUT);
    pinMode(RELE_PIN, OUTPUT);
    sensorDS18B20.begin();
    eMon.voltage(TENSION_PIN, 226.0, 1.7);
}
