#include "contact.h" // including the contact.h where all globle variable are defined and functions are declared

//extern Contact dummyContacts[10];

void listContacts(AddressBook *addressBook)  {

    printf("\033[1;37m#######  List Contact :\033[0m\n\n");

    if ( addressBook->contactCount == 0 ) { //checking the contact are exist in addressbook or not
        printf("\033[0;31mThe Address Book is Empty\033[0m\n");
        continue_key(); // used as delay untill user press enter key
        return;
    }

    printheader(addressBook); //printing header

    for ( j = 0; j < addressBook->contactCount; j++ )
        printcontact( addressBook, j ); // copeing the data to structure
    printline();
    
    continue_key();
}

void initialize(AddressBook *addressBook)  {
    /* 
    //using dummy contact
    addressBook->contactCount = sizeof(dummyContacts) / sizeof(dummyContacts[0]);

    for ( i = 0; i < addressBook->contactCount; i++ )
        addressBook->contacts[i] = dummyContacts[i];
    */
    //using Local data
    char buffer[200]; 
    file = fopen("Local_database.txt", "r");
    if (file == NULL) { //checking file exits or not
        printf("Unable to access contacts file!\n");
        return;
    }

    addressBook->contactCount = 0; 

    while (fgets(buffer, sizeof(buffer), file) != NULL) { // reading line by line and storing the data
        sscanf( buffer, "%[^,],%[^,],%s", addressBook->contacts[addressBook->contactCount].name, addressBook->contacts[addressBook->contactCount].phone, addressBook->contacts[addressBook->contactCount].email );
        addressBook->contactCount++;
    }

    fclose(file);
}

void createContact(AddressBook *addressBook) {
    while ( name[0] == '\0' ) { 
        print_title();
        printf("\033[1;37m#######  Add Contact :\033[0m\n\n");
        printf("Enter the Name : ");
        scanf(" %[^\n]", name );
        validate_name( addressBook, name ); //valideting name
        if ( name[0] == '\0' ) {
            printf("\nPlease enter \033[0;31mvalid\033[0m name!\n");
            continue_key();
        }
    }
    while ( phone[0] == '\0' ) {
        print_title();
        printf("\033[1;37m#######  Add Contact :\033[0m\n\n");
        printf("Enter the Phone No : ");
        scanf(" %s", phone );
        validate_phone( addressBook, phone ); //validating phone number
        if ( phone[0] == '\0' ) {
            printf("\nPlease enter \033[0;31mvalid\033[0m Phone number!\n");
            continue_key();
        }
    }
    while ( email[0] == '\0' ) {
        print_title();
        printf("\033[1;37m#######  Add Contact :\033[0m\n\n");
        printf("Enter the Email ID : ");
        scanf(" %s", email );
        validate_email( addressBook, email ); // validating the phone number
        if ( email[0] == '\0' ) {
            printf("\nPlease enter \033[0;31mvalid\033[0m Email Id!\n");
            continue_key();
        }
    }

    i = addressBook->contactCount++; // incimenting the contact count
    strcpy( addressBook->contacts[i].name , name ); //storing the name
    strcpy( addressBook->contacts[i].phone , phone ); //storing the phone
    strcpy( addressBook->contacts[i].email , email ); //storing the email

    print_title();
    printf("\033[1;37m#######  Add Contact :\n\n\033[0;32mContact Saved as:\033[0m\n");
    printf("\nName      : %s\nPhone No. : %s\nMail id   : %s\n\n", name, phone, email  );
    name[0] = '\0'; // clearing the name for further use 
    phone[0] = '\0'; 
    email[0] = '\0';
    continue_key();
}

