#include <core.h>

#include "sender.h"
#include "read_temp.h"

void setup() {
  Serial.begin(115200);	// Debugging only

  setupReadTemp();
  setupSender();
}

void loop() {
  core::clock::check();
}

