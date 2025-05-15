#include “stm32f4xx.h”
void delay(long int a)
{
    long int b, c;
    for (b = 0; b < a; b++)
        for (c = 0; c < a; c++)
            ;
}
void main()
{
    RCC->AHB1ENR |= 1 << 0;                      // Enable clock for Port A
    RCC->APB1ENR |= 1 << 29;                     // Enable clock for DAC
    DAC->CR |= 0x00000901;
    GPIOA->MODER |= 0x00000F00; // PA4 & PA5 are in analog mode.
    int i = 0;
    while (1)
    {
        DAC->DHR12R1 = 4095; // Write data to 12-bit right aligned data
        delay(300);
        DAC->DHR12R1 = 0; // Write data to 12-bit right aligned data
        delay(300);
    }
}