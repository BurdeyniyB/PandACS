#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
using namespace std;

struct Buyer {
    string surname;
    string name;
    string patronymic;
    char gender;
    string nationality;
    float height;
    float weight;
    string dateOfBirth;
    string phoneNumber;
    struct Address {
        string postalCode;
        string country;
        string region;
        string district;
        string city;
        string street;
        string house;
        string apartment;
    } homeAddress;
    string creditCardNumber;
    string bankAccountNumber;
};

struct List {
    Buyer buyer;
    List* next;
};

void Insert(List** u, Buyer& x);
void Print(List* u, int odessa);
void Delete(List** u, Buyer& x);
void Clear(List** u);
void newBuyer(List** u);
void ExportBuyer(List* u, const string& filename);
void ImportBuyer(List** u, const string& filename);

int main() {
    int n;
    bool b = true;
    bool f = true;
    char r;
    List* u = nullptr;

    setlocale(LC_ALL, "rus");



    while (b) {
        cout << "Enter menu item: " << endl;
        cout << " 1 - Add data to the list" << endl;
        cout << " 2 - Print the list on the screen" << endl;
        cout << " 3 - Find buyer from Odessa" << endl;
        cout << " 4 - Delete a buyer" << endl;
        cout << " 5 - Clear the entire list" << endl;
        cout << " 6 - Export data to a file" << endl;
        cout << " 7 - Import data from a file" << endl;
        cout << " 8 - Exit the program" << endl;
        cin >> n;
        switch (n) {
        case 1: {
            system("cls");
            newBuyer(&u);
            cout << "Would you like to continue? Enter any key (except Enter), or 0 to exit." << endl;
            cin >> r;
            if (r == '0') {
                f = false;
                system("pause");
                system("cls");
            }
            break;
        }
        case 2: {
            system("cls");
            Print(u, 0);
            system("pause");
            system("cls");
            break;
        }
        case 3: {
            system("cls");
            Print(u, 1);
            system("pause");
            system("cls");
            break;
        }
        case 4: {
            Buyer toDelete;
            cout << "Enter the buyer's surname and name to delete: ";
            cin >> toDelete.surname >> toDelete.name;
            Delete(&u, toDelete);
            break;
        }
        case 5: {
            Clear(&u);
            break;
        }
        case 6: {
            ExportBuyer(u, "Buyers.txt");
            cout << "Data exported successfully." << endl;
            break;
        }
        case 7: {
            Clear(&u); 
            ImportBuyer(&u, "Buyers.txt");
            cout << "Data imported successfully." << endl;
            break;
        }
        case 8: {
            b = false;
            break;
        }
        default: {
            cout << "Enter the correct menu item, please try again." << endl;
            break;
        }
        }
    }

    return 0;
}

void Insert(List** u, Buyer& x) {
    List* p = new List;
    p->buyer = x;
    p->next = *u;
    *u = p;
}

void Print(List* u, int odesa) {
    List* p = u;
    while (p) {
        if ((p->buyer.homeAddress.city == "Odesa" && odesa) || !odesa) {
            cout << "Surname: " << p->buyer.surname << endl;
            cout << "Name: " << p->buyer.name << endl;
            cout << "Patronymic: " << p->buyer.patronymic << endl;
            cout << "Gender: " << p->buyer.gender << endl;
            cout << "Nationality: " << p->buyer.nationality << endl;
            cout << "Height: " << p->buyer.height << endl;
            cout << "Weight: " << p->buyer.weight << endl;
            cout << "Date of Birth: " << p->buyer.dateOfBirth << endl;
            cout << "Phone Number: " << p->buyer.phoneNumber << endl;
            cout << "Home Address: " << endl;
            cout << "Postal Code: " << p->buyer.homeAddress.postalCode << endl;
            cout << "Country: " << p->buyer.homeAddress.country << endl;
            cout << "Region: " << p->buyer.homeAddress.region << endl;
            cout << "District: " << p->buyer.homeAddress.district << endl;
            cout << "City: " << p->buyer.homeAddress.city << endl;
            cout << "Street: " << p->buyer.homeAddress.street << endl;
            cout << "House: " << p->buyer.homeAddress.house << endl;
            cout << "Apartment: " << p->buyer.homeAddress.apartment << endl;
            cout << "Credit Card Number: " << p->buyer.creditCardNumber << endl;
            cout << "Bank Account Number: " << p->buyer.bankAccountNumber << endl;
            cout << "---------------------" << endl;
        }
        p = p->next;
    }
}

