#include "stm32f4xx.h"
#include <stdio.h>
int ConvertedValue = 0; // Converted value read from ADC1
void adc_configure()
{   
    RCC->APB2ENR |= 1 << 10; // The ADC3 is connected the APB2 peripheral bus thus we will use its clock source
    RCC->AHB1ENR |= 1 << 0; // Enable port A
    // Analog pin configuration
    GPIOA->MODER |= 0x0000000F;
    GPIOA->OSPEEDR = 0xFFFFFFFF;
    GPIOA->PUPDR = 0x00000000;
    /* ADC configuration */
    ADC3->CR2 = 0x00000001;
    ADC3->CR1 = 0x00000000;
    ADC3->CR2 |= 0x00000002;
    ADC3->SQR1 = 0x00000000; 
    ADC3->SQR3 = 0x00000001;
    ADC3->SMPR2 = 0x00000030; // sample time reg
}
int adc_convert()
{
    ADC3->CR2 |= 0x40000000;
    while (!(ADC3->SR & 0x0002));
    return ADC3->DR;
}
void USART2_config()
{
    RCC->AHB1ENR |= 1 << 0;
    RCC->APB1ENR |= 1 << 17;
    // clock to portA
    // clock to USART2
    GPIOA->MODER |= 0x000000A0; // alternate function mode(PA2,PA3)
    GPIOA->AFR[0] |= 0x00007700;
    // USART2 AF
    USART2->CR1 = 0x200C;
    USART2->BRR = 0x16D;
    USART2->CR2 = 0x000;
}
int main(void)
{
    USART2_config();
    adc_configure(); // Start configuration
    while (1)
    {
        // 115200 baud rate
        ConvertedValue = adc_convert();                 // Read the ADC converted value
        printf("\n\r ADC value => %d", ConvertedValue); // print the ADC value
    }
}
int putchar(int data)
{
    USART2->DR = (data & 0x01FF);
    while ((USART2->SR & 0x40) == 0);
    return data;
}