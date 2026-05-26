# ESP32 Tấn Công Deauth - Giao Diện OLED

Ứng dụng tấn công Deauth WiFi ESP32 với giao diện OLED 0.96 inch và 2 nút bấm.

## Cấu Hình Chân Kết Nối (Pinout)

### Màn Hình OLED (SSD1306 128x64 - U8x8)
- **SDA**: GPIO 21
- **SCL**: GPIO 22
- **Địa chỉ I2C**: 0x3C (7-bit)

### Nút Bấm
- **Nút LÊN (Điều hướng)**: GPIO 13 (Input Pull-up)
- **Nút CHỌN (Xác nhận/Dừng)**: GPIO 12 (Input Pull-up)

### Đèn LED (Chỉ Báo Trạng Thái)
- **LED**: GPIO 2

## Sơ Đồ Nối Dây

```
┌─────────────────────────────────────────────────────────────┐
│                   ESP32 Dev Kit                             │
│                                                             │
│  ┌──────────────────────────────────────────────────────┐  │
│  │           OLED SSD1306 128x64                       │  │
│  │          Địa Chỉ I2C: 0x3C                         │  │
│  │                                                    │  │
│  │  [      Màn Hình Hiển Thị      ]                  │  │
│  │                                                    │  │
│  └─────┬──────────┬──────────────────────────────────┘  │
│        │          │                                       │
│     GPIO21      GPIO22                                    │
│     (SDA)       (SCL)                                     │
│        │          │                                       │
│  ┌─────┴──────────┴───────────────────────────────────┐  │
│  │                                                    │  │
│  │  [Nút LÊN]    [Nút CHỌN]      [LED]               │  │
│  │  GPIO 13      GPIO 12         GPIO 2              │  │
│  │     │             │               │                 │  │
│  └─────┴─────────────┴───────────────┴─────────────────┘  │
│        │             │               │                    │
│        └─────────────┴───────────────┘                    │
│                      │                                    │
│                     GND                                   │
│                                                            │
│  Nguồn: 5V USB hoặc 3.3V điều chỉnh                     │
└─────────────────────────────────────────────────────────────┘

Kết Nối Chi Tiết:

┌─ Màn Hình OLED (SSD1306 I2C)
│
│  Chân OLED   →    Chân ESP32
│  ─────────────────────────────
│  VCC         →    3.3V
│  GND         →    GND
│  SDA (pin 4) →    GPIO 21
│  SCL (pin 5) →    GPIO 22

├─ Nút LÊN (GPIO 13)
│  
│  Nút Bấm    →    ESP32
│  ─────────────────────────
│  Chân 1      →    GPIO 13
│  Chân 2      →    GND (có pull-up ~10K bên trong)

├─ Nút CHỌN (GPIO 12)
│  
│  Nút Bấm    →    ESP32
│  ─────────────────────────
│  Chân 1      →    GPIO 12
│  Chân 2      →    GND (có pull-up ~10K bên trong)

└─ Đèn LED (GPIO 2)
   
   LED         →    ESP32
   ───────────────────────────
   Dương (+)   →    GPIO 2 (qua điện trở ~200Ω)
   Âm (-)      →    GND
```

## Các Trạng Thái Giao Diện

1. **QUÉT (SCAN)**: Quét tìm mạng WiFi
2. **CHỌN (SELECT)**: Chọn mạng đích (Nút LÊN/XUỐNG để điều hướng)
3. **XÁC NHẬN (CONFIRM)**: Xác nhận tấn công (LÊN/XUỐNG để chọn CÓ/KHÔNG)
4. **ĐANG TẤN CÔNG (ATTACKING)**: Đang thực hiện tấn công deauth
5. **DỪNG (STOPPED)**: Tấn công hoàn tất, hiển thị thống kê

## Các Phím Điều Khiển

- **Nút LÊN (GPIO 13)**: Điều hướng lên/xuống, chuyển đổi cách chọn
- **Nút CHỌN (GPIO 12)**: Chọn/Xác nhận, dừng tấn công

## Biên Dịch & Tải Lên

```bash
# Biên dịch và tải lên
pio run -t upload

# Theo dõi dữ liệu chuỗi (Serial)
pio device monitor
```

## Tính Năng

- ✅ Quét mạng WiFi
- ✅ Chọn mạng đích bằng điều hướng nút bấm
- ✅ Xác nhận trước khi tấn công
- ✅ Hiển thị trạng thái tấn công real-time trên OLED
- ✅ Hiển thị số lượng thiết bị bị loại bỏ
- ✅ Dừng tấn công bất cứ lúc nào
- ✅ Quay lại quét sau khi tấn công
- ✅ Tối ưu hóa cho màn hình OLED 128x64
- ✅ Nút bấm có chống rung (debouncing)

## Thư Viện Phụ Thuộc

- U8x8 Library (olikraus)
- WiFi (Built-in ESP32)
- esp_wifi (Built-in ESP32)

Tất cả được quản lý trong platformio.ini

## Ghi Chú

- Dự án sử dụng chế độ STA để quét WiFi
- Gửi frame deauth ở chế độ SINGLE (mục tiêu mạng cụ thể)
- Mã lý do deauth mặc định: 7 (Rời khỏi BSS)
- Thời gian chống rung nút: 50ms
- Debug serial kích hoạt (115200 baud)
