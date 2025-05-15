#include “stm32f4xx.h”
void delay()
{
    long int i;
    for (i = 0; i < 300000; i++)
}
void motor_PIN_config()
{
    RCC->AHB1ENR |= 1 << 1;     // Enable clock for Port B
    GPIOB->MODER |= 0x55000000; // PB12, PB13, PB14 & PB15 are in output mode.
}
void clockwise()
{
    for (int i = 0; i <= 25; i++)
    {
        GPIOB->ODR = 0x9000;
        delay();
        GPIOB->ODR = 0x5000;
        delay();
        GPIOB->ODR = 0x6000;
        delay();
        GPIOB->ODR = 0xA000;
        delay();
    }
}
void anticlockwise()
{
    for (int i = 0; i <= 25; i++)
    {
        GPIOB->ODR = 0xA000;
        delay();
        GPIOB->ODR = 0x6000;
        delay();
        GPIOB->ODR = 0x5000;
        delay();
        GPIOB->ODR = 0x9000;
        delay();
    }
}

void main()
{
    motor_PIN_config();
    while (1)
    {
        clockwise();
        anticlockwise();
    }
}