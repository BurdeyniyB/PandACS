#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Person {
    char surname[15];
    char name[50];
    char patronymic[50];
    char address[100];
    char phone[20];
    int age;
};

void inputPerson(struct Person *p) {
    printf("Прізвище: ");
    scanf("%s", p->surname);
    printf("Ім'я: ");
    scanf("%s", p->name);
    printf("По батькові: ");
    scanf("%s", p->patronymic);
    printf("Домашня адреса: ");
    scanf("%s", p->address);
    printf("Номер телефону: ");
    scanf("%s", p->phone);
    printf("Вік: ");
    scanf("%d", &p->age);
    printf("\n");
}

void printPerson(struct Person *p) {
    printf("Прізвище: %s\n", p->surname);
    printf("Ім'я: %s\n", p->name);
    printf("По батькові: %s\n", p->patronymic);
    printf("Домашня адреса: %s\n", p->address);
    printf("Номер телефону: %s\n", p->phone);
    printf("Вік: %d\n", p->age);
    printf("\n");
}

int main() {
    int num_people;

    printf("Введіть кількість людей: ");
    scanf("%d", &num_people);
    printf("\n");

    printf("Розмірність масиву структур: %d\n\n", num_people);
    printf("Розмірність структури Person: %lu байт\n\n", sizeof(struct Person));

    struct Person *people = (struct Person*)malloc(num_people * sizeof(struct Person));
    if (people == NULL) {
        fprintf(stderr, "Помилка виділення пам'яті.\n");
        return 1;
    }

    for (int i = 0; i < num_people; i++) {
        printf("Дані для людини %d:\n", i + 1);
        inputPerson(&people[i]);
    }

    FILE *file = fopen("structdata.bin", "wb");
    if (file == NULL) {
        fprintf(stderr, "Помилка відкриття файлу для запису.\n");
        return 1;
    }

    fwrite(people, sizeof(struct Person), num_people, file);
    fclose(file);
    free(people);

    printf("Дані про людей:\n\n");

    file = fopen("structdata.bin", "rb");
    if (file == NULL) {
        fprintf(stderr, "Помилка відкриття файлу для читання.\n");
        return 1;
    }

    struct Person person;
    int search_index;
    do {
        printf("Введіть номер людини (1-%d): ", num_people);
        scanf("%d", &search_index);
    } while (search_index < 1 || search_index > num_people);

    fseek(file, (search_index - 1) * sizeof(struct Person), SEEK_SET);
    fread(&person, sizeof(struct Person), 1, file);
    printPerson(&person);

    fclose(file);

    printf("Ім'я файлу: structdata.bin\n\n");
    printf("Автор програми: Бурдейний Борис\n");
    printf("Індекс академічної групи: ТР-31\n");

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    printf("Поточний рік: %d\n", t->tm_year + 1900);

    return 0;
}
