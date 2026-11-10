#define BUTTON_PIN 4      // Nút nhấn nối vào chân D2
#define LED_PIN 5         // Đèn LED nối vào chân D4

volatile bool ledState = false; // Biến lưu trạng thái bật/tắt của LED
volatile bool buttonPressed = false; // Cờ báo có sự kiện nhấn nút

// Hàm phục vụ ngắt (ISR) - Chạy cực nhanh khi có tín hiệu nhấn nút
void IRAM_ATTR handleButtonInterrupt() {
  ledState = !ledState;     // Đảo trạng thái LED ngay lập tức
  buttonPressed = true;     // Bật cờ báo về hàm loop để in Serial
}

void setup() {
  Serial.begin(115200);
  
  // Cấu hình nút nhấn có điện trở kéo lên nội bộ
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  // Cấu hình ngắt: kích hoạt khi chân BUTTON_PIN chuyển từ HIGH xuống LOW (FALLING)
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), handleButtonInterrupt, FALLING);
  
  // Cấu hình chân LED
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); // Ban đầu tắt LED
  
  Serial.println("=== BAI 1: SU DUNG NGAT (INTERRUPT) DIEU KHIEN LED ===");
}

void loop() {
  // Khi cờ ngắt được bật, xử lý xuất tín hiệu ra LED và in Serial
  if (buttonPressed) {
    buttonPressed = false; // Xóa cờ để đợi lần nhấn tiếp theo
    
    digitalWrite(LED_PIN, ledState); // Cập nhật trạng thái sáng/tắt cho LED
    
    if (ledState) {
      Serial.println("Nut duoc nhan -> LED SANG");
    } else {
      Serial.println("Nut duoc nhan -> LED TAT");
    }
  }
}
