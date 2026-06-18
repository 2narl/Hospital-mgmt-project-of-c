# Hospital Management System

## Overview
This is a **Hospital Management System** written in C that manages patient records and hospital bed allocation. It provides a menu-driven interface to add, search, update, and delete patient information. All patient data is stored persistently in a text file.

---

## Features

### Core Functionality
1. **Add Patient** - Register new patients with automatic ID generation (starting from 1000)
2. **Display All Patients** - View complete list of all admitted patients
3. **Search Patient by Name** - Find patient using their name (case-insensitive)
4. **Search Patient by ID** - Locate patient using their unique ID
5. **Update Patient** - Modify existing patient information
6. **Delete Patient** - Remove patient from the system
7. **View Total Patients** - Check total number of patients in hospital
8. **Check Bed Status** - Monitor available and occupied beds

---

## System Requirements

### Software Requirements
- **Compiler**: GCC or any C compiler
- **OS**: Linux, Windows (with MinGW), or macOS
- **RAM**: Minimum 512 MB
- **Storage**: 1 MB (for patient records)

### Hardware Requirements
- Basic computer with standard input/output devices

---

## File Structure

```
hospital_management_system/
│
├── hospital.c          (Main source code)
├── patients.txt        (Data storage file - auto-created)
└── README.md          (This file)
```

---

## How to Compile and Run

### Step 1: Compile the Program
```bash
gcc -o hospital hospital.c
```

### Step 2: Run the Program
```bash
./hospital
```

**For Windows:**
```bash
gcc -o hospital.exe hospital.c
hospital.exe
```

---

## Data Storage Format

Patient data is stored in `patients.txt` with pipe-separated values:

```
PatientID|Name|Age|Disease|Phone|AdmissionDate
1000|Raj Kumar|35|Fever|9841234567|15/06/2026
1001|Priya Singh|28|Cough|9847654321|16/06/2026
```

---

## System Constraints

| Parameter | Value |
|-----------|-------|
| Maximum Patients | 50 |
| Maximum Bed Capacity | 50 |
| Patient Name Length | 50 characters |
| Disease Name Length | 50 characters |
| Phone Number Length | 15 digits (10 required) |
| Patient ID Range | Starting from 1000 |

---

## Function Descriptions

### 1. `void addPatient()`
- Adds a new patient to the system
- Auto-generates unique Patient ID
- Validates phone number (exactly 10 digits)
- Validates admission date in DD/MM/YYYY format
- Decreases available bed count

### 2. `void displayPatients()`
- Shows formatted table of all patients
- Displays in tabular format with columns: ID, Name, Age, Disease, Phone, Admission Date

### 3. `void searchPatient()`
- Searches for patient by name
- Case-insensitive search
- Displays complete patient details if found

### 4. `void searchPatientByID()`
- Searches for patient using unique ID
- Returns patient details if found

### 5. `void updatePatient()`
- Modifies patient information
- Requires Patient ID
- Validates all input fields
- Saves changes to file

### 6. `void deletePatient()`
- Removes patient from system
- Requires Patient ID
- Increases available bed count after deletion
- Updates patient file

### 7. `void displayBedStatus()`
- Shows hospital bed statistics
- Displays: Total beds, Occupied beds, Available beds

### 8. `int isValidDate(const char *date)`
- Validates date in DD/MM/YYYY format
- Checks for leap years
- Validates day, month, and year ranges

### 9. `void savePatientsToFile()` & `int loadPatientsFromFile()`
- Saves patient data to persistent file
- Loads data on program startup
- Uses pipe (|) as delimiter

---

## Input Validation Rules

### Phone Number
- Must be exactly **10 digits**
- Only numeric values allowed
- Example: `9841234567`

### Admission Date
- Format: **DD/MM/YYYY**
- Valid day range: 1-31 (depends on month)
- Valid month range: 01-12
- Valid year: 1900 onwards
- Example: `15/06/2026`

### Age
- Positive integer only

### Names and Disease
- Alphanumeric with spaces
- Maximum 50 characters

---

## Menu Options Explained

```
========== HOSPITAL MANAGEMENT SYSTEM ==========
1. Add Patient              → Register new patient
2. Display All Patients     → View all patients list
3. Search Patient by Name   → Find by patient name
4. Search Patient by ID     → Find by patient ID
5. Update Patient           → Modify patient details
6. Delete Patient           → Remove patient record
7. Total Patients           → Show patient count
8. Bed Status               → Display bed availability
9. Exit                     → Close the program
```

---

## Example Usage

### Adding a Patient
```
Enter Patient Name: Ramesh Kumar
Enter Age: 45
Enter Disease/Condition: Diabetes
Enter Phone Number (10 digits): 9841234567
Enter Admission Date (DD/MM/YYYY): 15/06/2026
```

### Searching Patient
```
Enter Patient Name to search: Ramesh Kumar
```

---

## Error Handling

The system handles following errors:

| Error | Message |
|-------|---------|
| Invalid Phone | "Phone number must be exactly 10 digits" |
| Invalid Date | "Please enter a valid date in DD/MM/YYYY format" |
| Patient Not Found | "Patient 'name' not found in the system" |
| No Beds Available | "No beds available! Cannot admit more patients" |
| Full Capacity | "Hospital is at full capacity!" |
| No Patients | "No patients in the system" |

---

## Key Concepts Used

### 1. **Structures** 
- `struct Patient` to store patient information

### 2. **Arrays**
- Global array `patients[]` to maintain patient records in memory

### 3. **File I/O**
- File operations for persistent data storage
- Read and write operations

### 4. **String Functions**
- `strcasecmp()` for case-insensitive search
- `strtok()` for parsing file data
- `strncpy()` for safe string copying

### 5. **Date Validation**
- Leap year checking
- Month-specific day validation

### 6. **Dynamic ID Generation**
- Auto-increment from 1000
- Handles ID gaps after deletion

---

## Advantages

✓ Simple and user-friendly menu interface  
✓ Data persistence using file storage  
✓ Comprehensive input validation  
✓ Efficient search operations  
✓ Real-time bed availability tracking  
✓ Case-insensitive patient search  
✓ Automatic ID generation  

---

## Limitations

✗ Console-based UI (no graphical interface)  
✗ Single-user system (no multi-user support)  
✗ No user authentication  
✗ No database backend  
✗ Fixed patient and bed limits  
✗ No backup/recovery mechanism  
✗ No reporting features  

---

## Future Enhancements

1. Add user authentication and login system
2. Implement database (SQLite/MySQL)
3. Add reporting and statistics features
4. Create graphical user interface (GUI)
5. Add appointment scheduling module
6. Implement doctor-patient assignment
7. Add billing system
8. Mobile app integration

---

## Author Notes

- This project demonstrates fundamental C programming concepts
- Suitable for learning file I/O, data structures, and input validation
- Can be extended for real-world hospital management systems

---

## License

This project is open-source and available for educational purposes.

---

## Support

For issues or questions about the system, ensure:
- All input follows specified formats
- `patients.txt` file has read/write permissions
- Sufficient disk space is available
- Compiler is properly installed

---

**Last Updated**: June 2026  
**Version**: 1.0
