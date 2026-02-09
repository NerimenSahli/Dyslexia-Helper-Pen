# LexiPal: Dyslexia-Assistive Smart Pen

![Project Banner](https://img.shields.io/badge/Project-LexiPal-blue)
![Award](https://img.shields.io/badge/Award-3rd%20Place%20IEEE%20WIE%2C%20CIS%20%26%20EMBS-orange)
![ESP32](https://img.shields.io/badge/ESP32-CAM-success)
![IoT](https://img.shields.io/badge/IoT-Assistive%20Technology-green)

## 🏆 Project Recognition
**3rd Place Award** – IEEE WIE, CIS & EMBS Technical Challenge

## 📖 Overview
LexiPal is an innovative smart pen designed to help children with dyslexia read printed text independently. The device combines a miniature camera, ESP32 microcontroller, and mobile application to provide real-time word scanning, text-to-speech feedback, and learning analytics in a child-friendly, ergonomic package.

## 🎯 Problem Statement
Children with dyslexia often struggle with reading, writing, and spelling, which can lead to frustration and reduced academic confidence. Existing assistive tools typically treat users as passive recipients rather than active learners, potentially diminishing motivation for independent reading practice.

## 💡 Our Solution
LexiPal addresses these challenges through:
- **Active Learning Design**: Encourages independent word decoding before providing assistance
- **Real-Time Assistance**: Instant auditory feedback for difficult words
- **Parental Monitoring**: Detailed progress tracking and engagement analytics
- **Ergonomic Hardware**: Child-friendly pen design with comfortable grip

## 🛠️ Technical Implementation

### Hardware Architecture
- **Processor**: ESP32-CAM module with OV2640 camera
- **Power**: 3.7V 2000mAh LiPo battery with MT3608 boost converter
- **Connectivity**: Dual Wi-Fi mode (AP + STA) for simultaneous local streaming and internet access
- **Form Factor**: Custom 3D-printed enclosure (140mm × 35mm)

### Firmware Features
- Dual Wi-Fi network configuration (Access Point + Station)
- MJPEG streaming server for real-time camera feed
- Static IP configuration for reliable connectivity
- Power management optimization for extended battery life

### Software Pipeline
1. **Video Capture**: Live MJPEG stream via ESP32-CAM
2. **Image Processing**: OpenCV-based preprocessing (grayscale, thresholding, noise removal)
3. **OCR**: Tesseract engine with multi-language support (Arabic, English, French)
4. **Text Processing**: Spell correction, simplification, and keyword extraction
5. **Mobile Interface**: Flutter app for user interaction and parental monitoring

## 📁 Repository Contents

| File | Description |
|------|-------------|
| `dyslexia_pen_project.pdf` | **Individual portfolio report** - Detailed documentation of my specific contributions to hardware development, 3D modeling, circuit design, and firmware programming |
| `LexiPal.pdf` | **IEEE club project report** - Comprehensive project documentation including background research, methodology, and team contributions |
| `DyslexiaPenCode.ino` | **Complete firmware source code** - Arduino sketch implementing dual Wi-Fi mode and camera streaming|
| `camera testing.mp4` | **Functionality demonstration** - Video showing the ESP32-CAM streaming to a web browser |
| `3DmodelVideo.mp4.zip` | **3D design showcase** - Video demonstrating the SolidWorks model and enclosure design |
| `voltage regulation.mp4` | **Hardware validation** - Video testing the power management system and battery performance |

## 🚀 Key Features
- **Dual Network Architecture**: Simultaneous AP (for mobile app connection) and STA (for internet access) operation
- **Active Learning**: Step-by-step assistance that encourages independent problem-solving
- **Parental Controls**: Real-time notifications and progress tracking
- **Multi-Language Support**: Arabic, English, and French OCR capabilities
- **Ergonomic Design**: Child-sized, comfortable grip with optimal camera positioning

## 🏗️ My Contributions
As documented in `dyslexia_pen_project.pdf`, my primary contributions included:
- **3D Mechanical Design**: Complete SolidWorks modeling of the pen enclosure
- **Electrical System**: Circuit design, component assembly, and power management optimization
- **Firmware Development**: Implementation of dual Wi-Fi mode and camera streaming server
- **Hardware Debugging**: Diagnosed and resolved battery current supply issues
- **Systems Integration**: Validated end-to-end functionality through iterative testing

## 🔧 Technologies Used (For my part)
- **Hardware**: ESP32-CAM, LiPo Battery, MT3608 Boost Converter
- **Software**: Arduino C++, SolidWorks
- **Networking**: Wi-Fi AP/STA modes, HTTP server, MJPEG streaming
- **Design**: 3D modeling

## 📈 Impact
- Successfully transformed conceptual design into functional prototype
- Resolved critical connectivity challenges through innovative firmware solutions
- Created foundation for mobile application development
- Demonstrated practical approach to assistive technology development

## 🔮 Future Work
- Adaptive learning algorithms for personalized assistance
- Enhanced hardware durability and comfort
- Integration with educational institutions and support associations
- Expanded language and character set support

## 📚 References
Project based on research into dyslexia assistive technologies and best practices for inclusive educational tools.

## 📄 License
This project is developed for educational and assistive purposes.

---

*Note: This repository contains both individual contributions (`dyslexia_pen_project.pdf`) and team documentation (`LexiPal.pdf`). The individual report details specific technical implementations, while the team report provides comprehensive project context.*
