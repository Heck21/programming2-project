/*
Group Members: Cavin Warren
ID#: 1908573
Date: February 22, 2023
Description: Main C Code for Programming 2 Project
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "wash.h"

int main(void){
    char selection;
    int customer_num = 0, bay_num = 0, choice, total_customers = 0, bay_choice;
    float grand_total = 0, tip_total = 0;
    float service_totals[6] = {0, 0, 0, 0, 0, 0};
    Status cw_status = NOT_FULL, b_status = NOT_FULL;

    fp = fopen("data.txt", "a+");

    time_t t;
    t = time(0);
    struct tm date = *localtime(&t); // Creates struct with date members

    while (true)
    {   
        do
        {
            fflush(stdin);
            printf(
                "a)\t Accept Customer's Information and Payment\n"
                "b)\t Wash Car\n"
                "c)\t Display Returning Customers\n"
                "d)\t Display Sales Report\n"
                "e)\t Exit Program\n"
                "\n\nSelect any option: ");

            scanf("%1c", &selection);
            selection = tolower(selection);

            if (selection < 'a' || selection > 'e')
            {
                printf("\nYou have entered an invalid choice. Try again.\n\n");
            }
        } while (selection < 'a' || selection > 'e');
        
        if (selection == 'a')
        {
            int choices[] = {0, 1, 2, 3, 4, 5, 6}; // Used for keeping track of choices made
            capacity_check(&cw_status, customer_num);
            printf("\nNumber of spaces occupied: %d\n", customer_num);

            if (cw_status == NOT_FULL)
            {
                customer_num++;
                float total_service_cost = 0, tip_amount = 0, card_amount = 0;
                Customer cust = record_information();

                printf("\n+-%-35s+%20s-+\n", "-----------------------------------", "--------------------");
                printf("| %-35s|%20s |\n", "SERVICE", "COST ($)");
                printf("+-%-35s+%20s-+\n", "-----------------------------------", "--------------------");
                printf("| %-35s|%20.2f |\n", "1. Wash and Vacuum", service_costs[1]);
                printf("| %-35s|%20.2f |\n", "2. Engine Wash", service_costs[2]);
                printf("| %-35s|%20.2f |\n", "3. Polishing", service_costs[3]);
                printf("| %-35s|%20.2f |\n", "4. Buffing", service_costs[4]);
                printf("| %-35s|%20.2f |\n", "5. Roof Cleaning", service_costs[5]);
                printf("| %-35s|%20.2f |\n", "6. Detailing/Interior Shampooing", service_costs[6]);
                printf("+-%-35s+%20s-+\n", "-----------------------------------", "--------------------");

                while (true)
                {
                    fflush(stdin);
                    
                    printf("\nSelect any choices (-1 when done): ");
                    scanf("%d", &choice);
                
                    if (choice < 1 || choice > 6)
                    {
                        if (choice == -1)
                        {
                            break;
                        }
                        
                        printf("\nYou have entered an invalid choice. Try again.\n");
                    }
                    else if (choices[choice] == 0)
                    {
                        printf("\nYou have already selected that service. Try again.\n");
                    }
                    else
                    {
                        choices[choice] = 0;

                        calculate_service_cost(choice, &total_service_cost);

                        float cost_add = service_cost_adder(choice);
                        service_totals[(choice - 1)] += cost_add;
                    }
                }

                grand_total += total_service_cost;

                int response = random_response();

                if (response == 1)
                {
                    printf("\nYou have been randomly chosen to tip.\n");
                    tip_amount = tip(total_service_cost);

                    tip_total += tip_amount;
                }

                if (cust.pay_method == 2)
                {
                    card_amount = card_fee(total_service_cost);

                    grand_total += card_amount;
                }

                float total = calculate_total_cost(total_service_cost, tip_amount, card_amount);
                print_receipt(cust, total_service_cost, tip_amount, card_amount, total, date);

                fseek(fp, 0, SEEK_END); // Goes to the end of the file
                fprintf(fp, "%s\n%s\n%s\n%.2f\n\n", cust.name, cust.plate_num, payment_method[cust.pay_method], total);
                fflush(fp);

                calculate_cust_total(&total_customers);
            }
            else
            {
                printf("Maximum capacity reached. Please try again later.\n\n");
            }
        }
        else if (selection == 'b')
        {
            bay_check(&b_status, bay_num);

            printf("\n\n");
            show_bay_status();
            printf("\n");
            printf("\nNumber of customers: %d\n", customer_num);
            printf("\nNumber of Car(s) in Wash Bay: %d\n", bay_num);

            do
            {
                fflush(stdin);

                printf(
                    "\n1.\t Add car to wash bay\n"
                    "2.\t Remove car from wash bay\n"
                    "3.\t Go back to main menu\n"
                    "\nEnter choice: ");
                
                scanf("%d", &choice);

                if (choice < 1 || choice > 3)
                {
                    printf("\nYou have entered an invalid choice. Try again.\n");
                }  
            } while (choice < 1 || choice > 3);
            
            switch (choice)
            {
                case 1:
                    if (b_status == NOT_FULL && customer_num >= 1)
                    {
                        printf("\nAdding car to wash bay...\n");

                        bay_choice = add_car();

                        printf("\nAdded car to bay #%d\n\n\n", bay_choice);

                        bay_num++;
                        customer_num--;
                    }
                    else
                    {
                        printf("\nThis option cannot be selected at this moment.\n\n");
                    }
                    break;
                case 2:
                    if (bay_num >= 1)
                    {
                        printf("\nRemoving car from wash bay...\n");

                        bay_choice = remove_car();

                        printf("\nRemoved car from bay #%d\n\n\n", bay_choice);

                        bay_num--;
                    }
                    else
                    {
                        printf("\nThis option cannot be selected at this moment.\n\n");
                    }
                    break;
                case 3:
                    printf("\nReturning to main menu...\n\n");
            }
        }
        else if (selection == 'c')
        {
            if (customer_num < 1)
            {
                printf("\nThis option cannot be selected at this moment.\n\n");
            }
            else
            {
                printf("\n");
                rewind(fp); // Goes to the beginning of the file
                find_repeat_customers();
                printf("\n");
            }
        }
        else if (selection == 'd')
        {
            if (customer_num < 1 && bay_num < 1)
            {
                printf("\nThis option cannot be selected at this moment.\n\n");
            }
            else
            {
                display_sales(service_totals, &total_customers, &grand_total, &tip_total, date);
            }
        }
        else
        {
            printf("\nExiting program...\n");
            break;
        }
    }

    fflush(stdin);
    printf("\nPress ENTER key to close program...");
    getchar();

    fclose(fp);

    return 0;
}
