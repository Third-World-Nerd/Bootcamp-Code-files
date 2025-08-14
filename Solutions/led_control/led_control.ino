#include "utility.h"

void setup() {
  Serial.begin(115200);

  setup_led_pins();
  stopAll();             // Motors off at start
  connect_to_wifi();
  get_ip_address();
  setup_server_command(); // Register server route once
  start_server();
}

void loop() {
  String command = get_server_command();

  if (command.length() > 0) {
    if (command == "w") forward();
    else if (command == "s") backward();
    else if (command == "a") left();
    else if (command == "d") right();
    else if (command == "x") stopAll();

    clear_command(); // Ready for next one
  }
}
