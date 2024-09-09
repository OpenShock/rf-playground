#ifdef MODE_RX

#include <collar.h>

/*
 * Simple shock collar receive example 
 */

// Set this to the pin which has the 433MHz receiver connected to it
const uint8_t  rx_pin = 13;

CollarRx *_rx;
volatile bool got_message = false;
struct collar_message rx_message;

// Called from within an interupt handler when a message is received,
// therefore it shouldn't do much.
void message_callback (const struct collar_message *msg, void *userdata)
{
  memcpy(&rx_message, msg, sizeof(struct collar_message));
  got_message = true;
}


void setup() 
{
  Serial.begin(115200);

  // Change "CollarRxType1" to "CollarRxType2" below if nessesary
  _rx =  new CollarRxType1(rx_pin, message_callback, NULL);
}

void loop() 
{
  if (got_message)
  {
    Serial.println("\nGot message:");
    CollarRx::print_message(&rx_message);
    got_message = false;
    Serial.println("");
  }
}

#endif