#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATIENTS 50
#define MAX_NAME 50
#define MAX_DISEASE 50
#define MAX_PHONE 15
#define TOTAL_BEDS 50
#define PATIENT_FILE "patients.txt"

// Structure to store patient information
struct Patient {
    int patientID;
    char name[MAX_NAME];
    int age;
    char disease[MAX_DISEASE];
    char phone[MAX_PHONE];
    char admissionDate[15];
};

// Global patient list loaded from file
struct Patient patients[MAX_PATIENTS];
int patientCount = 0;
int availableBeds = TOTAL_BEDS;
int nextPatientID = 1000;

// Function to save patients to file
void savePatientsToFile() {
    FILE *file = fopen(PATIENT_FILE, "w");
    if (!file) {
        printf("Error: Unable to save patient records to %s\n", PATIENT_FILE);
        return;
    }

    for (int i = 0; i < patientCount; i++) {
        fprintf(file, "%d|%s|%d|%s|%s|%s\n",
                patients[i].patientID,
                patients[i].name,
                patients[i].age,
                patients[i].disease,
                patients[i].phone,
                patients[i].admissionDate);
    }

    fclose(file);
}

// Function to load patients from file
int loadPatientsFromFile() {
    FILE *file = fopen(PATIENT_FILE, "r");
    if (!file) {
        return 0;
    }

    char line[256];
    patientCount = 0;
    nextPatientID = 1000;

    while (fgets(line, sizeof(line), file) && patientCount < MAX_PATIENTS) {
        struct Patient temp;
        char *token;

        token = strtok(line, "|\n");
        if (!token) continue;
        temp.patientID = atoi(token);

        token = strtok(NULL, "|\n");
        if (!token) continue;
        strncpy(temp.name, token, MAX_NAME - 1);
        temp.name[MAX_NAME - 1] = '\0';

        token = strtok(NULL, "|\n");
        if (!token) continue;
        temp.age = atoi(token);

        token = strtok(NULL, "|\n");
        if (!token) continue;
        strncpy(temp.disease, token, MAX_DISEASE - 1);
        temp.disease[MAX_DISEASE - 1] = '\0';

        token = strtok(NULL, "|\n");
        if (!token) continue;
        strncpy(temp.phone, token, MAX_PHONE - 1);
        temp.phone[MAX_PHONE - 1] = '\0';

        token = strtok(NULL, "|\n");
        if (!token) continue;
        strncpy(temp.admissionDate, token, sizeof(temp.admissionDate) - 1);
        temp.admissionDate[sizeof(temp.admissionDate) - 1] = '\0';

        patients[patientCount++] = temp;
        if (temp.patientID >= nextPatientID) {
            nextPatientID = temp.patientID + 1;
        }
    }

    fclose(file);
    availableBeds = TOTAL_BEDS - patientCount;
    return 1;
}

// Returns the smallest unused patient ID starting from 1000
int getNextPatientID() {
    int candidate = 1000;

    while (1) {
        int used = 0;
        for (int i = 0; i < patientCount; i++) {
            if (patients[i].patientID == candidate) {
                used = 1;
                break;
            }
        }
        if (!used) {
            return candidate;
        }
        candidate++;
    }
}

// Function to validate admission date in DD/MM/YYYY format
int isValidDate(const char *date) {
    if (strlen(date) != 10 || date[2] != '/' || date[5] != '/') {
        return 0;
    }

    int day, month, year;
    if (sscanf(date, "%2d/%2d/%4d", &day, &month, &year) != 3) {
        return 0;
    }

    if (year < 1900 || month < 1 || month > 12 || day < 1) {
        return 0;
    }

    int maxDay;
    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            maxDay = 31;
            break;
        case 4: case 6: case 9: case 11:
            maxDay = 30;
            break;
        case 2:
            if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
                maxDay = 29;
            } else {
                maxDay = 28;
            }
            break;
        default:
            return 0;
    }

    return day <= maxDay;
}

