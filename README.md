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
| U1 | MCU | ESP32-WROOM-32 | Module | 1 | 4$ | [AliExpress](https://www.aliexpress.com/item/1005001636295529.html?spm=a2g0o.detail.pcDetailTopMoreOtherSeller.2.4b0eXZoGXZoG1r&gps-id=pcDetailTopMoreOtherSeller&scm=1007.40050.354490.0&scm_id=1007.40050.354490.0&scm-url=1007.40050.354490.0&pvid=b26f0aa3-3a19-4b8b-97b6-e263f44fa6d1&_t=gps-id%3ApcDetailTopMoreOtherSeller%2Cscm-url%3A1007.40050.354490.0%2Cpvid%3Ab26f0aa3-3a19-4b8b-97b6-e263f44fa6d1%2Ctpp_buckets%3A668%232846%238113%231998&pdp_ext_f=%7B%22order%22%3A%225751%22%2C%22eval%22%3A%221%22%2C%22sceneId%22%3A%2230050%22%2C%22fromPage%22%3A%22recommend%22%7D&pdp_npi=6%40dis%21MKD%2176.52%2166.66%21%21%211.32%211.15%21%400b15831117878424859683325e1000%2112000045248870857%21rec%21MK%21180636434%21XZ%211%210%21n_tag%3A-29919%3Bd%3Acd05e435%3Bm03_new_user%3A-29895&utparam-url=scene%3ApcDetailTopMoreOtherSeller%7Cquery_from%3A%7Cx_object_id%3A1005001636295529%7C_p_origin_prod%3A) |
| U2 | Li-Ion Charger | TP4056_USB-C | Module | 1 | 1$ | [AliExpress](https://www.aliexpress.com/item/1005006169600517.html?spm=a2g0o.detail.pcDetailBottomMoreOtherSeller.2.7667CScTCScTar&gps-id=pcDetailBottomMoreOtherSeller&scm=1007.40050.354490.0&scm_id=1007.40050.354490.0&scm-url=1007.40050.354490.0&pvid=c7883d09-beb2-4dd3-b515-49f1040d3a12&_t=gps-id%3ApcDetailBottomMoreOtherSeller%2Cscm-url%3A1007.40050.354490.0%2Cpvid%3Ac7883d09-beb2-4dd3-b515-49f1040d3a12%2Ctpp_buckets%3A668%232846%238113%231998&pdp_ext_f=%7B%22order%22%3A%221359%22%2C%22spu_best_type%22%3A%22price%22%2C%22eval%22%3A%221%22%2C%22sceneId%22%3A%2230050%22%2C%22fromPage%22%3A%22recommend%22%7D&pdp_npi=6%40dis%21MKD%214.49%214.49%21%21%210.52%210.52%21%402103849717878432579587754e10f9%2112000036091518074%21rec%21MK%21180636434%21XZ%211%210%21n_tag%3A-29919%3Bd%3Acd05e435%3Bm03_new_user%3A-29895&utparam-url=scene%3ApcDetailBottomMoreOtherSeller%7Cquery_from%3A%7Cx_object_id%3A1005006169600517%7C_p_origin_prod%3A) |
| J5 | Buck-Boost converter | TPS63020 | Module | 1 | 1$ | [AliExpress](https://www.aliexpress.com/item/1005008003604371.html?spm=a2g0o.productlist.main.22.19ed375b8PDIcn&algo_pvid=74ad3d26-5dc2-42b8-af4c-ad6863628e32&algo_exp_id=74ad3d26-5dc2-42b8-af4c-ad6863628e32-21&pdp_ext_f=%7B%22order%22%3A%22712%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21MKD%2185.13%2152.12%21%21%211.47%210.90%21%402140f2bd17873236924262103e0c95%2112000044617176286%21sea%21MK%210%21ABX%211%210%21n_tag%3A-29910%3Bd%3Acd05e435%3Bm03_new_user%3A-29895&curPageLogUid=DzkogbJnKaCp&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005008003604371%7C_p_origin_prod%3A) |
| J6 | Fuel Gauge | MAX17048 | Module | 1 | 13$ | [AliExpress](https://www.aliexpress.com/item/1005010173459854.html?spm=a2g0o.productlist.main.5.4cf57c39NUC8sX&algo_pvid=472eb1c5-b154-478d-b8c0-a61671b4709f&algo_exp_id=472eb1c5-b154-478d-b8c0-a61671b4709f-4&pdp_ext_f=%7B%22order%22%3A%2242%22%2C%22spu_best_type%22%3A%22price%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21MKD%21357.97%21336.49%21%21%2141.50%2139.01%21%40212a6dc917878480884081692e0e14%2112000051402478901%21sea%21MK%21180636434%21X%211%210%21n_tag%3A-29919%3Bd%3Acd05e435%3Bm03_new_user%3A-29895&curPageLogUid=Yf0c9ARxOWht&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005010173459854%7C_p_origin_prod%3A) |
| J4 | Screen | TFT RGB 128x160 | 1.8' | 1 | 9$ | [AliExpress](https://www.aliexpress.com/item/33015586094.html?spm=a2g0o.detail.pcDetailBottomMoreOtherSeller.56.edbdmm56mm56fK&gps-id=pcDetailBottomMoreOtherSeller&scm=1007.40050.354490.0&scm_id=1007.40050.354490.0&scm-url=1007.40050.354490.0&pvid=cb780494-59d5-4fba-8b24-dae42988ced1&_t=gps-id%3ApcDetailBottomMoreOtherSeller%2Cscm-url%3A1007.40050.354490.0%2Cpvid%3Acb780494-59d5-4fba-8b24-dae42988ced1%2Ctpp_buckets%3A668%232846%238113%231998&pdp_ext_f=%7B%22order%22%3A%226088%22%2C%22spu_best_type%22%3A%22price%22%2C%22eval%22%3A%221%22%2C%22sceneId%22%3A%2230050%22%2C%22fromPage%22%3A%22recommend%22%7D&pdp_npi=6%40dis%21MKD%21186.66%21139.70%21%21%213.22%212.41%21%402103842a17878413830755290e0fbd%2112000026583382487%21rec%21MK%21%21ABXZ%211%210%21n_tag%3A-29910%3Bd%3Acd05e435%3Bm03_new_user%3A-29895&utparam-url=scene%3ApcDetailBottomMoreOtherSeller%7Cquery_from%3A%7Cx_object_id%3A33015586094%7C_p_origin_prod%3A) |
| SW 1-3 | Buttons | Push button | tactile | 3(20) | 8$ | [Aliexpress](https://www.aliexpress.com/item/1005007361046397.html?spm=a2g0o.detail.pcDetailBottomMoreOtherSeller.4.678fJO77JO77Yo&gps-id=pcDetailBottomMoreOtherSeller&scm=1007.40050.354490.0&scm_id=1007.40050.354490.0&scm-url=1007.40050.354490.0&pvid=10126ee4-0070-4e8d-91a3-34750f3daa25&_t=gps-id%3ApcDetailBottomMoreOtherSeller%2Cscm-url%3A1007.40050.354490.0%2Cpvid%3A10126ee4-0070-4e8d-91a3-34750f3daa25%2Ctpp_buckets%3A668%232846%238113%231998&pdp_ext_f=%7B%22order%22%3A%22366%22%2C%22spu_best_type%22%3A%22price%22%2C%22eval%22%3A%221%22%2C%22sceneId%22%3A%2230050%22%2C%22fromPage%22%3A%22recommend%22%7D&pdp_npi=6%40dis%21MKD%21470.45%21310.10%21%21%2154.54%2135.95%21%402161390417878533559533754e0d07%2112000040423378864%21rec%21MK%21180636434%21XZ%211%210%21n_tag%3A-29919%3Bd%3Acd05e435%3Bm03_new_user%3A-29895&utparam-url=scene%3ApcDetailBottomMoreOtherSeller%7Cquery_from%3A%7Cx_object_id%3A1005007361046397%7C_p_origin_prod%3A) |
| D1 | RGB LED | WB2812S | 5050 | 1m 30 IP67 | 5$ | [AliExpress](https://www.aliexpress.com/item/2036819167.html?spm=a2g0o.detail.pcDetailTopMoreOtherSeller.11.489ebmqjbmqjw9&gps-id=pcDetailTopMoreOtherSeller&scm=1007.40050.354490.0&scm_id=1007.40050.354490.0&scm-url=1007.40050.354490.0&pvid=d61f209a-1294-4252-9f5c-cc0f501e744c&_t=gps-id%3ApcDetailTopMoreOtherSeller%2Cscm-url%3A1007.40050.354490.0%2Cpvid%3Ad61f209a-1294-4252-9f5c-cc0f501e744c%2Ctpp_buckets%3A668%232846%238113%231998&pdp_ext_f=%7B%22order%22%3A%2223645%22%2C%22eval%22%3A%221%22%2C%22sceneId%22%3A%2230050%22%2C%22fromPage%22%3A%22recommend%22%7D&pdp_npi=6%40dis%21MKD%21260.86%21224.34%21%21%214.50%213.87%21%402161390417878535374338593e0d07%2112000033705280745%21rec%21MK%21180636434%21X%211%210%21n_tag%3A-29919%3Bd%3Acd05e435%3Bm03_new_user%3A-29895&utparam-url=scene%3ApcDetailTopMoreOtherSeller%7Cquery_from%3A%7Cx_object_id%3A2036819167%7C_p_origin_prod%3A) |
| X | Resistor | 1KΩ / 10KΩ / 100Ω / 220Ω / 100KΩ | THT | 100 x 5 | 5$ | [AliExpress](https://www.aliexpress.com/item/1005004675087796.html?spm=a2g0o.detail.pcDetailTopMoreOtherSeller.5.91d1NPJhNPJhQe&gps-id=pcDetailTopMoreOtherSeller&scm=1007.40050.354490.0&scm_id=1007.40050.354490.0&scm-url=1007.40050.354490.0&pvid=92b910a5-a79a-4f7f-8176-09390be49348&_t=gps-id%3ApcDetailTopMoreOtherSeller%2Cscm-url%3A1007.40050.354490.0%2Cpvid%3A92b910a5-a79a-4f7f-8176-09390be49348%2Ctpp_buckets%3A668%232846%238113%231998&pdp_ext_f=%7B%22order%22%3A%221048%22%2C%22eval%22%3A%221%22%2C%22sceneId%22%3A%2230050%22%2C%22fromPage%22%3A%22recommend%22%7D&pdp_npi=6%40dis%21MKD%2113.33%218.11%21%21%210.23%210.14%21%402103956a17878540877675730e0e9d%2112000030061650010%21rec%21MK%21180636434%21XZ%211%210%21n_tag%3A-29919%3Bd%3Acd05e435%3Bm03_new_user%3A-29895&utparam-url=scene%3ApcDetailTopMoreOtherSeller%7Cquery_from%3A%7Cx_object_id%3A1005004675087796%7C_p_origin_prod%3A) |
| X | Ceramic Capacitor | 100nF | THT | 100 | 1$ | [AliExpress](https://www.aliexpress.com/item/1005006579533330.html?spm=a2g0o.detail.pcDetailTopMoreOtherSeller.9.4e98EEKAEEKAk0&gps-id=pcDetailTopMoreOtherSeller&scm=1007.40050.354490.0&scm_id=1007.40050.354490.0&scm-url=1007.40050.354490.0&pvid=f69e0589-9326-4dc2-ad84-4f444727c2c0&_t=gps-id%3ApcDetailTopMoreOtherSeller%2Cscm-url%3A1007.40050.354490.0%2Cpvid%3Af69e0589-9326-4dc2-ad84-4f444727c2c0%2Ctpp_buckets%3A668%232846%238113%231998&pdp_ext_f=%7B%22order%22%3A%223117%22%2C%22eval%22%3A%221%22%2C%22sceneId%22%3A%2230050%22%2C%22fromPage%22%3A%22recommend%22%7D&pdp_npi=6%40dis%21MKD%2114.49%2114.49%21%21%210.25%210.25%21%402161390417878544232071165e0d4a%2112000037720340835%21rec%21MK%21180636434%21X%211%210%21n_tag%3A-29919%3Bd%3Acd05e435%3Bm03_new_user%3A-29895&utparam-url=scene%3ApcDetailTopMoreOtherSeller%7Cquery_from%3A%7Cx_object_id%3A1005006579533330%7C_p_origin_prod%3A) |
| X | Polarized Capacitor | 10uF | THT | 10 | 3$ | [AliExpress](https://www.aliexpress.com/item/1005006773833658.html?spm=a2g0o.productlist.main.43.3b50ae71kV4mLU&algo_pvid=a62a9145-5f70-4899-8425-422a8d6ff660&algo_exp_id=a62a9145-5f70-4899-8425-422a8d6ff660-40&pdp_ext_f=%7B%22order%22%3A%2220%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21MKD%21124.56%21118.35%21%21%2114.44%2113.72%21%402101737817878568676627425e0c24%2112000038256846756%21sea%21MK%21180636434%21X%211%210%21n_tag%3A-29919%3Bd%3Acd05e435%3Bm03_new_user%3A-29895&curPageLogUid=IloixCtXNMcv&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005006773833658%7C_p_origin_prod%3A) |
| X | JST Pin | P2 | SH / PH / XH | 10 x 3 | 4$ | [AliExpress](https://www.aliexpress.com/item/4001235017139.html?spm=a2g0o.productlist.main.59.458b4a1e4hev03&algo_pvid=4457dbd3-0b45-4f84-a8ec-87e13c04edc5&algo_exp_id=4457dbd3-0b45-4f84-a8ec-87e13c04edc5-56&pdp_ext_f=%7B%22order%22%3A%2215727%22%2C%22spu_best_type%22%3A%22price%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21MKD%21105.50%21100.28%21%21%211.82%211.73%21%40212a6dc917878546769815293e0d84%2110000015400386596%21sea%21MK%210%21ABX%211%210%21n_tag%3A-29910%3Bd%3Aaeed944%3Bm03_new_user%3A-29895&curPageLogUid=DicSMvRtoGFK&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A4001235017139%7C_p_origin_prod%3A) |
| X | Brass Hot Nut | M3 | OD 4.5mm l. 9mm | 10 | 7$ | [AliExpress](https://www.aliexpress.com/item/1005003582355741.html?spm=a2g0o.detail.pcDetailTopMoreOtherSeller.3.26aboFBAoFBA2D&gps-id=pcDetailTopMoreOtherSeller&scm=1007.40050.354490.0&scm_id=1007.40050.354490.0&scm-url=1007.40050.354490.0&pvid=08a6c528-6fd3-47c1-a069-cea2c753eff1&_t=gps-id%3ApcDetailTopMoreOtherSeller%2Cscm-url%3A1007.40050.354490.0%2Cpvid%3A08a6c528-6fd3-47c1-a069-cea2c753eff1%2Ctpp_buckets%3A668%232846%238111%231996&pdp_ext_f=%7B%22order%22%3A%2258043%22%2C%22eval%22%3A%221%22%2C%22sceneId%22%3A%2230050%22%2C%22fromPage%22%3A%22recommend%22%7D&pdp_npi=6%40dis%21MKD%21309.96%21301.52%21%21%2135.98%2135.00%21%400b88ab6717873349934185770e0de0%2112000026370649842%21rec%21MK%21%21ABXZ%211%210%21n_tag%3A-29910%3Bd%3Aaeed944%3Bm03_new_user%3A-29895&utparam-url=scene%3ApcDetailTopMoreOtherSeller%7Cquery_from%3A%7Cx_object_id%3A1005003582355741%7C_p_origin_prod%3A) |
| X | Screw | M3 | 10mm length | 10 | 8$ | [AliExpress](https://www.aliexpress.com/item/1005003970883424.html?spm=a2g0o.productlist.main.23.21064221B0XnB9&algo_pvid=aa52fa44-e5f3-419c-80e2-749ce981a2eb&algo_exp_id=aa52fa44-e5f3-419c-80e2-749ce981a2eb-22&pdp_ext_f=%7B%22order%22%3A%22218%22%2C%22spu_best_type%22%3A%22price%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21MKD%21365.21%21365.21%21%21%216.30%216.30%21%4021410daa17878554730808162e0cdb%2112000027602745006%21sea%21MK%21180636434%21X%211%210%21n_tag%3A-29919%3Bbm%3A1%3Bd%3Acd05e435%3Bm03_new_user%3A-29895&curPageLogUid=znGLE1nIk6yr&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005003970883424%7C_p_origin_prod%3A) |
| *3D Printing* | 50$ | with cargo | | | | | | 
| **TOTAL** | *approx. 119$* | with cargo | | | | |

Thanks to the newest tarrifs by our president (20% tax import on international goods) ***EVERYTHING IS COOKED WITH PRICES***

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
