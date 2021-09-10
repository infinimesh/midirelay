/* MIDI Relay Simple CC-BY-SA Simon Kowalewski */

/* The uart that is connected to the MIDI In port. */
#define MIDIPORT Serial1

/* Debug out? Needs an additional UART, so don't use on
   *duino devices that only have one. */
#define DEBUGPORT Serial

/* Number of relays to toggle */
#define NUM 24

/* First relay pin number. For performance reasons, the relays
   must be used in order, so the last relay is on pin FIRST+NUM-1 */
#define FIRST 26

byte thisByte;
byte note;

void setup() {
#ifdef DEBUGPORT
  DEBUGPORT.begin(115200);
  while (!DEBUGPORT) {
    ; // Wait for serial port to connect.
  }
  Serial.println("MIDI Relay");
#endif
  MIDIPORT.begin(31250);

  for (int i = FIRST; i < NUM+FIRST; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
    
}

void loop() {
  while (MIDIPORT.available() == 0);
  thisByte = MIDIPORT.read();
  
  if ((thisByte >> 4) == 9) { //NOTE ON
    while (MIDIPORT.available() == 0);
    note = MIDIPORT.read();
    digitalWrite((note % NUM) + FIRST, LOW);
#ifdef DEBUGPORT
    DEBUGPORT.print(note);
    DEBUGPORT.println(" on.");
#endif
  }

  else if ((thisByte >> 4) == 8) { //NOTE OFF
    while (MIDIPORT.available() == 0);
    note = MIDIPORT.read();
    digitalWrite((note % NUM) + FIRST, HIGH);
#ifdef DEBUGPORT
    Serial.print(note);
    Serial.println(" off.");
#endif
  }
}
