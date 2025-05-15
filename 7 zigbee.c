/*Header Files*/
#include "stm32f4xx.h"
#include< stdio.h >
char t, val;
int relay = 0;
void USART3_config()
{   RCC->AHB1ENR |= 1 << 1;      // Clock for PORTB
    RCC->APB1ENR |= 1 << 18;     // Clock for USART3
    GPIOB->MODER |= 0x00A00000;  // Alternate function of PORTB
    GPIOB->AFR[1] |= 0x00007700; // TX and RX function
    USART3->BRR = 0x1117;        // 9600 baudrate
    USART3->CR1 = 0x200C;        // Enable Transmission and Reception
    USART3->CR1 |= (1 << 5);     // Enable Receive Interrupt
    NVIC->STIR = 39;             // ISR number
    NVIC->ISER[1] |= (1 << 7);   // Enable NVIC_USART3 Interrupt
}
void key_config(void)
{
    /*Enable or disable the AHB1 peripheral clock */
    RCC->AHB1ENR |= 1 << 3;     // enable the clock to portD
    GPIOD->MODER |= 0x00000055; // set port D0-D3 as o/p mode,other pins are input moode 
    GPIOD->OSPEEDR |= 0xAAAAAAAA;
}
/*Function to Initialize
LED*/
void led_config()
{
    RCC->AHB1ENR |= 1 << 3;     // enable clock for port D
    GPIOD->MODER |= 0X00550000; // enable pD8,pD9,pD10,pD11 as output mode
}
void relay_config()
{
    RCC->AHB1ENR |= 1 << 2; // enable clock for port C 
    GPIOC-> MODER |= 0X00050000;  // enable PC16,18 as output mode
}
void stepper_config(void)
{
    RCC->AHB1ENR |= 1 << 1;           // Motor is connected to PORTB 
    GPIOB->MODER |= 0x55000000; // PORTB as output
}
/*Delay Function for Stepper motor*/
void delay()
{
    long int i;
    for (i = 0; i < 300000; i++)
        ;
}
/*Main
Routine*/
void main()
{
    USART3_config();
    led_config();
    key_config();
    stepper_config();
    relay_config();
    GPIOD->ODR =0X0000;
    while (1)
    {
        val = (GPIOD->IDR) & 0xF0; // status of D4 to D7
        if (val == 0xE0)           // 1st column
        {
            USART3->DR = ('R' & 0x01FF);
            while ((USART3->SR & 0x40) == 0)
            {
            }
        }
        else if (val == 0xD0) // 2nd column
        {
            USART3->DR = ('S' & 0x01FF);
            while ((USART3->SR & 0x40) == 0)
            {
            }
        }
        else if (val == 0xB0) // 3rd column
        {
            USART3->DR = ('L' & 0x01FF);
            while ((USART3->SR & 0x40) == 0)
            {
            }
        }
        else if (val == 0x70) // 4th column
        {
            USART3->DR = ('O' & 0x01FF);
            while ((USART3->SR & 0x40) == 0)
            {
            }
        }
    }
}
/*Interrupt Service Routine for USART3*/
void USART3_IRQHandler(void)
{
    int i;
    if (((USART3 > SR) & 0x20) == 0x20)

    {

        t = USART3->DR; // the character from the USART2 data register is saved in t
        if (t == 'R')
        {
            GPIOC->ODR = (~relay) << 9;
        }
        else if (t == 'S')
        {
            for (i = 0; i < 56; i++)
            {
                GPIOB->ODR =
                    0x9000;
                delay();
                GPIOB->ODR = 0x5000;

                delay();
                GPIOB->ODR = 0x6000;
                delay();
                GPIOB->ODR = 0xA000;
                delay();
            }
        }
        else if (t == 'L')
        {
            GPIOD->ODR = 0X0F00;
        }
        else if (t == 'O')
        {
            GPIOD->ODR = 0X0000;
        }
    }
}

int putchar(int data)
{
    USART2->DR = (data & 0x01FF);
    /* Loop until the end of transmission */ 
    while ((USART2->SR & 0x40) == 0);
    return data;
}