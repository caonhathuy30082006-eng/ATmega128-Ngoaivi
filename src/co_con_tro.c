#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define LCD_RS  PA0
#define LCD_RW  PA1
#define LCD_E   PA2

unsigned char ma_7doan[] = {
    0x3F, 0x06, 0x5B, 0x4F, 0x66,
    0x6D, 0x7D, 0x07, 0x7F, 0x6F
};

volatile unsigned char so_dem = 0;
volatile unsigned char dem_ngat = 0;

ISR(TIMER0_COMP_vect)
{
    dem_ngat++;
    if (dem_ngat >= 125)
    {
        dem_ngat = 0;
        so_dem++;
        if (so_dem > 9)
            so_dem = 0;
    }
}

void timer0_init(void)
{
    TCCR0 = (1 << WGM01) | (1 << CS02) | (1 << CS01);
    OCR0  = 249;
    TIMSK |= (1 << OCIE0);
}

void lcd_xung_enable(void)
{
    PORTA |= (1 << LCD_E);
    _delay_us(2);
    PORTA &= ~(1 << LCD_E);
    _delay_us(100);
}

void lcd_gui_4bit(unsigned char du_lieu)
{
    PORTA = (PORTA & 0x0F) | (du_lieu & 0xF0);
    lcd_xung_enable();
}

void lcd_gui_byte(unsigned char du_lieu)
{
    lcd_gui_4bit(du_lieu);
    lcd_gui_4bit(du_lieu << 4);
}

void lcd_gui_lenh(unsigned char lenh)
{
    PORTA &= ~(1 << LCD_RS);
    PORTA &= ~(1 << LCD_RW);
    lcd_gui_byte(lenh);
    _delay_ms(2);
}

void lcd_putc(unsigned char kytu)
{
    PORTA |= (1 << LCD_RS);
    PORTA &= ~(1 << LCD_RW);
    lcd_gui_byte(kytu);
    _delay_us(100);
}

void lcd_print(char chuoi[])
{
    unsigned char i = 0;
    while (chuoi[i] != '\0')
    {
        lcd_putc(chuoi[i]);
        i++;
    }
}

void lcd_goto(unsigned char hang, unsigned char cot)
{
    if (hang == 0)
        lcd_gui_lenh(0x80 + cot);
    else
        lcd_gui_lenh(0xC0 + cot);
}

void lcd_init(void)
{
    _delay_ms(20);

    lcd_gui_4bit(0x30);
    _delay_ms(5);
    lcd_gui_4bit(0x30);
    _delay_us(150);
    lcd_gui_4bit(0x30);
    _delay_us(150);

    lcd_gui_4bit(0x20);
    _delay_us(150);

    lcd_gui_lenh(0x28);
    lcd_gui_lenh(0x0C);
    lcd_gui_lenh(0x06);
    lcd_gui_lenh(0x01);
    _delay_ms(2);
}

void chay_led(void)
{
    unsigned char i;

    for (i = 0; i < 8; i++)
    {
        PORTB = (1 << i);
        PORTE = ma_7doan[so_dem];
        _delay_ms(150);
    }

    for (i = 7; i > 0; i--)
    {
        PORTB = (1 << i);
        PORTE = ma_7doan[so_dem];
        _delay_ms(150);
    }
}

int main(void)
{
    DDRA = 0xFF;
    DDRB = 0xFF;
    DDRE = 0x7F;

    lcd_init();
    lcd_goto(0, 0);
    lcd_print("Huy hoc DTVT");
    lcd_goto(1, 0);
    lcd_print("ATmega128 Lab");

    timer0_init();
    sei();

    while (1)
    {
        PORTE = ma_7doan[so_dem];
        chay_led();
    }
}