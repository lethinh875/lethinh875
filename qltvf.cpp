#include <iomanip>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <windows.h>
using namespace std;

//--------------------------------

struct Book{
    string ISBN; //Ma so
    string title; //Ten sach
    string subject; //Chu de
    string author; //Tac gia
    string publisher; //Nha xuat ban
    string date; //Ngay xuat ban
    int pages; //So trang
    int copies; //So ban copy
};

struct User{
    string userid;
    string username;
    string password;
    string perm;
};

//-----------------BOOK------------------------

void addBookFile(vector<Book>& library){
    ofstream outfile;
    outfile.open("Sach.txt");
    for (const Book& book : library){
        outfile << book.ISBN << "|" << book.title << "|" << book.subject << "|" << book.author << "|"
        << book.publisher << "|" << book.date << "|" << book.pages << "|" << book.copies << endl;
    }
    outfile.close();
}

void readBookFile(vector<Book>& library){
	library.clear();
    ifstream infile;
    infile.open("Sach.txt");
    while (infile>> ws) {
            Book book;
            getline(infile, book.ISBN, '|');
            if (book.ISBN.empty()) {
                break;
            }
            getline(infile, book.title, '|');
            getline(infile, book.subject, '|');
            getline(infile, book.author, '|');
            getline(infile, book.publisher, '|');
            getline(infile, book.date, '|');
        	infile >> book.pages;
        	infile.ignore();
        	infile >> book.copies;
        	infile.ignore();
            library.push_back(book);
        }
    infile.close();
}

void addBook(vector<Book>& library){
	readBookFile(library);
    Book newBook;
    
    cout << "Ma so: "; cin >> newBook.ISBN; cin.ignore();
	    
    vector<Book>::iterator i = find_if(library.begin(), library.end(), [newBook](const Book& book) {
        return book.ISBN == newBook.ISBN;
    });

    if (i != library.end()) {
        cout << "Sach voi ma so " << "[" << newBook.ISBN << "]" << " da ton tai.\n";
        return; 
    }
    
    cout << "Ten sach: "; getline(cin, newBook.title);
    cout << "Chu de: "; getline(cin, newBook.subject);
    cout << "Ten tac gia: "; getline(cin, newBook.author);
    cout << "Nha xuat ban: "; getline(cin, newBook.publisher);
    cout << "Ngay thang xuat ban: "; getline(cin, newBook.date);
    cout << "So Trang: "; cin >> newBook.pages; cin.ignore();
    cout << "So ban copy trong thu vien: "; cin >> newBook.copies; cin.ignore();
	cout << "Them sach vao thu vien thanh cong" << endl;
    library.push_back(newBook);
    addBookFile(library);
}

void deleteBook(vector<Book>& library) {
    readBookFile(library);
    string isbn;
    cout << "Nhap ma so sach: "; cin >> isbn; cin.ignore();

    vector<Book>::iterator i = remove_if(library.begin(), library.end(), [isbn](const Book& book) {
        return book.ISBN == isbn;
    });

    if (i != library.end()) {
        library.erase(i, library.end());
        cout << "Sach da duoc xoa" << endl;
        addBookFile(library);
    } else {
        cout << "Khong tim thay ma so sach" << endl;
    }
}


void editBook(vector<Book>& library){
    readBookFile(library);
    string isbn;
    
    cout << "Nhap ma so sach: "; cin >> isbn; cin.ignore();
    for (Book& book : library) {
        if (book.ISBN == isbn) {
            cout << "Ten sach: "; getline(cin, book.title);
            cout << "Chu de: "; getline(cin, book.subject);
            cout << "Ten tac gia: "; getline(cin, book.author);
            cout << "Nha xuat ban: "; getline(cin, book.publisher);
            cout << "Ngay thang xuat ban: "; getline(cin, book.date);
            cout << "So Trang: "; cin >> book.pages; cin.ignore();
            cout << "So ban copy trong thu vien: "; cin >> book.copies; cin.ignore();
            cout << "Da cap nhat thong tin cua sach voi ma so " << "[" << isbn << "]" << endl;
            addBookFile(library);
            return;
        }
    }
    cout << "Khong tim thay sach voi ma so " << "[" << isbn << "]" << endl;
}

