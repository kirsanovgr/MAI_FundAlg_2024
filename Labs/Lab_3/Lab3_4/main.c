#include "post.h"
#include "my_string.h"
int main() {
    Post post = {0};  // Инициализация структуры поста
    int choice;

    while (1) {
        printf("\nВыберите действие:\n");
        printf("1. Добавить новое отправление\n");
        printf("2. Удалить отправление\n");
        printf("3. Найти отправление по почтовому идентификатору\n");
        printf("4. Показать все доставленные отправления\n");
        printf("5. Показать все просроченные отправления\n");
        printf("6. Выйти\n");
        printf("Ваш выбор: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                // Добавить новое отправление
                Mail mail;
                int result = Mail_create(&mail);
                if (result == STRING_SUCCESS) {
                    Post_add_mail(&post, &mail);
                    printf("Отправление добавлено успешно.\n");
                } else {
                    printf("Ошибка при создании отправления.\n");
                }
                break;
            }
            case 2: {
                // Удалить отправление
                int index;
                printf("Введите индекс отправления для удаления: ");
                scanf("%d", &index);
                int result = Post_remove_mail(&post, index);
                if (result == STRING_SUCCESS) {
                    printf("Отправление удалено успешно.\n");
                } else {
                    printf("Ошибка при удалении отправления.\n");
                }
                break;
            }
            case 3: {
                // Найти отправление по почтовому идентификатору
                char postal_id[15];
                printf("Введите почтовый идентификатор: ");
                scanf("%14s", postal_id);
                
                int found = 0;
                for (int i = 0; i < post.mail_count; i++) {
                    if (strcmp(post.mails[i].postal_id.data, postal_id) == 0) {
                        printf("Отправление найдено: %s, %s\n", post.mails[i].address.recipient_id.data, postal_id);
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    printf("Отправление с данным почтовым идентификатором не найдено.\n");
                }
                break;
            }
            case 4: {
                // Показать все доставленные отправления
                Post_display_delivered(&post);
                break;
            }
            case 5: {
                // Показать все просроченные отправления
                Post_display_undelivered(&post);
                break;
            }
            case 6:
                // Выход из программы
                Post_destroy(&post);
                printf("Программа завершена.\n");
                return 0;
            default:
                printf("Некорректный выбор. Попробуйте снова.\n");
                break;
        }
    }
}
