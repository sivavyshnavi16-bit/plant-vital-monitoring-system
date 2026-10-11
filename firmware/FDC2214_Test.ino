
#include <Wire.h>

// FDC2214 I2C address used in the project report.
// 0x2B when ADDR is HIGH; 0x2A when ADDR is LOW.
#define FDC2214_ADDR 0x2B

// Write 16-bit data to a 16-bit register
void writeRegister_FDC(uint8_t reg, uint16_t value) {
    Wire.beginTransmission(FDC2214_ADDR);
    Wire.write(reg);
    Wire.write(value >> 8);
    Wire.write(value & 0xFF);
    Wire.endTransmission();
}

// Read 16-bit data from a 16-bit register
uint16_t readRegister_FDC(uint8_t reg) {
    uint16_t value = 0;

    Wire.beginTransmission(FDC2214_ADDR);
    Wire.write(reg);
    Wire.endTransmission(false);

    Wire.requestFrom(FDC2214_ADDR, (uint8_t)2);

    if (Wire.available() == 2) {
        value = Wire.read() << 8;
        value |= Wire.read();
    }

    return value;
}

// Configure Channel 2
void FDC_setup_channel2() {
    writeRegister_FDC(0x0A, 0xFFFF); // RCOUNT_CH2
    writeRegister_FDC(0x0E, 0x0000); // OFFSET_CH2
    writeRegister_FDC(0x12, 0x0000); // SETTLECOUNT_CH2
    writeRegister_FDC(0x16, 0x1000); // CLOCK_DIVIDERS_CH2
    writeRegister_FDC(0x20, 0xE800); // DRIVE_CURRENT_CH2
}

// Configure Channel 3
void FDC_setup_channel3() {
    writeRegister_FDC(0x0B, 0xFFFF); // RCOUNT_CH3
    writeRegister_FDC(0x0F, 0x0000); // OFFSET_CH3
    writeRegister_FDC(0x13, 0x0000); // SETTLECOUNT_CH3
    writeRegister_FDC(0x17, 0x1000); // CLOCK_DIVIDERS_CH3
    writeRegister_FDC(0x21, 0xE800); // DRIVE_CURRENT_CH3
}

// Configure FDC2214 for Channel 3
void FDC_setup() {
    // Channel 2 configuration from report (inactive):
    // writeRegister_FDC(0x1A, 0xB200);
    // FDC_setup_channel2();

    // Select Channel 3 while in sleep mode
    writeRegister_FDC(0x1A, 0xF200);

    FDC_setup_channel3();

    // Input deglitch filter
    writeRegister_FDC(0x1B, 0x020C);

    // Exit sleep mode
    writeRegister_FDC(0x1A, 0x0000);

    Serial.print("FDC Setup Completed\n");
}

// Read Channel 2
void FDC_read_channel2() {
    uint16_t msb = readRegister_FDC(0x04);
    uint16_t lsb = readRegister_FDC(0x05);

    uint32_t result =
        ((uint32_t)(msb & 0x0FFF) << 16) | lsb;
}

// Read Channel 3
void FDC_read_channel3() {
    uint16_t msb = readRegister_FDC(0x06);
    uint16_t lsb = readRegister_FDC(0x07);

    uint32_t result =
        ((uint32_t)(msb & 0x0FFF) << 16) | lsb;
}

void setup() {
    Wire.begin();
    Serial.begin(115200);

    FDC_setup();
}

void loop() {
    // FDC_read_channel2();

    Serial.print("\nMANUFACTURER_ID: ");
    Serial.print(readRegister_FDC(0x7E));

    Serial.print("\nDEVICE_ID: ");
    Serial.print(readRegister_FDC(0x7F));

    FDC_read_channel3();

    delay(1000);
}