void showBook(vector<Book>& library) {
	readBookFile(library);
    cout << left << setw(8) << "ISBN" << setw(50) << "Title" << setw(15) << "Subject"
         << setw(20) << "Author" << setw(20) << "Publisher" << setw(20) << "Date"
         << setw(15) << "Pages" << setw(15) << "Copies" << endl;

    for (const Book& book : library) {
        cout << left << setw(8) << book.ISBN << setw(50) << book.title << setw(15) << book.subject
             << setw(20) << book.author << setw(20) << book.publisher << setw(20) << book.date
             << setw(15) << book.pages << setw(15) << book.copies << endl;
    }
}

void searchBook(vector<Book> library) {
	readBookFile(library);
	bool found = false; string keyword;
	cout << "Nhap tu khoa: "; getline(cin, keyword);
	cout << left << setw(8) << "ISBN" << setw(50) << "Title" << setw(15) << "Subject"
         << setw(20) << "Author" << setw(20) << "Publisher" << setw(20) << "Date"
         << setw(15) << "Pages" << setw(15) << "Copies" << endl;

	for (const Book& book : library) {
		if (book.title.find(keyword) != string::npos ||
		book.subject.find(keyword) != string::npos ||
		book.author.find(keyword) != string::npos ||
		book.publisher.find(keyword) != string::npos) {
        cout << left << setw(8) << book.ISBN << setw(50) << book.title << setw(15) << book.subject
             << setw(20) << book.author << setw(20) << book.publisher << setw(20) << book.date
             << setw(15) << book.pages << setw(15) << book.copies << endl;
			found = true;
		}	
	}
	cout << endl;
	
	if (!found) {
		cout << "Khong tim thay sach voi tu khoa '" << keyword << "'.\n";
	}
	
}


//--------------------------------------------------

void addUserFile(vector<User>& userList){
	ofstream outfile;
    outfile.open("User.txt");
    for (const User& users : userList){
        outfile << users.userid << "|" << users.username << "|" << users.password << "|"
        << users.perm << endl;
    }
    outfile.close();
}

void readUserFile(vector<User>& userList) {
	userList.clear();
    ifstream infile;
    infile.open("User.txt");
    while (infile >> ws) {
        User users;
        getline(infile, users.userid, '|');
        if (users.userid.empty()) {
            break;
        }
        getline(infile, users.username, '|');
        getline(infile, users.password, '|');
        getline(infile, users.perm);
        userList.push_back(users);
    }
    infile.close();
}

void addUser(vector<User>& userList) {
    readUserFile(userList);
    User newUser;

    do {
        cout << "Nhap userid: ";
        getline(cin, newUser.userid);
        if (newUser.userid.empty()) {
            cout << "Userid khong duoc trong. Nhap lai" << endl;
        }
    } while (newUser.userid.empty());

    vector<User>::iterator useridDuplicate = find_if(userList.begin(), userList.end(), [newUser](const User& user) {
        return user.userid == newUser.userid;
    });

    if (useridDuplicate != userList.end()) {
        cout << "Tai khoan nay da co san tren he thong" << endl;
        return;
    }

    do {
        cout << "Nhap username: ";
        getline(cin, newUser.username);
        if (newUser.username.empty()) {
            cout << "Username khong duoc trong. Nhap lai" << endl;
        }
    } while (newUser.username.empty());

    vector<User>::iterator usernameDuplicate = find_if(userList.begin(), userList.end(), [newUser](const User& user) {
        return user.username == newUser.username;
    });

    if (usernameDuplicate != userList.end()) {
        cout << "Username nay da co san tren he thong" << endl;
        return;
    }

    do {
        cout << "Nhap mat khau: ";
        getline(cin, newUser.password);
        if (newUser.password.empty()) {
            cout << "Password khong duoc trong. Nhap lai" << endl;
        }
    } while (newUser.password.empty());

    do {
        cout << "Perm (user/admin): ";
        getline(cin, newUser.perm);
        if (newUser.perm != "user" && newUser.perm != "admin") {
            cout << "Vui long nhap perm la user/admin" << endl;
        }
    } while (newUser.perm != "user" && newUser.perm != "admin");

    cout << "Nguoi dung da duoc tao" << endl;
    userList.push_back(newUser);
    addUserFile(userList);
}



