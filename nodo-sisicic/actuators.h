/**
    Header que contiene funcionalidades referidas a los actuadores conectados.
    @file actuators.h
    @author Franco Abosso
    @author Julio Donadello
    @version 1.0 29/03/2021
*/

int totalPitidos = 3;           // Total de pitidos por alarma.
int tiempoPitido = 133;         // Tiempo de cada pitido del buzzer [ms].
bool resetAlert = false;        // Flag responsable de resetear pitidosRestantes.
int pitidosRestantes = 0;       // Variable que contiene los pitidos restantes.

/**
    blockingAlert() se encarga de realizar una subrutina bloqueante de alerta,
    en base a una cantidad de tiempo y de pitidos dados como parámetros.
    Esta función se utiliza cuando el programa presenta algún tipo de fallo.
    Realiza una serie de 3 pitidos en donde cada pitido (y no-pitido) del buzzer dura 133 ms.
    @param tiempo Tiempo que dura cada pitido.
    @param pitidos Cantidad de pitidos.
*/
void blockingAlert(int tiempo, int pitidos) {
    for (int i = 0; i < pitidos * 2 + 1; i++) {
        digitalWrite(BUZZER_PIN, !digitalRead(BUZZER_PIN));
        delay(tiempo);
    }
}

/**
    startAlert() se encarga de inicializar la subrutina no bloqueante
    de alerta, en base a una cantidad de tiempo y de pitidos dados como parámetros.
    Por ejemplo:
        startAlert(133, 3);
    Realiza una serie de 3 pitidos en donde cada pitido (y no-pitido) del buzzer dura 133 ms.
    @param tiempo Tiempo que dura cada pitido.
    @param pitidos Cantidad de pitidos.
*/
void startAlert(int tiempo, int pitidos) {
    if (resetAlert && pitidosRestantes == 0) {
        return;
    } else {
        tiempoPitido = tiempo;
        totalPitidos = pitidos;
        resetAlert = true;
    }
}

/**
    callbackAlert() se encarga de consultar el estado de la variable resetAlert:
    si existe un pedido de iniciar la alerta, actualiza pitidosRestantes
    en base a totalPitidos (configurado por startAlert()) y baja el flag de pedido.
    Luego, si existen pedidos restantes, los realiza en base a tiempoPitido (configurado
    por startAlert()).
*/
void callbackAlert() {
    if (resetAlert && pitidosRestantes == 0) {
        pitidosRestantes = totalPitidos;
        resetAlert = false;
    }
    if (pitidosRestantes > 0) {
        if(runEvery(tiempoPitido, 3)) {
            digitalWrite(BUZZER_PIN, !digitalRead(BUZZER_PIN));
            if (digitalRead(BUZZER_PIN) == BUZZER_INACTIVO) {
                pitidosRestantes--;
            }
        }
    }
}

/**
    callbackLoRaCommand() se encarga de consultar el estado de la variable incomingPayload.
    Si la variable está vacía, sale de la función.
    Si el comando existe dentro del array de comandos conocidos, ejecuta cierta acción.
    Incluso si no existiera, limpia incomingPayload.
*/
void callbackLoRaCommand() {
    if (incomingPayload == "") {
        return;
    } else if (incomingPayload == knownCommands[0]) { // knownCommands[0]: startAlert
        #if DEBUG_LEVEL
            Serial.print("Haciendo esto >> ");
            Serial.println(incomingPayload);
        #endif
        startAlert(750, 10);
        incomingPayload = "";
    } else {
        #if DEBUG_LEVEL >= 1
            Serial.println(incomingPayload);
            Serial.println("Descartado por payload incorrecto!");
        #endif
        incomingPayload = "";
    }
}
