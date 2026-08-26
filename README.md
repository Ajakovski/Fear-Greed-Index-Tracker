<div align = "center">

# A Wi-Fi powered Fear & Greed Index Tracker

<p>

<img src="" width="40%" height="500">
<img src="" width="40%" height="450">
</p>

### _Live tracker on your desk displaying how the market *FEELS*._

</div>

---
# Motivation

<div align = "center">

Have you ever felt overwhelmed by the sheer amount of work that you have limiting your councousness that you **HAVE** to check the US stock market because your whole childhood lifesavings could be **GONE** thanks to **YOUR** irresonsible trading???

</div>

> _If you said yes..._

<div align = "center">

***WORRY NO MORE!!!***

------------------------------------------- ***THE FEAR & GREED INDEX TRACKER*** --------------------------------------------

</div>

**The gadget on your working desk that you did not know you ever needed.**

Always have a quick look on the current state of the market while working on something else giving you the power to intervene in the market when needed and not stress out about FOMO.

I wanted to have something long lasting on my desk that wont fail  me in the middle of the week because this project is meant to save time, not external work :)

Have the power of changing indexes based on your preference (coming in future versions)






# Overview

**Fear&Greed Index Tracker**

A portable working-desk gadget to remind you of the madness happening in the US market world. Thanks to the ESP32-S3 WiFi integrations we can fetch data from the internet and make this cool project alive on your desk.

The information is displayed on our RGB display with the highest quality for monitoring the most popular indexes.
Also thanks to the battery management you dont have to bother charging it very often because it can last up to one week!!!


Built as an open-source hardware product - every schematic and line of firmware is available to reproduce, modify and improve so ***ENJOYYYYY***

---

# Assembly Guide

## Hardware

***A visual representation of the whole project has been given with the file:***

```bash
Hardware/XXXXX.step
```

***If you dont prefer the files view you can always refer to the visual representation via [OnShape](https://cad.onshape.com/documents/b0f9f3ad3455fa4c269f5d70/w/b12c68eb17b42f73cf325935/e/728434c4884acb47f862d1fd?renderMode=0&uiState=6a8efb587598d3d7533a051f)***

### 1. Order the 3D Print

Navigate to: (For 3D Model)
```bash
Hardware/3D_Printing/
```
*If multiple versions are available i recommend sticking to the newest one because i dont commit untill its fully tested*

### 2. Order the Components

I recommend sticking to the BOM file if you want to really copy the project.

```bash
Hardware/BOM.csv
```

Order all parts before starting your assembly.

### 3. Solder the Components

Before assembling i suggest soldering everything together with flexible wires and strong solder joints so that everything stays in contact when you assemble it inside the case.

Prefer using wires without pins and soldering  on top of the ESP Devkit unless you have an extention that could be mounted onto the male pins of the ESP32.

Start with the power management components and then connect them with the ESP32 but keep the battery connection at last because that will start immediate power usage.

Then i would recommend moving onto the screen and buttons plus the RGB LED strip.

And finally finish the whole project by upgrading the hardware with passive components according to the KiCAD schematic.

Recommended tools:
- Flux
- A strong soldering iron with a fine-tip
- Tweezers
- Solder paste + hot air
- Helping hands with a magnifying glass

### 4. Add Customized Button Layer

I havent designed button caps on purpose because i wanted to have stickers on top of of them because the button itself is supposed to be tiny with its cute clicking sound so it is up to you to design it how you want :))))

### 5. Assemble the Enclosure

***Materials needed for assembling:***

- 4x M3 brass hot melt insert nuts
- Glue, any type just make sure to get a strong one
- 4x M3 screw screw
- Notice: if you dont get screws with the oled screen you will have to acquire them personally

***Steps for assembling***

The main and only part of assembling the casing is mounting the hat.
There are three steps for this:
- Allign the hat on top of the casing and in the desired screw holes you have mark them in any possible way either pen, pencil or etc.
- Get the M3 brass ho hot melt insert nuts and with a soldering iron melt them into the casing.
- Then just screw in the M3 in there and pray for the best (just kidding everythings gonna be fine (hopefully)).

---

## Firmware Installation

### 1. Install ESP-IDF

