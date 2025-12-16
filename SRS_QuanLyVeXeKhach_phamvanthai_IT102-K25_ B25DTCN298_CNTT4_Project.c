#include<stdio.h>
#include<stdlib.h>
#include<string.h>
// =============================================================
// 1. KHAI BAO CAU TRUC (STRUCTS)
// =============================================================

typedef struct {
	char name[50];
	char address[100];
} Location;
typedef struct {
	char tripId[20];
	Location departure;
	Location destination;
	char date[20];
	int totalSeats;
	int bookedSeats;
} Trip;
typedef struct {
	char name[50];
	char phone[15];
} Passenger;
typedef struct {        
	char tiketId[20];
	char tripId[20];
	Passenger passenger;
	int seatNumber;
	double price;
	int paymentStatus;
	char date[20];
} Tiket;
// =============================================================
// 2. NGUYEN MAU HAM  (FUNCTION PROTOTYPES)
// =============================================================
//Ham tien ich 
void removeNewline(char *str);//Xoa khoang trang khi nhap chuoi 
int isEmpty(char *str);//Dieu kien de cac chuc nang yeu cau (phai nhap vao cac gia tri) 
int isValidDate(char *str);//Dieu kien nhap ngay-thang-nam hop le
//Cac chuc nang  
void CreateNewTrip(Trip *trips, int *length);//Them chuyen xe  
void UpdateTripInfo(Trip *trips, int length);//Cap nhat chuyen xe  
void BookTicket(Trip *trips, int tripLength, Tiket *tikets, int *tiketLength);//Mua ve 
void CheckTicketStatus(Tiket *tikets, int tiketLength, Trip *trips, int tripLength);//Kiem tra ve  
void ListTrips(Trip *trips, int tripLength);//In ra danh sach chuyen xe  
void PayTicket(Tiket *tikets, int tiketLength);//Thanh toan tien ve  
void LockCancelTicket(Tiket tikets[], int tiketLength, Trip trips[], int tripLength);//Quan ly trang thai ve  
void RevenueTicketStatisticsRepor(Trip *trips, int tripLength, Tiket *tikets, int tiketLength);//Thong ke va bao cao doanh thu 
// =============================================================
// 3. HAM MAIN
// =============================================================
int main(){
	 
	Trip trips[200];
	Tiket tikets[500];
	int tripLength = 0 ;
	int tiketLength = 0 ;
	char choose[50];
	
	int choice;
	do{
		printf("\n+----------------------------------------------------------+\n");
		printf("|                   TICKET MANAGEMENT                      |\n");
		printf("+----------------------------------------------------------+\n");
		printf("| 1. Create New Trip                                       |\n");
		printf("| 2. Update Trip Info                                      |\n");
		printf("| 3. Book Ticket                                           |\n");
		printf("| 4. Check Ticket Status                                   |\n");
		printf("| 5. List Trips                                            |\n");
		printf("| 6. Pay Ticket                                            |\n");
		printf("| 7. Lock / Cancel Ticket                                  |\n");
		printf("| 8. Revenue & Ticket Statistics Report                    |\n");
		printf("| 9. Exit                                                  |\n");
		printf("+----------------------------------------------------------+\n");
	    printf("Enter your selection: ");
		fgets(choose, sizeof(choose), stdin);
        removeNewline(choose);
        
        // Kiem tra input rong
        if (strlen(choose) == 0 || isEmpty(choose)) {
            printf("\nLoi: Vui long nhap lua chon!\n");
            choice = 0; // Gán giá tri mac dinh de switch không bi loi
        } else {
            choice = atoi(choose);
        }
        
		switch(choice){
			case 1 :{
				CreateNewTrip(trips,&tripLength);
				break;
			}
			case 2 :{
				UpdateTripInfo(trips,tripLength); 
				break;
			} 
			case 3 :{
				BookTicket(trips, tripLength, tikets, &tiketLength);
				break;
			}
			case 4 :{
				CheckTicketStatus(tikets, tiketLength, trips, tripLength);
				break;
			}
			case 5 :{
				ListTrips(trips, tripLength);
				break;
			}
			case 6 :{
				PayTicket(tikets, tiketLength);
				break;
			}
			case 7 :{
				LockCancelTicket(tikets, tiketLength, trips, tripLength);
				break;
			}
			case 8 :{
            	RevenueTicketStatisticsRepor(trips, tripLength, tikets, tiketLength);
				break;
			}
			case 9 :{
				printf("Thanks for choosing!!!");
				break;
			}
			default:{
				printf("Wrong choice!!!"); 
				break;
			}
		}
	}while(choice != 9); 
}
// =============================================================
// 4.DINH NGHIA CAC HAM  (FUNCTION DEFINITIONS)
// =============================================================
void removeNewline(char *str){
	str[strcspn(str, "\n")] = 0; 
} 
int isEmpty(char *str){
    int i;
	for( i = 0; str[i] != '\0'; i++){
        if(str[i] != ' ' && str[i] != '\t'){
            return 0; 
        }
    }
    return 1; 
}
int isValidDate(char *str){
    if (strlen(str) != 10)
        return 0;
    if (str[2] != '/' || str[5] != '/')
        return 0;
    int i;    
    for (i = 0; i < 10; i++) {
        if (i == 2 || i == 5) 
		continue; 
        if (str[i] < '0' || str[i] > '9')
            return 0;
    }
    return 1;
}

