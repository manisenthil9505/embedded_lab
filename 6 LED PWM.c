#include "stm32f4xx.h"
uint16_t PrescalerValue = 0;
static int duty_cycle = 1;
int duty;
void switch_config(void)
{
    RCC->AHB1ENR |= (1 << 3) | (1 << 4); // enable the clock to portD // RCC->AHB1ENR //enable clock to portE
    GPIOD->MODER |= 0x00000055; // set portE as i/p mode,other pins are inputmoode
    GPIOD->OTYPER = 0x00000000;
    GPIOD->PUPDR = 0x00000000;
    GPIOD->OSPEEDR = 0xAAAAAAAA;
}
void delay(int delay)
{
    // int d1,d2;
    for (int i = 0; i < delay; i++)
        for (int j = 0; j < delay; j++)
            ;
}
void TIM3_Config(void)
{
    RCC->APB1ENR |= (1 << 1); // clock for TIM
    RCC->AHB1ENR |= (1 << 2);
    GPIOC->MODER |= 0x0000A000;
    GPIOC->AFR[0] |= 0x22000000;
}
int switch_read()
{
    int val;
    switch_config();
    val = ((GPIOD->IDR) & 0xF0);
    if (val == 0xE0)
    {
        if (duty_cycle <= 0)
            duty_cycle = 1;
        duty_cycle--; // variable decrement
        delay(250);
    }
    else if (val == 0xD0)
    {
        duty_cycle++; // variable increment
        delay(250);
        if (duty >= 1500)
            duty = 1500;
    }
    return (duty_cycle);
}
/* main functions */
int main(void)
{
    TIM3_Config();
    while (1)
    {
        duty = switch_read(); // receive switch value
        /* Compute the prescaler value */
        PrescalerValue = ((uint16_t)((SystemCoreClock / 2) / 21000000) - 1);
        TIM3->ARR = 0x348; // 25khz
        TIM3->PSC = PrescalerValue;
        TIM3->CR1 = (0 << 8) | (0 << 9);
        TIM3->CCMR1 = (1 << 4) | (1 << 5) | (1 << 6);
        TIM3->CCER |= (1 << 0) | (1 << 1); // enable capture/compare2
        TIM3->CCR1 = duty;                 // apply duty cycle
        TIM3->CCMR1 = (1 << 3);            // enable channel1 preload register
        TIM3->CCMR1 = (1 << 12) | (1 << 13) | (1 << 14);
        TIM3->CCER |= (1 << 4) | (1 << 5); // enable capture/compare2
        TIM3->CCR2 = duty;                 // apply duty cycle
        TIM3->CCMR1 = (1 << 11);           // enable channel2 preload register
        TIM3->CR1 = (1 << 0);
    }
}
