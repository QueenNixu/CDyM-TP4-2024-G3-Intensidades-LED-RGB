#include "UART.h"
#include "SerialPort.h"
#include <avr/io.h>
#include <stdlib.h>

extern volatile uint8_t red_intensity;
extern volatile uint8_t green_intensity;
extern volatile uint8_t blue_intensity;
extern volatile uint8_t color_recieved_flag;
extern volatile char current_color;

ISR(USART_RX_vect) {
	char received_char = UDR0;
	if (received_char == 'R' || received_char == 'G' || received_char == 'B') {
		current_color = received_char;
		color_recieved_flag = 1;
	}
}

void UART_send_color_intensity(void) {
	char buffer[10];
	
	SerialPort_Wait_For_TX_Buffer_Free();
	SerialPort_Send_String("R: ");
	itoa(red_intensity, buffer, 10);
	SerialPort_Send_String(buffer);
	SerialPort_Wait_For_TX_Buffer_Free();
	SerialPort_Send_String("\r\n");

	SerialPort_Wait_For_TX_Buffer_Free();
	SerialPort_Send_String("G: ");
	itoa(green_intensity, buffer, 10);
	SerialPort_Send_String(buffer);
	SerialPort_Wait_For_TX_Buffer_Free();
	SerialPort_Send_String("\r\n");

	SerialPort_Wait_For_TX_Buffer_Free();
	SerialPort_Send_String("B: ");
	itoa(blue_intensity, buffer, 10);
	SerialPort_Send_String(buffer);
	SerialPort_Wait_For_TX_Buffer_Free();
	SerialPort_Send_String("\r\n");
}