void searchContact(AddressBook *addressBook) {
    print_title();
    
    printf("\033[1;37m#######  Search Contact :\033[0m\n");
    printf("\n0. Back\n1. Name\n2. Phone No.\n3. Email Id.\n\nPlease select an option: " );
    scanf(" %c", &opt );

    switch ( opt ) {
        case '0':
            return;
        case '1':
            printf("Enter the Name : ");
            scanf(" %[^\n]", name );
            for ( i = 0; name[i]; i++ ) // validateing name
                if ( !isupper( name[i] ) && !islower( name[i] ) && !isspace( name[i] ) && name[i] != '\n' ) {
                name[0] = '\0';
                printf("\nPlease enter \033[0;31mvalid\033[0m name!\n");
                continue_key();
                return;
            }
            print_title();
            printf("\033[1;37m#######  Search Contact :\033[0m\n");
            print_name( addressBook, name ); //printing name
            continue_key();
            name[0] = '\0';
            return;
        case '2': 
            printf("Enter the Phone No : ");
            scanf(" %s", phone );
            for ( i = 0; phone[i]; i++ ) // validateing phone
                if ( !isdigit( phone[i]) ) {
                    printf("\nPlease enter \033[0;31mvalid\033[0m number!\n");
                    continue_key();
                    return;
                }
            print_title();
            printf("\033[1;37m#######  Search Contact :\033[0m\n");
            print_phone( addressBook, phone ); //printing phone
            continue_key();
            phone[0] = '\0';
            return;
        case '3':
            printf("Enter the Email : ");
            scanf(" %s", email );
            for ( i = 0; email[i]; i++) // validateing email
                if (!(isalnum(email[i]) || email[i] == '.' || email[i] == '@' )) {
                    printf("\nPlease enter \033[0;31mvalid\033[0m email!\n");
                    email[0] = '\0';
                    continue_key();
                    return;
                }
            print_title();
            printf("\033[1;37m#######  Search Contact :\033[0m\n");
            print_email( addressBook, email ); //printing email
            continue_key();
            email[0] = '\0';
            return;
        default:
            printf("\n\033[0;31mInvalid Option!\033[0\n");
            continue_key();
    }
}

void editContact(AddressBook *addressBook)  {
    print_title();
    
    printf("\033[1;37m#######  Edit Contact :\033[0m\n\nSearch conatct to edit :\n");
    printf("\n0. Back\n1. Name\n2. Phone No.\n3. Email Id.\n\nPlease select an option: " );
    scanf(" %c", &opt );

    switch ( opt ) {
        case '0':
            return;
        case '1':
            printf("Enter the Name : ");
            scanf(" %[^\n]", name );
            for ( i = 0; name[i]; i++ ) // validateing name
                if ( !isupper( name[i] ) && !islower( name[i] ) && !isspace( name[i] ) && name[i] != '\n' ) {
                name[0] = '\0';
                printf("\nPlease enter \033[0;31mvalid\033[0m name!\n");
                continue_key();
                return;
            }
            print_title();
            printf("\033[1;37m#######  Edit Contact :\033[0m\n");
            print_name( addressBook, name ); //printing name
            edit_name( addressBook ); //edit name
            name[0] = '\0';
            break;
        case '2':
            printf("Enter the Phone number : ");
            scanf(" %s", phone );
            for ( i = 0; phone[i]; i++ ) // validateing phone
                if ( !isdigit( phone[i]) ) {
                    printf("\nPlease enter \033[0;31mvalid\033[0m number!\n");
                    continue_key();
                    return;
                }
            print_title();
            printf("\033[1;37m#######  Edit Contact :\033[0m\n");
            print_phone( addressBook, phone ); //printing phone
            edit_phone( addressBook ); //edit phone
            phone[0] = '\0';
            break;
        case '3':
            printf("Enter the Email Id : ");
            scanf(" %s", email );
            for ( i = 0; email[i]; i++) { // validateing email
                if (!(isalnum(email[i]) || email[i] == '.' || email[i] == '@')) {
                    printf("\nPlease enter \033[0;31mvalid\033[0m email!\n");
                    email[0] = '\0';
                    continue_key();
                    return;
                }
            }
            print_title();
            printf("\033[1;37m#######  Edit Contact :\033[0m\n");
            print_email( addressBook, email ); //printing email
            edit_email( addressBook ); //edit email
            email[0] = '\0';
            break;
        default:
            printf("\n\033[0;31mInvalid Option!\033[0\n");
            continue_key();
    }        
}

