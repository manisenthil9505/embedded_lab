#include "stm32f4xx.h"
void delay(long int a)
{
    long int b, c;
    for (b = 0; b < a; b++)
        for (c = 0; c < a; c++);
}
void LED_init()
{
    RCC->AHB1ENR = 1 << 3;     // enable the clock to port D
    GPIOD->MODER = 0x55555555;   // select all pins as output mode
    GPIOD->OTYPER = 0x00000000;  // push-pull type
    GPIOD->OSPEEDR = 0xAAAAAAAA; // 50MHz speed
    GPIOD->PUPDR = 0x00000000;   // no pull-up no pull down
}
void main()
{
    LED_init(); // LED initialization 
    while(1)
    {
        GPIOD->ODR = 0x00000A00; // led turns ON 
        delay(3000); //delay
        GPIOD->ODR = 0x00000000; // led turns OFF 
        delay(3000); //delay
    }
}