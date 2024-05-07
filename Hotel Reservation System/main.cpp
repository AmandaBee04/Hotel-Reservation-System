#include<iostream>
#include<iomanip>

#include"classRoom.cpp"
#include"customer.cpp"
#include"get_hotel_room_preferences.cpp"
#include"staff.cpp"
#include"print_receipt_func.cpp"
#include"ui.cpp"


using namespace std;

chrono::system_clock::time_point now = chrono::system_clock::now();
time_t currentTime = chrono::system_clock::to_time_t(now);
tm* localTime = localtime(&currentTime);
int year = localTime->tm_year + 1900;
int month = localTime->tm_mon + 1;
int day = localTime->tm_mday;

void printWelcome();
int availableD(Double room[]);
int availableP(Presidential room[]);
int availableV(Villa room[]);


int main(){
	Customer *head = NULL;
	int choice;
	// Declaring 3 types of rooms, each with 10 space to represent 10 rooms for storing customer.
	Double dRoom[10];
	Presidential pRoom[10];
	Villa vRoom[10];
	// Initialize the Staff members in the system (3 staffs)
	Staff s[3] = {Staff("Madam Ruzanna", 1234, 18, "BOSS", "ilovemadam"), Staff("Abu", 2345, 35, "Manager", "imManager"), Staff("Ahmad", 3456, 25, "Receptionist", "imReceptionist")};

	// Loop to initialize the room number for each room.
	for (int i = 0; i < 10; ++i)
	{
		dRoom[i].setRoomNum(1001 + i);
		pRoom[i].setRoomNum(2001 + i);
		vRoom[i].setRoomNum(3001 + i);
	}
	while(1){
		mainpage();
		do{
			printWelcome();
			cout << "                                                                               Enter choice : ";
			cin >> choice;
			cin.ignore();
			if (choice == 1){
				break;
			}
			else if (choice == 2){
				// To verify if the staff is in the system
				if(verifystaff(s, 3) == 0){
					invalidstaff();
					continue;
				}
				// To delete customer if staff is valid
				delCus(head, &head, dRoom, pRoom, vRoom);
				continue;
			}
			else if (choice == 3){
				// To verify if the staff is in the system
				Customer *c = findCus(head);
				if (c == NULL){
					// If staff not valid it will go back to the start of the loop
					continue;
				}
				// If staff is valid, it will print the receipt
				print_receipt_func(c, dRoom, pRoom, vRoom);
				continue;
			}
			else if (choice == 4){
				//To verify if the staff is in the system
				if(verifystaff(s, 3) == 0){
					invalidstaff();
					continue;
				}
				cout << "                                                                        __________________________________" << endl;
    			cout << "                                                                      /\\                                  \\" << endl;
    			cout << "                                                                      \\_|          < TODAY SALES >        |" << endl;
    			cout << "                                                                        | =============================== |" << endl;
				cout << "                                                                        |                                 |" << endl; 
				cout << "                                                                        |        " << "Date  : " << day << "/" << month << "/" << year << "        |" << endl;
				cout << "                                                                        |                                 |" << endl; 
				cout << "                                                                        |  " << "Total Sales : RM " << setw(8) << left << fixed << setprecision(0) << printTotal(dRoom, pRoom, vRoom) << "      |" << endl;
				cout << "                                                                        |  _______________________________|_" << endl;
				cout << "                                                                        \\_/_______________________________/ " << endl;
				continue;
			}
			else if (choice == 5){
				// To free the linked list and end the program
				freeList(head);
				endprogram();
				return 0;
			}
			else{
				invalid();
				continue;
			}
			
		}while(choice != 5);

		Customer *b = new Customer;

		if (head == NULL){
			head = b;
		}
		else{
			checkNull(head, b);
		}
		get_hotel_room_preferences(*b, dRoom, pRoom, vRoom);
		// To prompt the user to edit for the last time
		cout << "                                                                Do you want to edit your booking? (Y/N) : ";
		char choice2;
		cin >> choice2;
		cin.ignore();
		if (choice2 == 'Y' || choice2 == 'y'){
			editRoom(*b, dRoom, pRoom, vRoom);
		}
		else{
			thankyou();
		}
		// To show and print the rooms booked
		roomBooked(*b, dRoom, pRoom, vRoom);
		system("cls");
		print_receipt_func(b, dRoom, pRoom, vRoom);



	}
} // End of main function


// Function to check how many double rooms are available
int availableD(Double room[]){
	int avai = 0;
	for (int i = 0; i < 10; ++i)
	{
		if (room[i].getCustomer() == "")
		{
			avai ++;
		}
	}
	return avai;
}

// Functions to check how many presidential rooms are available
int availableP(Presidential room[]){
	int avai = 0;
	for (int i = 0; i < 10; ++i)
	{
		if (room[i].getCustomer() == "")
		{
			avai ++;
		}
	}
	return avai;
}

// Function to check how many villas are available
int availableV(Villa room[]){
	int avai = 0;
	for (int i = 0; i < 10; ++i)
	{
		if (room[i].getCustomer() == "")
		{
			avai ++;
		}
	}
	return avai;
}