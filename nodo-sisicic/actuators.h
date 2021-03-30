/**
    Header que contiene funcionalidades referidas a los actuadores conectados.
    @file actuators.h
    @author Franco Abosso
    @author Julio Donadello
    @version 1.0 29/03/2021
*/

int pitidosRestantes = 0;   // variable que contiene los pitidos restantes.

/**
    alert() se encarga de consultar el estado de la variable initiateAlert.
        - si existe un pedido de iniciar la alerta, actualiza pitidosRestantes
        en base a TOTAL_PITIDOS y baja el flag de pedido.
    Luego, si existen pedidos restantes, los realiza en base a TIEMPO_PITIDO.
*/
void alert() {
    if (initiateAlert && pitidosRestantes == 0) {
        pitidosRestantes = TOTAL_PITIDOS;
        initiateAlert = false;
    }
    if (pitidosRestantes > 0) {
        if(runEvery(TIEMPO_PITIDO, 3)) {
            digitalWrite(BUZZER_PIN, !digitalRead(BUZZER_PIN));
            if (digitalRead(BUZZER_PIN) == BUZZER_INACTIVO) {
                pitidosRestantes--;
            }
        }
    }
}