// Function to add a new patient
void addPatient() {
    if (patientCount >= MAX_PATIENTS) {
        printf("\nHospital is at full capacity! Cannot add more patients.\n");
        return;
    }

    if (availableBeds <= 0) {
        printf("\nNo beds available! Cannot admit more patients.\n");
        return;
    }

    struct Patient newPatient;
    newPatient.patientID = getNextPatientID();

    printf("\n========== Add New Patient ==========\n");
    printf("Patient ID: %d\n", newPatient.patientID);

    printf("Enter Patient Name: ");
    scanf(" %49[^\n]", newPatient.name);

    printf("Enter Age: ");
    scanf("%d", &newPatient.age);

    printf("Enter Disease/Condition: ");
    scanf(" %49[^\n]", newPatient.disease);

    // Validate phone number - must be exactly 10 digits
    int validPhone = 0;
    while (!validPhone) {
        printf("Enter Phone Number (10 digits): ");
        scanf("%14s", newPatient.phone);
        
        if (strlen(newPatient.phone) != 10) {
            printf("Error! Phone number must be exactly 10 digits. Please try again.\n");
            continue;
        }
        
        validPhone = 1;
        for (int i = 0; i < 10; i++) {
            if (newPatient.phone[i] < '0' || newPatient.phone[i] > '9') {
                validPhone = 0;
                printf("Error! Phone number must contain only digits. Please try again.\n");
                break;
            }
        }
    }

    int validDate = 0;
    while (!validDate) {
        printf("Enter Admission Date (DD/MM/YYYY): ");
        scanf(" %14[^\n]", newPatient.admissionDate);

        if (!isValidDate(newPatient.admissionDate)) {
            printf("Error! Please enter a valid admission date in DD/MM/YYYY format.\n");
            continue;
        }

        validDate = 1;
    }

    patients[patientCount] = newPatient;
    patientCount++;
    availableBeds--;  // Reduce available beds
    savePatientsToFile();

    printf("\nPatient added successfully!\n");
    printf("Available beds now: %d/%d\n", availableBeds, TOTAL_BEDS);
}

// Function to display all patients
void displayPatients() {
    if (patientCount == 0) {
        printf("\nNo patients in the system.\n");
        return;
    }

    printf("\n========== Patient List ==========\n");
    printf("%-5s | %-20s | %-5s | %-20s | %-15s | %-12s\n",
           "ID", "Name", "Age", "Disease", "Phone", "Admission Date");
    printf("------------------------------------------------------------------------------------\n");

    for (int i = 0; i < patientCount; i++) {
        printf("%-5d | %-20s | %-5d | %-20s | %-15s | %-12s\n",
               patients[i].patientID,
               patients[i].name,
               patients[i].age,
               patients[i].disease,
               patients[i].phone,
               patients[i].admissionDate);
    }
    printf("------------------------------------------------------------------------------------\n");
}

// Function to search for a patient by name
void searchPatient() {
    if (patientCount == 0) {
        printf("\nNo patients in the system.\n");
        return;
    }

    char searchName[MAX_NAME];
    printf("\n========== Search Patient ==========\n");
    printf("Enter Patient Name to search: ");
    scanf(" %49[^\n]", searchName);

    int found = 0;
    printf("\n------- Search Results -------\n");

    for (int i = 0; i < patientCount; i++) {
        if (strcasecmp(patients[i].name, searchName) == 0) {
            printf("\nPatient Found!\n");
            printf("Patient ID: %d\n", patients[i].patientID);
            printf("Name: %s\n", patients[i].name);
            printf("Age: %d\n", patients[i].age);
            printf("Disease: %s\n", patients[i].disease);
            printf("Phone: %s\n", patients[i].phone);
            printf("Admission Date: %s\n", patients[i].admissionDate);
            found = 1;
        }
    }

    if (!found) {
        printf("\nPatient '%s' not found in the system.\n", searchName);
    }
}

