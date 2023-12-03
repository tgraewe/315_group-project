#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define data structures for bus routes, schedules, and fares
struct BusRoute {
    char routeID[10];
    char origin[50];
    char destination[50];
};

struct BusSchedule {
    char scheduleID[10];
    char routeID[10];
    char departureTime[10];
    int availableSeats;
    float fare;
};

// Function prototypes
void displayOperatorMenu();
void addBusRoute();
void addBusSchedule();
void displayPassengerMenu();
void viewRoutes();
void viewSchedules();
void makeReservation(float fare);

// Global arrays to store bus routes and schedules (replace with dynamic memory allocation for a real project)
struct BusRoute routes[10];
struct BusSchedule schedules[20];
int routeCount = 0;
int scheduleCount = 0;
int main() {

int userType;

    // Initialize any necessary variables or data structures here.

    do {
        printf("Choose User Type:\n");
        printf("1. Operator\n");
        printf("2. Passenger\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &userType);

        switch (userType) {
            case 1:
                displayOperatorMenu();
                break;
            case 2:
                displayPassengerMenu();
                break;
            case 0:
                printf("Exiting Bus Reservation System. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (userType != 0);

    return 0;
}

void displayOperatorMenu() {
   
    int operatorChoice;

    do {
        printf("\n=== Operator Menu ===\n");
        printf("1. Add Bus Route\n");
        printf("2. Add Bus Schedule\n");
        printf("0. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &operatorChoice);

        switch (operatorChoice) {
            case 1:
                addBusRoute();
                break;
            case 2:
                addBusSchedule();
                break;
            case 0:
                printf("Returning to Main Menu.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (operatorChoice != 0);
}

void addBusRoute() {
    // Implement functionality to add a new bus route to the system
    printf("\nEnter Route ID: ");
    scanf("%s", routes[routeCount].routeID);
    printf("Enter Origin: ");
    scanf("%s", routes[routeCount].origin);
    printf("Enter Destination: ");
    scanf("%s", routes[routeCount].destination);

    routeCount++;
    printf("Bus Route Added Successfully!\n");
}

void addBusSchedule() {
    // Implement functionality to add a new bus schedule to the system
    printf("\nEnter Schedule ID: ");
    scanf("%s", schedules[scheduleCount].scheduleID);
    printf("Enter Route ID: ");
    scanf("%s", schedules[scheduleCount].routeID);
    printf("Enter Departure Time: ");
    scanf("%s", schedules[scheduleCount].departureTime);
    printf("Enter Available Seats: ");
    scanf("%d", &schedules[scheduleCount].availableSeats);
    printf("Enter Fare: ");
    scanf("%f", &schedules[scheduleCount].fare);

    scheduleCount++;
    printf("Bus Schedule Added Successfully!\n");
}

void displayPassengerMenu() {
    int passengerChoice;

    do {
        printf("\n=== Passenger Menu ===\n");
        printf("1. View Bus Routes\n");
        printf("2. View Bus Schedules\n");
        printf("3. Make Reservation\n");
        printf("0. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &passengerChoice);

        switch (passengerChoice) {
            case 1:
                viewRoutes();
                break;
            case 2:
                viewSchedules();
                break;
            case 3:
                // Assume the fare is passed as an argument for simplicity
                makeReservation(20.0);
                break;
            case 0:
                printf("Returning to Main Menu.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (passengerChoice != 0);
}

void viewRoutes() {
    // Implement functionality to display available bus routes
    printf("\n=== Available Bus Routes ===\n");
    for (int i = 0; i < routeCount; i++) {
        printf("Route ID: %s, Origin: %s, Destination: %s\n", routes[i].routeID, routes[i].origin, routes[i].destination);
    }
}

void viewSchedules() {
    // Implement functionality to display available bus schedules
    printf("\n=== Available Bus Schedules ===\n");
    for (int i = 0; i < scheduleCount; i++) {
        printf("Schedule ID: %s, Route ID: %s, Departure Time: %s, Available Seats: %d, Fare: %.2f\n",
               schedules[i].scheduleID, schedules[i].routeID, schedules[i].departureTime,
               schedules[i].availableSeats, schedules[i].fare);
    }
}

void makeReservation(float fare) {
    // Implement functionality for passenger reservation, including payment processing
    printf("\nReservation Successful!\n");
    printf("Total Fare: $%.2f\n", fare);
    // Include additional steps for payment processing in a real-world scenario.
}