#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

typedef struct {
    char* data;
    int length;
} String;

String createString(const char* str) {
    String s;
    s.length = strlen(str);
    s.data = (char*)malloc(s.length + 1);
    if (!s.data) {
        printf("Memory allocation failed!\n");
        return (String){NULL, 0};
    }
    strcpy(s.data, str);
    return s;
}

void deleteString(String* s) {
    if (s && s->data) {
        free(s->data);
        s->data = NULL;
        s->length = 0;
    }
}

String copyStringToNew(const String* source) {
    return createString(source->data);
}

String concatenateStrings(const String* s1, const String* s2) {
    String result;
    result.length = s1->length + s2->length;
    result.data = (char*)malloc(result.length + 1);
    if (!result.data) {
        printf("Memory allocation failed!\n");
        return (String){NULL, 0};
    }
    strcpy(result.data, s1->data);
    strcat(result.data, s2->data);
    return result;
}

int compareStrings(const String* s1, const String* s2) {
    return strcmp(s1->data, s2->data);
}

typedef struct {
    String city;
    String street;
    int houseNumber;
    String building;
    int apartmentNumber;
    String index;
} Address;

typedef struct {
    Address recipient;
    double weight;
    String postalId;
    String creationTime;
    String deliveryTime;
    int delivered;
} Mail;

typedef struct {
    Mail* mails;
    int mailCount;
} Post;

int addMailToPost(Post* post, Mail mail) {
    Mail* temp = (Mail*)realloc(post->mails, (post->mailCount + 1) * sizeof(Mail));
    if (!temp) {
        printf("Memory allocation failed!\n");
        return -1;
    }
    post->mails = temp;
    post->mails[post->mailCount] = mail;
    post->mailCount++;
    return 0;
}

Mail* findMailById(Post* post, const String* postalId) {
    for (int i = 0; i < post->mailCount; i++) {
        if (compareStrings(&post->mails[i].postalId, postalId) == 0) {
            return &post->mails[i];
        }
    }
    return NULL;
}

void printMailDetails(const Mail* mail) {
    printf("City: %s\n", mail->recipient.city.data);
    printf("Street: %s\n", mail->recipient.street.data);
    printf("House Number: %d\n", mail->recipient.houseNumber);
    printf("Building: %s\n", mail->recipient.building.data);
    printf("Apartment Number: %d\n", mail->recipient.apartmentNumber);
    printf("Index: %s\n", mail->recipient.index.data);
    printf("Weight: %.2f\n", mail->weight);
    printf("Postal ID: %s\n", mail->postalId.data);
    printf("Creation Time: %s\n", mail->creationTime.data);
    printf("Delivery Time: %s\n", mail->deliveryTime.data);
    printf("Delivered: %s\n", mail->delivered ? "Yes" : "No");
}

void printMails(const Post* post) {
    for (int i = 0; i < post->mailCount; i++) {
        printf("Mail %d:\n", i + 1);
        printMailDetails(&post->mails[i]);
        printf("\n");
    }
}

void freeMail(Mail* mail) {
    deleteString(&mail->recipient.city);
    deleteString(&mail->recipient.street);
    deleteString(&mail->recipient.building);
    deleteString(&mail->recipient.index);
    deleteString(&mail->postalId);
    deleteString(&mail->creationTime);
    deleteString(&mail->deliveryTime);
}

void freePost(Post* post) {
    for (int i = 0; i < post->mailCount; i++) {
        freeMail(&post->mails[i]);
    }
    free(post->mails);
    post->mailCount = 0;
}

int isNaturalNumber(const char* str) {
    if (*str == '\0') return 0;
    while (*str) {
        if (!isdigit(*str)) return 0;
        str++;
    }
    return 1;
}

int isSixDigitIndex(const char* str) {
    return strlen(str) == 6 && isNaturalNumber(str);
}

