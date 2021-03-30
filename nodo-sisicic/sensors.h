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
    D Serial.println("Refrescando sensores!");
}

/**
    stopRefreshingAllSensors() se encarga de parar el refresco de todos los sensores,
    poniendo cada uno de los flags del vector refreshRequested en false.
*/
void stopRefreshingAllSensors() {
    for(int i = 0; i < 6; i++) {
        refreshRequested[i] = false;
    }
    D Serial.println("Abandonando refrescos!");
}

/**
    refreshCurrent() se encarga de refrescar el estado de la medición de corriente.
    Luego de hacerlo, baja el flag correspondiente en refreshRequested.
*/
void refreshCurrent() {
    currentStates[0] = String(eMon.Irms);
    D Serial.println("Nueva corriente: " + currentStates[0]);
    refreshRequested[0] = false;
}

/**
    refreshVoltage() se encarga de refrescar el estado de la medición de tensión.
    Luego de hacerlo, baja el flag correspondiente en refreshRequested
*/

void refreshVoltage() {
    currentStates[1] = String(eMon.Vrms);
    D Serial.println("Nueva tension: " + currentStates[1]);
    refreshRequested[1] = false;
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
    D Serial.println("Nueva flama: " + currentStates[2]);
    refreshRequested[2] = false;
}


/**
    refreshTemperature() se encarga de refrescar el estado de la medición de temperatura.
    Luego de hacerlo, baja el flag correspondiente en refreshRequested.
*/
void refreshTemperature() {
    sensorDS18B20.requestTemperatures();
    currentStates[3] = String(sensorDS18B20.getTempCByIndex(0));
    D Serial.println("Nueva temperatura: " + currentStates[3]);
    refreshRequested[3] = false;
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
    D Serial.println("Nueva lluvia: " + currentStates[4]);
    refreshRequested[4] = false;
}

float dist = 0.0;
float height = 0.0;
/**
    refreshGAs() se encarga de refrescar el estado del nivel de combustible
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
    D Serial.println("Nueva nafta: " + currentStates[5]);
    refreshRequested[5] = false;
}
