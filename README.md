# ENGR 4399 ST: Cyber-Physical and IoT Systems

Coursework repository for **ENGR 4399 ST: Cyber-Physical and IoT Systems** — Fall 2026, University of the Incarnate Word.

## Course Description

This special topics course introduces the design, implementation, and operation of cyber-physical systems (CPS) and IoT systems through hands-on ESP32 development. Intended for a multidisciplinary audience — Engineering, Computer Information Systems, and Cybersecurity students working in mixed teams — it integrates wireless communication, sensor networks, embedded real-time software, security, and cloud/edge computing to design and deploy IoT/CPS architectures for operational technology (OT) environments such as IIoT, smart cities, connected health, V2X, and smart buildings.

## Learning Outcomes

By the end of this course, students will be able to:

1. Describe the architecture and operation of cyber-physical and IoT systems, including embedded endpoints, sensors, actuators, networks, and cloud services.
2. Design and implement ESP32-based embedded applications using polling, interrupts, and FreeRTOS-based multitasking.
3. Interface and integrate multiple sensors and actuators using GPIO, ADC, PWM, I2C, SPI, and UART while considering real-time and safety constraints.
4. Implement wireless communication using Wi-Fi, Bluetooth Low Energy (BLE), HTTP, and MQTT, including secure communication practices.
5. Analyze and apply embedded and IoT security mechanisms such as secure boot, flash encryption, firmware signing, and OTA updates.
6. Evaluate cyber-physical threats and failure modes — sensor spoofing, network disruption, firmware compromise — and propose engineering mitigation strategies.
7. Design, document, and present a cyber-physical system solution as part of a multidisciplinary team.

## Required Hardware & Software

- [Arduino IDE](https://www.arduino.cc/)
- ESP32 Development Board ([Elegoo getting-started guide](https://wiki.elegoo.com/en/oshw-getting-started-&-kits))
- KS0487 Keyestudio 37-in-1 Sensor Kit v3.0
- [Wokwi Simulator](https://wokwi.com/)
- [Fritzing](https://fritzing.org/) (Electronic Design Automation)

## Texts

**Required**
- *Espressif IoT Development Framework (ESP32 ESP-IDF) Programming Guide*, Release v5.3.2 (2024), Espressif Systems — primary technical reference for ESP32 hardware, peripherals, and programming.
- *Making Embedded Systems*, 2nd ed. (2024), Elecia White, O'Reilly — primary conceptual reading.
- *Introduction to Instrumentation, Sensors, and Process Control* (2005), William Dunn, Artech House — primary conceptual reading.

**Supplementary**
- *Introduction to the IoT Coursebook*, IOT-OPEN.EU Consortium (open access) — fills weeks not covered by the required texts (cloud/edge, mesh networking, lightweight security).

All readings and reference materials are distributed via Canvas.

## Repository Structure

This repo tracks my coursework for the semester. Suggested organization (adjust as the semester progresses):

```
.
├── assignments/          # Weekly/bi-weekly individual assignments (AR reports + code)
├── in-class-exercises/   # Short collaborative in-class work
├── project-1/            # Project 1: design review, workday files, presentation
├── project-2/            # Project 2: distributed ESP32 CPS (mesh)
├── final-project/        # Final project proposal + final report
└── README.md
```

## Tentative Schedule

| Week | Date | Topic |
|---|---|---|
| 1 | 08/25 – 08/27 | Introduction, Overview & Background; ESP32 Hardware, GPIO & Digital I/O |
| 2 | 09/01 – 09/03 | Analog Interfacing (ADC/DAC) & Sensor Signal Conditioning; Actuator Integration (PWM, Motors, Relays) |
| 3 | 09/08 – 09/10 | Communication Protocols: I2C/SPI; UART & Serial Peripheral Integration |
| 4 | 09/15 – 09/17 | Real-Time Concepts: Polling vs. Interrupt-Driven Design; Intro to FreeRTOS |
| 5 | 09/22 – 09/24 | FreeRTOS Synchronization (Semaphores, Mutexes, Queues); Wi-Fi & HTTP/REST |
| 6 | 09/29 – 10/01 | MQTT Protocol & Broker Architecture; Bluetooth Low Energy (BLE) |
| 7 | 10/06 – 10/08 | Project 1 Design Review; Project 1 Workday |
| 8 | 10/13 | **Project 1 Presentations** (10/15 – No Class, Fall Break) |
| 9 | 10/20 – 10/22 | OT Environments & Industrial IoT (IIoT); Intro to Wireless Mesh Networks |
| 10 | 10/27 – 10/29 | ESP32 Mesh I: Formation & Node Discovery (ESP-NOW); Mesh II: Multi-Hop & Broadcast (painlessMesh) |
| 11 | 11/03 – 11/05 | Distributed Sensor Data Aggregation & Mesh Gateway; **Project 2 Design Review** |
| 12 | 11/10 – 11/12 | Project 2 Workdays (Mesh Deployment & Testing) |
| 13 | 11/17 – 11/19 | **Project 2 Presentations**; Final Project Planning & Proposal Setup |
| 14 | 11/24 | Final Project Proposal Workday (11/26 – No Class, Thanksgiving) |
| 15 | 12/01 – 12/03 | **Final Project Proposal Presentations**; Final Project Workday & Integration Testing |
| 16 | 12/08 | **Final Project Presentation** (1:30–3:30 pm, FH 2020) |

**Key date:** November 16, 2026 — last day to drop the course with a W.

## Final Project

Team-based design and implementation of an embedded or cyber-physical system including sensing (minimum three sensors), processing, and actuation. Wireless communication is encouraged but optional. Consists of a Project Proposal (10%) and a Final Report (20%), each with written and oral components. Topics require instructor approval.

---

*This README summarizes the official course outline for ENGR 4399 ST (Fall 2026). It is a personal coursework repository and is not an official University of the Incarnate Word document. For authoritative policies, schedules, and updates, see Canvas.*
