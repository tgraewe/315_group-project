#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Maximum number of FAQs
#define MAX_FAQS 100

// Define data structures for bus routes, schedules, and fares
struct BusRoute {
    char routeID[10];
    char origin[50];
    char destination[50];
    int availableSeats;
    float fare;
};

struct BusSchedule {
    char busLocation[50];
    char routeID[10];
    char departureTime[10];
};

struct Passenger {
  char firstName[50];
  char lastName[50];
  char phoneNumber[20];
  char routeBooked[10];
};

struct FAQ {
    char question[100];
    char answer[200];
};

// Global arrays to store bus routes and schedules (replace with dynamic memory allocation for a real project)
struct BusRoute routes[10];
int routeCount = 0;
struct BusSchedule schedules[50];
int scheduleCount = 0;
struct FAQ faqs[MAX_FAQS];
int faqCount = 0;
struct Passenger passengers[240];
int passengerCount = 0;

// Function prototypes
void displayOperatorMenu();
void addBusRoute();
void addBusSchedule();
void displayPassengerMenu();
void viewRoutes();
void viewSchedules();
void makeReservation(float fare);

// Function to add a question and answer to the FAQ
void addFAQ(struct FAQ faqs[], int *faqCount) {
    if (*faqCount >= MAX_FAQS) {
        printf("FAQ is full. Cannot add more entries.\n");
        return;
    }

  printf("Enter the question: ");
  scanf(" %[^\n]", faqs[*faqCount].question);  // %[^\n] to read the entire line including spaces

  printf("Enter the answer: ");
  scanf(" %[^\n]", faqs[*faqCount].answer);    // %[^\n] to read the entire line including spaces

    (*faqCount)++;
    printf("FAQ entry added successfully!\n");
}

// Function to view all FAQs
void viewFAQs(struct FAQ faqs[], int faqCount) {
    if (faqCount == 0) {
        printf("No FAQs available.\n");
        return;
    }

    printf("FAQs:\n");
    for (int i = 0; i < faqCount; i++) {
        printf("Q: %s\n", faqs[i].question);
        printf("A: %s\n", faqs[i].answer);
        printf("\n");
    }
}

void viewPassengers(struct Passenger passengers[], int passengerCount) {
    if (passengerCount == 0) {
        printf("There are no passengers yet.\n");
        return;
    }
    char routeChoice;
    printf("Enter Route ID to check for passengers: ");
    scanf("%s", &routeChoice);

    printf("\n=== Passengers ===\n");
    for (int i = 0; i < passengerCount; i++) {
        if(strcmp(passengers[i].routeBooked, &routeChoice) == 0){
          printf("First Name: %s, Last Name: %s, Phone Number: %s\n", passengers[i].firstName, passengers[i].lastName, passengers[i].phoneNumber);
        }
    }
}

void displayOperatorMenu() {

    int operatorChoice;

    do {
        printf("\n=== Operator Menu ===\n");
        printf("1. Add Bus Route\n");
        printf("2. Add Bus Schedule\n");
        printf("3. Modify FAQ\n");
        printf("4. View passengers\n");
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
            case 3:
                addFAQ(faqs, &faqCount);
                break;
          case 4:
                viewPassengers(passengers, passengerCount);
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
    printf("Enter available seats: ");
    scanf("%d", &routes[routeCount].availableSeats);
    printf("Enter Fare: ");
    scanf("%f", &routes[routeCount].fare);

    routeCount++;
    printf("Bus Route Added Successfully!\n");
}

void cancelReservation(){
    char lastName[50];
    char firstName[50];
    char cancelChoice;
  
    printf("Please enter your last name: ");
    scanf("%s", lastName);
    printf("Please enter your first name: ");
    scanf("%s", firstName);

    for (int i = 0; i < passengerCount; i++) {
        if(strcmp(passengers[i].lastName, lastName) == 0 && strcmp(passengers[i].firstName, firstName) == 0){
          printf("You have a reservation for route: %s\n", passengers[i].routeBooked);
          printf("Do you want to cancel your reservation? (y/n): ");
          scanf("%s", &cancelChoice);
          if(strcmp(&cancelChoice, "y")==0){
            for (int j = 0; j < routeCount; j++) {
              if(strcmp(routes[j].routeID, passengers[i].routeBooked)==0){
                routes[j].availableSeats++;
              }
            }
            strcpy(passengers[i].firstName, "");
            strcpy(passengers[i].lastName, "");
            strcpy(passengers[i].phoneNumber, "");
            strcpy(passengers[i].routeBooked, "");
            printf("Cancellation successful! See you another time!");
          }
        }
    }
    
}

void addBusSchedule() {
    // Implement functionality to add a new bus schedule to the system
    printf("\nEnter Location: ");
    scanf("%s", schedules[scheduleCount].busLocation);
    printf("Enter Route ID: ");
    scanf("%s", schedules[scheduleCount].routeID);
    printf("Enter Departure Time: ");
    scanf("%s", schedules[scheduleCount].departureTime);

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
        printf("4. Cancel Reservation\n");
        printf("5. View FAQ\n");
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
            case 4:
                cancelReservation();
                break;
            case 5:
                viewFAQs(faqs, faqCount);   
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
        printf("Route ID: %s, Origin: %s, Destination: %s, Available Seats: %d, Fare: $%.2f\n", routes[i].routeID, routes[i].origin, routes[i].destination, routes[i].availableSeats, routes[i].fare);
    }
}

