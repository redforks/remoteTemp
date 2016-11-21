#include <RCSwitch.h>
#include <core.h>

#include "remoteTemp.h"
#include "sender.h"

using namespace core;

RCSwitch mySwitch = RCSwitch();

void onTempChange() {
  // a value composed by 3 bit value type, 5 bit value id, 16 bit value.
  // so 7 types(type 0 reserved), 32 max value for each type.
  uint16_t temp = store::analogs[idTemp];
  // 0x21, type is 01, signed int transfered as unsigned int, value id is 01.
  uint32_t token = 0x210000 + temp;
  // send as 32bit, receiver will drop first 8bit, for lower transfer error.
  mySwitch.send(token, 32);
}

void setupSender() {
  mySwitch.enableTransmit(VW_SEND_PIN);
  mySwitch.setRepeatTransmit(10);

  store::monitorAnalogs(&onTempChange, 1, idTemp);
}
