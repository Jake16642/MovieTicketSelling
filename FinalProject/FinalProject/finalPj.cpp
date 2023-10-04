/*Andrew F, Andrew J, James, Jake
 CS 131 Final Project*/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <string>
using namespace std;

const char EMPTY = 'O';
const char TAKEN = 'X';
const int ROWS = 15;
const int COLUMNS = 30;
const double PRICE1 = 15.0; // Seats 1-5
const double PRICE2 = 10.0; // Seats 6-10
const double PRICE3 = 5.0; // Seats 11-15
int menu();
void display_Chart();
double purchase_Ticket(int, char[][COLUMNS], int);
double confirm_Order(char[][COLUMNS], int, int, double);
void display_SalesReport(int, double);

int main() {
    int tickets_amnt, tickets_sold;
    double total_sales, subtotal;
    string response;
    char seats[ROWS][COLUMNS];
    for (int rows = 0; rows < ROWS; rows++) {
        for (int columns = 0; columns < COLUMNS; columns++) {
            seats[rows][columns] = EMPTY;
        }
    }
    ifstream newFile("FinancialInfo.txt");
    newFile>>tickets_sold;
    cout<<tickets_sold<<endl;
    newFile>>total_sales;
    cout<<total_sales<<endl;
    
    cout << "******** Welcome to the movie theatre! ******** \n";
    int choice;
    do {
        cout << endl;
        choice = menu();
        
        switch (choice) {
                
            case 1:
                cout << endl;
                display_Chart();
                cout << endl;
                break;
            case 2:
                cout << endl;
                cout << "Ticket Prices: \n";
                cout << "Rows 1-5: $" << PRICE1 << endl;
                cout << "Rows 6-10: $" << PRICE2 << endl;
                cout << "Rows 11-15: $" << PRICE3 << endl;
                break;
                
            case 3:
                cout << endl;
                cout << "How many tickets would you like to purchase: ";
                cin >> tickets_amnt; // Amount of tickets to be purchased
                while(tickets_amnt > 450-tickets_sold){
                    cout << "Not enough seats. Re-enter amount of seats you would like: ";
                    cin >> tickets_amnt;
                }
                tickets_sold += tickets_amnt; // tickets_sold = total number of tickets sold for the theatre
                subtotal = purchase_Ticket(tickets_amnt, seats, ROWS);
                if (subtotal == 0.0) {
                    tickets_sold -= tickets_amnt;
                }
                total_sales += subtotal; // Adds $ amount of tickets bought to total for the theatre
                cout << endl;
                break;
            case 4:
                cout << endl;
                display_SalesReport(tickets_sold, total_sales);
                cout << endl;
                break;
            case 5:
                cout << endl;
                cout << "Thank you, goodbye\n";
                break;
            default:
                cout << "You must enter 1-5. Enter again please!!\n";
                
        }
    } while (choice != 5);
    ofstream inputFile("FinancialInfo.txt");
    inputFile<<tickets_sold<<endl;
    inputFile<<total_sales;
    
    
    system("pause");
    return 0;
}

int menu() {
    int choice;
    cout << "1. Display the seating chart\n";
    cout << "2. View ticket price for each row\n";
    cout << "3. Purchase ticket(s)\n";
    cout << "4. View ticket sales report\n";
    cout << "5. Quit\n";
    cout << "Please enter your choice: ";
    cin >> choice;
    return choice;
}

void display_Chart() {
    ifstream outputFile("SeatAvailability.txt");
    string s;
    cout << "         123456789012345678901234567890" << endl;
    for (int i = 1; i <= 15; i++) {
        outputFile >> s;
        cout << left << setw(4) << "Row " << setw(4) << i << " ";
        cout << s;
        cout << endl;
    }
}

double purchase_Ticket(int amount, char seats[][COLUMNS], int rows) {
    ofstream outputFile;
    int row, column;
    double price, total = 0;
    for (int i = 0; i < amount; i++) {
        cout << "Enter the row number for ticket " << (i + 1) << ": ";
        cin >> row;
        while (row > 15) {
            cout << "Row must be 1-15. Re-enter row number: ";
            cin >> row;
        }
        
        cout << "Enter the column number for ticket " << (i + 1) << ": ";;
        cin >> column;
        while (column > 30) {
            cout << "Column must be 1-30. Re-enter column number: ";
            cin >> column;
        }
        
        while (seats[row][column] == TAKEN) {
            cout << "This seat is not available. Please enter another seat\n";
            cout << "Enter the row number for ticket " << (i + 1) << ": ";
            cin >> row;
            while (row > 15) {
                cout << "Row must be 1-15. Re-enter row number: ";
                cin >> row;
            }
            
            cout << "Enter the column number for ticket " << (i + 1) << ": ";
            cin >> column;
            while (column > 30) {
                cout << "Column must be 1-30. Re-enter column number: ";
                cin >> column;
            }
        }
        
        
        if (row > 0 && row < 5) {
            price = PRICE1;
            total += price;
        }
        
        else if (row > 5 && row < 11) {
            price = PRICE2;
            total += price;
        }
        
        else {
            price = PRICE3;
            total += price;
        }
    }
    
    
    total = confirm_Order(seats, row, column, total);
    return total;
    
    
}

double confirm_Order( char seats[][COLUMNS], int row, int column, double total) {
    string response;
    cout << "Your sub-total is $" << total << ". Would you like to purchase these tickets?\n";
    cout << "Type yes or no: ";
    cin >> response;
    if (response == "Yes" || response == "yes"|| response=="YES") {
        cout << "Thank you for your purchase, enjoy your movie";
        seats[row][column] = TAKEN;
    }
    else if (response == "No" || response == "no"|| response=="NO") {
        cout << "Your order has been cancled. ";
        seats[row][column] = EMPTY;
        total=0.0;
    }
    return total;
}

void display_SalesReport(int tickets_sold, double total_sales) {
    cout << "*****SALES REPORT*****" << endl;
    cout << "Seats sold: " << tickets_sold << endl;
    cout << "Seats still available: " << 450 - tickets_sold << endl;
    cout << "Total sales: $" << total_sales << endl;
}