void viewSchedules() {
    // Implement functionality to display available bus schedules
    char routeChoice;
    printf("Enter Route ID: ");
    scanf("%s", &routeChoice);
    
    printf("\n=== Bus Schedule ===\n");
    for (int i = 0; i < scheduleCount; i++) {
        if(strcmp(schedules[i].routeID, &routeChoice) == 0){
          printf("Route ID: %s, Location: %s, Departure Time: %s\n", schedules[i].routeID, schedules[i].busLocation, schedules[i].departureTime);
        }
    }
}


void makeReservation(float fare) {
    // Implement functionality for passenger reservation, including payment processing
    char routeChoice;
    char reserveChoice;
  
    printf("Which route would you like to make a reservation for? ");
    scanf("%s", &routeChoice);
  
    for (int i = 0; i < scheduleCount; i++) {
      if(strcmp(routes[i].routeID, &routeChoice) == 0 && routes[i].availableSeats > 0){
        printf("Great news, seats are available!\n");
        printf("The price for this route is: $%.2f\n", routes[i].fare);
        printf("Confirm reservation? [y/n] ");
        scanf("%s", &reserveChoice);
        if(reserveChoice == 'y'){
          printf("Enter your first Name: ");
          scanf("%s", passengers[passengerCount].firstName);
          printf("Enter your last Name: ");
          scanf("%s", passengers[passengerCount].lastName);
          printf("Enter your phone number: ");
          scanf("%s", passengers[passengerCount].phoneNumber);
          printf("Reservation confirmed!\n");
          strcpy(passengers[passengerCount].routeBooked, routes[i].routeID);
          routes[i].availableSeats--;
          passengerCount++;
        }
        break;
      }
      else if(strcmp(routes[i].routeID, &routeChoice) == 0 && routes[i].availableSeats <= 0){
        printf("Sorry, no more seats available! Check back soon!");
      }
    }
    
}

int main() {

    int userType;
    char passwordChoice[10];
    
    //Geerate Routes for user to view
    strcpy(routes[routeCount].routeID, "1");
    strcpy(routes[routeCount].origin, "Lafayette");
    strcpy(routes[routeCount].destination, "Chicago");
    routes[routeCount].availableSeats = 50;
    routes[routeCount].fare = 35.50;
    routeCount++;
    strcpy(routes[routeCount].routeID, "2");
    strcpy(routes[routeCount].origin, "Lafayette");
    strcpy(routes[routeCount].destination, "Indianapolis");
    routes[routeCount].availableSeats = 70;
    routes[routeCount].fare = 24.75;
    routeCount++;
    strcpy(routes[routeCount].routeID, "3");
    strcpy(routes[routeCount].origin, "Chicago");
    strcpy(routes[routeCount].destination, "Lafayette");
    routes[routeCount].availableSeats = 50;
    routes[routeCount].fare = 35.50;
    routeCount++;
    strcpy(routes[routeCount].routeID, "4");
    strcpy(routes[routeCount].origin, "Chicago");
    strcpy(routes[routeCount].destination, "Indianapolis");
    routes[routeCount].availableSeats = 70;
    routes[routeCount].fare = 24.75;
    routeCount++;

    //Generate schedules for route
    strcpy(schedules[scheduleCount].routeID, "1");
    strcpy(schedules[scheduleCount].busLocation, "CoRec");
    strcpy(schedules[scheduleCount].departureTime, "8:30");
    scheduleCount++;
    strcpy(schedules[scheduleCount].routeID, "1");
    strcpy(schedules[scheduleCount].busLocation, "PMU");
    strcpy(schedules[scheduleCount].departureTime, "8:45");
    scheduleCount++;
    strcpy(schedules[scheduleCount].routeID, "1");
    strcpy(schedules[scheduleCount].busLocation, "Krach");
    strcpy(schedules[scheduleCount].departureTime, "8:55");
    scheduleCount++;
    strcpy(schedules[scheduleCount].routeID, "1");
    strcpy(schedules[scheduleCount].busLocation, "O'Hare");
    strcpy(schedules[scheduleCount].departureTime, "12:30");
    scheduleCount++;
    strcpy(schedules[scheduleCount].routeID, "2");
    strcpy(schedules[scheduleCount].busLocation, "CoRec");
    strcpy(schedules[scheduleCount].departureTime, "8:30");
    scheduleCount++;
    strcpy(schedules[scheduleCount].routeID, "2");
    strcpy(schedules[scheduleCount].busLocation, "PMU");
    strcpy(schedules[scheduleCount].departureTime, "8:45");
    scheduleCount++;
    strcpy(schedules[scheduleCount].routeID, "2");
    strcpy(schedules[scheduleCount].busLocation, "Krach");
    strcpy(schedules[scheduleCount].departureTime, "8:55");
    scheduleCount++;
    strcpy(schedules[scheduleCount].routeID, "2");
    strcpy(schedules[scheduleCount].busLocation, "Indy Airport");
    strcpy(schedules[scheduleCount].departureTime, "10:30");
    scheduleCount++;

    //Add FAQs
    strcpy(faqs[faqCount].question, "Who owns this company?");
    strcpy(faqs[faqCount].answer, "This company is owned by CNIT 315 students.");
    faqCount++;
    
    do {
        printf("\nChoose User Type:\n");
        printf("1. Operator\n");
        printf("2. Passenger\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &userType);

        switch (userType) {
            case 1:
                printf("Enter operator password: ");
                scanf("%s", passwordChoice);
                if(strcmp(passwordChoice, "cookies")==0){
                  system("clear");
                  displayOperatorMenu();
                }
                else{
                  printf("That is incorrect.\n");
                }
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