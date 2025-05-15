#include "stm32f4xx.h"
int val;
void delay(int a)
{
    int i, j;
    for (i = 0; i < a; i++)
        for (j = 0; j < a; j++)
            ;
}
void lcd_out(unsigned int a)
{
    delay(200);
    GPIOE->BSRRL = 0x0020;            // high RS pin
    GPIOE->ODR = (a << 8) | (1 << 5); // write the data from 8th bit.(i.E) PD8 toPD15
    GPIOE->BSRRL = 0x0080; // enable pin high
    delay(200);
    GPIOE->BSRRH = 0x0080; // enable pin low
}
void Row1_check()
{
    /*1 st row */
    GPIOD->BSRRH = 0x0001;     // low PD0
    GPIOD->BSRRL = 0x000E;     // high PD1 to PD3
    val = (GPIOD->IDR) & 0xF0; // status of D4 to D7
    if (val == 0xE0)           // 1st column
        lcd_out('C');
    else if (val == 0xD0) // 2nd column
        lcd_out('D');
    else if (val == 0xB0) // 3rd column
        lcd_out('E');
    else if (val == 0x70) // 4th column
        lcd_out('F');
}

void Row2_check()
{
    /*2nd row */
    GPIOD->BSRRH = 0x0002;     // low PD1
    GPIOD->BSRRL = 0x000D;     // high PD0,PD2,PD3
    val = (GPIOD->IDR) & 0xF0; // status of D4 to D7
    if (val == 0xE0)           // 1st column
        lcd_out('8');
    else if (val == 0xD0) // 2nd column
        lcd_out('9');
    else if (val == 0xB0) // 3rd column
        lcd_out('A');
    else if (val == 0x70) // 4th column
        lcd_out('B');
}

void Row3_check()
{
    /*3rd row */
    GPIOD->BSRRH = 0x0004;     // low PD2
    GPIOD->BSRRL = 0x000B;     // high PD0,PD1,PD3
    val = (GPIOD->IDR) & 0xF0; // status of D4 to D7
    if (val == 0xE0)           // 1st column
        lcd_out('4');
    else if (val == 0xD0) // 2nd column
        lcd_out('5');
    else if (val == 0xB0) // 3rd column
        lcd_out('6');
    else if (val == 0x70) // 4th column
        lcd_out('7');
}

void Row4_check()
{
    /*4th row*/
    GPIOD->BSRRH = 0x0008;     // low PD3
    GPIOD->BSRRL = 0x0007;     // high PD0,PD1,PD2
    val = (GPIOD->IDR) & 0xF0; // status of D4 to D7
    if (val == 0xE0)           // 1st column
        lcd_out('0');
    else if (val == 0xD0) // 2nd column
        lcd_out('1');
    else if (val == 0xB0) // 3rd column
        lcd_out('2');
    else if (val == 0x70) // 4th column
        lcd_out('3');
}

void command_write(int comm)
{
    delay(200);
    GPIOE->BSRRH = 0x0020;               // low RS pin
    GPIOE->ODR = (comm << 8) | (0 << 5); // write the data from 8th bit.(i.E) PD8 toPD15
    GPIOE->BSRRL = 0x0080; // enable pin high
    delay(200);
    GPIOE->BSRRH = 0x0080; // enable pin low
}

/*Function to configure the GPIO*/
void pinout_config(void)
{
    RCC->AHB1ENR |= 1 << 3;     // enable the clock to portD,
    RCC->AHB1ENR |= 1 << 4;     // enable clock to portE
    GPIOD->MODER |= 0x00000055; // set port PD0-PD3 as o/p mode
    GPIOE->MODER = 0X55555500;  // lcd_pins PE4 to PE15 output pins
}

void main(void)
{
    pinout_config();     // Pinout Configurations
    command_write(0x38); // Function Set
    command_write(0x01); // Clear Display
    command_write(0x0C); // Cursor Off,0x0F for Cursor on
    command_write(0x06); // Address auto increment
    while (1)
    {
        command_write(0x87); // Choose Address 87
        Row1_check();        // Check which key is pressed in the Rows
        Row2_check();
        Row3_check();
        Row4_check();
    }
}
