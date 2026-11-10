const int potPin = 34;  // Chân đọc biến trở (ADC)
const int ledPin = 15;   // Chân nối LED (Đồng thời là LED có sẵn trên bo mạch ESP32)

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int potValue = analogRead(potPin); // Đọc từ biến trở (0 - 4095)
  
  // Chuyển đổi dải giá trị từ (0-4095) của biến trở sang (0-255) cho hàm analogWrite của ESP32
  int brightness = map(potValue, 0, 4095, 0, 255); 
  
  analogWrite(ledPin, brightness);   // Xuất độ sáng ra đèn LED
  delay(10);
}
