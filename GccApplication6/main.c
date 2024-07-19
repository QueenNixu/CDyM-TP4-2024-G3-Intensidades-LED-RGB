#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include "SerialPort.h"
#include "ADC.h"
#include "LED.h"
#include "UART.h"
#include "PWM.h"

volatile uint8_t color_recieved_flag = 0;

int main(void) {
	// Inicializar UART con configuración 9600bps, 8 bits de datos, 1 bit de parada
	SerialPort_Init(0x68);
	SerialPort_TX_Enable();
	SerialPort_RX_Enable();
	SerialPort_RX_Interrupt_Enable();
	
	// Inicializar ADC y PWM
	ADC_Init();
	PWM_Init();
	
	// Configurar el PWM para el manejo de intensidad del rojo
	//PWM_START;
	PWM_Init();
	LED_init();
	
	sei();  // Habilitar interrupciones globales
	
	while (1) {
		if (color_recieved_flag) {
			// Leer el valor del ADC para el color seleccionado
			uint16_t adc_value = ADC_Read(3);
			update_color_intensity(adc_value);
			
			// Enviar intensidades de color por UART
			//UART_send_color_intensity();
			
			// Limpiar el flag
			color_recieved_flag = 0;
		}
		
		// Esperar 500 ms antes de la siguiente iteración
		_delay_ms(500);
	}

	return 0;
}
