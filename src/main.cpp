#include <Arduino.h>
#include <assert.h>
#include <IRrecv.h>
#include <IRremoteESP8266.h>
#include <IRac.h>
#include <IRtext.h>
#include <IRutils.h>

#include "ACEnum.h"
#include "Display.h"
#include "Process.h"
// ==================== start of TUNEABLE PARAMETERS ====================

const uint16_t kRecvPin = 14;
const uint32_t kBaudRate = 115200;
const uint16_t kCaptureBufferSize = 1024;
const uint8_t kTimeout = 50;
const uint16_t kMinUnknownSize = 12;
const uint8_t kTolerancePercentage = kTolerance; // kTolerance is normally 25%

// Legacy (No longer supported!)
//
// Change to `true` if you miss/need the old "Raw Timing[]" display.
#define LEGACY_TIMING_INFO false
// ==================== end of TUNEABLE PARAMETERS ====================

// Use turn on the save buffer feature for more complete capture coverage.
IRrecv irrecv(kRecvPin, kCaptureBufferSize, kTimeout, true);
decode_results results; // Somewhere to store the results
Process process;
// This section of code runs only once at start-up.
void setup()
{
  Serial.begin(kBaudRate, SERIAL_8N1);

  while (!Serial) // Wait for the serial connection to be establised.
    delay(50);
  // Perform a low level sanity checks that the compiler performs bit field
  // packing as we expect and Endianness is as we expect.
  assert(irutils::lowLevelSanityCheck() == 0);

  Serial.printf("\n" D_STR_IRRECVDUMP_STARTUP "\n", kRecvPin);
#if DECODE_HASH
  // Ignore messages with less than minimum on or off pulses.
  irrecv.setUnknownThreshold(kMinUnknownSize);
#endif                                       // DECODE_HASH
  irrecv.setTolerance(kTolerancePercentage); // Override the default tolerance.
  irrecv.enableIRIn();                       // Start the receiver
  init_display();
}

// The repeating section of the code
void loop()
{
  // Check if the IR code has been received.
  if (irrecv.decode(&results))
  {

    String description = IRAcUtils::resultAcToString(&results);
    if (description.length())
    {
      Serial.println(D_STR_MESGDESC ": " + description);
      process.tick(description);
    }
    else
    {
      process.tick("no");
    };
    yield(); // Feed the WDT as the text output can take a while to print.
  }
  else
  {
    process.tick("");
  }
}