HueTime Lamp! — CSE Design Showcase Project
Developed by: Team Salamander (W5): 
Hamze Sigale, Yogitha, Emelia, and Ismail Yusuf
For our group project in CSE 1012: 3DP + Microcontrollers at the University of Minnesota Twin Cities, we set out to answer one question:
How can we make a lamp that reflects the time and temperature of the day?
Our answer is the HueTime Lamp! A smart ambient lamp that reflects the time and temperature through a wave of LED colors, a seashell inspired 3D-printed design, and looping playback of the Tetris theme for a fun touch!Core Features:
PCF8523 RTC: Provides real-time clock and date functionality.


TMP36 Sensor: Continuously monitors ambient temperature of the lamp.


NeoPixel Strip (#1426, 8 LEDs): Animates a wave-like gradient tied to the time of day.


Grove RGB LCD: Displays live time, date, and temperature in formatted output.


Piezo Buzzer: Continuously loops the Tetris theme for a playful touch.
3D Prints: Seashell Inspired lamp shade and sturdy base to conceal the wiring .

Code Highlights (Arduino):
Two Display Modes: A void function updates the NeoPixel wave animations based on the time. Either every 10 seconds or every 10 minutes controlled through loop logic.
Efficient Color Handling: RGB values are passed by reference in C++, optimizing memory use and enabling smooth, real-time LED transitions across all 8 NeoPixels within the loop function.

CAD Design Highlights (SolidWorks):
Lamp Shade: A seashell-inspired cover that radiates light from the NeoPixel LED. It serves a mix of design and art to offer some eye candy.


Study Base: Hides all the wiring, actuators and sensors and houses the LCD display for a sleek finish
We also had fun capturing photographic shots of the HueLight Lamp that showcases the gradient lighting effect, seashell shape, and LCD display.Showcase Reflection:
We had a blast presenting HueTime at the Spring 2025 CSE Design Showcase, and it was inspiring to see all the other projects from my peers. 
Checkout the In-Progress GitHub  Repository :github.com/90ismail
#UMNCSE #HueTimeLamp #Arduino #NeoPixel #TMP36 #PCF8523 #SolidWorks #SmartLamp #WaveGradient #TetrisTheme #3DPrinting #Microcontrollers #PassByReference #TeamSalamander #Wokwi

