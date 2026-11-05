#include <avr/io.h>
#include <util/delay.h>

/* Chạy 1 LED từ PB0 đến PB7 */
void chay_trai_phai(void)
{
    unsigned char i;
    for (i = 0; i < 8; i++)
    {
        PORTB = 1 << i;      // bật đúng LED thứ i
        _delay_ms(150);
    }
}

/* Chạy 1 LED từ PB7 về PB0 */
void chay_phai_trai(void)
{
    signed char i;           // phải dùng signed vì i giảm xuống -1 để thoát vòng lặp
    for (i = 7; i >= 0; i--)
    {
        PORTB = 1 << i;
        _delay_ms(150);
    }
}

/* Cả 8 LED nhấp nháy 3 lần */
void nhap_nhay(void)
{
    unsigned char i;
    for (i = 0; i < 3; i++)
    {
        PORTB = 0xFF;        // sáng hết
        _delay_ms(200);
        PORTB = 0x00;        // tắt hết
        _delay_ms(200);
    }
}

int main(void)
{
    DDRB = 0xFF;             // PB0..PB7 là ngõ ra

    while (1)
    {
        chay_trai_phai();
        chay_phai_trai();
        nhap_nhay();
    }
}