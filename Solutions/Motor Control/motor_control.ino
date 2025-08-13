#include "utility.h"

void setup() {
  Serial.begin(115200);

  setup_motor_pins();
  connect_to_wifi();
  get_ip_address();
  setup_server_command(); // Register route ONCE
  start_server();
}

void loop() {
  String command = get_server_command();

  if (command.length() > 0) {
    if (command == "w") forward();
    else if (command == "s") backward();
    else if (command == "a") turnLeft();
    else if (command == "d") turnRight();
    else if (command == "x") stopMotors();

    clear_command(); // Ready for next command
  }
}