String getDateTimeString() {
    int day, month, year, hour, minute, second;
    while (1) {
        printf("Enter date and time (dd:MM:yyyy hh:mm:ss): ");
        if (scanf("%2d:%2d:%4d %2d:%2d:%2d", &day, &month, &year, &hour, &minute, &second) == 6) {
            if (day >= 1 && day <= 31 && month >= 1 && month <= 12 &&
                year >= 1900 && year <= 2100 && hour >= 0 && hour <= 23 &&
                minute >= 0 && minute <= 59 && second >= 0 && second <= 59) {

                char buffer[20];
                snprintf(buffer, sizeof(buffer), "%02d:%02d:%04d %02d:%02d:%02d",
                         day, month, year, hour, minute, second);
                while (getchar() != '\n');
                return createString(buffer);
            }
        } else {
            while (getchar() != '\n');
        }
        printf("Invalid date and time format. Please use dd:MM:yyyy hh:mm:ss.\n");
    }
}

int isDeliveryTimePassed(const String* deliveryTimeStr) {
    struct tm deliveryTime = {0};
    sscanf(deliveryTimeStr->data, "%2d:%2d:%4d %2d:%2d:%2d", 
           &deliveryTime.tm_mday, &deliveryTime.tm_mon, &deliveryTime.tm_year, 
           &deliveryTime.tm_hour, &deliveryTime.tm_min, &deliveryTime.tm_sec);
    
    deliveryTime.tm_mon -= 1;
    deliveryTime.tm_year -= 1900;

    time_t currentTime;
    time(&currentTime);
    struct tm* now = localtime(&currentTime);

    struct tm current = *now;

    // Compare times
    return difftime(mktime(&current), mktime(&deliveryTime)) > 0;
}

int compareMails(const void* a, const void* b) {
    const Mail* mailA = (const Mail*)a;
    const Mail* mailB = (const Mail*)b;

    int indexComparison = compareStrings(&mailA->recipient.index, &mailB->recipient.index);
    if (indexComparison != 0) {
        return indexComparison;
    }
    return compareStrings(&mailA->postalId, &mailB->postalId);
}

void sortMails(Post* post) {
    qsort(post->mails, post->mailCount, sizeof(Mail), compareMails);
}

void printDeliveredMails(const Post* post) {
    int found = 0;
    for (int i = 0; i < post->mailCount; i++) {
        if (post->mails[i].delivered) {
            printf("Delivered Mail:\n");
            printMailDetails(&post->mails[i]);
            printf("\n");
            found = 1;
        }
    }
    if (!found) {
        printf("No delivered mails found.\n");
    }
}

void printUndeliveredMails(const Post* post) {
    int found = 0;
    for (int i = 0; i < post->mailCount; i++) {
        if (!post->mails[i].delivered) {
            printf("Undelivered Mail:\n");
            printMailDetails(&post->mails[i]);
            printf("\n");
            found = 1;
        }
    }
    if (!found) {
        printf("No undelivered mails found.\n");
    }
}


