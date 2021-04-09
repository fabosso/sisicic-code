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

void startAlert(int tiempo, int pitidos) {
    tiempoPitido = tiempo;
    totalPitidos = pitidos;
    resetAlert = true;
}

int pitidosRestantes = 0;       // Variable que contiene los pitidos restantes.
/**
    callbackAlert() se encarga de consultar el estado de la variable initiateAlert: 
    si existe un pedido de iniciar la alerta, actualiza pitidosRestantes
    en base a TOTAL_PITIDOS y baja el flag de pedido.
    Luego, si existen pedidos restantes, los realiza en base a TIEMPO_PITIDO.
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