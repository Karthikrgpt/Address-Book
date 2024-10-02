#include "contact.h" // including the contact.h where all globle variable are defined and functions are declared

void validate_name(AddressBook *addressBook, char *name) {
    for ( i = 0; name[i]; i++ ) // checking for uppercase, lowercase, space, and newline
        if ( !isupper( name[i] ) && !islower( name[i] ) && !isspace( name[i] ) && name[i] != '\n' ) {
            name[0] = '\0';
            return;
        }
    
    for (i = 0; i < addressBook->contactCount; i++) {
        if (strcasecmp(addressBook->contacts[i].name, name) == 0) { // checking for name exist in contact 
            name[0] = '\0';
            return;  
        }
    }
}

void validate_phone(AddressBook *addressBook, char *phone) {
    for ( i = 0; phone[i]; i++ ) {
        if ( !isdigit( phone[i] ) ) { //checking only for digit
            phone[0] = '\0';
            return;
        }
    }

    if ( ( i != 10 ) ) { //checking for  digit
        phone[0] = '\0';
        return;
    }

    for ( i = 0; i < addressBook->contactCount; i++ )
        if ( strstr( addressBook->contacts[i].phone, phone ) != NULL ) { // checking for phopne exist in contact 
            phone[0] = '\0';
            return;
        }
}

void validate_email(AddressBook *addressBook, char *email) {
    char *at_pos = strchr(email, '@');
    char *dot_com_pos = strstr(email, ".com");

    // checking for @, .com and @ at first and .com next
    if (at_pos == NULL || dot_com_pos == NULL || (dot_com_pos - at_pos <= 1)) {
        email[0] = '\0';
        return;
    }

    char com[] = ".com";
    for ( i = 0; i < 4; i++ ) // check .com is present at the end or not
        if ( email[strlen(email) - 4 + i] != com[i] ) {
            email[0] = '\0';
            return;
    }
    for ( i = 0; i < at_pos - email; i++) {
        if (!(isalnum(email[i]) || email[i] == '.' ) ) { // checkes only a-z, A-Z, 0-9 and . is till @ encounters
            email[0] = '\0';
            return;
        }
    }

    for (char *ptr = at_pos + 1; ptr < dot_com_pos; ptr++) {
        if (!isalpha(*ptr)) { // checkes only a-z, A-Z bitween till @ encounters
            email[0] = '\0';
            return;
        }
    }

    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcasestr(addressBook->contacts[i].email, email) != NULL) { // checking for name exist in contact 
            email[0] = '\0'; 
            return;
        }
    }
}

void print_name(AddressBook *addressBook, char *name) {
    flag = 0;
    for ( j = 0; j < addressBook->contactCount; j++ ) {
        if (strcasestr(addressBook->contacts[j].name, name) != NULL ) { // cheking for search character is present or not
            if ( !flag ) {
                printf("\nHere the search result for \"\033[0;32m%s\033[0m\"\n\n", name );
                printheader(addressBook);
                flag = 1;
            }
            printcontact(addressBook, j); //printing the contact
        }
    }

    if ( flag )
        printline();
    else printf("\n\033[0;31mSuch name does not exist!\033[0m\n");
}

void print_phone(AddressBook *addressBook, char *phone) {
    flag = 0;
    for ( j = 0; j < addressBook->contactCount; j++ ) {
    if (strstr(addressBook->contacts[j].phone, phone) != NULL ) { // cheking for search character is present or not
            if ( !flag ) {
                printf("\nHere the search result for \"\033[0;32m%s\033[0m\"\n\n", phone );
                printheader(addressBook);
                flag = 1;
            }
            printcontact(addressBook, j); //printing the conatct
        }
    }

    if ( flag )
        printline();
    else printf("\n\033[0;31mSuch phone number does not exist!\033[0m\n");
}

void print_email(AddressBook *addressBook, char *email) {
    flag = 0;
    for (int j = 0; j < addressBook->contactCount; j++) {
    if (strcasestr(addressBook->contacts[j].email, email ) != NULL ) { // cheking for search character is present or not
            if ( !flag ) {
                printf("\nHere the search result for \"\033[0;32m%s\033[0m\"\n\n", email );
                printheader(addressBook);
                flag = 1;
            }
            printcontact(addressBook, j); //printing the contact
        }
    }

    if ( flag )
        printline();
    else printf("\n\033[0;31mSuch email id does not exist!\033[0m\n");
}

void edit_name( AddressBook *addressBook ) {
    if ( flag ) {
        printf("Enter the serial number : ");
        scanf(" %hd", &i );
        find_index(addressBook); // checking serial number enterd is present or not
        if ( flag ) {
            while ( name[0] == '\0' ) {
                print_title();
                printf("\033[1;37m#######  Edit Contact:\033[0m\n\n");
                printf("Enter a Valid Name: ");
                scanf(" %[^\n]", name );
                validate_name( addressBook, name );//validate the enterd name
                if ( name[0] == '\0' ) {
                    printf("\nPlease enter \033[0;31mvalid\033[0m name!\n");
                    continue_key();
                }
            }
            print_title();
            printf("\033[1;37m#######  Edit Contact:\033[0m\n\nName of \"\033[0;31m%s\033[0m\" is updated as \"\033[0;32m%s\033[0m\"\n\n", addressBook->contacts[array_index].name, name );
            strcpy( addressBook->contacts[array_index].name , name ); // copy the enter data
            name[0] = '\0';
        } else printf("\n\033[0;31mInvalid serial number\033[0m\n");
        continue_key();
    } else continue_key();
}

