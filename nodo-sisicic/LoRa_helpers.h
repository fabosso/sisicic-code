/**
    Header que contiene funcionalidades referidas al módulo SX1278.
    @file LoRa_helpers.h
    @author Franco Abosso
    @author Julio Donadello
    @version 1.2 29/03/2021
*/

/*
    onRecieve() es la función por interrupción que se llama cuando
    existen datos en el buffer LoRa.
*/


void onReceive(int packetSize) {
    #if DEBUG_LEVEL >= 2
        Serial.println("Entering recieve mode");
    #endif
    if (packetSize == 0) {
        return; // if there's no packet, return
    }

    incomingFull = ""; // payload of packet

    while (LoRa.available()) {         // can't use readString() in callback, so
        incomingFull += (char)LoRa.read(); // add bytes one by one
    }


    int delimiter = incomingFull.indexOf(greaterThanStr);
    receiverStr = incomingFull.substring(1, delimiter);

    int receiver = receiverStr.toInt();
    #if DEBUG_LEVEL >= 1
        Serial.print("Receiver: ");
        Serial.println(receiver);
    #endif
    if (receiver == DEVICE_ID) {
        // incomingPayload.reserve(MAX_SIZE_INCOMING_LORA_COMMAND);
        incomingPayload = incomingFull.substring(delimiter + 1);
        #if DEBUG_LEVEL >= 1
            Serial.println("Wait, that's me!");
            Serial.print("I should do this: ");
            Serial.println(incomingPayload);
        #endif
    } else {
        #if DEBUG_LEVEL >= 2
            Serial.println("Whatever...");
        #endif
    }
}

/**
    LoRaInitialize() inicializa el módulo SX1278 con: 
        - la frecuencia y la palabra de sincronización indicados en constants.h
        - los pines indicados en pinout.h, 
    Si por algún motivo fallara, "cuelga" al programa.
*/
void LoRaInitialize() {
    LoRa.setPins(NSS_PIN, RESET_PIN, DIO0_PIN);

    if (!LoRa.begin(LORA_FREQ)) {
        Serial.println("Starting LoRa failed!");
        blockingAlert(2000, 10);    
        while (1);
    }
    LoRa.setSyncWord(LORA_SYNC_WORD);
    LoRa.onReceive(onReceive);
    LoRa.receive();
    
    #if DEBUG_LEVEL >= 1
        Serial.println("LoRa initialized OK.");
    #endif
}

/**
    composeLoRaPayload(states) se encarga de crear la string de carga útil de LoRa,
    a partir de los estados actuales de los sensores.
    Por ejemplo, si:
        DEVICE_ID = 10009;
        currentStates = {"7.66", "223.11", "0"; "23.11"; "0"; "128.22"; "150"}
    Entonces, esta función devuelve:
        "<10009>current=7.66&voltage=223.11&flame=0&temperature=23.11&raindrops=0&gas=128.22&capacity=150"
    @param measures[] Vector de Strings con los valores actuales de los sensores.
    @return La carga útil LoRa.
*/
void composeLoRaPayload(float volts[], float temps[], String& rtn) {
    // Payload LoRA = vector de bytes transmitidos en forma FIFO.
    // | Dev ID |  Tensión | Temperatura |
    rtn += "<";
    rtn += DEVICE_ID;
    rtn += ">";

    rtn += "voltage";
    rtn += "=";
    rtn += getAverage(volts);

    rtn += "&";
    rtn += "temperature";
    rtn += "=";
    rtn += getAverage(temps);
}
