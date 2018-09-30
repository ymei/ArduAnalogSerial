/**
 * Arduino Analog I/O controlled by serial commands.
 *
 * Controlling Arduino [Analog Shield](https://store.digilentinc.com/analog-shield-high-performance-add-on-board-for-the-arduino-uno-retired/)
 * with [manual](http://analogshield.com/user-manual.html).
 */

#include <analogShield.h>
#include <CmdMessenger.h>

/// Attach a new CmdMessenger object to the default Serial port
CmdMessenger cmdMessenger = CmdMessenger(Serial);

/// This is the list of recognized commands.  Either sent or received.
/// In order to receive, attach a callback function to these events
enum
{
    kError=0,
    kAcknowledge,
    kAnalogRead,
    kAnalogWrite,
    kAnalogWriteM
};

/// Called when a received command has no attached function
void onUnknownCommand()
{
    cmdMessenger.sendCmd(kError, "Unknown command!");
}

void onAnalogRead()
{
    uint16_t val, ch;
    bool diff;
    ch = cmdMessenger.readInt16Arg();
    // if there exists a 2nd argument, read differentially.
    (void)cmdMessenger.readInt16Arg();
    diff = cmdMessenger.isArgOk();
    val = analog.read(ch, diff);
    cmdMessenger.sendCmd(kAnalogRead, val);
}

void onAnalogWrite()
{
    const int N=4;
    uint16_t v, val[N], cnt;
    cnt = 0;
    while(cnt < N) {
        v = cmdMessenger.readInt16Arg();
        if(cmdMessenger.isArgOk()) {
            val[cnt++] = v;
        } else {
            break;
        }
    }
    if(cmdMessenger.commandID() == kAnalogWrite) {
        analog.write(val[0], val[1]); // channel, value
        cmdMessenger.sendCmdStart(cmdMessenger.commandID());
        cmdMessenger.sendCmdArg(val[0]);
        cmdMessenger.sendCmdArg(val[1]);
        cmdMessenger.sendCmdEnd();
    } else {
        switch(cnt) {
        case 1:
            analog.write(0, val[0]);
            break;
        case 2:
            analog.write(val[0], val[1], true);
            break;
        case 3:
            analog.write(val[0], val[1], val[2], true);
            break;
        case 4:
            analog.write(val[0], val[1], val[2], val[3], true);
            break;
        default:
            break;
        }
        cmdMessenger.sendCmd(cmdMessenger.commandID(), cnt);
    }
}

/// Callbacks define on which received commands we take action
void attachCommandCallbacks()
{
    // Attach callback methods
    cmdMessenger.attach(onUnknownCommand);
    cmdMessenger.attach(kAnalogRead, onAnalogRead);
    cmdMessenger.attach(kAnalogWrite, onAnalogWrite);
    cmdMessenger.attach(kAnalogWriteM, onAnalogWrite);
}

void setup() {
    // initialize serial communications at a baud rate of 9600
    Serial.begin(115200);
    // Adds newline to every command
    cmdMessenger.printLfCr();
    // Attach my application's user-defined callback methods
    attachCommandCallbacks();
    // Send the status to the PC that says the Arduino has booted
    // Note that this is a good debug function: it will let you also know
    // if your program had a bug and the arduino restarted
    cmdMessenger.sendCmd(kAcknowledge, "ArduAnalogSerial started.");
    // ZERO outputs
    analog.write(32767, 32767, 32767, 32767, true);
}

void loop() {
    // Process incoming serial data, and perform callbacks
    cmdMessenger.feedinSerialData();
}
/* Local Variables: */
/* mode: c++        */
/* End:             */
