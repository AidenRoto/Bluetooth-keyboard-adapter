#include <btHIDBoot.h>
#include <LowPower.h>3
#include <SoftwareSerial.h>
#include <SPI.h>

USB Usb;
HIDBoot<HID_PROTOCOL_KEYBOARD> HidKeyboard(&Usb);

uint32_t next_time;
const int btTx = 3;
const int btRx = 2;
const int btRst = 4;
SoftwareSerial BT = SoftwareSerial(btRx, btTx);

void send_to_bluefruit(uint8_t buf[]) {
  BT.write(0xFD);
  for(uint8_t i = 0; i < 8; ++i)
    BT.write(buf[i]);
}

void debug(uint8_t buf[]) {
  for(uint8_t i = 0; i < 8; ++i) {
    Serial.print(buf[i]);
    Serial.print(" ");
  }
  Serial.println("");
}

class BtKeyboardParser : public BtKeyboardReportParser {
    // =============== custom settings start =============== //
    uint8_t map_table[102] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 129, 0, 0, 132, 133, 130, 131, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };
    uint8_t modifier_table[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    uint8_t defult_mouse_move_pixels = 15;
    uint8_t mouse_switch = 60;
    uint8_t mouse_actions[6] = { 44, 101, 82, 81, 80, 79 };
    uint8_t mouse_move_pair_num = 1;
    uint8_t mouse_move_pixels_paris[1][2] = { { 9, 4 } };
    // =============== custom settings end ================ //
    uint8_t bt_buf[8];
    uint8_t previous_mouse_code[8];
    bool mouse_mode = false;
    bool send_consumer_report = false;
    bool send_mouse_key = false;
    void modify_bt_buffer(uint8_t buf[]);
    void modify_to_consumer_report(uint8_t buf[], uint8_t report_code);
    void modify_to_mouse(uint8_t buf[]);
    void modify_modifier(uint8_t buf[], uint8_t modifier);
    void copy_buffer(uint8_t buf[]);
  protected:
    void OnKeyDown(uint8_t mod, uint8_t key, uint8_t buf[]);
    void OnKeyUp(uint8_t mod, uint8_t key, uint8_t buf[]);
  public:
    void continue_mouse_move();
};

void BtKeyboardParser::modify_modifier(uint8_t buf[], uint8_t modifier) {
  switch(modifier) {
    case 224:
      buf[0] += 1;
      break;
    case 225:
      buf[0] += 2;
      break;
    case 226:
      buf[0] += 4;
      break;
    case 227:
      buf[0] += 8;
      break;
    case 228:
      buf[0] += 16;
      break;
    case 229:
      buf[0] += 32;
      break;
    case 230:
      buf[0] += 64;
      break;
    case 231:
      buf[0] += 128;
      break;
  }
}

void BtKeyboardParser::modify_to_consumer_report(uint8_t buf[], uint8_t report_code) {
  buf[0] = 0;
  buf[1] = 2;
  switch (report_code) {
    case 128: // volume up
      buf[2] = 16;
      buf[3] = 0;
      break;
    case 129: // volume down
      buf[2] = 32;
      buf[3] = 0;
      break;
    case 130: // home
      buf[2] = 1;
      buf[3] = 0;
      break;
    case 131: // search
      buf[2] = 4;
      buf[3] = 0;
      break;
    case 132: // play/pause
      buf[2] = 64;
      buf[3] = 0;
      break;
    case 133: // stop
      buf[2] = 0;
      buf[3] = 16;
      break;
    default:
      buf[2] = 0;
      buf[3] = 0;
  }
  buf[4] = buf[5] = buf[7] = 0;

  send_consumer_report = true;
}

void BtKeyboardParser::modify_to_mouse(uint8_t buf[]) {
  buf[0] = 0;
  buf[1] = 3;
  bool x_move = false;
  bool y_move = false;
  bool button_action = false;
  uint8_t move_pixels = defult_mouse_move_pixels;

  debug(buf);

  for(uint8_t i = 0; i < mouse_move_pair_num; ++i) {
    for(uint8_t j = 2; j < 8; ++j) {
      if(buf[j] == mouse_move_pixels_paris[i][0]) {
        move_pixels = mouse_move_pixels_paris[i][1];
      }
    }
  }

  for(uint8_t i = 0; i < 2; ++i) {
    // check left or right click
    for(uint8_t j = 2; j < 8; ++j) {
      if(buf[j] == mouse_actions[i]) {
        buf[2] = i + 1;
        button_action = true;
        break;
      }
    }
    if(button_action)
      break;
  }
  for(uint8_t i = 2; i < 6; ++i) {
    for(uint8_t j = 2; j < 8; ++j) {
      if(buf[j] == mouse_actions[i]) {
        switch(i) {
          case 2:
            buf[4] = (-1) * move_pixels;
            y_move = true;
            break;
          case 3:
            buf[4] = move_pixels;
            y_move = true;
            break;
          case 4:
            buf[3] = (-1) * move_pixels;
            x_move = true;
            break;
          case 5:
            buf[3] = move_pixels;
            x_move = true;
            break;
        }
      }
    }
  }

  if(!button_action) buf[2] = 0;
  if(!x_move) buf[3] = 0;
  if(!y_move) buf[4] = 0;

  buf[5] = buf[6] = buf[7] = 0;

  debug(buf);

  send_mouse_key = true;
  for(uint8_t i = 0; i < 8; ++i) {
    previous_mouse_code[i] = buf[i];
  }
}

