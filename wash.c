/*
Group Members: Cavin Warren
ID#: 1908573
Date: February 22, 2023
Description: Function Definitions for Programming 2 Project
*/

#include "wash.h"

// Lookup table used for costs of services
const float service_costs[] = {
    0.0,
    2500.0,
    2000.0,
    3500.0,
    5500.0,
    3200.0,
    7500.0
};

// Lookup table used for payment methods
const char payment_method[3][5] = {
    "",
    "CASH",
    "CARD"
};

FILE *fp;

Bay bays[WASH_BAY_CAPACITY] = {VACANT, VACANT, VACANT};

/* Checks if car wash if at max capacity and updates status when necessary. */
void capacity_check(Status *status, int cust_num){
    if (cust_num >= TOTAL_VEHICLE_CAPACITY)
    {
        *status = FULL;
    }
    else
    {
        *status = NOT_FULL;
    }
}

/* Collects customer's information, creates struct with information. */
Customer record_information(void){
    bool check;
    fflush(stdin);

    Customer c;
    memset(c.name, 0, MAX_NAME_LENGTH);

    printf("\nEnter name of customer: ");
    fgets(c.name, MAX_NAME_LENGTH, stdin);
    remove_newline(c.name);

    printf("\n");

    do
    {
        fflush(stdin);
        printf("Enter customer's license plate number: ");
        scanf("%s", c.plate_num);

        check = license_check(c.plate_num);

        if (check == false)
        {
            printf("\nInvalid license plate number. Try again.\n");
            printf("License plate number should have 4 digits followed by 2 capital letters.\n\n");
        }
    } while (check == false);
    
    do
    {
        printf(
            "\n1.\t CASH\n"
            "2.\t CARD\n"
            "\nSelect customer's payment method: ");
        scanf("%d", &c.pay_method);

        if (c.pay_method != 1 && c.pay_method != 2)
        {
            printf("\nYou have entered an invalid choice. Try again.\n");
        }
    } while (c.pay_method != 1 && c.pay_method != 2);    

    return c;
}

/* Checks if license plate entered is valid. */
bool license_check(char license[]){
    bool valid_license = true;

    // Checks if length is not 6 characters. 
    if (strlen(license) != 6)
    {
        valid_license = false;
        return valid_license;
    }

    // Checks if first 4 characters are digits. 
    for (int i = 0; i < 4; i++)
    {
        if (isdigit(license[i]) == 0)
        {
            valid_license = false;
            return valid_license;
        }
    }

    // Checks if last 2 characters are capital. 
    for (int i = 4; i < 6; i++)
    {
        if (isupper(license[i]) == 0)
        {
            valid_license = false;
            return valid_license;
        }
    }

    return valid_license;
}

/* Uses lookup table to obtain the cost of the service chosen, adds cost of service to a total cost. */
void calculate_service_cost(int c, float *total){
    float service_cost = service_costs[c];

    *total += service_cost;
}

/* Determines fee for using a card. */
float card_fee(float total){
    
    return CARD_PERCENTAGE * total;
}

/* Determines amount to be tipped. */
float tip(float total){
    
    return TIP_PERCENTAGE * total;
}

/* Generates random integer. */
int random_response(void){
    srand(time(0)); // Seeds rand() using computer's clock

    return rand() % 2;
}

/* Determines total amount with tip and card fee included. */
float calculate_total_cost(float tsc, float tip, float card){

    return tsc + tip + card;
}

/* Prints out receipt. */
void print_receipt(Customer cus, float tsc, float tip, float card, float tot, struct tm d){
    printf("\n\t\t\t    RECEIPT");
    
    printf("\n+-%-30s%-30s-+\n", "------------------------------", "------------------------------");
    printf("| %-30s%-30s |\n", "Name", cus.name);
    printf("| %-30s%02d-%02d-%d%-20s |\n", "Date visited", d.tm_mday, (d.tm_mon + 1), (d.tm_year + 1900), "");
    printf("| %-30s%-30s |\n", "License Plate #", cus.plate_num);
    printf("| %-30s%-30s |\n", "Method of Payment", payment_method[cus.pay_method]);
    printf("|-%-30s%-30s-|\n", "------------------------------", "------------------------------");
    printf("| %-30s%-30.2f |\n", "Total Service Cost ($)", tsc);
    printf("| %-30s%-30.2f |\n", "Tip Percentage", TIP_PERCENTAGE);
    printf("| %-30s%-30.2f |\n", "Tip Amount ($)", tip);
    printf("| %-30s%-30.2f |\n", "Card Fee ($)", card);
    printf("|-%-30s%-30s-|\n", "------------------------------", "------------------------------");
    printf("| %-30s%-30.2f |\n", "Total ($)", tot);
    printf("+-%-30s%-30s-+\n\n", "------------------------------", "------------------------------");
}

