# 🏎️ Photoresistor Line-Following Robot

Source code for a photoresistor-based line-following robot. This project was developed for the line-following electronics competition at PTIT.

## 🛠️ Hardware Components
* **Microcontroller:** STM32 (Tailored to the custom hardware configuration)
* **Sensors:** Photoresistor (LDR) module array for light/dark surface detection.
* **Motor Driver:** TB6612 motor driver IC.
* **Motors:** N20 micro DC gear motors with wheels.

## 📸 Media & Schematics
<img width="2560" height="1927" alt="image" src="https://github.com/user-attachments/assets/7707472e-8d71-4aad-80f4-90d0df16aae6" />

## ⚙️ Setup & Configuration
1. Download and install the [Arduino IDE](https://www.arduino.cc/en/software) (ensure the STM32 board manager extension is installed).
2. Open the `line_following.ino` file.
3. Fine-tune the parameters in the code to suit your specific ambient light environment:
   * Photoresistor light/dark threshold values.
   * Motor PWM speed constants.
4. Connect the development board to your computer and click **Upload**.
