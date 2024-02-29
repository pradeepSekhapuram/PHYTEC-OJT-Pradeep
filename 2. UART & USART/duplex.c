#include"stm32f4xx.h"

void uart1_init(void);
void uart1_write(int ch);
char uart1_read(void);
void uart6_init(void);
void uart6_write(int ch);
char uart6_read(void);

int main(void)
{
	char c;
	char ch;
	uart1_init();
	uart6_init();
//	ch = uart6_read();
//	uart6_write(ch);

	while(1)
	{
		c = uart1_read();
		uart1_write(c);
	}


}


void uart1_init(void)
{
	RCC->AHB1ENR |= 1;
	RCC->APB2ENR |= 0x00000010;
	GPIOA->MODER &= ~0x003C0000;
	GPIOA->MODER |= 0x00280000;
	GPIOA->AFR[1] &= ~0x0FF0;
	GPIOA->AFR[1] |= 0x0770 ; /* alt8 for UART4 */
	USART1->BRR = 0x0683; /* 9600 baud @ 16 MHz */
	USART1->CR1 = 0x000C;/* enable Tx, Rx, 8-bit data */
	USART1->CR2 = 0x0000; /* 1 stop bit*/
	USART1->CR3 = 0x0000; /* no flow control */
	USART1->CR1 |= 0x2000; /*enable UART4 */

}



void uart1_write(int ch) {
while (!(USART1->SR & 0x0080)) {} // wait until Tx buffer empty
USART1->DR = (ch & 0xFF);
}
/* Read a character from UART4 */
char uart1_read(void) {
while (!(USART1->SR & 0x0020)) {} // wait until char arrives
return USART1->DR;
}








void uart6_init(void)
{
	RCC->AHB1ENR |= 1;
	RCC->APB2ENR |= 0x00000020;
	GPIOA->MODER &= ~0x03C00000;
	GPIOA->MODER |= 0x02800000;
	GPIOA->AFR[1] &= ~0x0FF0;
	GPIOA->AFR[1] |= 0x00088000 ; /* alt8 for UART4 */
	USART6->BRR = 0x0683; /* 9600 baud @ 16 MHz */
	USART6->CR1 = 0x000C;/* enable Tx, Rx, 8-bit data */
	USART6->CR2 = 0x0000; /* 1 stop bit*/
	USART6->CR3 = 0x0000; /* no flow control */
	USART6->CR1 |= 0x2000; /*enable UART4 */

}



void uart6_write(int ch) {
while (!(USART6->SR & 0x0080)) {} // wait until Tx buffer empty
USART6->DR = (ch & 0xFF);
}
/* Read a character from UART4 */
char uart6_read(void) {
while (!(USART6->SR & 0x0020)) {} // wait until char arrives
return USART6->DR;
}