void deleteUser(vector<User>& userList) {
    readUserFile(userList);
    string id;
    cout << "Nhap userid: "; getline(cin, id);

    vector<User>::iterator i = remove_if(userList.begin(), userList.end(), [id](const User& user) {
        return user.userid == id;
    });


    if (i != userList.end()) {
        userList.erase(i, userList.end());
        cout << "User da duoc xoa" << endl;
        addUserFile(userList);
    } else {
        cout << "Khong tim thay userid" << endl;
    }
}

void editUser(vector<User>& userList){
    readUserFile(userList);
    string id;
    cout << "Nhap userid: "; getline(cin, id);
    for (User& user : userList) {
        if (user.userid == id) {
        	cout << "Nhap username: "; getline(cin, user.username);
            cout << "Nhap password: "; getline(cin, user.password);
            cout << "Da cap nhat thong tin cua user" << "[" << id << "]" << endl;
            addUserFile(userList);
            return;
        }
    }
    cout << "Khong tim thay user" << "[" << id << "]" << endl;
}

//-----------------------------------------


bool login(vector<User>& userList, string& perm) {
	readUserFile(userList);
    string username, password;
    
    cout << "Nhap username: "; getline(cin, username);
    cout << "Nhap mat khau: "; getline(cin, password);

    for (const User& user : userList) {
        if (user.username == username && user.password == password) {
            perm = user.perm;
            cout << "Dang nhap thanh cong!" << endl;
            return true;
        }
    }
    cout << "Dang nhap that bai. Vui long kiem tra lai thong tin dang nhap." << endl;
    return false;
}

//-------------------------------------------------------------------
struct Borrow{
    string username;
    string bookISBN;
    string bookTitle;
    string status;
    string time;
};

string getCurrentTime() {
    time_t now = time(nullptr);
    tm *ltm = localtime(&now);

    char buffer[30];
    strftime(buffer, sizeof(buffer), "%c", ltm);

    return buffer;
}


bool userExists(const vector<User>& userList, const string& id) {
    return find_if(userList.begin(), userList.end(), [&id](const User& user) {
        return user.username == id;
    }) != userList.end();
}

bool bookExists(const vector<Book>& library, const string& isbn) {
    return find_if(library.begin(), library.end(), [&isbn](const Book& book) {
        return book.ISBN == isbn;
    }) != library.end();
}

void readBorrowFile(vector<Borrow>& borrowList){
	borrowList.clear();
    ifstream infile;
    infile.open("Muonsach.txt");
    while (infile >> ws) {
        Borrow borrow;
        getline(infile, borrow.username, '|');
        if (borrow.username.empty()) {
            break;
        }
        getline(infile, borrow.bookISBN, '|');
        getline(infile, borrow.bookTitle, '|');
        getline(infile, borrow.status, '|');
        getline(infile, borrow.time);
        borrowList.push_back(borrow);
    }
    infile.close();
}


void writeBorrowFile(const vector<Borrow>& borrowList) {
    ofstream outfile;
    outfile.open("muonsach.txt");  
    for (const Borrow& borrow : borrowList) {
        string timeStr = borrow.time;
        timeStr.erase(remove(timeStr.begin(), timeStr.end(), '\n'), timeStr.end());
        outfile << borrow.username << "|" << borrow.bookISBN << "|" << borrow.bookTitle << "|" << borrow.status << "|" << borrow.time << endl;
    }
    outfile.close();
}


