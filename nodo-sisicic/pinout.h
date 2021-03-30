/**
    Header que indica el pinout de los nodos LoRa.
    También define el modo de trabajo (active low / active high) de:
        - buzzer
        - sensor fuego
        - sensor lluvia
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
#define CORRIENTE_PIN A2
#define TENSION_PIN A1
#define FLAMA_PIN A0
#define BUZZER_PIN 9
#define TEMPERATURA_PIN 8
#define LLUVIA_PIN 7
#define COMBUSTIBLE_ECHO_PIN 6
#define COMBUSTIBLE_TRIG_PIN 5

// Definición de modo de trabajo.
#define FLAMA_THRESHOLD 2.0
#define FLAMA_ACTIVA GND
#if FLAMA_ACTIVA == GND
    #define FUEGO analogRead(FLAMA_PIN) < (FLAMA_THRESHOLD * 1024 / 3.3)
#else
    #define FUEGO analogRead(FLAMA_PIN) >= (FLAMA_THRESHOLD * 1024 / 3.3)
#endif
#define BUZZER_ACTIVO LOW
#define BUZZER_INACTIVO HIGH
#define LLUVIA_ACTIVA LOW

// Instanciamiento de objetos relacionados al pinout.
EnergyMonitor eMon;                   
OneWire oneWireObjeto(TEMPERATURA_PIN);
DallasTemperature sensorDS18B20(&oneWireObjeto);
NewPing sonar(COMBUSTIBLE_TRIG_PIN, COMBUSTIBLE_ECHO_PIN, 300);

/**
    setupPinout() determina las I/Os digitales, inicializa al DS18B20
    y calibra los sensores de tensión y corriente.
*/
void setupPinout() {
    pinMode(BUZZER_PIN, OUTPUT);
    digitalWrite(BUZZER_PIN, BUZZER_INACTIVO);
    pinMode(TEMPERATURA_PIN, INPUT);
    pinMode(LLUVIA_PIN, INPUT);
    pinMode(COMBUSTIBLE_ECHO_PIN, INPUT);
    pinMode(COMBUSTIBLE_TRIG_PIN, OUTPUT);  
    sensorDS18B20.begin(); 
    eMon.voltage(TENSION_PIN, 226.0, 1.7);
    eMon.current(CORRIENTE_PIN, 58.8);    
}
