#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <windows.h>

using namespace std;

// ================= ESP32 CHECK FUNCTION =================
bool checkESP32() {

    HANDLE hSerial;

    hSerial = CreateFile(
        "COM5",   // ?? CHANGE THIS TO YOUR ESP32 COM PORT
        GENERIC_READ | GENERIC_WRITE,
        0,
        0,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        0
    );

    if (hSerial == INVALID_HANDLE_VALUE) {
        return false;
    }

    CloseHandle(hSerial);
    return true;
}

// ================= STRUCT =================
struct Record {
    string spotID;
    string vehicleNumber;
    string vehicleType;
    string ownerName;
    string status;
};

// ================= LOAD DATA =================
vector<Record> loadData() {

    vector<Record> data;
    ifstream file("parking_database.csv");
    string line;

    if (!file.is_open()) {
        cout << "File not found!\n";
        return data;
    }

    getline(file, line);

    while (getline(file, line)) {

        stringstream ss(line);
        Record r;

        getline(ss, r.spotID, ',');
        getline(ss, r.vehicleNumber, ',');
        getline(ss, r.vehicleType, ',');
        getline(ss, r.ownerName, ',');
        getline(ss, r.status, ',');

        data.push_back(r);
    }

    file.close();
    return data;
}

// ================= SAVE DATA =================
void saveData(vector<Record> data) {

    ofstream file("parking_database.csv");

    file << "SpotID,VehicleNumber,VehicleType,OwnerName,Status\n";

    for (int i = 0; i < data.size(); i++) {

        file << data[i].spotID << ","
             << data[i].vehicleNumber << ","
             << data[i].vehicleType << ","
             << data[i].ownerName << ","
             << data[i].status << "\n";
    }

    file.close();
}

// ================= DISPLAY =================
void displayAll() {

    vector<Record> data = loadData();

    cout << "\n===== ALL RECORDS =====\n\n";
    cout << "SpotID\tVehicleNo\tType\tOwner\tStatus\n";

    for (int i = 0; i < data.size(); i++) {

        cout << data[i].spotID << "\t"
             << data[i].vehicleNumber << "\t\t"
             << data[i].vehicleType << "\t"
             << data[i].ownerName << "\t"
             << data[i].status << endl;
    }
}

// ================= SEARCH =================
void searchRecord(string id) {

    vector<Record> data = loadData();
    bool found = false;

    for (int i = 0; i < data.size(); i++) {

        if (data[i].spotID == id) {

            cout << "\nRecord Found:\n";
            cout << "SpotID: " << data[i].spotID << endl;
            cout << "Vehicle: " << data[i].vehicleNumber << endl;
            cout << "Type: " << data[i].vehicleType << endl;
            cout << "Owner: " << data[i].ownerName << endl;
            cout << "Status: " << data[i].status << endl;

            found = true;
            break;
        }
    }

    if (!found)
        cout << "Record not found.\n";
}

// ================= UPDATE STATUS =================
void updateStatus(string id, string status) {

    vector<Record> data = loadData();
    bool found = false;

    for (int i = 0; i < data.size(); i++) {

        if (data[i].spotID == id) {

            data[i].status = status;
            found = true;
            break;
        }
    }

    saveData(data);

    if (found)
        cout << "Status updated successfully.\n";
    else
        cout << "Record not found.\n";
}

// ================= REPLACE RECORD =================
void replaceRecord(string id, string vehicle, string type, string owner, string status) {

    vector<Record> data = loadData();
    bool found = false;

    for (int i = 0; i < data.size(); i++) {

        if (data[i].spotID == id) {

            data[i].vehicleNumber = vehicle;
            data[i].vehicleType = type;
            data[i].ownerName = owner;
            data[i].status = status;

            found = true;
            break;
        }
    }

    if (!found) {

        Record r;
        r.spotID = id;
        r.vehicleNumber = vehicle;
        r.vehicleType = type;
        r.ownerName = owner;
        r.status = status;

        data.push_back(r);
    }

    saveData(data);

    cout << "Record replaced/updated successfully.\n";
}

// ================= MAIN =================
int main() {

    // ================= ESP32 CHECK =================
    cout << "Checking ESP32 connection...\n";

    if (!checkESP32()) {
        cout << "ESP32 not detected. Please connect device first.\n";
        return 0;
    }

    cout << "ESP32 connected successfully!\n";

    // ================= LOGIN SYSTEM =================
    string username, password;

    cout << "\n===== SMART PARKING SYSTEM LOGIN =====\n";

    cout << "Username: ";
    getline(cin, username);

    cout << "Password: ";
    getline(cin, password);

    if (username != "shahzaib" || password != "2501528") {
        cout << "\nInvalid username or password. Access denied!\n";
        return 0;
    }

    cout << "\nLogin successful!\n";

    // ================= MENU =================
    int choice;

    do {
        cout << "\n===== SMART PARKING SYSTEM =====\n";
        cout << "1. Search Record\n";
        cout << "2. Display All\n";
        cout << "3. Update Status\n";
        cout << "4. Replace Full Record\n";
        cout << "5. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {

            string id;
            cout << "Enter Spot ID: ";
            getline(cin, id);

            searchRecord(id);
        }

        else if (choice == 2) {
            displayAll();
        }

        else if (choice == 3) {

            string id, status;

            cout << "Enter Spot ID: ";
            getline(cin, id);

            cout << "Enter Status (IN/OUT): ";
            getline(cin, status);

            updateStatus(id, status);
        }

        else if (choice == 4) {

            string id, vehicle, type, owner, status;

            cout << "Enter Spot ID: ";
            getline(cin, id);

            cout << "Enter Vehicle Number: ";
            getline(cin, vehicle);

            cout << "Enter Vehicle Type: ";
            getline(cin, type);

            cout << "Enter Owner Name: ";
            getline(cin, owner);

            cout << "Enter Status (IN/OUT): ";
            getline(cin, status);

            replaceRecord(id, vehicle, type, owner, status);
        }

    } while (choice != 5);

    return 0;
}
