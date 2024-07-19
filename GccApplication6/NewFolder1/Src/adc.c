#include "ADC.h"
#include <avr/io.h>

void ADC_Init(void) {
	// Seleccionar la referencia de voltaje: AVcc, canal ADC3
	ADMUX = (1<<REFS0); // AVcc como referencia
	// Habilitar el ADC y establecer el prescaler a 128 (para una frecuencia de reloj de 16 MHz)
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
}

uint16_t ADC_Read(uint8_t channel) {
	// Seleccionar el canal ADC (enmascarar los 3 bits más bajos del canal)
	channel &= 0x07;
	ADMUX = (ADMUX & 0xF8) | channel;

	// Iniciar la conversión
	ADCSRA |= (1<<ADSC);
	// Esperar a que la conversión termine
	while (ADCSRA & (1<<ADSC));
	// Leer el valor del ADC (ADCL primero, luego ADCH)
	return ADCW;
}
