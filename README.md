
# WandDuel - Gesture-Controlled Magic Wand 1v1



## Team Members

- **Aashrit Marripelli**
- **Sahil Shaik**
- **Shashank Subbaraman**
- **Eshwar Thammineni**
---

## Project Purpose

MysticWand is an interactive gesture-controlled magic wand that brings fantasy spellcasting into reality. Using a custom 3D-printed wand embedded with motion sensors, users can perform magical gestures to control smart home devices, trigger visual effects, and interact with digital environments in an immersive way.



## Challenges & Solutions

### Challenge 1: 3D-Printed Wand Structure Issues

**Problem:** Initial wand designs were consistently too thick, making them heavy, awkward to hold, and visually disproportionate. The bulky design compromised the wand's usability and didn't have the sleek, elegant appearance we envisioned for a magical wand.

**Solution:** We went through multiple redesign iterations to slim down the wand while maintaining structural integrity. We experimented with variable wall thickness - using thicker walls only at critical stress points like the grip and tip connection, while thinning other sections significantly. We hollowed out non-essential areas and tested different infill patterns to find the right balance between strength and weight reduction. We also refined the overall proportions, creating a gradual taper from handle to tip that felt more natural and balanced. After several prototype iterations, we achieved a noticeably slimmer profile that was much lighter and more comfortable to handle. The final design strikes the right balance - slim and elegant enough to look like a proper wand, yet strong enough to withstand regular use and the occasional accidental drop.

---

### Challenge 2: Gesture Recognition Reliability

**Problem:** The system suffered from both false positives (random movements triggering spells) and false negatives (valid gestures not being recognized). Any wand movement could randomly trigger effects, and different users performed the same gestures in vastly different ways.

**Solution:** We implemented a multi-layered approach to address both error types. To reduce false positives, we added an activation requirement so the system only listens for gestures when the user explicitly signals intent. We implemented confidence thresholds in our machine learning model to filter out uncertain matches and added cooldown periods between spell casts to prevent motion echoes. We also created motion magnitude filters to ignore vibrations and small unintentional movements. To reduce false negatives, we used flexible pattern matching that accommodates user variation in speed and amplitude. We implemented user-specific calibration modes where individuals could train their own gesture templates and provided real-time visual feedback during gesture performance so users could adjust mid-cast. We expanded our training dataset to include gestures from multiple users at varying speeds. This combination dramatically improved recognition reliability and user satisfaction.

---

### Challenge 3: Limited Battery Components for Second Wand
**Problem:** We only had one PiSugar S battery module available, but needed to create two functional wands for our project. We couldn't order another PiSugar in time for the hackathon deadline, forcing us to find an alternative power solution for the second wand.

**Solution:** We adapted the second wand to use a standard rechargeable lithium battery combined with a buck converter to step down the voltage to the required level for our microcontroller and sensors. This required redesigning the internal cavity of the second wand to accommodate the different form factor of the battery and buck converter module, as they took up more space than the compact PiSugar. We had to adjust the weight distribution since the components were bulkier and positioned differently. We also added additional wiring and soldering to connect the buck converter properly, and implemented voltage regulation to ensure stable power delivery. While the second wand ended up slightly heavier and with a different internal layout than the first, both wands functioned identically from the user's perspective. This taught us the importance of having backup components and the value of adaptable designs that can accommodate different hardware configurations.

---

### Challenge 4: Internal Component Movement and Rattling

**Problem:** After assembling the wand, the battery and internal components would shift and rattle inside the handle during use. This created distracting noise, caused wires to strain and disconnect, and affected the wand's balance, making gesture recognition inconsistent.

**Solution:** We redesigned the internal structure by 3d printing custom mounting brackets and compartments inside the handle. We created precisely-sized cavities that matched the exact dimensions of each component - the battery, ESP32, MPU-6050 sensor, and buck converter. These internal casing structures held each component securely in place and prevented any movement. We added friction-fit slots and snap-in features that allowed components to be inserted during assembly but held them firmly once installed. We also designed wire routing channels that kept cables organized and prevented them from getting pinched or pulled during movement. After printing the updated handle with integrated internal structure, we reassembled the wand and tested it - no more rattling, no more disconnections, and consistent balance throughout use.

## 📚 Credits & Acknowledgments

### APIs 
