#include <Arduino.h>
#include <config.h>
#include <lecturaDatos.h>

// Datos conversor ADC
const double tensionReferencia = 1.5, resolucionLectura = 1023;
// Sensor de temperatura.
double temperatura, lecturaTMP36, tension;
unsigned long inicioCuentaAtras;      // Variable genérica para controlar tiempos en bucles.

// Lee la temperatura del termometro y la tensión de la bateria.
double lecturaDatos()
{
    // Encendemos el termómetro.
    digitalWrite(TMP36_POWER, HIGH);

    // Esperamos a que se complete el tiempo de encendido.
    inicioCuentaAtras = millis();
    while (millis() - inicioCuentaAtras < TMP36_TIEMPO_ENCENDIDO)
    {
    }

    // Una ve que ha pasado el tiempo de encendido leemos el valor.
    lecturaTMP36 = analogRead(TMP36_DATA);

    // Una vez leida la temperatura apagamos el termómetro.
    digitalWrite(TMP36_POWER, LOW);

    // Ahora convertimos la lectura a voltios.
    tension = tensionReferencia * lecturaTMP36 / resolucionLectura;

    // Ya tenemos la tensión, ahora la pasamos a grados.
    temperatura = (tension - TMP36_V_A_0_GRADOS) * 100.0;
	return temperatura;
}
