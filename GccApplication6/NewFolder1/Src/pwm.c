#include "PWM.h"

#define F_CPU 16000000UL
#define PWM_PERIOD 256
//#define PWM_DELTA 25
#define PWM_DELTA 0
#define PWM_OFF PORTB &= ~(1<<PORTB5)
#define PWM_ON PORTB |= (1<<PORTB5)
#define PWM_START DDRB |= (1<<PORTB5)

volatile uint8_t PWM_delta = PWM_DELTA;

void Timer0_Init(void) {
	
	// Configurar el temporizador 0 en modo CTC (Clear Timer on Compare Match)
	TCCR0A = (1<<WGM01); // Modo CTC
	TCCR0B = (1<<CS01) | (1<<CS00); // Prescaler 64

	// Configurar el valor de comparación para generar interrupciones periódicas
	OCR0A = (F_CPU / 64 / 256 / 50) - 1; // Ajustar para 50 Hz con 256 niveles

	// Habilitar la interrupción de comparación
	TIMSK0 = (1<<OCIE0A);
	
	PWM_START;
}

void PWM_Init(void) {
	
	DDRB |= (1<<DDB5) | (1<<DDB2) | (1<<DDB1); // Configurar los pines PB5, PB2, PB1 como salidas

	// Configurar los temporizadores para generar señales PWM en los pines PB2 y PB1
	// Temporizador 1 para PB1 (OC1A) y PB2 (OC1B)
	TCCR1A = (1<<COM1A1) | (1<<COM1B1) | (1<<WGM10);
	TCCR1B = (1<<WGM12) | (1<<CS11);
	
	Timer0_Init(); // inicializar Timer0 para PWM por software
}

void PWM_soft_Update(void) { // PWM por software
	static uint16_t PWM_position = 0;
	if (++PWM_position >= PWM_PERIOD) {
		PWM_position = 0;
	}
	if (PWM_position < PWM_delta) {
		PWM_ON;
	} else {
		PWM_OFF;
	}
}

ISR(TIMER0_COMPA_vect) {
	PWM_soft_Update();
}
