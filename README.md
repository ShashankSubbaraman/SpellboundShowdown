
<div align="center">
  
# Spellbound Showdown- Gesture-Controlled Magic Wand 1v1 
 </div>
 
## Team Members

 Aashrit Marripelli  
 Sahil Shaik  
 Shashank Subbaraman    
 Eshwar Thammineni 
---

## Purpose

Spellbound Showdown involves two interactive magic wands with the goal of bringing magic-themed battles to life. With gesture recognition, users can wave their respective wands to cast a variety of spells and face off against each other. 

## Tools Used
### Backend Development:
- Python
- Mosquitto (MQTT)
- NetworkManager (nmcli)

### Firmware & Embedded Programming
- Arduino IDE
- Visual Studio Code

### Machine Learning
- Edge Impulse

### Hardware
- 3D printer: Bambu Lab H2D
- Microcontroller: Raspberry Pi Zero with PiSugar S battery module
- Motion Sensor: MPU-6050 6-axis accelerometer and gyroscope
  
### Power Components:
- PiSugar S integrated battery module (Wand 1)
- 3.7V rechargeable lithium battery + buck converter (Wand 2)

### CAD softwares: 
- Autodesk Inventor
- Fusion 360

## Challenges & Solutions

### Challenge 1: 3D-Printed Wand Structure Issues

**Problem:** Initial wand designs were consistently too thick, making them heavy, awkward to hold, and visually disproportionate. The bulky design compromised the wand's usability and didn't have the sleek, elegant appearance we envisioned for a magical wand.

**Solution:** We went through multiple redesign iterations to slim down the wand while maintaining structural integrity. We experimented with variable wall thickness - using thicker walls only at critical stress points like the grip and tip connection, while thinning other sections significantly. We hollowed out non-essential areas and tested different infill patterns to find the right balance between strength and weight reduction. We also refined the overall proportions, creating a gradual taper from handle to tip that felt more natural and balanced. After several prototype iterations, we achieved a noticeably slimmer profile that was much lighter and more comfortable to handle. This also led us to part of the solution for challenge 3.

<p align ="center" >
  <img src="https://github.com/user-attachments/assets/641f6100-afc0-4bc9-9512-943bfd81cb40" />
</p>

---
### Challenge 2: Limited Battery Components for Second Wand
<p align ="center" >
  <img  src="https://github.com/user-attachments/assets/f3b21914-88ad-458b-9d7e-e509e9e7d74f" />
  <img  src="https://github.com/user-attachments/assets/7cf35507-80ff-4f5e-8bac-fb48f0277cd2" />
</p>


**Problem:** We only had one PiSugar S battery module available, but needed to create two functional wands for our project. We couldn't order another PiSugar in time for the hackathon deadline, forcing us to find an alternative power solution for the second wand.

**Solution:** We adapted the second wand to use a standard rechargeable lithium battery combined with a buck converter to step down the voltage to the required level for our microcontroller and sensors. This required redesigning the internal cavity of the second wand to accommodate the different form factor of the battery and buck converter module, as they took up more space than the compact PiSugar. We had to adjust the weight distribution since the components were bulkier and positioned differently. We also added additional wiring and soldering to connect the buck converter properly, and implemented voltage regulation to ensure stable power delivery. While the second wand ended up slightly heavier and with a different internal layout than the first, both wands functioned identically from the user's perspective. This taught us the importance of having backup components and the value of adaptable designs that can accommodate different hardware configurations.



---

### Challenge 3: Internal Component Movement and Rattling

<p align ="center" >
  <img  src="https://github.com/user-attachments/assets/ac93e67a-df8a-4801-a1f8-97807a2acdc7" />
  <img src="https://github.com/user-attachments/assets/b2ce3e1c-e561-4d8a-b79e-f9b7b3bf81cb" />
</p>

**Problem:** After printing our initial wand handle, we discovered the internal components wouldn't fit. The cavity we had designed was designed for the PiSugar and did not account for the extra battery we had to add. We had printed the handle with just a hollow interior, assuming we could figure out component placement during assembly, but this approach failed. Without proper mounting points, we couldn't secure anything in place, wires had nowhere to route cleanly, and the components would shift around during any movement, making assembly impossible.

**Solution:** We went back to CAD and completely redesigned the internal structure with dedicated compartments for each component. We measured the exact dimensions of the battery and created a storage compartment padded with foam inserts to fit specifically for the battery. We also designed a dedicated mounting location for the IMU sensor with the exact footprint needed to hold it securely. We added wire routing channels throughout the interior to keep cables organized and prevent them from getting pinched during assembly or movement. After printing the updated handle with these integrated internal compartments, we were able to insert all components smoothly. Each piece fit snugly in its designated space, wires routed cleanly through the channels, and everything stayed firmly in place during use with no rattling or disconnections.


