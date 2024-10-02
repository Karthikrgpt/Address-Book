#ifndef CONTACT_H
#define CONTACT_H

#define _GNU_SOURCE // for strcasestr function

#define MAX_CONTACTS 100

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;

FILE *file; // declareing file

//all globle variable
static short i = 0, j = 0, count = 0, array_index = -1;
static bool flag = 0;
static short arr[MAX_CONTACTS] = {0};
static char name[50] = "\0", phone[20] = "\0", email[50] = "\0", opt, Sl_No, option;

//function prototype
void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void saveContact(AddressBook *addressBook);
void exitContact(AddressBook *addressBook);
void initialize(AddressBook *addressBook);

//function prototype used in supportive file for multiple calls
void printline();
void print_title();
void printheader(AddressBook *addressBook);
void continue_key();
void find_index(AddressBook *addressBook);
void printcontact(AddressBook *addressBook, int short i);

void validate_name(AddressBook *addressBook, char *name);
void validate_phone(AddressBook *addressBook, char *phone);
void validate_email(AddressBook *addressBook, char *email);

void validate_search_name(AddressBook *addressBook, char *name);
void validate_search_phone(AddressBook *addressBook, char *phone);
void validate_search_email(AddressBook *addressBook, char *email);

void print_name(AddressBook *addressBook, char *name);
void print_phone(AddressBook *addressBook, char *phone);
void print_email(AddressBook *addressBook, char *email);

void edit_name( AddressBook *addressBook );
void edit_phone( AddressBook *addressBook );
void edit_email( AddressBook *addressBook );

void delete_list( AddressBook *addressBook );

#endif