int main() {
    Post post = {NULL, 0};
    String command;
    char buffer[BUFSIZ];

    while (1) {
        printf("Enter command (add, find, list, delete, delivered, undelivered, exit): ");
        if (scanf("%s", buffer) != 1) {
            printf("Failed to read command.\n");
            continue;
        }
        getchar();
        command = createString(buffer);

        if (compareStrings(&command, &(String){"add", 3}) == 0) {
            Mail mail = {0};
            mail.delivered = 0;

            printf("Enter city: ");
            scanf("%s", buffer);
            getchar();
            mail.recipient.city = createString(buffer);
            if (mail.recipient.city.length == 0) {
                printf("City cannot be empty.\n");
                deleteString(&mail.recipient.city);
                continue;
            }

            printf("Enter street: ");
            scanf("%s", buffer);
            getchar();
            mail.recipient.street = createString(buffer);
            if (mail.recipient.street.length == 0) {
                printf("Street cannot be empty.\n");
                deleteString(&mail.recipient.street);
                continue;
            }

            printf("Enter house number (natural number): ");
            while (scanf("%d", &mail.recipient.houseNumber) != 1 || mail.recipient.houseNumber <= 0) {
                printf("Invalid input. Please enter a natural number for the house number: ");
                while (getchar() != '\n');
            }
            getchar();

            printf("Enter building number: ");
            scanf("%s", buffer);
            getchar();
            mail.recipient.building = createString(buffer);
            if (mail.recipient.building.length == 0) {
                printf("Building cannot be empty.\n");
                deleteString(&mail.recipient.building);
                continue;
            }

            printf("Enter apartment number (natural number): ");
            while (scanf("%d", &mail.recipient.apartmentNumber) != 1 || mail.recipient.apartmentNumber <= 0) {
                printf("Invalid input. Please enter a natural number for the apartment number: ");
                while (getchar() != '\n');
            }
            getchar();

            printf("Enter postal index (6 digits): ");
            scanf("%s", buffer);
            getchar();
            if (!isSixDigitIndex(buffer)) {
                printf("Invalid postal index. It must be a string of 6 digits.\n");
                continue;
            }
            mail.recipient.index = createString(buffer);

            printf("Enter weight (non-negative number): ");
            while (scanf("%lf", &mail.weight) != 1 || mail.weight < 0) {
                printf("Invalid input. Please enter a non-negative number for the weight: ");
                while (getchar() != '\n');
            }
            getchar();

            printf("Enter postal ID (14 digits): ");
            scanf("%s", buffer);
            getchar();
            if (strlen(buffer) != 14 || !isNaturalNumber(buffer)) {
                printf("Invalid postal ID. It must be a string of 14 digits.\n");
                continue;
            }
            mail.postalId = createString(buffer);

            mail.creationTime = getDateTimeString();
            mail.deliveryTime = getDateTimeString();

            if (addMailToPost(&post, mail) == -1) {
                freeMail(&mail);
                continue;
            }

            if (isDeliveryTimePassed(&mail.deliveryTime)) {
                post.mails[post.mailCount - 1].delivered = 1;
            }

            printf("Mail added successfully.\n");
        } else if (compareStrings(&command, &(String){"find", 4}) == 0) {
            printf("Enter postal ID to find: ");
            scanf("%s", buffer);
            getchar();
            String postalId = createString(buffer);
            Mail* foundMail = findMailById(&post, &postalId);
            if (foundMail) {
                printf("Found mail with postal ID %s:\n", postalId.data);
                printMailDetails(foundMail);
            } else {
                printf("Mail with postal ID %s not found.\n", postalId.data);
            }
            deleteString(&postalId);
        } else if (compareStrings(&command, &(String){"list", 4}) == 0) {
            printMails(&post);
        } else if (compareStrings(&command, &(String){"delete", 6}) == 0) {
            printf("Enter postal ID to delete: ");
            scanf("%s", buffer);
            getchar();
            String postalId = createString(buffer);
            Mail* mailToDelete = findMailById(&post, &postalId);
            if (mailToDelete) {
                *mailToDelete = post.mails[post.mailCount - 1];
                post.mailCount--;
                post.mails = realloc(post.mails, post.mailCount * sizeof(Mail));
                printf("Mail with postal ID %s deleted successfully.\n", postalId.data);
            } else {
                printf("Mail with postal ID %s not found.\n", postalId.data);
            }
            deleteString(&postalId);
        } else if (compareStrings(&command, &(String){"delivered", 8}) == 0) {
            printDeliveredMails(&post);
        } else if (compareStrings(&command, &(String){"undelivered", 10}) == 0) {
            printUndeliveredMails(&post);
        } else if (compareStrings(&command, &(String){"exit", 4}) == 0) {
            break;
        } else {
            printf("Unknown command.\n");
        }

        deleteString(&command);
    }

    freePost(&post);
    return 0;
}
