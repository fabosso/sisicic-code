/**
    Header que contiene funcionalidades referidas a los sensores conectados.
    @file sensors.h
    @author Franco Abosso
    @author Julio Donadello
    @version 1.0 29/03/2021
*/


/**
    refreshAllSensors() se encarga de pedir el refresco de todos los sensores,
    poniendo cada uno de los flags del vector refreshRequested en true.
*/
void refreshAllSensors() {
    for(int i = 0; i < 6; i++) {
        refreshRequested[i] = true;
    }
    #if DEBUG_LEVEL >= 2
        Serial.println("Refrescando sensores!");
    #endif
}

/**
    stopRefreshingAllSensors() se encarga de parar el refresco de todos los sensores,
    poniendo cada uno de los flags del vector refreshRequested en false.
*/
void stopRefreshingAllSensors() {
    for(int i = 0; i < 6; i++) {
        refreshRequested[i] = false;
    }
    #if DEBUG_LEVEL >= 2
        Serial.println("Abandonando refrescos!");
    #endif
}

/**
    refreshCurrent() se encarga de refrescar el estado de la medición de corriente.
    Luego de hacerlo, baja el flag correspondiente en refreshRequested.
*/
void refreshCurrent() {
    currentStates[0] = String(eMon.Irms);
    refreshRequested[0] = false;
    #if DEBUG_LEVEL >= 3
        Serial.println("Nueva corriente: " + currentStates[0]);
    #endif
}

/**
    refreshVoltage() se encarga de refrescar el estado de la medición de tensión.
    Luego de hacerlo, baja el flag correspondiente en refreshRequested
*/

void refreshVoltage() {
    currentStates[1] = String(eMon.Vrms);
    refreshRequested[1] = false;
    #if DEBUG_LEVEL >= 3
        Serial.println("Nueva tension: " + currentStates[1]);
    #endif
}

/**
    refreshFlame() se encarga de chequear que el valor de tensión analógica devuelto
    por el sensor de fuego haya (o no haya) superado el nivel threshold correspondiente.
    Luego de hacerlo, baja el flag correspondiente en refreshRequested.
*/
void refreshFlame() {  
    if (FUEGO) {
        currentStates[2] = "1";
    } else {
        currentStates[2] = "0";
    }
    refreshRequested[2] = false;
    #if DEBUG_LEVEL >= 3
        Serial.println("Nueva flama: " + currentStates[2]);
    #endif
}


/**
    refreshTemperature() se encarga de refrescar el estado de la medición de temperatura.
    Luego de hacerlo, baja el flag correspondiente en refreshRequested.
*/
void refreshTemperature() {
    sensorDS18B20.requestTemperatures();
    currentStates[3] = String(sensorDS18B20.getTempCByIndex(0));
    refreshRequested[3] = false;
    #if DEBUG_LEVEL >= 3
        Serial.println("Nueva temperatura: " + currentStates[3]);
    #endif
}

/**
    refreshTemperature() se encarga de refrescar el estado del sensado de lluvia.
    Luego de hacerlo, baja el flag correspondiente en refreshRequested.
*/
void refreshRaindrops() {
    if (digitalRead(LLUVIA_PIN) == LLUVIA_ACTIVA) {
        currentStates[4] = "1";
    } else {
        currentStates[4] = "0";
    }
    refreshRequested[4] = false;
    #if DEBUG_LEVEL >= 3
        Serial.println("Nueva lluvia: " + currentStates[4]);
    #endif
}

float dist = 0.0;
float height = 0.0;
/**
    refreshGas() se encarga de refrescar el estado del nivel de combustible
    Luego de hacerlo, baja el flag correspondiente en refreshRequested.
*/
void refreshGas() {
    dist = sonar.ping_median(PING_SAMPLES);
    dist = sonar.convert_cm(dist);
    if (dist < MIN_DISTANCE) {
        currentStates[5] = String(float(CAPACIDAD_COMBUSTIBLE));
    } else {
        height = MAX_DISTANCE - dist;
        currentStates[5] = String(PI_TIMES_R_SQUARED * height);
    }
    refreshRequested[5] = false;
    
    #if DEBUG_LEVEL >= 4
        Serial.println(String(dist) + " cm");
    #elif DEBUG_LEVEL >= 3  
        Serial.println("Nueva nafta: " + currentStates[5]);
    #endif
}
