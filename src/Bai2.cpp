#define BUTTON_PIN 4      // Nút nhấn nối vào chân D2
#define LED_PIN 5         // Đèn LED nối vào chân D4
#define DEBOUNCE_MS 50    // Thời gian chống dội 50ms

volatile uint32_t count = 0;
volatile unsigned long lastTime = 0;
volatile bool buttonPressed = false; // Cờ báo hiệu có nhấn nút

void IRAM_ATTR handleInterrupt() {
  unsigned long now = millis();
  if (now - lastTime >= DEBOUNCE_MS) {
    count++;
    buttonPressed = true; // Bật cờ khi nút nhấn hợp lệ
    lastTime = now;
  }
}

void setup() {
  Serial.begin(115200);
  
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), handleInterrupt, FALLING);
  
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); // Ban đầu cho LED tắt
  
  Serial.println("=== DEM SO LAN & DIEN KHIEN PHAN HOI LED ===");
}

void loop() {
  // Khi phát hiện có nhấn nút, tiến hành đảo trạng thái LED ngay lập tức
  if (buttonPressed) {
    buttonPressed = false; // Xóa cờ để đợi lần nhấn tiếp theo
    
    // Đảo trạng thái: Đang tắt thành bật, đang bật thành tắt
    digitalWrite(LED_PIN, !digitalRead(LED_PIN)); 
    
    // In số lần đã nhấn lên màn hình Serial Monitor
    Serial.print("So lần đã nhấn: ");
    Serial.println(count);
  }
}
