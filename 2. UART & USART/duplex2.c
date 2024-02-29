#include"stm32f4xx.h"

void delay(int n) {
int i;
for(i=0;i<(n*3195);i++);
}

void uart6_init(void);
void uart6_write(int ch);
char uart6_read(void);
void uart2_init(void);
void uart2_write(int ch);
char uart2_read(void);
int main(void)
{

	uart6_init();
	uart2_init();
	while (1) {
	char c = uart2_read();
	uart6_write(c);
	//delay(100);
	c = uart6_read();
	uart2_write(c);
	delay(100);


	}


}

void uart6_init(void)
{
	RCC->AHB1ENR |= 1;
	RCC->AHB1ENR |= 4;
	RCC->APB2ENR |= 0x00000020;
	GPIOA->MODER &= ~0x03C00000;
	GPIOA->MODER |= 0x02800000;
	GPIOC->MODER &=~0x0000F000;
	GPIOC->MODER |= 0x0000A000;
	GPIOA->AFR[1] &= ~0x0FF000;
	GPIOA->AFR[1] |= 0x00088000 ;
	GPIOC->AFR[0] &=~0xFF000000;
	GPIOC->AFR[0] |= 0x88000000;
	USART6->BRR = 0x0683;
	USART6->CR1 = 0x000C;
	USART6->CR2 = 0x0000;
	USART6->CR3 = 0x0000;
	USART6->CR1 |= 0x2000;
	//USART6->CR3 =0x0008;

}


void uart2_init(void)
{
	RCC->AHB1ENR |= 1;
	RCC->APB1ENR |= 0x00020000;
	GPIOA->MODER &= ~0x000000F0;
	GPIOA->MODER |= 0x000000A0;

	GPIOA->AFR[0] &= ~0x0000FF00;
	GPIOA->AFR[0] |= 0x00007700 ; /* alt8 for UART4 */
	USART2->BRR = 0x0683; /* 9600 baud @ 16 MHz */
	USART2->CR1 = 0x000C;/* enable Tx, Rx, 8-bit data */
	USART2->CR2 = 0x0000; /* 1 stop bit*/
	USART2->CR3 = 0x0000; /* no flow control */
	USART2->CR1 |= 0x2000;/*enable UART4 */
	//USART2->CR3 =0x0008;
}
void uart2_write(int ch) {
while (!(USART2->SR & 0x0080)) {} // wait until Tx buffer empty
USART2->DR = (ch & 0xFF);
}

void uart6_write(int ch) {
while (!(USART6->SR & 0x0080)) {}
USART6->DR = (ch & 0xFF);
}
char uart6_read(void) {
while (!(USART6->SR & 0x0020)) {}
return USART6->DR;
}
char uart2_read(void) {
while (!(USART2->SR & 0x0020)) {}
return USART2->DR;
}
