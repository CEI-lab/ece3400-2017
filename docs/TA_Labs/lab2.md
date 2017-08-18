# ECE3400 Fall 2017
## Lab 2 TA Reference
### Introduction
This lab is all about interfacing and with and processing values from sensors. Specifically, it is about using the Arduino to preform a Fourier Transform on IR and Audio signals. Here are some talking points for the start of the lab, feel free to use as many or little of these talking points as you want.
* **Review Fourier Transforms:** Briefly go over how a Fourier Transform represents a signal in the frequency domain.  Describe the advantages of representing a signal in the frequency domain for signal processing purposes.  
* **What is an FFT?** Explain how an FFT is an algorithm for quickly calculating the Fourier transform of a signal. The Arduino represents a signal's Fourier coefficients by using "bins" which cover a range of frequencies
* **Sources of infrared noise:** Discuss sources of IR noise, such as the sun and fluorescent lights in the room. Explain the nature of this noise, does this noise have a frequency associated with it or is it constant magnitude?
* **Sources of audible noise:** Discuss the range frequencies that human voice covers. Discuss harmonics and how it might help them identify the sound of the whistle.
* **Different types of analog filters:** Review methods of analog filtering, such as low pass, high pass, and bandpass filters made with resistors/capacitors/inductors. Discuss the active filters and their advantage over passive filters, especially when dealing with low magnitude signals.
* **A/D conversion limitations:** Discuss the basic functionality of an A/D converter. Explain the constraints on an A/D converter such as resolution and sampling time. The built-in Arduino A/D converter has 10 bits of resolution and runs at 9615 Hz when using analog read.
* **Different types of digital filters:** Explain the basic methods of digital filtering. Go over what the Nyquist frequency of a signal is and why it is important.
* **How phototransistors work:** Explain that light allows current to flow through a phototransistor. Describe how the gain of the transistor makes it more sensitive to light than a than a photodiode.
* **How the microphone works:** Briefly describe piezo-electric materials and how they are used to detect sound.

### Team materials
#### Microphone circuit
- 1 Arduino
- 1 µF capacitor
- 300 Ω resistors
- ~3 kΩ resistor
- 1 Op-Amp
- Various resistors/capacitors
#### Treasure detection circuit
- 1 Arduino
- 1 800nm phototransistors
- 300 Ω resistors
- 1 Treasure emitter
- 1 Op-Amp
- Various resistors/capacitors

#### Useful references
- [FFT library wiki](http://wiki.openmusiclabs.com/wiki/ArduinoFFT) (Has list of functions and some example code)
- [Sallen Key filter design](http://sim.okawa-denshi.jp/en/OPseikiLowkeisan.htm) (Useful for microphone circuit)
- [Active band-pass filter review](http://www.electronics-tutorials.ws/filter/filter_7.html)
- [Microphone and amplifier datasheets](https://learn.adafruit.com/adafruit-agc-electret-microphone-amplifier-max9814/downloads)
- [Phototransistor datasheet](http://rohmfs.rohm.com/en/products/databook/datasheet/opto/optical_sensor/photo_transistor/rpt-34pb3f.pdf)
- [LM358 Op-Amp datasheet](http://www.ti.com/lit/ds/symlink/lm358.pdf	)
- [LF353 Op-Amp datasheet](http://www.ti.com/lit/ds/symlink/lf353-n.pdf)