void borrowBook(vector<User>& userList, vector<Book>& library, vector<Borrow>& borrowList) {
    readUserFile(userList);
    readBookFile(library);
    readBorrowFile(borrowList);

    string username, isbn;

    cout << "Nhap username: "; getline(cin, username);
    if (!userExists(userList, username)) {
        cout << "Username khong ton tai" << endl;
        return;
    }

    cout << "Nhap ma so sach (ISBN): "; getline(cin, isbn);
    if (!bookExists(library, isbn)) {
        cout << "Ma so sach khong ton tai" << endl;
        return;
    }
	
//	time_t result = time(nullptr);
//    string s = asctime(localtime(&result));


    for (Book& book : library) {
        if (book.ISBN == isbn) {
            if (book.copies > 0) {
                book.copies--;
                addBookFile(library);
                Borrow newBorrow{username, isbn, book.title, "Chua tra", getCurrentTime()};
                borrowList.push_back(newBorrow);
                writeBorrowFile(borrowList);
                cout << "Da muon sach thanh cong" << endl;
            } else {
                cout << "So luong sach khong du de muon" << endl;
            }
        }
    }
}


void returnBook(vector<User>& userList, vector<Book>& library, vector<Borrow>& borrowList) {
    readUserFile(userList);
    readBookFile(library);
    readBorrowFile(borrowList);

    string username, isbn;

    cout << "Nhap username: "; getline(cin, username);
    if (!userExists(userList, username)) {
        cout << "Username khong ton tai" << endl;
        return;
    }

    cout << "Nhap ma so sach (ISBN): "; getline(cin, isbn);
    if (!bookExists(library, isbn)) {
        cout << "Ma so sach khong ton tai" << endl;
        return;
    }

    for (Book& book : library) {
        if (book.ISBN == isbn) {
            auto it = find_if(borrowList.begin(), borrowList.end(), [username, isbn](const Borrow& borrow) {
                return borrow.username == username && borrow.bookISBN == isbn && borrow.status == "Chua tra";
            });

            if (it != borrowList.end()) {
                book.copies++;
                addBookFile(library);
                it->status = "Da tra";
                writeBorrowFile(borrowList);
                cout << "Da tra sach thanh cong" << endl;
            } else {
                cout << "Sach da duoc tra hoac ban chua muon sach nay" << endl;
            }
            return;
        }
    }
    cout << "Khong tim thay sach" << endl;
}


void showBorrowReturn(vector<Borrow>& borrowList) {
	readBorrowFile(borrowList);
	if (borrowList.empty()) {
        cout << "Khong tim thay danh sach muon/tra" << endl;
        return;
    }

    cout << left << setw(20) << "Username" << setw(15) << "ISBN" << setw(50) << "Title"
         << setw(15) << "Status" << setw(20) << "Date & Time" << endl;

    for (const Borrow& borrow : borrowList) {
        cout << left << setw(20) << borrow.username << setw(15) << borrow.bookISBN << setw(50) << borrow.bookTitle
             << setw(15) << borrow.status << setw(20) << borrow.time << endl;
    }
}

//---------------------

void showAdminMenu();
void normalUserMenu();
void showUserMenu();
void showbookMenu();

void adminMenu(vector<User>& userList, vector<Book>& library, vector<Borrow>& borrowList, string& perm);
void userMenu(vector<User>& userList);
void bookMenu(vector<Book>& library, vector<User>& userList, vector<Borrow>& borrowList);

int main() {
    vector<Book> library;
    vector<User> userList;
    vector<Borrow> borrowList;
    string perm;

    int mainChoice;
    do {
        cout << "----------- MENU CHINH -----------" << endl;
        cout << "1. Dang nhap......................" << endl;
        cout << "2. Xem sach trong thu vien........" << endl;
        cout << "3. Thoat.........................." << endl;
        cout << "Nhap lua chon: "; cin >> mainChoice; cin.ignore();

        switch (mainChoice) {
			case 1:
			    if (login(userList, perm) && perm == "user") {
			        system("cls"); cout << "Dang nhap thanh cong" << endl;
			        normalUserMenu();
			    } else if (perm == "admin") {
			        system("cls"); cout << "Dang nhap thanh cong" << endl;
			        adminMenu(userList, library, borrowList, perm);
			    }
   			 	break;
            case 2:
            	system("cls");
                showBook(library);
                break;
            case 3:
                exit(0);
            default:
                cout << "Lua chon khong hop le." << endl;
        }
    } while (true);

    return 0;
}

