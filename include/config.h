#ifndef __CONFIG__
#define __CONFIG__

#include <Arduino.h>
// Define si el programa se compila en modo "DEPURACIÓN"
#define NO_DEBUG
// -----------------------------------------------------

// Definiciones para el termometro.
#define TMP36_POWER PIN_A2
#define TMP36_DATA PIN_A1
#define TMP36_V_A_0_GRADOS 0.5
#define TMP36_TIEMPO_ENCENDIDO 2
#define MINUTOS_ENVIO 1 // Cada X minutos realizamos un envío.

#endif