### Challenge 4: Misprints 
<p align ="center" >
  <img src="https://github.com/user-attachments/assets/1539ad0b-96ce-48f5-8b4c-d83931841b6f" />
</p>

**Problem**  Our wand handle print failed when the filament became clogged in the nozzle. When we checked on the print's progress, we found the extruder clicking and skipping, with no filament coming out. The print had continued running with the motors moving but no material being deposited, leaving gaps in the layers and a structurally weak piece. This wasted 3 hours of print time and filament on an unusable part. After clearing the clog and starting a new print that completed successfully, we discovered the handle had minor warping at the base where it had lifted slightly off the bed. While not as severe as the first failure, the warping was enough to cause dimensional inaccuracies - the internal cavity was slightly twisted, and the mounting ring wouldn't fit properly. This meant we needed to print the handle a third time.

**Solution** To address the clogging issue, we cleaned the nozzle thoroughly and increased the printing temperature slightly to improve filament flow. We also checked the filament path for tangles and ensured smooth feeding from the spool. For the warping problem on our third attempt, we increased bed temperature to improve adhesion and applied glue stick to the print surface. The third print completed successfully with no clogging and minimal warping, producing a dimensionally accurate handle that fit our components and mated properly with the mounting ring.


### Challenge 5: cannot connect IMU to pi0 sugar
**Problem** We encountered persistent difficulties connecting the IMU sensor to the raspberry pi zero when using the PiSugar power module. The sensor worked perfectly on a breadboard with direct Pi connection, but completely failed to communicate through the PiSugar's GPIO headers. Running i2c detect, we found that the PiSugar could see the IMU but there was no way to communicate with it. We suspected that the PiSugar's circuitry was conflicting with the GPIO pins. Without the IMU, the wand had no ways of detecting any gestures. 

**Solution** We first swapped the SD cars between our working Pi and the problematic one to fihure out weather the issue was hardware or software related. The end result confirmed that the Pi hardware itself was functional but the problem was the GPIO pin conflicting with the PiSugar. By implementing a workaround, we removed the physical connections from the GPIO 2 & GPIO 3, and replaced it with configured virtual 12C pins with i2c bit banging. We selected two available GPIO pins that weren't being used by PiSugar's internal circuitry, but could handle the data transfer requirements we needed. We then remapped the original pins to these new alternative pins, by using i2c-gpio overlay in /boot/config.txt.This created a new I2C bus (/dev/i2c-3) on GPIO 23 (SDA) and GPIO 24 (SCL) that completely bypassed the PiSugar's GPIO conflicts.  We then connected our IMU sensor to these new pins and modified our code to reference the new virtual pins. This ultimately resulted in the IMU being detected and being able to communicate reliably.

### Challenge 6: Wifi Restrictions 
**Problem** Our Raspberry Pi Zeros couldn't connect to the school's enterprise WiFi network (eduroam), which uses WPA-Enterprise authentication instead of the simple WPA2-PSK used by home networks. Unlike regular WiFi that just needs a password, eduroam requires username-based authentication with encrypted credential verification through PEAP and MSCHAPv2 protocols. The Raspberry Pi's graphical WiFi configuration tools didn't support this authentication method, and we couldn't access the captive portal or login page that students normally use on laptops and phones. Without internet connectivity, we couldn't download necessary libraries, update our code repository, or test our MQTT communication over the network. This blocked our development progress since we needed to install Python packages, pull code from GitHub, and verify our networking setup. We spent hours trying different approaches, attempting to use the GUI WiFi settings, trying to connect through command line with simple passwords, and searching for configuration files, but nothing worked. The error messages were cryptic and didn't clearly explain that enterprise authentication was the issue.

**Solution** We used NetworkManager command-line tools to configure enterprise authentication:
```
nmcli connection add type wifi ifname wlan0 con-name enterprise-wifi ssid "eduroam" 
nmcli connecti on modify enterprise-wifi wifi-sec.key-mgmt wpa-eap 802-1x.eap peap 802-1x.identity "username" 802-1x.password "password!" 802-1x.phase2-auth mschapv2 
nmcli connection modify enterprise-wifi ipv4.method auto 
nmcli connection up enterprise-wifi
```
These commands created a WiFi profile, configured PEAP authentication with our school credentials, set up automatic IP assignment, and activated the connection. After replacing "username" and "password!" with our actual login, the Pi connected successfully.

## 📚 Credits & Acknowledgments
 
### APIs 
- Edge Impulse Python SDK: Model deployment and inference
-MPU6050 Library: Sensor interface and motion processing
- PubSubClient: MQTT client for Arduino/ESP
- paho-mqtt: MQTT client library for Python
- smbus: I2C communication for MPU-6050 sensor
- RPi.GPIO: Raspberry Pi GPIO control
- numpy: Numerical computing for sensor data processing

### Code & Solutions
Rishab Seshadri - Enterprise WiFi (eduroam) configuration solution for Raspberry Pi
