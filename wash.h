/*
Group Members: Cavin Warren
ID#: 1908573
Date: February 22, 2023
Description: Header File for Programming 2 Project
*/

#ifndef WASH_H
#define WASH_H

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


/* Macro definitions */

#define TOTAL_VEHICLE_CAPACITY 20
#define WASH_BAY_CAPACITY 3
#define TIP_PERCENTAGE 0.02
#define CARD_PERCENTAGE 0.03
#define MAX_NAME_LENGTH 50
#define MAX_ARRAY_SIZE 200


/* Enums */

typedef enum Status {NOT_FULL, FULL} Status;
typedef enum Bay {VACANT, OCCUPIED} Bay;


/* Structs */

typedef struct Customer
{
    char name[MAX_NAME_LENGTH];
    char plate_num[7];
    int pay_method;
} Customer;


/* Lookup tables */

extern const float service_costs[];

extern const char payment_method[][5];


/* File pointer */

extern FILE *fp;


/* Enum array */

extern Bay bays[];


/* Function declarations */

void capacity_check(Status *status, int cust_num);

Customer record_information(void);

bool license_check(char license[]);

void calculate_service_cost(int c, float *total);

float card_fee(float total);

float tip(float total);

int random_response(void);

float calculate_total_cost(float tsc, float tip, float card);

void print_receipt(Customer cus, float tsc, float tip, float card, float tot, struct tm d);

void bay_check(Status *status, int bay_num);

void show_bay_status(void);

int bay_choice_check(void);

int add_car(void);

int remove_car(void);

void find_repeat_customers(void);

int most_frequent(int cnt_arr[], int size);

float service_cost_adder(int c);

void calculate_cust_total(int *ctotal);

void display_sales(float totals[], int *ctotal, float *gtotal, float *ttotal, struct tm d);

char *remove_newline(char string[]);

#endif