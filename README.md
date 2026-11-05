Project ATmega128 — Lập trình giao tiếp ngoại vi

Bài tập môn Kỹ thuật Vi xử lý — Chủ đề: Lập trình giao tiếp ngoại vi với ATmega128 (Proteus, bộ nhớ + con trỏ).

Chức năng
Ngoại vi	Mô tả
LCD 16x2	Chế độ 4-bit, hiển thị "Huy hoc DTVT" / ATmega128 Lab"
LED 7 đoạn	Đếm 0–9, mỗi số 1 giây, dùng Timer0 chế độ CTC
8 LED đơn	Hiệu ứng chạy trái–phải liên tục
Phần cứng
Vi điều khiển: ATmega128, clock nội 8 MHz
Mô phỏng: Proteus 8 Professional
Sơ đồ nối chân
Ngoại vi	Chân ATmega128
LCD RS, RW, E	PA0, PA1, PA2
LCD D4–D7	PA4–PA7
8 LED hiệu ứng	PB0–PB7 (qua điện trở 330Ω)
LED 7 đoạn a–g	PE0–PE6 (common cathode, qua 330Ω)

Biến trở 1kΩ nối chân VEE của LCD để chỉnh tương phản.

Môi trường phát triển
VS Code + extension PlatformIO IDE
Trình biên dịch: avr-gcc (toolchain-atmelavr)
Build
bash
# Build môi trường mặc định
pio run

# Build một môi trường cụ thể
pio run -e lcd_7seg

Hoặc trong VS Code: nhấn Ctrl+Alt+B.

File hex sau khi build nằm ở:

.pio/build/<ten_moi_truong>/firmware.hex
Nạp vào Proteus
Mở file mạch trong Proteus
Bấm đúp vào U1 (ATmega128)
Ở ô Program File, chọn file firmware.hex
Bấm OK rồi nhấn Play

Các kỹ thuật bộ nhớ và con trỏ áp dụng
Kỹ thuật	Áp dụng ở đâu
Mảng và chỉ số	Bảng mã 7 đoạn ma_7doan[]
Con trỏ tới mảng	Hàm chay_hieu_ung(unsigned char *p, ...)
Số học con trỏ	p++ để duyệt qua từng phần tử
Con trỏ chuỗi	Hàm lcd_print(char chuoi[]) duyệt đến '\0'
Biến volatile	so_dem, dem_ngat dùng chung giữa ISR và chương trình chính
Thanh ghi ánh xạ bộ nhớ	PORTA, PORTB, PORTE, DDRx, TCCR0, OCR0
Tính toán Timer0 (chế độ CTC)
Clock hệ thống      = 8.000.000 Hz
Prescaler           = 256
Tần số Timer        = 8.000.000 / 256 = 31.250 Hz
OCR0                = 249  (đếm 0 → 249, tức 250 bước)
Tần số ngắt         = 31.250 / 250 = 125 Hz
Số lần ngắt / giây  = 125  → đếm đủ 125 lần = đúng 1 giây
