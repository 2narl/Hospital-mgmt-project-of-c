# Hospital Management System

A simple console-based Hospital Management System developed in C. This project helps manage patient records, bed availability, and hospital operations efficiently using file handling for permanent data storage.

## Features

- Add New Patient
- Display All Patients
- Search Patient by Name
- Search Patient by ID
- Update Patient Information
- Delete Patient Record
- Check Total Patients
- Display Bed Status
- Automatic Data Storage Using File Handling
- Phone Number Validation
- Admission Date Validation

## Technologies Used

- C Programming Language
- File Handling
- Structures
- Functions
- Arrays
- String Manipulation

## Project Structure

```
Hospital-Management-System/
│
├── main.c
├── patients.txt
└── README.md
```

## Patient Information Stored

Each patient record contains:

- Patient ID
- Name
- Age
- Disease/Condition
- Phone Number
- Admission Date

## Functional Modules

### 1. Add Patient
- Generates unique Patient ID
- Checks bed availability
- Validates phone number
- Validates admission date
- Saves record to file

### 2. Display Patients
- Shows all patient records in tabular format

### 3. Search Patient
- Search by Name
- Search by ID

### 4. Update Patient
- Modify existing patient details
- Updates file automatically

### 5. Delete Patient
- Removes patient records
- Updates available bed count

### 6. Bed Management
- Shows:
  - Total Beds
  - Occupied Beds
  - Available Beds

## Data Storage

Patient records are stored permanently in:

```
patients.txt
```

Data format:

```
PatientID|Name|Age|Disease|Phone|AdmissionDate
```

Example:

```
1000|John Doe|25|Fever|9876543210|15/05/2026
```

## Compilation

Using GCC:

```bash
gcc main.c -o hospital
```

## Run Program

Windows:

```bash
hospital.exe
```

Linux/macOS:

```bash
./hospital
```

## Menu Options

```
1. Add Patient
2. Display All Patients
3. Search Patient by Name
4. Search Patient by ID
5. Update Patient Information
6. Delete Patient
7. Total Patients
8. Bed Status
9. Exit
```

## Validation Features

### Phone Number Validation
- Must contain exactly 10 digits
- Only numeric values allowed

### Date Validation
- Format: DD/MM/YYYY
- Checks valid day, month, and leap year

## Future Enhancements

- Doctor Management
- Appointment Scheduling
- Billing System
- Medicine Inventory
- User Authentication
- Database Integration (MySQL)

## Learning Outcomes

This project demonstrates:

- Structured Programming
- File Handling
- Data Validation
- Record Management
- Menu-Driven Applications
- Problem Solving in C

## Author

**Arl2n**
Student, Purbanchal University

---

⭐ If you found this project useful, consider giving it a star on GitHub.
