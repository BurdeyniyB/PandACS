#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Структура для представлення відділів підприємства
struct Department {
    string name; // Назва відділу
    vector<Department*> subDepartments; // Вектор для зберігання підвідділів

    // Конструктор для створення відділу з вказаною назвою
    Department(const string& n) : name(n) {}

    // Деструктор для видалення всіх підвідділів
    ~Department() {
        for (Department* dept : subDepartments) {
            delete dept;
        }
    }
};

// Функція для виведення дерева відділів на екран
void printTree(Department* parentDept, int level = 0) {
    if (!parentDept) return;
    // Виводимо відступ, щоб показати ієрархію відділів
    for (int i = 0; i < level; ++i) {
        cout << "  ";
    }   
    // Виводимо назву поточного відділу
    cout << parentDept->name << endl;
    // Рекурсивно виводимо всі підвідділи цього відділу
    if (!parentDept->subDepartments.empty()) {
        for (Department* subDept : parentDept->subDepartments) {
            printTree(subDept, level + 1);
        }
    } 
}


void printPartTree(Department* parentDept, string departmentsName, int level = 0) {
    if(parentDept->name == departmentsName || level != 0){
        if (!parentDept) return;
        // Виводимо відступ, щоб показати ієрархію відділів
        for (int i = 0; i < level; ++i) {
            cout << "  ";
        }   
        // Виводимо назву поточного відділу
        cout << parentDept->name << endl;
        // Рекурсивно виводимо всі підвідділи цього відділу
        if (!parentDept->subDepartments.empty()) {
            for (Department* subDept : parentDept->subDepartments) {
                printPartTree(subDept, departmentsName, level + 1);
            }
        } 
    }
    else{
        if (!parentDept->subDepartments.empty()) {
            for (Department* subDept : parentDept->subDepartments) {
                printPartTree(subDept, departmentsName);
            }
        } else {
            cout << "No departments" << endl;
        }
    }
}

// Функція для додавання нового відділу до певного батьківського відділу
void addDepartment(Department* parentDept, string departmentsName) {
    // Створюємо новий відділ з введеною назвою
    if(parentDept->name == departmentsName){
        cout << "Enter name for the new department: ";
        string name;
        cin >> name;
        Department* newDept = new Department(name);
        // Додаємо новий відділ до підвідділів батьківського відділу
        parentDept->subDepartments.push_back(newDept);
        cout << "Department '" << name << "' added to '" << parentDept->name << "'" << endl;
    } 
    else{
        if(!parentDept->subDepartments.empty()) {
            for (Department* dept : parentDept->subDepartments) {
                addDepartment(dept, departmentsName);
            }
        }else{
            cout << "No departament" << endl;
        }
    }
}

// Функція для видалення певного відділу з підвідділами
void deleteDepartment(Department* parentDept, string departmentsName) {
    if(parentDept->name == departmentsName){
        cout << "Enter the index of the department to delete: ";
        int index;
        cin >> index;
        // Перевіряємо, чи індекс є коректним
        if (index >= 0 && index < parentDept->subDepartments.size()) {
            // Отримуємо відділ, який потрібно видалити
            Department* deptToDelete = parentDept->subDepartments[index];
            // Видаляємо відділ з підвідділами
            parentDept->subDepartments.erase(parentDept->subDepartments.begin() + index);
            // Звільняємо пам'ять, зайняту відділом і його підвідділами
            delete deptToDelete;
            cout << "Department deleted successfully." << endl;
        } else {
            cout << "Invalid index." << endl;
        }
    }else{
        if(!parentDept->subDepartments.empty()) {
            for (Department* dept : parentDept->subDepartments) {
                deleteDepartment(dept, departmentsName);
            }
        }else{
            cout << "No departament" << endl;
        }
    }
}

int main() {
    // Створюємо кореневий відділ підприємства
    Department* root = new Department("Company");

    bool done = false;
    // Головний цикл програми
    while (!done) {
        // Виводимо меню користувачу
        cout << "\n1. Print Tree\n2. Print part of tree\n3. Add Department\n4. Delete Department\n5. Quit\nEnter your choice: ";
        int choice;
        cin >> choice;

    string departmentsName; // Оголошення змінної перед switch-блоком

    switch (choice) {
        case 1:
            // Виводимо структуру всього дерева відділів
            cout << "Company Structure:" << endl;
            printTree(root);
            break;
        case 2:
            cout << "Enter name of department which you want to print: ";
            cin >> departmentsName; // Зчитуємо значення для departmentsName
            // Виводимо структуру всього дерева відділів
            cout << "Company Structure:" << endl;
            printPartTree(root, departmentsName);
            break;
        case 3:
            // Додаємо новий відділ
            cout << "Enter name of department which you want to add new departament: ";
            cin >> departmentsName; // Зчитуємо значення для departmentsName
            addDepartment(root, departmentsName);
            break;
        case 4:
            // Видаляємо існуючий відділ
            cout << "Enter name of department which you want to delete departament: ";
            cin >> departmentsName;
            deleteDepartment(root, departmentsName);
            break;
        case 5:
            // Виходимо з програми
            done = true;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
    }
    }

    // Звільняємо пам'ять, зайняту деревом відділів
    delete root;
    return 0;
}
