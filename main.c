#include "contact.h" // including the contact.h where all globle variable are defined and functions are declared

int main() {
    
    AddressBook addressbook_var;
    initialize( &addressbook_var ); //initializing addressbook by storing data from local database

    do {
        print_title(); // printing title
        printf("\033[1;37m#######  Features:\033[0m\n\n0. Exit\n1. Add Contact\n2. Search Contact\n3. Edit Contact\n4. Delete Contact\n5. List Contact\n6. Save Contact\n\nPlease select an option: ");
        scanf(" %c", &option ); // selecting user selected option

        switch ( option ) { //based upon the option, it will call the function
            case '0':
                print_title();
                printf("\033[1;37m#######  Exit Contact\033[0m\n");
                exitContact( &addressbook_var );
                exit(0);
            case '1':
                print_title();
                createContact( &addressbook_var );
                break;
            case '2':
                print_title();
                searchContact( &addressbook_var );
                break;
            case '3':
                print_title();
                editContact( &addressbook_var );
                break;
            case '4':
                print_title();
                deleteContact( &addressbook_var );
                break;
            case '5':
                print_title();
                listContacts( &addressbook_var ); 
                break;
            case '6':
                print_title();
                printf("\033[1;37m#######  Save Contact\033[0m\n");
                saveContact( &addressbook_var );
                continue_key();
                break;
            default:
                printf("\n\033[0;31mInvalid Option!\033[0\n");
                continue_key();
            }
    } while ( 1 );
}