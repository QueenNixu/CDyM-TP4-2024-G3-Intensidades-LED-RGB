#include "UART.h"
#include "SerialPort.h"

extern volatile uint8_t red_intensity;
extern volatile uint8_t green_intensity;
extern volatile uint8_t blue_intensity;
extern volatile char current_color;

ISR(USART_RX_vect) {
	char received_char = UDR0; // Si el valor recibido es valido (R, G o B) se guarda
	if (received_char == 'R' || received_char == 'G' || received_char == 'B') {
		current_color = received_char;
	}
}

void UART_send_color_intensity(void) { // Enviar a la serie terminal 'RGB: (intensidad rojo, intensidad verde, intensidad azul)'
	char buffer[50]; 
	snprintf(buffer, sizeof(buffer), "RGB: (%d, %d, %d)\r\n", red_intensity, green_intensity, blue_intensity);
	SerialPort_Wait_For_TX_Buffer_Free();
	SerialPort_Send_String(buffer);
}

