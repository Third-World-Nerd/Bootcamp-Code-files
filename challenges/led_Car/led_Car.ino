#include "utility.h"

void setup() {
  Serial.begin(115200);
  // Set up connection led 
  //connect_to_wifi
  connect_to_wifi();
  //get_ip_address
  //ask_server_for_input
  // start_communication_with_server
  


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