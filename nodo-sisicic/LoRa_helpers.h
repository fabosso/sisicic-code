/**
    Header que contiene funcionalidades referidas al módulo SX1278.
    @file LoRa_helpers.h
    @author Franco Abosso
    @author Julio Donadello
    @version 1.2 29/03/2021
*/

/**
    LoRaInitialize() inicializa el módulo SX1278 con: 
        - la frecuencia y la palabra de sincronización indicados en constants.h
        - los pines indicados en pinout.h, 
    Si por algún motivo fallara, "cuelga" al programa.
*/
void LoRaInitialize() {
    D Serial.println("LoRa Sender non-blocking");

    LoRa.setPins(NSS_PIN, RESET_PIN, DIO0_PIN);

    if (!LoRa.begin(LORA_FREQ)) {
        Serial.println("Starting LoRa failed!");
        while (1);
    }
    LoRa.setSyncWord(LORA_SYNC_WORD);
}

/**
    composeLoRaPayload(states) se encarga de crear la string de carga útil de LoRa,
    a partir de los estados actuales de los sensores.
    Por ejemplo, si:
        DEVICE_ID = 10009;
        currentStates = {"7.66", "223.11", "0"; "23.11"; "0"; "128.22"; "150"}
    Entonces, esta función devuelve:
        "<10009>current=7.66&voltage=223.11&flame=0&temperature=23.11&raindrops=0&gas=128.22&capacity=150"
    @param measures[] Vector de trings con los valores actuales de los sensores.
    @return La carga útil LoRa.
*/
String composeLoRaPayload(String measures[]) {
    // Payload LoRA = vector de bytes transmitidos en forma FIFO.
    // | Dev ID | Corriente | Tensión | Fuego | Temperatura | Lluvia | Combustible (nivel) | Combustible (total) |
    String payload;
    payload += "<";
    payload += String(DEVICE_ID);
    payload += ">";

    payload += "current";
    payload += "=";
    payload += measures[0];

    payload += "&";
    payload += "voltage";
    payload += "=";
    payload += measures[1];

    payload += "&";
    payload += "flame";
    payload += "=";
    payload += measures[2];

    payload += "&";
    payload += "temperature";
    payload += "=";
    payload += measures[3];

    payload += "&";
    payload += "raindrops";
    payload += "=";
    payload += measures[4];

    payload += "&";
    payload += "gas";
    payload += "=";
    payload += measures[5];

    payload += "&";
    payload += "capacity";
    payload += "=";
    payload += String(CAPACIDAD_COMBUSTIBLE);
    
    return payload;
}