void CreateNewTrip(Trip *trips, int *length) {
	do{
	    printf("Enter Trip ID: ");
	    fgets(trips[*length].tripId, sizeof(trips[*length].tripId), stdin);
	    removeNewline(trips[*length].tripId);
	
	    if(isEmpty(trips[*length].tripId)){
	        printf("Trip ID cannot be empty.\n");
	        continue ; // Quay lai nhap thong tin tu dau  khong kiem tra tiep  
	    }
		int duplicated = 0;//Gan flag = 0 -> khong giong  
	    int i;
		for( i=0; i<*length; i++){
	        if(strcmp(trips[i].tripId, trips[*length].tripId) == 0){ // strcmp dung de so sanh giua gia tri da co va gia tri nhap vao  
	            duplicated = 1;// Giong nhau  
	            break;
	        }
	    }
	    if(duplicated){
	    	printf("Trip ID already exists!\n");
		}else break; // Neu khong giong ket thuc kiem tra  
		
	}while(1);//Chay toi khi nao dung het dieu kien  
	
	do{
	    printf("Enter Departure Name: ");
	    fgets(trips[*length].departure.name, sizeof(trips[*length].departure.name), stdin);
	    removeNewline(trips[*length].departure.name);
	    
	    if(strlen(trips[*length].departure.name) == 0 || isEmpty(trips[*length].departure.name)){
			printf("Departure name cannot be empty!\n");
		}else break; 
		
	}while(1); // lap lai thao tac voi departure name : ten diem khoi hanh  
	
	do{
	    printf("Enter Departure Address: ");
	    fgets(trips[*length].departure.address, sizeof(trips[*length].departure.address), stdin);
	    removeNewline(trips[*length].departure.address);
	    
	    if(strlen(trips[*length].departure.address) == 0 || isEmpty(trips[*length].departure.address)){
			printf("Departure address cannot be empty!\n");
		}else break; 
		
	}while(1); // lap lai thao tac voi Departure Address : dia chi khoi hanh 
	
	do{
	    printf("Enter Destination Name: ");
	    fgets(trips[*length].destination.name, sizeof(trips[*length].destination.name), stdin);
	    removeNewline(trips[*length].destination.name);
	    if(strlen(trips[*length].destination.name) == 0 || isEmpty(trips[*length].destination.name)){
			printf("Destination name cannot be empty!\n");
		}else break; 
    
	}while(1); //lap lai thao tac voi Destination name : ten diem den 
	
	do {
        printf("Enter Destination Address: ");
        fgets(trips[*length].destination.address, sizeof(trips[*length].destination.address), stdin);
        removeNewline(trips[*length].destination.address);

        if(strlen(trips[*length].destination.address) == 0 || isEmpty(trips[*length].destination.address)){
            printf("Destination address cannot be empty!\n");
        } else break;

    } while(1);//lap lai thao tac voi Destination address : dia chi diem den 

     do {
	    printf("Enter Date (dd/mm/yyyy): ");
	    fgets(trips[*length].date, sizeof(trips[*length].date), stdin);
	    removeNewline(trips[*length].date);
	
	    if(strlen(trips[*length].date) == 0 || isEmpty(trips[*length].date)){
	        printf("Date cannot be empty!\n");
	        continue;
	    }
	
	    if(!isValidDate(trips[*length].date)){  // Dung ham validDate kiem tra dinh dang nhap ngay-thang-nam
	        printf("Date must contain only numbers and '/'\n");
	        continue;
	    }

    break;
	} while(1);
	
    int seats;
	char buffer[50];
	
	do {
	    printf("Enter Total Seats: ");
	    fgets(buffer, sizeof(buffer), stdin); // Fget thay vi scanf vi fget doc ca ky tu khoang trang va khong de lai ky tu thua trong input buffer .
	    if (sscanf(buffer, "%d", &seats) != 1) { //sscanf dung de doc chuoi tim xem trong buffer co ki tu so hay khong
	        printf("Seats must be a number!\n");//neu co  gan vao seats va tra ve 1 khong thi tra ve 0 va yeu cau nhap lai.
	        continue;//Dung fget + scanf vi giup doc ca dong nguoi dung nhap neu sai thi bao loi va continue de tiep tuc 
	    }          //nhap toi khi dung .
	
	    if (seats <= 0) {
	        printf("Total seats must be > 0!\n");
	        continue;
	    }
	
	    break;
	
	} while (1);

    trips[*length].totalSeats = seats; // Gan so ghe vua nhap vao chuyen xe moi .
    trips[*length].bookedSeats = 0;    //Khi tao chuyen xe moi so ghe mac dinh = 0. 
    (*length)++;                       //Moi khi them do dai mang tang len mot.

    printf("\nTrip added successfully!\n");
}
void UpdateTripInfo(Trip *trips, int length) {
     int i; 
    // Kiem tra danh sach rong
    if (length == 0) {
        printf("No trips available.\n");
        return;
    }
    char id[20];
    // Nhap tripId de cap nhat
    do {
        printf("Enter Trip ID to update: ");
        fgets(id, sizeof(id), stdin);
        removeNewline(id);
        if (strlen(id) == 0 || isEmpty(id)) {
            printf("Trip ID cannot be empty.\n");
            continue;
        }
        break;
    } while (1);
    // Tim trip
    int found = -1;
    for (i = 0; i < length; i++) {
        if (strcmp(trips[i].tripId, id) == 0) {
            found = i;
            break;
        }
    }
    if (found == -1) {
        printf("Trip not found.\n");
        return;
    }
    int choice;
    do {
        // ------- MENU UPDATE -------
        printf("\n+------------UPDATE TRIP MENU------------+\n");
        printf("1. Update Departure Name                 |\n");
        printf("2. Update Departure Address              |\n");         
        printf("3. Update Destination Name               |\n");
        printf("4. Update Destination Address            |\n");
        printf("5. Update Date                           |\n");
        printf("6. Update Total Seats                    |\n");
        printf("0. Exit Update Menu                      |\n");             
        printf("+----------------------------------------+\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid choice.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');
        switch (choice) {
            case 1: {
                // Cap nhat ten diem di
                printf("New Departure Name: ");
                fgets(trips[found].departure.name, sizeof(trips[found].departure.name), stdin);
                removeNewline(trips[found].departure.name);
                // Validate khong de trong
                if (strlen(trips[found].departure.name) == 0 || isEmpty(trips[found].departure.name)) {
                    printf("Invalid. Departure name unchanged.\n");
                } else {
                    printf("Updated successfully.\n");
                }
                break;
            }
            case 2: {
                // Cap nhat dia chi diem di
                printf("New Departure Address: ");
                fgets(trips[found].departure.address, sizeof(trips[found].departure.address), stdin);
                removeNewline(trips[found].departure.address);

                if (strlen(trips[found].departure.address) == 0 || isEmpty(trips[found].departure.address)) {
                    printf("Invalid. Departure address unchanged.\n");
                } else {
                    printf("Updated successfully.\n");
                }
                break;
            }
            case 3: {
                // Cap nhat ten diem den
                printf("New Destination Name: ");
                fgets(trips[found].destination.name, sizeof(trips[found].destination.name), stdin);
                removeNewline(trips[found].destination.name);
                if (strlen(trips[found].destination.name) == 0 || isEmpty(trips[found].destination.name)) {
                    printf("Invalid. Destination name unchanged.\n");
                } else {
                    printf("Updated successfully.\n");
                }
                break;
            }
            case 4: {
                // Cap nhat dia chi diem den
                printf("New Destination Address: ");
                fgets(trips[found].destination.address, sizeof(trips[found].destination.address), stdin);
                removeNewline(trips[found].destination.address);
                if (strlen(trips[found].destination.address) == 0 || isEmpty(trips[found].destination.address)) {
                    printf("Invalid. Destination address unchanged.\n");
                } else {
                    printf("Updated successfully.\n");
                }
                break;
            }
            case 5: {
			    char newDate[20];
			    while (1) {
			        printf("New Date (dd/mm/yyyy): ");
			        fgets(newDate, sizeof(newDate), stdin);
			        removeNewline(newDate);			
			        // Kiem tra rong
			        if (strlen(newDate) == 0 || isEmpty(newDate)) {
			            printf("Invalid. Please enter again.\n");
			            continue;   // <-- yeu cau: nhap sai thi nhap lai ngay
			        }			
			        // Kiem tra dinh dang
			        if (!isValidDate(newDate)) {
			            printf("Date must contain only numbers and '/'. Enter again.\n");
			            continue;   // <-- tiep tuc nhap lai
			        }			
			        // Hop le => cap nhat
			        strcpy(trips[found].date, newDate);
			        printf("Updated successfully.\n");
			        break; // Thoat case 5, quay lai menu
			    	}
    			break;
			}
            case 6: {
			    int newSeats;
			    while (1) {
			        printf("New Total Seats: ");
			        // Kiem tra xem nguoi dung co nhap so hay nhap chu
			        if (scanf("%d", &newSeats) != 1) {
			            printf("Seats must be a number. Enter again.\n");
			            // Xoa ky tu rac trong bo nho dem de tranh lap vo han
			            while (getchar() != '\n');
			            continue; // Nhap lai ngay
			        }
			        // Xoa dau xuong dong con lai trong stdin
			        while (getchar() != '\n');
			        // Kiem tra so ghe phai lon hon 0
			        if (newSeats <= 0) {
			            printf("Total seats must be > 0. Enter again.\n");
			            continue;
			        }
			        // Kiem tra so ghe moi khong duoc nho hon so ghe da dat
			        if (newSeats < trips[found].bookedSeats) {
			            printf("Total seats must be >= booked seats (%d). Enter again.\n",
			                   trips[found].bookedSeats);
			            continue;
			        }
			        // Neu hop le thi cap nhat so ghe
			        trips[found].totalSeats = newSeats;
			        printf("Updated successfully.\n");
			        break; // Thoat vong lap va tro ve menu
			    }
			    break;
			}

            case 0:
                printf("Exiting update menu...\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 0);
    printf("\nTrip updated successfully.\n");
}
void BookTicket(Trip *trips, int tripLength, Tiket *tikets, int *tiketLength) {
    // Kiem tra neu danh sach chuyen xe rong
    if(tripLength == 0) {
        printf("\nNo trips available to book! (Khong co chuyen xe nao)\n");
        return;
    }
    char tripId[30];
    int tripIndex = -1; 
    // --- BUOC 1: CHON CHUYEN XE ---
    do {
        printf("\n+--------BOOKING TICKET--------+\n");
        printf("Enter Trip ID: ");
        fgets(tripId, sizeof(tripId), stdin);
        removeNewline(tripId); // Su dung ham ban da khai bao
        // Kiem tra rong
        if(strlen(tripId) == 0||isEmpty(tripId)) {
            printf("Error: Trip ID cannot be empty!\n");
            continue;
        }
        // Tim chuyen xe
        tripIndex = -1;
        int i;
        for(i = 0; i < tripLength; i++) {
            if(strcmp(trips[i].tripId, tripId) == 0) {
                tripIndex = i;
                break;
            }
        }
        if(tripIndex == -1) {
            printf("Error: Trip ID not found!\n");
        } else {
            // Kiem tra xem chuyen xe da day ghe chua
            if (trips[tripIndex].bookedSeats >= trips[tripIndex].totalSeats) {
                printf("Error: This trip is FULL (Het ghe)!\n");
                tripIndex = -1; 
            } else {
                break; // Hop le
            }
        }
    } while(1);
    Trip *selectedTrip = &trips[tripIndex]; 
    Tiket newTiket; 
    // Tu dong tao Ticket ID (T001, T002...)
    snprintf(newTiket.tiketId, sizeof(newTiket.tiketId), "T%03d", *tiketLength + 1);//tao chuoi an toan ket hop dinh dang ma khong lo tran bo nho  
    strcpy(newTiket.tripId, selectedTrip->tripId); 
    // --- BUOC 2: NHAP TEN HANH KHACH ---
    do {
        printf("Enter Passenger Name: ");
        fgets(newTiket.passenger.name, sizeof(newTiket.passenger.name), stdin);
        removeNewline(newTiket.passenger.name); // Su dung ham ban da khai bao

        if(strlen(newTiket.passenger.name) == 0||isEmpty(newTiket.passenger.name)) {
            printf("Error: Passenger name cannot be empty!\n");
            continue;
        } 
      
			break;
    } while(1);
    // --- BUOC 3: NHAP SDT ---
	do {
		int i; 
	    char buffer[50]; // luu input tam thoi
	    printf("Enter Passenger Phone: ");
	    // doc ca dong de tranh loi buffer
	    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
	        printf("Input error. Enter again.\n");
	        continue;
	    }
	    // xoa ky tu '\n' neu co
	    removeNewline(buffer); 
	    // kiem tra rong
	    if (strlen(buffer) == 0||isEmpty(buffer)) {
	        printf("Error: Phone cannot be empty!\n");
	        continue;
	    }
	    // kiem tra do dai va tat ca ky tu la so
	    int len = strlen(buffer);
	    int validPhone = 1;
	    if (len < 9 || len > 11) {
	        validPhone = 0;
	    } else {
	        for (i = 0; i < len; i++) {
	            if (buffer[i] < '0' || buffer[i] > '9') {
	                validPhone = 0;
	                break;
	            }
	        }
	    }
	    if (!validPhone) {
	        printf("Error: Phone number must be 9-11 digits!\n");
	        continue;
	    }
	    // hop le -> copy vao struct
	    strcpy(newTiket.passenger.phone, buffer);
	    break;
	} while (1);
    // --- BUOC 4: CHON GHE ---
    do {
        printf("Enter Seat Number (1-%d): ", selectedTrip->totalSeats);
        if(scanf("%d", &newTiket.seatNumber) != 1) {
            printf("Error: Invalid input! Please enter a number.\n");
            while(getchar() != '\n'); 
            continue;
        }
        while(getchar() != '\n'); 
        // Kiem tra pham vi ghe
        if(newTiket.seatNumber < 1 || newTiket.seatNumber > selectedTrip->totalSeats) {
            printf("Error: Seat number must be between 1 and %d!\n", selectedTrip->totalSeats);
            continue;
        }
        // Kiem tra ghe da duoc dat chua
        int isTaken = 0;
        int i;
        for(i = 0; i < *tiketLength; i++) {
            if(strcmp(tikets[i].tripId, selectedTrip->tripId) == 0 && 
               tikets[i].seatNumber == newTiket.seatNumber && 
               tikets[i].paymentStatus != -2) { // Neu ve huy (-2) thi ghe van coi la trong
                isTaken = 1;
                break;
            }
        }
        if(isTaken) {
            printf("Error: Seat %d is already taken!\n", newTiket.seatNumber);
        } else {
            break;
        }
    } while(1);
   // --- BUOC 5: NHAP GIA ---
	do {
	    char buffer[50];  // luu input tam thoi
	    double priceInput;
	    printf("Enter Price: ");
	    // doc ca dong tu ban phim
	    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
	        printf("Error: Input error. Enter again!\n");
	        continue;
	    }
	    // xoa ky tu xuong dong '\n' neu co
	    removeNewline(buffer); 
	    // kiem tra nhap co phai la so hay khong
	    if (sscanf(buffer, "%lf", &priceInput) != 1) {
	        printf("Error: Price must be a number. Enter again!\n");
	        continue;
	    }
	    // kiem tra gia hop le
	    if (priceInput <= 0) {
	        printf("Error: Price must be positive (> 0). Enter again!\n");
	        continue;
	    }
	    // hop le -> luu gia va thoat vong lap
	    newTiket.price = priceInput;
	    break;
	} while (1);
	// --- BUOC 6: LUU DU LIEU ---
	newTiket.paymentStatus = 0; // Mac dinh 0: chua thanh toan
	strcpy(newTiket.date, selectedTrip->date); 
	tikets[*tiketLength] = newTiket;
	(*tiketLength)++;
	selectedTrip->bookedSeats++;
	// thong bao dat ve thanh cong
	printf("\nTicket booked successfully! (Dat ve thanh cong)\n");
	printf("Ticket ID: %s | Seat: %d | Status: Unpaid\n", newTiket.tiketId, newTiket.seatNumber);
	// khong can nhan Enter nua -> tu dong quay ve menu
	return;
}
void CheckTicketStatus(Tiket *tikets, int tiketLength, Trip *trips, int tripLength) {
    // Kiem tra neu danh sach ve rong
    if (tiketLength == 0) {
        printf("\nNo tickets available in the system!\n");
        return;
    }
    char id[30];
    // Vong lap nhap lieu va kiem tra dau vao (Validation)
    while (1) {
        printf("\n+------- CHECK TICKET STATUS -------+\n");
        printf("Enter Ticket ID: ");
        fgets(id, sizeof(id), stdin);
        // Xoa ky tu xuong dong (enter) o cuoi chuoi
        removeNewline(id); 
        // Kiem tra ticketId khong duoc de trong
        if (strlen(id) == 0||isEmpty(id)) {
            printf("Error: Ticket ID cannot be empty! Please try again.\n");
            continue;
        }
        break; // Nhap dung thi thoat vong lap
    }
    int found = 0; // Bien co danh dau: 0 la khong thay, 1 la tim thay
    int i;
    // Duyet qua danh sach ve de tim kiem
    for (i = 0; i < tiketLength; i++) {
        // So sanh ticketId nhap vao voi ID trong danh sach
        if (strcmp(tikets[i].tiketId, id) == 0) {
            found = 1;
            // Xac dinh trang thai thanh toan de hien thi
            char statusText[30];
            if (tikets[i].paymentStatus == 1) {
                strcpy(statusText, "Paid (Da thanh toan)");
            } else if (tikets[i].paymentStatus == 0) {
                strcpy(statusText, "Unpaid (Chua thanh toan)");
            } else {
                strcpy(statusText, "Canceled/Locked (Huy/Khoa)");
            }
            // Case 1: Thanh cong - Hien thi day du thong tin
            printf("\n================ TICKET DETAILS ================\n");
            printf("%-20s : %s\n", "Ticket ID", tikets[i].tiketId);
            printf("%-20s : %s\n", "Passenger Name", tikets[i].passenger.name);
            printf("%-20s : %s\n", "Phone Number", tikets[i].passenger.phone); // Hien thi SDT
            printf("%-20s : %s\n", "Trip ID", tikets[i].tripId);
            printf("%-20s : %d\n", "Seat Number", tikets[i].seatNumber);
            printf("%-20s : %.0f VND\n", "Price", tikets[i].price);
            printf("------------------------------------------------\n");
            printf("%-20s : %s\n", "PAYMENT STATUS", statusText);
            printf("================================================\n");
            break; // Tim thay roi thi dung vong lap
        }
    }
    // Case 2: That bai - Khong tim thay ve
    if (found == 0) {
        printf("\nError: Ticket ID '%s' not found in the system!\n", id);
    }
    // Dung man hinh de xem ket qua
    printf("\nPress Enter to return...");
    getchar();
}
void ListTrips(Trip *trips, int tripLength) {
    char buffer[20];
    int pageSize = 10;     // default
    int pageNumber = 1;    // default
    int i; 
    // Kiem tra danh sach trong
    if (tripLength == 0) {
        printf("No trips to display.\n"); // Yeu cau output
        return;
    }
    // Nhap pageSize
    printf("Enter page size (default = 10): ");
    fgets(buffer, sizeof(buffer), stdin);
    if (sscanf(buffer, "%d", &pageSize) != 1 || pageSize <= 0) {
        pageSize = 10; // dung mac dinh
    }
    // Nhap pageNumber
    printf("Enter page number (default = 1): ");
    fgets(buffer, sizeof(buffer), stdin);
    if (sscanf(buffer, "%d", &pageNumber) != 1 || pageNumber <= 0) {
        pageNumber = 1; // dung mac dinh
    }
    // Tinh tong so trang
    int totalPages = (tripLength + pageSize - 1) / pageSize;
    // Kiem tra so trang hop le (yeu cau)
    if (pageNumber > totalPages) {
        printf("Invalid page number.\n");
        return;
    }
    // Tinh vi tri bat dau va ket thuc
    int start = (pageNumber - 1) * pageSize;
    int end = start + pageSize;
    if (end > tripLength) end = tripLength;
    // In tieu de bang
    printf("\nTrip list (Page %d / %d)\n", pageNumber, totalPages);
    printf("---------------------------------------------------------------------------\n");
    printf("%-10s | %-15s | %-15s | %-12s | %-10s\n",
           "TripID", "Departure", "Destination", "Date", "Booked/Tot");
    printf("---------------------------------------------------------------------------\n");

    // In cac dong trong trang
    for (i = start; i < end; i++) {
        printf("%-10s | %-15s | %-15s | %-12s | %3d/%-3d\n",
               trips[i].tripId,
               trips[i].departure.name,
               trips[i].destination.name,
               trips[i].date,
               trips[i].bookedSeats,
               trips[i].totalSeats);
    }

    printf("---------------------------------------------------------------------------\n");
}
void PayTicket(Tiket tikets[], int tiketLength) {
    int i; 
    char id[20];
    // Nhap ma ve
    do {
        printf("Enter Ticket ID: ");
        if (fgets(id, sizeof(id), stdin) == NULL) {
            printf("Input error.\n");
            return;
        }
        removeNewline(id);
        // Kiem tra rong
        if (strlen(id) == 0||isEmpty(id)) {
            printf("Ticket ID cannot be empty!\n");
        } else break;

    } while (1);

    // Tim ve theo ID
    int idx = -1;
    for (i = 0; i < tiketLength; i++) {
        if (strcmp(tikets[i].tiketId, id) == 0) {
            idx = i;
            break;
        }
    }
    // Kiem tra khong tim thay ve
    if (idx == -1) {
        printf("Ticket not found!\n");
        return;
    }
    Tiket *t = &tikets[idx];
    // Kiem tra ve da bi khoa hoac huy
    // -1 = Locked
    // -2 = Canceled
    if (t->paymentStatus == -1 || t->paymentStatus == -2) {
        printf("Ticket cannot be paid because it is disabled!\n");//vo hieu hoa  
        return;
    }
    // Kiem tra ve da thanh toan truoc do
    if (t->paymentStatus == 1) {
        printf("Ticket has been paid already.\n");
        return;
    }
    // Den day => paymentStatus = 0 => cho phep thanh toan
    t->paymentStatus = 1;
    printf("Payment successful.\n");
}
void LockCancelTicket(Tiket tikets[], int tiketLength, Trip trips[], int tripLength) {
    char input[50];
    int choice;
    int i, j; // bien j dung cho vong lap con

    do {
        printf("\n+----------Ticket Management (Lock / Cancel)-----------+\n");
        printf("|1. Lock ticket                                        |\n");
        printf("|2. Cancel ticket                                      |\n");
        printf("|0. Exit                                               |\n");
        printf("+------------------------------------------------------+\n");
        printf("Choose: ");
        fgets(input, sizeof(input), stdin);
        if (sscanf(input, "%d", &choice) != 1) { 
            // Nhap lieu an toan: doc ca dong vao buffer roi chuyen sang int
            printf("Invalid input!\n");
            continue;
        }
        if (choice == 0) break;
        char id[20];
        printf("Enter Ticket ID: ");
        fgets(id, sizeof(id), stdin);
        removeNewline(id);
        if (strlen(id) == 0||isEmpty(id)) {
            printf("[Case 3] Ticket ID cannot be empty!\n");
            continue;
        }
        // Tim ve trong mang
        int index = -1;
        for (i = 0; i < tiketLength; i++) {
            if (strcmp(tikets[i].tiketId, id) == 0) {
                index = i;
                break;
            }
    }
        if (index == -1) {
            printf("[Case 3] Ticket not found!\n");
            continue;
        }
        Tiket *t = &tikets[index]; // tao con tro den ticket
        // Kiem tra trang thai hien tai
        if (t->paymentStatus == -1 || t->paymentStatus == -2) {
            printf("[Case 3] Ticket is already disabled!\n"); // ve da lock hoac cancel
            continue;
        }
        // Lock ticket
        if (choice == 1) {
            t->paymentStatus = -1;
            printf("[Case 1] Ticket locked successfully.\n");
            printf("Status = Locked\n");
            continue;
        }
        // Cancel ticket
        if (choice == 2) {
            if (t->paymentStatus != 0) {
                printf("[Case 3] Cannot cancel because ticket is already paid!\n");
                continue;
            }
            // Tim trip lien quan de giam bookedSeats
            int foundTrip = 0;
            for (j = 0; j < tripLength; j++) {
                if (strcmp(trips[j].tripId, t->tripId) == 0) {
                    trips[j].bookedSeats--; // giai phong ghe
                    foundTrip = 1;
                    break;
                }
            }
            if (foundTrip) {
                t->paymentStatus = -2; // cap nhat trang thai canceled
                printf("[Case 2] Ticket canceled successfully.\n");
                printf("Status = Canceled\n");
                printf("Seat released (bookedSeats--)\n");
            } else {
                printf("[Case 3] Error: Associated trip not found.\n");//khong tim thay chuyen xe lien quan  
            }
            continue;
        }
        printf("Invalid choice!\n"); // lua chon khong hop le
    } while (1);
}
void RevenueTicketStatisticsRepor(Trip *trips, int tripLength, Tiket *tikets, int tiketLength) {
    // Kiem tra xem co ticket hay khong
    if (tiketLength == 0) {
        printf("\n[Case 4] No data available for reporting\n");
        return;
    }

    int type = 0;  // Loai bao cao nguoi dung chon
    int i, j;

    do {
        // --- HIEN THI MENU CON ---
        printf("\n+--Select report type--+\n");
        printf("|1. Total revenue      |\n");
        printf("|2. Trip statistics    |\n");
        printf("|3. Date range report  |\n");
        printf("|0. Exit report menu   |\n");
        printf("+----------------------+\n"); 
        printf("Enter your choice: ");

        char buffer[50];
        fgets(buffer, sizeof(buffer), stdin); // doc input
        sscanf(buffer, "%d", &type);          // chuyen string sang int

        // Kiem tra loai bao cao hop le
        if (type < 0 || type > 3) {
            printf("\n[Error] Invalid report type\n");
            continue; // quay lai menu con
        }

        // --- CASE 0: Thoat menu con ---
        if (type == 0) {
            printf("Exiting report menu...\n");
            break; // thoat khoi vong lap menu con
        }

        // CASE 1 – Bao cao tong doanh thu
        if (type == 1) {
            double totalRevenue = 0;
            int totalPaid = 0;

            for (i = 0; i < tiketLength; i++) {
                if (tikets[i].paymentStatus == 1) {
                    totalRevenue += tikets[i].price;
                    totalPaid++;
                }
            }

            printf("\n[Case 1] Total revenue report successful\n");
            printf("Total revenue: %.0f VND\n", totalRevenue);
            printf("Total paid tickets: %d\n", totalPaid);
        }

        // CASE 2 – Bao cao thong ke theo chuyen xe
        else if (type == 2) {
            printf("\n[Case 2] Trip statistics report:\n\n");
            printf("+------------+-------+-------+----------+-------+-----------------+\n");
            printf("| %-10s | %-5s | %-5s | %-8s | %-5s | %-15s |\n",
                   "TripID", "Total", "Paid", "Cancel", "Valid", "Revenue");
            printf("+------------+-------+-------+----------+-------+-----------------+\n");

            for (i = 0; i < tripLength; i++) {
                int total = 0, paid = 0, canceled = 0, valid = 0;
                double revenue = 0;
                for (j = 0; j < tiketLength; j++) {
                    if (strcmp(trips[i].tripId, tikets[j].tripId) == 0) {
                        total++;
                        if (tikets[j].paymentStatus == 1) {
                            paid++;
                            revenue += tikets[j].price;
                        } else if (tikets[j].paymentStatus == -2) {
                            canceled++;
                        }
                    }
                }
                valid = total - canceled; // ve con hieu luc
                printf("| %-10s | %-5d | %-5d | %-8d | %-5d | %-15.0f |\n",
                       trips[i].tripId, total, paid, canceled, valid, revenue);
            }

            printf("+------------+-------+-------+----------+-------+-----------------+\n");
        }

        // CASE 3 – Bao cao theo khoang thoi gian
        else if (type == 3) {
            char fromDate[20], toDate[20];

            // --- Nhap ngay bat dau ---
            do {
                printf("Enter start date (dd/mm/yyyy): ");
                fgets(fromDate, sizeof(fromDate), stdin);
                removeNewline(fromDate);

                if (!isValidDate(fromDate)) {
                    printf("Error: Invalid date format! Please enter in dd/mm/yyyy.\n");
                    continue;
                }
                break; // hop le
            } while (1);

            // --- Nhap ngay ket thuc ---
            do {
                printf("Enter end date (dd/mm/yyyy): ");
                fgets(toDate, sizeof(toDate), stdin);
                removeNewline(toDate);

                if (!isValidDate(toDate)) {
                    printf("Error: Invalid date format! Please enter in dd/mm/yyyy.\n");
                    continue;
                }
                break; // hop le
            } while (1);

            // Kiem tra thu tu ngay
            if (strcmp(fromDate, toDate) > 0) {
                printf("\n[Case 3] Invalid date range: start date > end date\n");
                continue; // quay lai menu con
            }

            double revenue = 0;
            int total = 0, canceled = 0, valid = 0;

            for (i = 0; i < tiketLength; i++) {
                if (strcmp(tikets[i].date, fromDate) >= 0 &&
                    strcmp(tikets[i].date, toDate) <= 0) {
                    total++;
                    if (tikets[i].paymentStatus == 1) {
                        revenue += tikets[i].price;
                    } else if (tikets[i].paymentStatus == -2) {
                        canceled++;
                    }
                }
            }

            valid = total - canceled;
            printf("\n[Case 3] Date range report\n");
            printf("Total tickets in range: %d\n", total);
            printf("Total revenue: %.0f VND\n", revenue);
            printf("Canceled tickets: %d\n", canceled);
            printf("Valid tickets: %d\n", valid);
        }

        // --- Ket thuc 1 lan chon menu con, quay lai menu ---
    } while (1);
}





    