void Delete(List** u, Buyer& x) {
    if (*u == nullptr) {
        cout << "List is empty. Cannot delete." << endl;
        return;
    }

    List* prev = nullptr;
    List* curr = *u;

    while (curr != nullptr) {
        if (curr->buyer.surname == x.surname && curr->buyer.name == x.name) {
            if (prev == nullptr) {
                *u = curr->next; // If the node to delete is the first one
            }
            else {
                prev->next = curr->next; // If the node to delete is not the first one
            }
            delete curr;
            cout << "Buyer deleted successfully." << endl;
            return;
        }
        prev = curr;
        curr = curr->next;
    }

    cout << "Buyer not found. Deletion failed." << endl;
}

void Clear(List** u) {
    List* curr = *u;
    List* next;

    while (curr != nullptr) {
        next = curr->next;
        delete curr;
        curr = next;
    }

    *u = nullptr;
    cout << "List cleared successfully." << endl;
}

void newBuyer(List** u) {
    Buyer newBuyer;
    cout << "Enter buyer's data:" << endl;
    cout << "Surname: ";
    cin >> newBuyer.surname;
    cout << "Name: ";
    cin >> newBuyer.name;
    cout << "Patronymic: ";
    cin >> newBuyer.patronymic;
    cout << "Gender: ";
    cin >> newBuyer.gender;
    cout << "Nationality: ";
    cin >> newBuyer.nationality;
    cout << "Height: ";
    cin >> newBuyer.height;
    cout << "Weight: ";
    cin >> newBuyer.weight;
    cout << "Date of Birth (YYYY-MM-DD): ";
    cin >> newBuyer.dateOfBirth;
    cout << "Phone Number: ";
    cin >> newBuyer.phoneNumber;
    cout << "Postal Code: ";
    cin >> newBuyer.homeAddress.postalCode;
    cout << "Country: ";
    cin >> newBuyer.homeAddress.country;
    cout << "Region: ";
    cin >> newBuyer.homeAddress.region;
    cout << "District: ";
    cin >> newBuyer.homeAddress.district;
    cout << "City: ";
    cin >> newBuyer.homeAddress.city;
    cout << "Street: ";
    cin >> newBuyer.homeAddress.street;
    cout << "House: ";
    cin >> newBuyer.homeAddress.house;
    cout << "Apartment: ";
    cin >> newBuyer.homeAddress.apartment;
    cout << "Credit Card Number: ";
    cin >> newBuyer.creditCardNumber;
    cout << "Bank Account Number: ";
    cin >> newBuyer.bankAccountNumber;

    Insert(u, newBuyer);
}

void ExportBuyer(List* u, const string& filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cerr << "Unable to open file " << filename << " for writing." << endl;
        return;
    }

    List* p = u;
    while (p) {
        outFile << p->buyer.name << ","
            << p->buyer.surname << ","
            << p->buyer.patronymic << ","
            << p->buyer.dateOfBirth << ","
            << p->buyer.phoneNumber << ","
            << p->buyer.homeAddress.postalCode << ","
            << p->buyer.homeAddress.country << ","
            << p->buyer.homeAddress.region << ","
            << p->buyer.homeAddress.district << ","
            << p->buyer.homeAddress.city << ","
            << p->buyer.homeAddress.street << ","
            << p->buyer.homeAddress.house << ","
            << p->buyer.homeAddress.apartment << ","
            << p->buyer.creditCardNumber << ","
            << p->buyer.bankAccountNumber << endl;
        p = p->next;
    }

    outFile.close();
}
void ImportBuyer(List** u, const string& filename) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cerr << "Unable to open file " << filename << " for reading." << endl;
        return;
    }

    Clear(u);
    Buyer newBuyer;
    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        getline(ss, newBuyer.surname, ',');
        getline(ss, newBuyer.name, ',');
        getline(ss, newBuyer.patronymic, ',');
        ss >> newBuyer.gender;
        ss.ignore();
        getline(ss, newBuyer.nationality, ',');
        ss >> newBuyer.height;
        ss.ignore();
        ss >> newBuyer.weight;
        ss.ignore();
        getline(ss, newBuyer.dateOfBirth, ',');
        getline(ss, newBuyer.phoneNumber, ',');
        getline(ss, newBuyer.homeAddress.postalCode, ',');
        getline(ss, newBuyer.homeAddress.country, ',');
        getline(ss, newBuyer.homeAddress.region, ',');
        getline(ss, newBuyer.homeAddress.district, ',');
        getline(ss, newBuyer.homeAddress.city, ',');
        getline(ss, newBuyer.homeAddress.street, ',');
        getline(ss, newBuyer.homeAddress.house, ',');
        getline(ss, newBuyer.homeAddress.apartment, ',');
        getline(ss, newBuyer.creditCardNumber, ',');
        getline(ss, newBuyer.bankAccountNumber, ',');

        Insert(u, newBuyer);
    }

    inFile.close();
}