/*

This program is free software: you can redistribute it and/or modify　it under the terms of the GNU General Public License as published by　the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,　but WITHOUT ANY WARRANTY; without even the implied warranty of　MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.　　See the　GNU General Public License for more details.

About GPL, see <http://www.gnu.org/licenses/>.
*/

#include <SoftwareSerial.h>

SoftwareSerial BT = SoftwareSerial(3,2);
int codes[8];
int idx = 0;
int tmp;

void setup() {
  Serial.begin(9600);
  Serial1.begin(57600);
  BT.begin(9600);
}

void consumerCommand(int codes[8]) {
  BT.write(0xFD);
  BT.write((byte)0x00);
  BT.write((byte)0x02);

  if(codes[1] == 0 && codes[2] == 4 && codes[3] == 0) {
    BT.write((byte)0x10);
    BT.write((byte)0x00);
  }
  else if(codes[1] == 0 && codes[2] == 2 && codes[3] == 0) {
    BT.write((byte)0x20);
    BT.write((byte)0x00);
  }
  else if(codes[1] == 16 && codes[3] == 0 && codes[4] == 0) {
    BT.write((byte)0x40);
    BT.write((byte)0x00);
  }
  else if(codes[1] == 128 && codes[3] == 0 && codes[4] == 0) {
    BT.write((byte)0x00);
    BT.write((byte)0x02);
  }
  else if(codes[1] == 64 && codes[3] == 0 && codes[4] == 0) {
    BT.write((byte)0x00);
    BT.write((byte)0x04);
  }
  else {
    BT.write((byte)0x00);
    BT.write((byte)0x00);
  }

  for(int i = 0; i < 4; ++i) {
    BT.write((byte)0x00);
  }
}

void keyCommand(int codes[8], int idx) {
  if(idx == 8) {
    BT.write(0xFD);
    for(int i = 0; i < 8; ++i) {
      BT.write(codes[i]);
    }
  }
  else if(idx == 5) {
    consumerCommand(codes);
  }
}

void loop() {
  if(Serial1.available()) {
    tmp = Serial1.read();
    delay(1);
    if(tmp == 181) {
      keyCommand(codes, idx);
      idx = 0;
    }
    else {
      codes[idx] = tmp;
      ++idx;
    }
  }
}
