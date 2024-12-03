

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         21          // Configurable, see typical pin layout above
#define SS_PIN          5         // Configurable, see typical pin layout above

#define HATPIN          0
#define SHIRTPIN        0
#define PANTSPIN        0

#define BEAT            2667

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

int fit[3] = {0,0,0};

//should return array fit -> 3 bits 1 for wearing 0 for not
//fit should be returned every measure

void setup() {
 
	Serial.begin(9600);		// Initialize serial communications with the PC
	while (!Serial);		// Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
	SPI.begin();			// Init SPI bus

  pinMode(HATPIN, OUTPUT);
  pinMode(SHIRTPIN, OUTPUT);
  pinMode(PANTSPIN, OUTPUT);
  digitalWrite(HATPIN, LOW);
  digitalWrite(HATPIN, LOW);
  digitalWrite(HATPIN, HIGH);

	mfrc522.PCD_Init();		// Init MFRC522
	delay(4);				// Optional delay. Some board do need more time after init to be ready, see Readme
	mfrc522.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details
	Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}

void loop() {
//////////////////////////////////////////////////////////////////////////////////
  digitalWrite(HATPIN, HIGH);
  digitalWrite(SHIRTPIN, LOW);
  digitalWrite(PANTSPIN, LOW);
	// Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
	if ( ! mfrc522.PICC_IsNewCardPresent()) {
		fit[0] = 0;
	}
  else {
    fit[0] = 1;
  }
	mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
  delay(BEAT);
//////////////////////////////////////////////////////////////////////////////////
  digitalWrite(HATPIN, LOW);
  digitalWrite(SHIRTPIN, HIGH);
  digitalWrite(PANTSPIN, LOW);
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
		fit[1] = 0;
	}
  else {
    fit[1] = 1;
  }
  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
  delay(BEAT);
//////////////////////////////////////////////////////////////////////////////////////
  digitalWrite(HATPIN, LOW);
  digitalWrite(SHIRTPIN, LOW);
  digitalWrite(PANTSPIN, HIGH);
	// Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
	if ( ! mfrc522.PICC_IsNewCardPresent()) {
		fit[2] = 0;
	}
  else {
    fit[2] = 1;
  }
  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
  delay(BEAT);
  delay(BEAT);

}