void edit_phone( AddressBook *addressBook ) {
    if ( flag ) {
        printf("Enter the serial number : ");
        scanf(" %hd", &i );
        find_index(addressBook);// checking serial number enterd is present or not
        if ( flag ) {
            while ( phone[0] == '\0' ) {
                print_title();
                printf("\033[1;37m#######  Edit Contact:\033[0m\n\n");
                printf("Enter a Valid Phone number: ");
                scanf(" %s", phone );
                validate_phone( addressBook, phone );//validate the enterd phone
                if ( phone[0] == '\0' ) {
                    printf("\nPlease enter \033[0;31mvalid\033[0m Phone number!\n");
                    continue_key();
                }
            }
            strcpy( addressBook->contacts[array_index].phone , phone );// copy the enter data
            print_title();
            printf("\033[1;37m#######  Edit Contact:\033[0m\n\nPhone number of \"\033[0;31m%s\033[0m\" is updated as \"\033[0;32m%s\033[0m\"\n\n", addressBook->contacts[array_index].name, phone );
            phone[0] = '\0';
        } else printf("\n\033[0;31mInvalid serial number\033[0m\n");
        continue_key();
    } else continue_key();
}

void edit_email( AddressBook *addressBook ) {
        if ( flag ) {
        printf("Enter the serial number : ");
        scanf(" %hd", &i );
        find_index(addressBook);// checking serial number enterd is present or not
        if ( flag ) {
            while ( email[0] == '\0' ) {
                print_title();
                printf("\033[1;37m#######  Edit Contact:\033[0m\n\n");
                printf("Enter a Valid Email Id: ");
                scanf(" %s", email );
                validate_email( addressBook, email );//validate the enterd email
                if ( email[0] == '\0' ) {
                    printf("\nPlease enter \033[0;31mvalid\033[0m Email Id!\n");
                    continue_key();
                }
            }
            strcpy( addressBook->contacts[array_index].email , email );// copy the enter data
            print_title();
            printf("\033[1;37m#######  Edit Contact:\033[0m\n\nEmail Id of \"\033[0;31m%s\033[0m\" is updated as \"\033[0;32m%s\033[0m\"\n\n", addressBook->contacts[array_index].name, email );
            email[0] = '\0';
        } else printf("\n\033[0;31mInvalid serial number\033[0m\n");
        continue_key();
    } else continue_key();
}

void delete_list( AddressBook *addressBook ) {
    if ( flag ) {
        printf("Enter the serial number : ");
        scanf(" %hd", &i );
        find_index(addressBook);// checking serial number enterd is present or not
        if ( flag ) {
            strcpy( name , addressBook->contacts[array_index].name );
            addressBook->contactCount--;//decrement the contact count
            for ( i = array_index; i < addressBook->contactCount; i++ ) { //over write by next index data
                addressBook->contacts[i] = addressBook->contacts[i+1];
            }
            print_title();
            printf("\033[1;37m#######  delete Contact:\033[0m\n\nContact of \"\033[0;31m%s\033[0m\" is deleted\n\n",name );
        } else printf("\n\033[0;31mInvalid serial number\033[0m\n");
        continue_key();
    } else continue_key();
}

void print_title() {
    system("clear"); //clear the stdout window
    printf("\033[1;37m#######  Address Book  #######\033[0m\n" );
}

void printline() {
    printf("\033[0;30m"); 
    for ( i = 0; i < 104; i++ )
        printf("=");//print = for 104 times
    printf("\033[0m\n");
}

void printheader(AddressBook *addressBook) {
    printline();
    Sl_No = 1;
    printf("\033[1;30m"); 
    //print the header
    printf("%-2s%-5s%-2s%-30s%-2s%-30s%-2s%-30s%-2s\n", ":","S.No ", ":", "Name", ":", "Phone No", ":", "Email Id", ":");
    printline();
    for ( array_index = 0; array_index < addressBook->contactCount; array_index++ )
        arr[array_index] = 0;
}

void printcontact(AddressBook *addressBook, short i ) {
    //print the data stored in address book
    printf("%-2s%-5d%-2s%-30s%-2s%-30s%-2s%-30s%-2s\n", "\033[1;30m: \033[0m", Sl_No++, "\033[1;30m: \033[0m", addressBook->contacts[i].name, "\033[1;30m: \033[0m", addressBook->contacts[i].phone, "\033[1;30m: \033[0m", addressBook->contacts[i].email, "\033[1;30m: \033[0m");
    arr[i] = 1;
}

void continue_key() {

    //waits till user press enter
    printf("\n\033[0;34mPress \"Enter\" key to continue\033[0m");
    getchar();
    getchar();
}

void find_index(AddressBook *addressBook) {
    flag = 0;
    count = 0;
    for ( array_index = 0; array_index < addressBook->contactCount; array_index++ ) {
        if ( arr[array_index] == 1 ) // verify the serail number
            count++; 
        if ( i == count ) {
            flag = 1; //crate flag if serial number exist
            break;
        }
    }
}