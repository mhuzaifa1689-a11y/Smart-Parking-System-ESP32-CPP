# Smart-Parking-System-ESP32-CPP
A C++ Parking System featuring hardware authentication via ESP32 and a CSV database.
# Smart Parking Management System (ESP32 + C++)

## 📌 Project Overview
This is a **Smart Hardware-Authenticated Parking Management System** developed for the Mechatronics Engineering department at Air University. It utilizes an **ESP32 microcontroller** as a physical security key. 

## 👥 Team Members
* **Malik Ahsan (2501522)** - Team Lead
* **Shahzaib (2501528)** - Database Management
* **Muhammad Huzaifa (2501549)** - Hardware Interfacing

## 🛠️ Technical Features
- **Hardware-Key Security:** Verified via Windows API handshake on `COM5`.
- **Data Management:** Handles 100 parking records via `parking_database.csv`.
- **Persistence:** Real-time logging of vehicle entry/exit.

## 🚀 Usage
1. Connect ESP32 to COM5.
2. Compile `Main.cpp`.
3. Run executable and log in with admin credentials.

