/*
*Funciones para calcular el nivel de la batería conectada al dispositivo.
*/
#include <adc.h>
// Variable para lectura bateria
const byte bits_Resolucion = 10;
const float tensionMedida = 1100;   // En milivoltios para trabajar sin decimales.
VREF_t estadoVREF;
ADC_t estadoADC0;
float valorConversion = tensionMedida * (pow(2, bits_Resolucion) - 1);


float ADC_BateriaLeerVoltaje(void)
{
    // antes de modificar los registros VREF y ADC0 copiamos el estado actual de los mismos.
    estadoADC0 = ADC0;
    estadoVREF = VREF;
    // Configuramos el valor de la referencia a la entrada del ADC.
    VREF.CTRLA |= VREF_AC0REFSEL_1V1_gc;     // Referencia a la entrada del ADC 1V1.

    // Configuramos el ADC.
    ADC0.CTRLC |= ADC_REFSEL_VDDREF_gc;      // seleccionamos la tensión de la batería como referencia del ADC.
    ADC0.CTRLC |= ADC_PRESC_DIV8_gc;         // Frecuencia ADC FCPU/8, 50 kHz a 1.5MHz para 10 bits de res.

    ADC0.MUXPOS = ADC_MUXPOS_DACREF_gc;      // Seleccionamos DACREF0 (tensión de referencia 1,1) como entrada al ADC.
    ADC0.CTRLD |= ADC_INITDLY_DLY64_gc;      // Delay antes de la primera muestra cuando se despierta.
    ADC0.CTRLA |= ADC_ENABLE_bm;             // Habilitamos el ADC.

    ADC0.COMMAND = ADC_STCONV_bm;            // Empezar una conversión.
    while (!(ADC0.INTFLAGS & ADC_RESRDY_bm)) // Esperar a que la conversión se haya realizado.
    {
        ;
    }
    ADC0.INTFLAGS = ADC_RESRDY_bm; // Limpiar el Flag que indica que se ha realizado la conversión

    // Restauramos el estado inicial de VREF y ADC0.
    ADC0 = estadoADC0;
    VREF = estadoVREF;

    return ((valorConversion / (float)ADC0.RES));
}