void showAdminMenu() {
	system("cls");
    cout << "----------- MENU ADMIN -----------" << endl;
    cout << "3. Quan li nguoi dung............." << endl;
    cout << "4. Quan li sach..................." << endl;
    cout << "5. Dang xuat......................" << endl;
    cout << "6. Thoat.........................." << endl;
}

void showUserMenu() {
	system("cls");
    cout << "----------- QUAN LI NGUOI DUNG -----------" << endl;
    cout << "1. Them nguoi dung........................" << endl;
    cout << "2. Sua thong tin nguoi dung..............." << endl;
    cout << "3. Xoa nguoi dung........................." << endl;
    cout << "4. Quay ve menu admin....................." << endl;
    cout << "5. Thoat.................................." << endl;
}

void showBookMenu() {
	system("cls");
    cout << "----------- QUAN LI SACH -----------" << endl;
    cout << "1. Xem sach........................." << endl;
    cout << "2. Tim kiem........................." << endl;
    cout << "3. Them sach........................" << endl;
    cout << "4. Sua sach........................." << endl;
    cout << "5. Xoa sach........................." << endl;
    cout << "6. Muon sach........................" << endl;
    cout << "7. Tra sach........................." << endl;
    cout << "8. Hien danh sach muon tra.........." << endl;
    cout << "9. Thoat............................" << endl;
}

void adminMenu(vector<User>& userList, vector<Book>& library, vector<Borrow>& borrowList, string& perm) {
    system("cls");
	int adminChoice;
    do {
        showAdminMenu();
        cout << "Nhap lua chon: "; cin >> adminChoice;
        cin.ignore();

        switch (adminChoice) {
            case 3:
            	system("cls");
                userMenu(userList);
                break;
            case 4:
            	system("cls");
                bookMenu(library, userList, borrowList);
                break;
            case 5:
            	system("cls");
                perm = "";
                break;
            case 6:
                exit(0);
            default:
                cout << "Lua chon khong hop le." << endl;
        }

    } while (adminChoice != 5);
}

void userMenu(vector<User>& userList) {
    system("cls");
	int userMenuChoice;
    bool backToAdminMenu = false;
    bool logout = false;
    char backToUserMenu;

    do {
        showUserMenu();
        cout << "Nhap lua chon: "; cin >> userMenuChoice;
        cin.ignore();

        switch (userMenuChoice) {
            case 1:
            	system("cls");
                addUser(userList);
        		cout << "Ban muon quay lai menu quan li nguoi dung? (y/n): "; cin >> backToUserMenu; cin.ignore();
        		if (backToUserMenu != 'y' && backToUserMenu != 'Y') {
            		system("cls");
					break;
        		}
                break;
            case 2:
            	system("cls");
                editUser(userList);
        		cout << "Ban muon quay lai menu quan li nguoi dung? (y/n): "; cin >> backToUserMenu; cin.ignore();
        		if (backToUserMenu != 'y' && backToUserMenu != 'Y') {
            		system("cls");
					break;
        		}
                break;
            case 3:
            	system("cls");
                deleteUser(userList);
        		cout << "Ban muon quay lai menu quan li nguoi dung? (y/n): "; cin >> backToUserMenu; cin.ignore();                
        		if (backToUserMenu != 'y' && backToUserMenu != 'Y') {
            		system("cls");
					break;
        		}
                break;
            case 4:
                backToAdminMenu = true;
                break;
            case 5:
                system("cls");
                return;
                break;
            default:
                cout << "Lua chon khong hop le." << endl;
        }


    } while (userMenuChoice != 4 && userMenuChoice != 5);
}



