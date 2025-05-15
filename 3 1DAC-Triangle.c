#include “stm32f4xx.h”
void main()
{
    RCC->AHB1ENR |= 1 << 0;    // Enable clock for Port A
    RCC->APB1ENR |= 1 << 29;   // Enable clock for DAC
    DAC->CR |= 0x000009C1;     // Enable DAC channel 1, Triangular wave generation
    GPIOA->MODER |= 0x00000F00; // PA4 & PA5 are in analog mode.
    int i = 0;
    while (1)
    {
        for (i = 0; i < 4096; i++)
            DAC->DHR12R1 = i; // Write data to 12-bit right aligned data
        for (i = 4096; i >= 0; i--)
            DAC->DHR12R1 = i; // Write data to 12-bit right aligned data
    }
}