# Plant Vital Monitoring with Industrial Sensors

### Embedded Systems | Teensy 4.0 | SPI/I²C | Sensor Integration | Bluetooth | Data Logging

**Academic Team Project — Technische Universität Chemnitz, Germany | July 2025**

## Project Overview

This project explores a non-invasive plant monitoring system using industrial-grade inductive and capacitive sensing technologies.

The prototype combines the **LDC1101 inductance-to-digital converter** and **FDC2214 capacitance-to-digital converter** with a **Teensy 4.0 microcontroller**.

The system was designed to acquire sensor measurements, record timestamps, store data locally, and transmit readings wirelessly for remote monitoring.

## Project Objectives

- Develop an embedded platform for non-invasive plant monitoring.
- Interface industrial sensors using SPI and I²C.
- Integrate real-time timestamps using an RTC module.
- Implement local data logging using an SD card.
- Enable wireless monitoring through Bluetooth.
- Investigate hardware communication problems using debugging tools.

## Hardware Components

| Component | Function |
|---|---|
| Teensy 4.0 | Main microcontroller |
| LDC1101 | Inductive sensing |
| FDC2214 | Capacitive sensing |
| HW-689 RTC | Measurement timestamps |
| MicroSD Card Adapter | Local data logging |
| Bluetooth Module | Wireless data transmission |
| Custom PCBs | Sensor circuit integration |

## Technologies Used

**Programming:** Embedded C/C++, Arduino/Teensy environment

**Communication:** SPI, I²C, UART, Bluetooth

**Hardware Design:** Autodesk EAGLE, PCB layout, circuit assembly

**Debugging:** Logic analyzer, multimeter, serial monitoring

**Libraries:** SPI, Wire, SdFat, RTClib

## System Architecture

The Teensy 4.0 acts as the central controller.

- **LDC1101:** SPI-based inductive sensing.
- **FDC2214:** I²C-based capacitive sensing.
- **RTC:** Timestamp generation.
- **SD Card:** Local storage of measurements.
- **Bluetooth:** Wireless transmission to a mobile device.
- **USB Serial:** Monitoring and debugging through a computer.

## Firmware Development

The project includes embedded firmware for:

- LDC1101 register configuration and sensor data acquisition.
- FDC2214 register configuration and I²C communication.
- RTC initialization and timestamp retrieval.
- SD card initialization, file writing, and reading.
- Bluetooth-based transmission of sensor measurements.

The firmware was developed for the Teensy 4.0 using C/C++.

## Testing and Results

The prototype successfully demonstrated:

- Real-time LDC1101 sensor data acquisition using SPI.
- RTC-based timestamp generation.
- SD card read/write operations.
- Wireless transmission of sensor data to a mobile application.
- Serial monitoring of measurements on a computer.

### Hardware Debugging

During FDC2214 integration, an I²C communication problem was investigated using a logic analyzer.

A missing acknowledgment (ACK) was observed, and the investigation identified incorrect PCB connections. The team corrected the design and prepared an updated PCB layout.

This debugging process demonstrated the importance of hardware-software verification and systematic troubleshooting.

## My Contributions

My primary responsibilities included:

- Bluetooth communication configuration.
- Real-Time Clock (RTC) integration.
- SD card configuration and data logging.
- Supporting system integration and testing.

I also gained experience with the overall sensor architecture, embedded firmware, PCB design process, and hardware debugging through this collaborative project.

## Project Team

This project was completed as part of the Embedded Systems Project Lab at Technische Universität Chemnitz.

**Team members:**

- Komma Siva Vyshnavi Reddy
- Sheikh Zeeshan Ahmed
- Rushikesh Lakadkar
- Randhir Bhagat

## Future Improvements

Potential future enhancements include:

- Further validation of FDC2214 measurements.
- Improved sensor calibration and measurement analysis.
- A dedicated dashboard for monitoring plant conditions.
- Long-term data visualization and trend analysis.
- More compact hardware integration.

## Contact

**Vyshnavi Reddy**

Embedded Systems Engineer | Firmware & Electronics

Email: sivavyshnavi16@gmail.com

LinkedIn: https://www.linkedin.com/in/vyshnavi-reddy-344b66211



*Academic engineering project focused on embedded sensing, firmware integration, wireless communication, and hardware validation.*