void bookMenu(vector<Book>& library, vector<User>& userList, vector<Borrow>& borrowList) {
    system("cls");
    string perm;
	int bookMenuChoice;
    bool backToAdminMenu = false;
    char backtoBookMenu;

    do {
        showBookMenu();
        cout << "Nhap lua chon: "; cin >> bookMenuChoice;
        cin.ignore();

        switch (bookMenuChoice) {
            case 1:
            	system("cls");
                showBook(library);
        		cout << "Ban muon quay lai menu quan li sach? (y/n): "; cin >> backtoBookMenu; cin.ignore();
        		if (backtoBookMenu != 'y' && backtoBookMenu != 'Y') {
        			system("cls");
            		break;
        		}
                break;
            case 3:
            	system("cls");
                addBook(library);
        		cout << "Ban muon quay lai menu quan li sach? (y/n): "; cin >> backtoBookMenu; cin.ignore();
        		if (backtoBookMenu != 'y' && backtoBookMenu != 'Y') {
        			system("cls");
            		break;
        		}
                break;
            case 4:
            	system("cls");
                editBook(library);
        		cout << "Ban muon quay lai menu quan li sach? (y/n): "; cin >> backtoBookMenu; cin.ignore();
        		if (backtoBookMenu != 'y' && backtoBookMenu != 'Y') {
        			system("cls");
            		break;
        		}
                break;
            case 5:
            	system("cls");
                deleteBook(library);
        		cout << "Ban muon quay lai menu quan li sach? (y/n): "; cin >> backtoBookMenu; cin.ignore();
        		if (backtoBookMenu != 'y' && backtoBookMenu != 'Y') {
        			system("cls");
            		break;
        		}
                break;
            case 8:
            	system("cls");
            	showBorrowReturn(borrowList);
        		cout << "Ban muon quay lai menu quan li sach? (y/n): "; cin >> backtoBookMenu; cin.ignore();
        		if (backtoBookMenu != 'y' && backtoBookMenu != 'Y') {
        			system("cls");
            		break;
        		}
        		break;
            case 9:
                exit(0);
                break;
            case 6:
            	system("cls");
            	borrowBook(userList, library, borrowList);
            	showBorrowReturn(borrowList);
        		cout << "Ban muon quay lai menu quan li sach? (y/n): "; cin >> backtoBookMenu; cin.ignore();
        		if (backtoBookMenu != 'y' && backtoBookMenu != 'Y') {
        			system("cls");
            		break;
        		}
        		break;
            case 7:
            	system("cls");
            	returnBook(userList, library, borrowList);
            	showBorrowReturn(borrowList);
        		cout << "Ban muon quay lai menu quan li sach? (y/n): "; cin >> backtoBookMenu; cin.ignore();
        		if (backtoBookMenu != 'y' && backtoBookMenu != 'Y') {
        			system("cls");
            		break;
        		}
        		break;
            case 2:
            	system("cls");
            	searchBook(library);
        		cout << "Ban muon quay lai menu quan li sach? (y/n): "; cin >> backtoBookMenu; cin.ignore();
        		if (backtoBookMenu != 'y' && backtoBookMenu != 'Y') {
        			system("cls");
            		break;
        		}
				break;       	
            default:
                cout << "Lua chon khong hop le." << endl;
        }

    } while (bookMenuChoice != 5 && bookMenuChoice != 6 && bookMenuChoice != 7);
}


void userMenuText(){
	system("cls");
    cout << "----------- USER MENU -----------" << endl;
    cout << "1. Xem sach......................" << endl;
    cout << "2. Tim kiem......................" << endl;
    cout << "3. Dang xuat....................." << endl;
    cout << "4. Thoat........................." << endl;
}


void normalUserMenu(){
    vector<Book> library;
    char backtoBookMenu;
    int userChoice;


    do {
    	userMenuText();
        cout << "Nhap lua chon: "; cin >> userChoice;
        cin.ignore();

        switch (userChoice) {
            case 1:
                system("cls");
                showBook(library);
                cout << "Ban muon quay lai menu? (y/n): "; cin >> backtoBookMenu;
                if (backtoBookMenu != 'y' && backtoBookMenu != 'Y') {
                    system("cls");
                    return;
                }
                break;
            case 2:
                system("cls");
                searchBook(library);
                cout << "Ban muon quay lai menu? (y/n): "; cin >> backtoBookMenu;
                if (backtoBookMenu != 'y' && backtoBookMenu != 'Y') {
                    system("cls");
                    return;
                }
                break;
            case 3:
                system("cls");
                return;
                break;
            case 4:
                system("cls");
                exit(0);
                break;
            default:
                cout << "Lua chon khong hop le." << endl;
        }

    } while (userChoice != 3);
}
