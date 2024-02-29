/*#include"stm32f4xx.h"
#include"adc.h"
uint32_t sensor_value;

int main()
{
	pa1_adc_init();
	start();
	//uint32_t adc_read();
	while(1){
	sensor_value= adc_read();
	}

}*/
/*#include "stm32f4xx.h"

void pa1_adc_init(void);
void start(void);
uint32_t adc_read(void);

int main()
{
    pa1_adc_init(); // Initialize the ADC
    start();        // Start the ADC conversion

    while (1)
    {
        uint32_t adcValue = adc_read(); // Read the ADC value
        // Use the adcValue as needed for sensor measurements or other tasks
    }
}

void pa1_adc_init(void)
{
    RCC->AHB1ENR |= (1U << 0);
    GPIOA->MODER |= (3U << 2); // Set PA1 to analog mode

    RCC->APB2ENR |= (1U << 8);
    ADC1->SQR3 = (1U << 1);   // Channel 1 is selected
    ADC1->SQR1 = 0x00;
    ADC1->CR2 |= (1U << 0);   // Enable ADC
}

void start(void)
{
    ADC1->CR2 |= (1U << 30); // Start the conversion
}

uint32_t adc_read(void)
{
    while (!(ADC1->SR & (1U << 1))) {} // Wait for conversion to complete
    return (ADC1->DR);
}
*/
#include "stm32f4xx.h"
#include "adc.h"

#define GPIOAEN		    (1U<<0)
#define ADC1EN			(1U<<8)
#define ADC_CH1			(1U<<0)
#define ADC_SEQ_LEN_1	 0x00
#define CR2_ADON		(1U<<0)
#define CR2_SWSTART		(1U<<30)
#define SR_EOC			(1U<<1)
uint32_t sensor_value;



void pa1_adc_init(void)
{
	/**Configure the ADC GPIO pin **/

	//Enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;
	//Set the mode of PA1 to analog/
	GPIOA->MODER |= (1U<<2);
	GPIOA->MODER |= (1U<<3);

	/**Configure the ADC module**/
	/*Enable clock access to ADC */
	RCC->APB2ENR |= ADC1EN;
	//Conversion sequence start/
	ADC1->SQR3 = ADC_CH1;
	//Conversion sequence length/
	ADC1->SQR1 = ADC_SEQ_LEN_1;
	//Enable ADC module/
	ADC1->CR2 |= CR2_ADON;
}


void start_converstion(void)
{
	ADC1->CR2 |= 2;
	//Start adc conversion/
	ADC1->CR2 |= CR2_SWSTART;

}



uint32_t adc_read(void)
{
	//Wait for conversion to be complete/
	while(!(ADC1->SR & SR_EOC)){}

	//Read converted result/
	return (ADC1->DR);
}
int main(void)
{
	pa1_adc_init();
	start_converstion();
	while(1)
	{

		sensor_value=adc_read();

	}

}
