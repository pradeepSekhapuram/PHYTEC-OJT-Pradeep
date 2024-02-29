#include"stm32f4xx.h"

void uart6_init(void);
void uart6_write(int ch);
char uart6_read(void);

int main(void)
{
	char c;
	uart6_init();
	while (1) {
	c = uart6_read();
	uart6_write(c);
	}

}

void uart6_init(void)
{
	RCC->AHB1ENR |= 1;
	RCC->APB2ENR |= 0x00000020;
	GPIOA->MODER &= ~0x03C00000;
	GPIOA->MODER |= 0x02800000;
	GPIOA->AFR[1] &= ~0x0FF000;
	GPIOA->AFR[1] |= 0x00088000 ;
	USART6->BRR = 0x0683;
	USART6->CR1 = 0x000C;
	USART6->CR2 = 0x0000;
	USART6->CR3 = 0x0000;
	USART6->CR1 |= 0x2000;

}



void uart6_write(int ch) {
while (!(USART6->SR & 0x0080)) {}
USART6->DR = (ch & 0xFF);
}
char uart6_read(void) {
while (!(USART6->SR & 0x0020)) {}
return USART6->DR;
}