// Function to search for a patient by ID
void searchPatientByID() {
    if (patientCount == 0) {
        printf("\nNo patients in the system.\n");
        return;
    }

    int searchID;
    printf("\n========== Search Patient by ID ==========\n");
    printf("Enter Patient ID to search: ");
    scanf("%d", &searchID);

    int found = 0;

    for (int i = 0; i < patientCount; i++) {
        if (patients[i].patientID == searchID) {
            printf("\nPatient Found!\n");
            printf("Patient ID: %d\n", patients[i].patientID);
            printf("Name: %s\n", patients[i].name);
            printf("Age: %d\n", patients[i].age);
            printf("Disease: %s\n", patients[i].disease);
            printf("Phone: %s\n", patients[i].phone);
            printf("Admission Date: %s\n", patients[i].admissionDate);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nPatient with ID %d not found in the system.\n", searchID);
    }
}

// Function to update patient information
void updatePatient() {
    if (patientCount == 0) {
        printf("\nNo patients in the system.\n");
        return;
    }

    int searchID;
    printf("\n========== Update Patient ==========\n");
    printf("Enter Patient ID to update: ");
    scanf("%d", &searchID);

    for (int i = 0; i < patientCount; i++) {
        if (patients[i].patientID == searchID) {
            printf("\nCurrent Details:\n");
            printf("Name: %s\n", patients[i].name);
            printf("Age: %d\n", patients[i].age);
            printf("Disease: %s\n", patients[i].disease);
            printf("Phone: %s\n", patients[i].phone);

            printf("\nEnter New Name: ");
            scanf(" %49[^\n]", patients[i].name);

            printf("Enter New Age: ");
            scanf("%d", &patients[i].age);

            printf("Enter New Disease/Condition: ");
            scanf(" %49[^\n]", patients[i].disease);

            // Validate phone number - must be exactly 10 digits
            int validPhone = 0;
            while (!validPhone) {
                printf("Enter New Phone Number (10 digits): ");
                scanf("%14s", patients[i].phone);
                
                if (strlen(patients[i].phone) != 10) {
                    printf("Error! Phone number must be exactly 10 digits. Please try again.\n");
                    continue;
                }
                
                validPhone = 1;
                for (int j = 0; j < 10; j++) {
                    if (patients[i].phone[j] < '0' || patients[i].phone[j] > '9') {
                        validPhone = 0;
                        printf("Error! Phone number must contain only digits. Please try again.\n");
                        break;
                    }
                }
            }

            int validDate = 0;
            while (!validDate) {
                printf("Enter New Admission Date (DD/MM/YYYY): ");
                scanf(" %14[^\n]", patients[i].admissionDate);

                if (!isValidDate(patients[i].admissionDate)) {
                    printf("Error! Please enter a valid admission date in DD/MM/YYYY format.\n");
                    continue;
                }
                validDate = 1;
            }

            savePatientsToFile();
            printf("\nPatient updated successfully!\n");
            return;
        }
    }

    printf("\nPatient with ID %d not found.\n", searchID);
}

// Function to delete a patient
void deletePatient() {
    if (patientCount == 0) {
        printf("\nNo patients in the system.\n");
        return;
    }

    int searchID;
    printf("\n========== Delete Patient ==========\n");
    printf("Enter Patient ID to delete: ");
    scanf("%d", &searchID);

    for (int i = 0; i < patientCount; i++) {
        if (patients[i].patientID == searchID) {
            // Shift patients array
            for (int j = i; j < patientCount - 1; j++) {
                patients[j] = patients[j + 1];
            }
            patientCount--;
            availableBeds++;  // Increase available beds
            savePatientsToFile();
            printf("\nPatient deleted successfully!\n");
            printf("Available beds now: %d/%d\n", availableBeds, TOTAL_BEDS);
            return;
        }
    }

    printf("\nPatient with ID %d not found.\n", searchID);
}

// Function to display bed status
void displayBedStatus() {
    printf("\n========== Hospital Bed Status ==========\n");
    printf("Total Beds: %d\n", TOTAL_BEDS);
    printf("Occupied Beds: %d\n", patientCount);
    printf("Available Beds: %d\n", availableBeds);
    
}

// Function to display menu
void displayMenu() {
    printf("\n========== HOSPITAL MANAGEMENT SYSTEM  ==========\n");
    printf("1. Add Patient\n");
    printf("2. Display All Patients\n");
    printf("3. Search Patient by Name\n");
    printf("4. Search Patient by ID\n");
    printf("5. Update Patient Information\n");
    printf("6. Delete Patient\n");
    printf("7. Total Patients\n");
    printf("8. Bed Status\n");
    printf("9. Exit\n");
    printf("\nEnter your choice (1-9): ");
}

// Main function
int main() {
    int choice;

    if (!loadPatientsFromFile()) {
        savePatientsToFile();
    }

    while (1) {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addPatient();
                break;

            case 2:
                displayPatients();
                break;

            case 3:
                searchPatient();
                break;

            case 4:
                searchPatientByID();
                break;

            case 5:
                updatePatient();
                break;

            case 6:
                deletePatient();
                break;

            case 7:
                printf("\nTotal Patients in Hospital: %d/%d\n", patientCount, MAX_PATIENTS);
                break;

            case 8:
                displayBedStatus();
                break;

            case 9:
                printf("\nThank you for using Hospital Management System.\n\n");
                exit(0);

            default:
                printf("\nInvalid choice! Please enter a number between 1 and 9.\n");
        }
    }

    return 0;
}
