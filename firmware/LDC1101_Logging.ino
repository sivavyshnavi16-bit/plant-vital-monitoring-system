#include <SPI.h>
#include <SdFat.h>
#include <Wire.h>
#include "RTClib.h"

SdFat SD;
RTC_PCF8563 rtc;
const int chipSelect_SDCard = 9;
const int CS_PIN_LDC = 10;
#define BTSerial Serial1 // Bluetooth via Serial1 (pins 0 and 1)
#define READ_REG 0x80
#define WRITE_REG 0x00

void writeRegister_LDC(uint8_t reg, uint8_t value) {
    digitalWrite(CS_PIN_LDC, LOW);
    SPI.transfer(WRITE_REG | (reg & 0x3F));
    SPI.transfer(value);
    digitalWrite(CS_PIN_LDC, HIGH);
}

uint8_t readRegister_LDC(uint8_t reg) {
    digitalWrite(CS_PIN_LDC, LOW);
    SPI.transfer(READ_REG | (reg & 0x3F));
    uint8_t val = SPI.transfer(0x00);
    digitalWrite(CS_PIN_LDC, HIGH);
    return val;
}

void LHR_modeSetup() {
    SPI.begin();
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
    pinMode(CS_PIN_LDC, OUTPUT);
    digitalWrite(CS_PIN_LDC, HIGH);
    while (readRegister_LDC(0x20) & 0x01); // Wait for power-on reset to finish
    writeRegister_LDC(0x01, 0x05);
    writeRegister_LDC(0x0B, 0x01); // Sleep mode for configuration
    writeRegister_LDC(0x34, 0x00);
    writeRegister_LDC(0x30, 0xFF);
    writeRegister_LDC(0x31, 0xFF);
    writeRegister_LDC(0x32, 0x00);
    writeRegister_LDC(0x33, 0x00);
    writeRegister_LDC(0x05, 0x01);
    writeRegister_LDC(0x0C, 0x01);
    writeRegister_LDC(0x0B, 0x00); // Exit sleep mode
    Serial.print("LHR Setup Completed\n");
}

uint32_t read_LHR_Data() {
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
    while (readRegister_LDC(0x3B) & 0x01); // Wait for data ready
    uint8_t lsb = readRegister_LDC(0x38);
    uint8_t mid = readRegister_LDC(0x39);
    uint8_t msb = readRegister_LDC(0x3A);
    uint32_t lhrValue = ((uint32_t)msb << 16) | ((uint32_t)mid << 8) | lsb;
    return lhrValue;
}

void SDcard_setup() {
    pinMode(chipSelect_SDCard, OUTPUT);
    digitalWrite(chipSelect_SDCard, HIGH);
    if (!SD.begin(chipSelect_SDCard, SD_SCK_MHZ(10))) {
        Serial.println("Card failed or not present.");
        while (1);
    }
    Serial.println("Card initialized.");
}

void setup() {
    Serial.begin(9600);
    while (!Serial);
    BTSerial.begin(9600);
    Wire.begin();
    if (!rtc.begin()) {
        Serial.println("Couldn't find RTC");
        while (1);
    }
    // Original report uses a fixed 2025 test timestamp; update before deployment.
    rtc.adjust(DateTime(2025, 6, 29, 13, 25, 0));
    Serial.println("\nRTC is running.");
    SDcard_setup();
    LHR_modeSetup();
}

void loop() {
    Serial.print("\n");
    uint32_t lhrValue = read_LHR_Data();
    DateTime now = rtc.now();
    BTSerial.print("LHRData: " + String(lhrValue));

    FsFile file = SD.open("Data7.txt", FILE_WRITE);
    if (file) {
        file.println(" LHRData: " + String(lhrValue) + " Time: " + String(now.hour()) + ":" +
                     String(now.minute()) + ":" + String(now.second()) + " Date: " +
                     String(now.day()) + "/" + String(now.month()) + "/" + String(now.year()));
        file.close();
    } else {
        Serial.println("Failed to open file.");
    }
    delay(1000);

    file = SD.open("Data7.txt", FILE_READ);
    if (file) {
        Serial.print("\n *****SD Card Data***** \n");
        while (file.available()) {
            char c = file.read();
            Serial.print(c);
        }
        file.close();
        Serial.print(" *****SD Card END***** \n");
    } else {
        Serial.println("Failed to open file for reading.");
    }
}