/* Checks if wash bay if at max capacity and updates status when necessary. */
void bay_check(Status *status, int bay_num){
    if (bay_num >= WASH_BAY_CAPACITY)
    {
        *status = FULL;
    }
    else
    {
        *status = NOT_FULL;
    }
}

/* Displays status of each wash bay. */
void show_bay_status(void){
    printf("+-%4s--+-%-10s-+\n", "----", "----------");
    for (int i = 0; i < WASH_BAY_CAPACITY; i++)
    {
        if (bays[i] == VACANT)
        {
            printf("| %3s %1d | %-10s |\n", "Bay", (i + 1), "VACANT");
            printf("+-%4s--+-%-10s-+\n", "----", "----------");
        }
        else
        {
            printf("| %3s %1d | %-10s |\n", "Bay", (i + 1), "OCCUPIED");
            printf("+-%4s--+-%-10s-+\n", "----", "----------");
        }
    }
}

/* Validates choice of bay. */
int bay_choice_check(void){
    int b_choice;

    fflush(stdin);
    printf("\nEnter bay number: ");
    scanf("%d", &b_choice);

    if (b_choice < 1 || b_choice > WASH_BAY_CAPACITY)
    {
        printf("\nNot a valid bay number. Try again.\n");
        return -1;
    }

    return b_choice;
}

/* Adds car to bay of choice, updates status of bay chosen. */
int add_car(void){
    int b_choice;

    do
    {
        do
        {
            b_choice = bay_choice_check();
        } while (b_choice == -1);  

        if (bays[b_choice - 1] != VACANT)
        {
            printf("\nThat bay is not vacant. Try again.\n");
        }  
    } while (bays[b_choice - 1] != VACANT);

    bays[b_choice - 1] = OCCUPIED;

    return b_choice;
}

/* Removes car from bay of choice, updates status of bay chosen. */
int remove_car(void){
    int b_choice;

    do
    {
        do
        {
            b_choice = bay_choice_check();
        } while (b_choice == -1);  

        if (bays[b_choice - 1] != OCCUPIED)
        {
            printf("\nThat bay is not occupied. Try again.\n");
        }  
    } while (bays[b_choice - 1] != OCCUPIED);

    bays[b_choice - 1] = VACANT;

    return b_choice;
}

