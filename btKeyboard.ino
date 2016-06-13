#include <btHIDBoot.h>
#include <LowPower.h>
#include <SoftwareSerial.h>
#include <SPI.h>

USB Usb;
HIDBoot<HID_PROTOCOL_KEYBOARD> HidKeyboard(&Usb);

uint32_t next_time;
const int btTx = 3;
const int btRx = 2;
const int btRst = 4;
SoftwareSerial BT = SoftwareSerial(btRx, btTx);

class BtKeyboardParser : public BtKeyboardReportParser {
  protected:
    void OnKeyDown(uint8_t mod, uint8_t key, uint8_t buf[]);
    void OnKeyUp(uint8_t mod, uint8_t key, uint8_t buf[]);
};

void BtKeyboardParser::OnKeyDown(uint8_t mod, uint8_t key, uint8_t buf[]) {
  BT.write(0xFD);
  Serial.println("Key Down");
  for(uint8_t i = 0; i < 8; ++i) {
    Serial.print(buf[i]);
    BT.write(buf[i]);
    Serial.print(" ");  
  }
  Serial.println("");
  if(buf[0] == 0 && buf[1] == 0 && buf[2] == 21 && buf[3] == 22 && buf[4] == 23 && buf[5] == 0 && buf[6] == 0 && buf[7] == 0) {
    digitalWrite(btRst, HIGH);
    Serial.println("reset");
    delay(7000);
    digitalWrite(btRst, LOW);
  }
}

void BtKeyboardParser::OnKeyUp(uint8_t mod, uint8_t key, uint8_t buf[]) {
  BT.write(0xFD);
  Serial.println("Key Up");
  for(uint8_t i = 0; i < 8; ++i) {
    Serial.print(buf[i]);
    BT.write(buf[i]);
    Serial.print(" ");  
  }
  Serial.println("");
}

BtKeyboardParser Prs;

void setup() {
  pinMode(btRst, OUTPUT);
  digitalWrite(btRst, LOW);
  Serial.begin(115200);
  BT.begin(9600);
  Serial.println("Start");

  if (Usb.Init() == -1) Serial.println("OSC did not start.");
  delay(200);

  next_time = millis() + 5000;
  HidKeyboard.SetReportParser(0, (HIDReportParser*)&Prs);
  LowPower.idle(SLEEP_FOREVER, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_ON, SPI_ON, USART0_ON, TWI_OFF);
}

void loop() {
  Usb.Task();
}
