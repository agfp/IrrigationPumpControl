#include <EEPROM.h>

long dataIndex;

const uint16_t SIGNATURE = 0xADA0;
const uint16_t SIGNATURE_IDX = 0;
const uint16_t DATAINDEX_IDX = 2;

void loadState() {
  randomSeed(analogRead(EMPTY_ANALOG_PIN));
  dataIndex = generateNewIndex();

  if (isEepromInitialized()) {
    Serial << "EEPROM is initialized" << endl;
    loadStateAndRelocate();
  } else {
    Serial << "EEPROM is not initialized" << endl;
    initializeEeprom();
  }
}

void saveState() {
  EEPROM.update(dataIndex, halt);
}

bool isEepromInitialized() {
  uint16_t signature;
  EEPROM.get(SIGNATURE_IDX, signature);
  return signature == SIGNATURE;
}

void initializeEeprom() {
  EEPROM.put(DATAINDEX_IDX, dataIndex);
  EEPROM.put(SIGNATURE_IDX, SIGNATURE);
  Serial << "Storing state at " << dataIndex << endl;
}

void loadStateAndRelocate() {
  long previousDataIndex;
  EEPROM.get(DATAINDEX_IDX, previousDataIndex);
  EEPROM.get(previousDataIndex, halt);
  Serial << "Relocating state from " << previousDataIndex << " to " << dataIndex << endl;
  EEPROM.put(dataIndex, halt);
  EEPROM.put(DATAINDEX_IDX, dataIndex);
  alert = halt;
}

long generateNewIndex() {
  uint16_t headerSize = sizeof(SIGNATURE) + sizeof(long);
  long index = random(headerSize, E2END - sizeof(halt));
  return index;
}
