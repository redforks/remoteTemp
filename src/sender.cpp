#include <VirtualWire.h>
#include <core.h>

#include "remoteTemp.h"
#include "sender.h"

using namespace core;

void onTempChange() {
  int16_t temp = (int16_t)store::analogs[idTemp];

  uint8_t buf[1+1+5+1]; // 0 -12.5\n
  buf[0] = 0;
  buf[1] = 32;

  int idx = 2;
  if (temp < 0) {
    buf[idx++] = '-';
    temp = -temp;
  }

  int d = temp / 100;
  buf[idx++] = d + '0';
  temp %= 100;

  d = temp / 10;
  buf[idx++] = d + '0';
  temp %= 10;

  buf[idx++] = '.';
  buf[idx++] = temp + '0';

  vw_send(buf, idx);
  vw_wait_tx();
}

void setupSender() {
  // Initialise the IO and ISR
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_set_tx_pin(VW_SEND_PIN);
  vw_setup(2000);	 // Bits per sec

  store::monitorAnalogs(&onTempChange, 1, idTemp);
}