/* Searches file for repeat customers, determines how many time they use the car wash 
and the total they spend. */
void find_repeat_customers(void){
    int i = 0; // Used for general indexing and file line number 
    int j = 0; // Used for looping through array from the start 
    int k = 0; // Used to correctly position unique names
    bool dupe_flag;

    char buffer[MAX_NAME_LENGTH]; // Used to store each line read from file
    char current_name[MAX_NAME_LENGTH];

    // Parallel arrays used to store necessary information
    char names[MAX_ARRAY_SIZE][MAX_NAME_LENGTH];
    int counts[MAX_ARRAY_SIZE] = {0};
    float amounts[MAX_ARRAY_SIZE] = {0.0};

    memset(buffer, 0, MAX_NAME_LENGTH);
    memset(current_name, 0, MAX_NAME_LENGTH);

    for (i = 0; i < MAX_ARRAY_SIZE; i++)
    {
        memset(names[i], 0, MAX_NAME_LENGTH);
    }

    i = 0;

    // Reads each line from file until end of file
    while (fgets(buffer, MAX_NAME_LENGTH, fp) != NULL)
    {
        remove_newline(buffer);

        if (i % 5 == 0)
        {
            dupe_flag = false;

            for (j = 0; j < k; j++)
            {
                if (strcmp(names[j], buffer) == 0) // Checks if name is already in array
                {
                    counts[j]++; // Updates counter for name
                    dupe_flag = true;
                    break;
                }
            }

            // Adds new name to list and initialize values
            // Increments k as it is used to index unique names
            if (dupe_flag == false)
            {
                strcpy(names[k], buffer);
                counts[k] = 1;
                amounts[k] = 0.0;
                k++;
            }

            strcpy(current_name, buffer); // Stores most recent name
        }
        else if (i % 5 == 3)
        {
            for (j = 0; j < k; j++)
            {
                if (strcmp(names[j], current_name) == 0) // Checks if name is most recent 
                {
                    amounts[j] += atof(buffer); // Add amount to array index matching name
                    break;
                }
            }
        }

        memset(buffer, 0, MAX_NAME_LENGTH);
        i++; // Move to next line
    }

    // Displays customers that appear more than once as well as relevant information
    printf("+-%-30s+-%-20s+%20s-+\n", "------------------------------", "--------------------", "--------------------");
    printf("| %-30s| %-20s|%20s |\n", "NAME", "TIMES VISITED", "AMOUNT SPENT ($)");
    printf("+-%-30s+-%-20s+%20s-+\n", "------------------------------", "--------------------", "--------------------");
    for (i = 0; i < k; i++)
    {
        if (counts[i] > 1)
        {
            printf("| %-30s| %-20d|%20.2f |\n", names[i], counts[i], amounts[i]);
        }
    }
    printf("+-%-30s+-%-20s+%20s-+\n", "------------------------------", "--------------------", "--------------------");

    int f_index = most_frequent(counts, k); // Index of most frequent customer

    printf("\n\t  Most Frequent Returning Customer");
    printf("\n+-%-30s+%20s-+\n", "------------------------------", "--------------------");
    printf("| %-30s|%20d |\n", names[f_index], counts[f_index]);
    printf("+-%-30s+%20s-+\n", "------------------------------", "--------------------");
}

/* Finds position of highest number in array. */
int most_frequent(int cnt_arr[], int size){
    int largest = cnt_arr[0];
    int j = 0;

    for (int i = 1; i < size; i++)
    {
        if (cnt_arr[i] > largest)
        {
            j = i;
            largest = cnt_arr[i];
        }     
    }

    return j;
}

/* Finds cost of service selected. */
float service_cost_adder(int c){
    float cost = 0;
    switch (c)
    {
        case 1:
            cost = service_costs[c];
            break;
        case 2:
            cost = service_costs[c];
            break;
        case 3:
            cost = service_costs[c];
            break;
        case 4:
            cost = service_costs[c];
            break;
        case 5:
            cost = service_costs[c];
            break;
        case 6:
            cost = service_costs[c];
    }

    return cost;
}

/* Increments overall number of customers. */
void calculate_cust_total(int *ctotal){
    (*ctotal)++;
}

/* Displays sales report. */
void display_sales(float totals[], int *ctotal, float *gtotal, float *ttotal, struct tm d){
    printf("\n\t       Sales Report for %02d-%02d-%d", d.tm_mday, (d.tm_mon + 1), (d.tm_year + 1900));
    
    printf("\n+-%-35s+%20s-+\n", "-----------------------------------", "--------------------");
    printf("| %-35s|%20s |\n", "SERVICE", "TOTAL ($)");
    printf("+-%-35s+%20s-+\n", "-----------------------------------", "--------------------");
    printf("| %-35s|%20.2f |\n", "Wash and Vacuum", totals[0]);
    printf("| %-35s|%20.2f |\n", "Engine Wash", totals[1]);
    printf("| %-35s|%20.2f |\n", "Polishing", totals[2]);
    printf("| %-35s|%20.2f |\n", "Buffing", totals[3]);
    printf("| %-35s|%20.2f |\n", "Roof Cleaning", totals[4]);
    printf("| %-35s|%20.2f |\n", "Detailing/Interior Shampooing", totals[5]);
    printf("+-%-35s+%20s-+\n", "-----------------------------------", "--------------------");

    printf("\n+-%-35s+%20s-+\n", "-----------------------------------", "--------------------");
    printf("| %-35s|%20d |\n", "Total # of Customers", *ctotal);
    printf("| %-35s|%20.2f |\n", "Grand Total ($)", *gtotal);
    printf("| %-35s|%20.2f |\n", "Tips Total ($)", *ttotal);
    printf("+-%-35s+%20s-+\n\n", "-----------------------------------", "--------------------");
}

/* Removes the newline character generated at the end of a string read by fgets. */
char *remove_newline(char string[]){
    string[strlen(string) - 1] = '\0';

    return string;
}