void BtKeyboardParser::modify_bt_buffer(uint8_t buf[]) {
  uint8_t counter = 7;
  uint8_t modifier = buf[0];
  for(int i = 128; i > 0; i /= 2) {
    if(modifier >= i) {
      modifier -= i;
      // check modifier_table[counter] need to be modified
      if(modifier_table[counter] != 0) {
        if(modifier_table[counter] <= 101) { // if the re-map key is normal key
          buf[0] -= i;
          for(int j = 2; j < 8; ++j) {
            if(buf[j] == 0) {
              buf[j] = modifier_table[counter];
              break;
            }
          }
        } else if(modifier_table[counter] <= 133) { // if the re-map key is consumer report 
          modify_to_consumer_report(buf, map_table[buf[i]]);
          return;
        } else { // the remap key is another modifier key
          buf[0] -= i;
          modify_modifier(buf, modifier_table[counter]);
        }
      }
    }
    
    counter -= 1;
  }
  
  for(int i = 2; i < 8; ++i) {
    if(map_table[buf[i]] != 0) {
      if(map_table[buf[i]] <= 101) {// if the re-map key is normal key
        buf[i] = map_table[buf[i]];
      } else if(map_table[buf[i]] <= 133) { // if the re-map key is consumer report
        modify_to_consumer_report(buf, map_table[buf[i]]);
        return;
      } else { // if the re-map key is modifier key
        modify_modifier(buf, map_table[buf[i]]);
        // move rest keys to front
        buf[i] = 0;
        for(int j = i+1; j < 8; ++j) {
          buf[j-1] = buf[j];
          buf[j] = 0;
        }
      }
    }
  }

  if(buf[2] == mouse_switch)
    mouse_mode = !mouse_mode;

  if(send_consumer_report && (buf[0] + buf[2] + buf[3] + buf[4] + buf[5] + buf[6] + buf[7] == 0)) {
    buf[1] = 2;
    send_consumer_report = false;
    return;
  }

  if(send_mouse_key && (buf[0] + buf[2] + buf[3] + buf[4] + buf[5] + buf[6] + buf[7] == 0)) {
    buf[1] = 3;
    send_mouse_key = false;
    return;
  }

  if(mouse_mode)
    modify_to_mouse(buf);
}

void BtKeyboardParser::OnKeyDown(uint8_t mod, uint8_t key, uint8_t buf[]) {
  copy_buffer(buf);
  modify_bt_buffer(bt_buf);
  send_to_bluefruit(bt_buf);
  if(bt_buf[0] == 0 && bt_buf[1] == 0 && bt_buf[2] == 21 && bt_buf[3] == 22 && bt_buf[4] == 23 && bt_buf[5] == 0 && bt_buf[6] == 0 && bt_buf[7] == 0) {
    digitalWrite(btRst, HIGH);
    delay(7000);
    digitalWrite(btRst, LOW);
  }
}

void BtKeyboardParser::OnKeyUp(uint8_t mod, uint8_t key, uint8_t buf[]) {
  copy_buffer(buf);
  modify_bt_buffer(bt_buf);
  send_to_bluefruit(bt_buf);
}

void BtKeyboardParser::continue_mouse_move() {
  if(send_mouse_key) {
    uint8_t release_key_buf[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    send_to_bluefruit(release_key_buf);
    delay(10);
    send_to_bluefruit(previous_mouse_code);
  }
}

void BtKeyboardParser::copy_buffer(uint8_t buf[]) {
  for(uint8_t i = 0; i < 8; ++i) 
    bt_buf[i] = buf[i];
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

  HidKeyboard.SetReportParser(0, (HIDReportParser*)&Prs);
  LowPower.idle(SLEEP_FOREVER, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_ON, SPI_ON, USART0_ON, TWI_OFF);
}

void loop() {
  Usb.Task();
  Prs.continue_mouse_move();
}