```bash
git clone --recursive https://github.com/espressif/esp-idf.git ~/esp/esp-idf
cd ~/esp/esp-idf
./install.sg esp32s3
source ./export.sh
```
Follow the [official Espressif guide](https://docs.espressif.com/projects/esp-idf/en/stable/esp32s3/get-started/index.html) for WIndows and macOS variants.

### 2. Close the Repository

```bash
git clone https:/github.com/Ajakovski/Fear-Greed-Index-Tracker.git
cd Fear-Greed-Index-Tracker
cd Firmware
```

### 3. Set Target and Build

```bash
idf.py set-starget esp32s3
idf.py build
```

### 4. Flash the firmware

Connect via USB-C. If the board does not enter download mode automatically, hold **BOOT** and tap **EN**, then release BOOT.

```bash
# Linux
idf.py -p /dev/tty/USB0 flash

# macOS
idf.py -p /dev/cu.ubserial-XXXX flash

#Windows
idf.py -p COM3 flash
```

### 5. Monitor Serial Output

```bash
idf.py-p /dev/ttyUSB0 monitor
```

Exit with 'Ctrl+]'.

---

# BOM

**If you are refering from the BOM.csv file please use a converter scv to table because it will be hard for you to read the documentation. And as always you can recall from my githubs BOM anytime you want**

| Designator | Function | Value / Part | Package | Qty | Price (USD) | Link |
|---|---|---|---|---|---|---|
| **TOTAL** | *approx. $* | | | | | |

*Notice: Theese shipping costs are for a 3rd world country so if you are from the EU or USA there are high chances of having lower shipping costs*

*Notice: Theese are just recommendations that i have found to be secure and hopefully the cheapest option. Do your own research if you think that better deals exist on the current market depending on when you are buying them.*

---

# Features

- **Live Market Data** - Immersive market data for monitoring the US market
- **RGB LED Matrix** - Visual representation of the current state of the trading index
- **RGB Display** - High quality representation of the current situation about the markets
- **18650 Battery Powered** - Single Li-Ion with onboard USB-C charging
- **Deep Sleep** - power saving mode and market data retaied in RTC memory across sleep cycles
- **Fuel Gauge** - Battery monitoring and safety guardrails
- **Longevity** - Battery lasts up to 40 working hours

---

# Hardware Stack

| Subsystem | Component | Description |
|---|---|---|
| MCU | ESP32-S3-WROOM-32 | 8MB Flash, None PSRAM, Xtensa LX6 dual-core |
| LED Strip| WB2182S Strip |---|
| Display | 128x160 TFT 1.8' | SPI Interface |
| Battery | Li-Ion 18650 3600mAh battery | |
| Charger | TP4056 | Single-cell Li-ion, USB-C input, battery protection |
| 3.3V Rail | TPS61023 | Boost converter |
| Fuel Gauge | MAX17048 | Battery measure, battery protection |

---

# KiCAD Design

***Refer to the PDF file for better overview*** [PDF](Pictures/Schematic_Print.pdf)

<img src="./Pictures/Main_Sch.png" width="100">

---

# Enclosure

- Simple to assemble
- Firm and high-quality material for premium feel
- The board is made out of PLA
- 10% in-fill on the whole 3D model
- Tolerances applied accordingly

*Feel free to change the material/in-fill according to your desire and budget approach*

---

Firmware features:
- FreeRTOS machine
- Deep sleep with RTC memory retention
- Wi-Fi communication
- Power saving modes beyond deep sleep

```bash
Fear_Greed_Index/
|--- Firmware/
|    |--- main/
|        |--- main.c/
|    |--- CMakeLists.txt
|    |--- sdkconfig
|--- Hardware/
|    |--- 3D_Printing/
|    |--- KiCad/
|    |--- BOM.csv
|--- Pictures/
|--- LICENSE
|--- README.md
```

# Current Status

- [ ] Initial Concept
- [ ] Layout Finalized
- [ ] Schematic
- [ ] Firmware
- [ ] Deep Sleep + RTC Retention
- [ ] Battery Monitoring
- [ ] 3D Model
- [ ] Final BOM
- [ ] Soldering
- [ ] Final Build
- [ ] Upgraded Firmware
- [ ] Upgraded Schematic

---

# Contributing

Contributions, suggestions and feedback are welcome!!!

If you'd like to improve Fear & Greed Index Tracker:

1. Fork or clone the repository
```bash
git clone https:/github.com/Ajakovski/Fear-Greed-Index-Tracker.git
cd Fear-Greed-Index-Tracker
```

2. Create your feature branch (if forked)
3. Commit your changes
4. Open a pull request

For significant hardware changes, open an issue first to discuss before investing time in layout work. Any new implementation must be self-contained in its own `.c`/`.h` pair.

If you build one, open an issue with photos.

---

# Creator

### Ajakovski aka. Marsovac

Hey my name is Andrej and im from Macedonia, Kratovo. Im 18 years old and i really enjoy making cool projects which are all posted on my github.

Main focus while building the project:
- Individual planning and structuring
- Nothing from something
- Embedded systems engineering
- Schematic construction with core electrical concepts
- Make something useful
- Save me from phone screentime
- Market awareness
- Trading

---

# License

This project is licensed under the **MIT License** - see [LICENSE](LICENSE) for full terms.

API used: ....

---

<div align="center">

## Fear & Greed Index Tracler

### _At any time prepared for disasters._

</div>