void deleteContact(AddressBook *addressBook) {
    print_title();
    
    printf("\033[1;37m#######  Delete Contact :\033[0m\n\nSearch contact to delete :\n");
    printf("\n0. Back\n1. Name\n2. Phone No.\n3. Email Id.\n\nPlease select an option: " );
    scanf(" %c", &opt );

    switch ( opt ) {
        case '0':
            return;
        case '1':
            printf("Enter the Name : ");
            scanf(" %[^\n]", name );
            for ( i = 0; name[i]; i++ ) // validateing name
                if ( !isupper( name[i] ) && !islower( name[i] ) && !isspace( name[i] ) && name[i] != '\n' ) {
                name[0] = '\0';
                printf("\nPlease enter \033[0;31mvalid\033[0m name!\n");
                continue_key();
                return;
            }
            print_title();
            printf("\033[1;37m#######  Delete Contact :\033[0m\n");
            print_name( addressBook, name ); //printing name
            delete_list( addressBook ); //delete contact
            name[0] = '\0';
            break;
        case '2':
            printf("Enter the Phone number : ");
            scanf(" %s", phone );
            for ( i = 0; phone[i]; i++ ) // validateing phone
                if ( !isdigit( phone[i]) ) {
                    printf("\nPlease enter \033[0;31mvalid\033[0m number!\n");
                    continue_key();
                    return;
                }
            print_title();
            printf("\033[1;37m#######  Delete Contact :\033[0m\n");
            print_phone( addressBook, phone ); //printing phone
            delete_list( addressBook ); //delete contact
            phone[0] = '\0';
            break;
        case '3':
            printf("Enter the Email Id : ");
            scanf(" %s", email );
            for ( i = 0; email[i]; i++) { // validateing email
                if (!(isalnum(email[i]) || email[i] == '.' || email[i] == '@')) {
                    printf("\nPlease enter \033[0;31mvalid\033[0m email!\n");
                    email[0] = '\0';
                    continue_key();
                    return;
                }
            }
            print_title();
            printf("\033[1;37m#######  Delete Contact :\033[0m\n");
            print_email( addressBook, email ); //printing email
            delete_list( addressBook ); //delete contact
            email[0] = '\0';
            break;
        default:
            printf("\n\033[0;31mInvalid Option!\033[0\n");
            continue_key();
    }    
}


void saveContact(AddressBook *addressBook) {
    file = fopen("Local_database.txt", "w"); // delete the stored data
    if (file == NULL) {
        printf("Unable to access contacts file!\n");
        return;
    }
    for ( i = 0; i < addressBook->contactCount; i++ ) // save the updated conatct to data base
        fprintf(file, "%s,%s,%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    fclose(file);

    int progressBarWidth = 25;
    printf("\nSaving conatcts\n");

    for (i = 0; i <= progressBarWidth; i++) {
        printf("[");
        for (int j = 0; j < progressBarWidth; j++) {
            if (j < i) {
                printf("#");
            } else {
                printf(" ");
            }
        }
        printf("]%d%%", (i * 100) / progressBarWidth);
        fflush(stdout);
        usleep(100000);
        printf("\r");
    }
    printf("\n\n\033[0;32mContact Saved Successfully\033[0m\n");
}


void exitContact(AddressBook *addressBook) {
    printf("\n\nDo you want to save the changes [\033[0;32my\033[0m/\033[0;31mn\033[0m] : ");
    scanf(" %c", &option );
    if ( option == 'Y' || option == 'y' ) { // if user enter 'y' then save the data to address book
        print_title();
        printf("\033[1;37m#######  Exit Contact\033[0m\n");
        saveContact( addressBook );
    }
}