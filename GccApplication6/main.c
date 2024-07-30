#include <avr/io.h>
#include <avr/interrupt.h>
#include "SerialPort.h"
#include "ADC.h"
#include "LED.h"
#include "UART.h"
#include "PWM.h"

int main(void) {
	
	SerialPort_Init(0x68); // Inicializar UART con configuración 9600bps, 8 bits de datos, 1 bit de parada
	SerialPort_TX_Enable(); // Habilitar transmision
	SerialPort_RX_Enable(); // Habilitar Recepsion
	SerialPort_RX_Interrupt_Enable(); // Habilitar interrupcion
	
	ADC_Init(); // inicializar ADC
	PWM_Init(); // inicializar PWM (por software y hardware)
	LED_init(); // inicializar intensidades de cada color del LED
	
	sei(); 
	
	while (1) {
		
		// Leer el valor del ADC para el color seleccionado (valor seleccionado por default: 'B')
		uint16_t adc_value = ADC_Read(3);
		update_color_intensity(adc_value);
			
		// Enviar intensidades de color por UART
		UART_send_color_intensity();
	}

	return 0;
}
