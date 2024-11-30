#include "post.h"
#include "my_string.h"

int Mail_create(Mail *mail) {
    if (!mail) {
        return STRING_ALLOCATION_ERROR;
    }

    printf("Введите город: ");
    char city[100];
    scanf("%99s", city);
    String_create(&mail->address.city, city);

    printf("Введите улицу: ");
    char street[100];
    scanf("%99s", street);
    String_create(&mail->address.street, street);

    printf("Введите номер дома: ");
    scanf("%d", &mail->address.house_number);

    printf("Введите корпус: ");
    char building[100];
    scanf("%99s", building);
    String_create(&mail->address.building, building);

    printf("Введите номер квартиры: ");
    scanf("%d", &mail->address.apartment);

    printf("Введите идентификатор получателя: ");
    char recipient_id[100];
    scanf("%99s", recipient_id);
    String_create(&mail->address.recipient_id, recipient_id);

    printf("Введите вес посылки: ");
    scanf("%lf", &mail->weight);

    printf("Введите почтовый идентификатор (14 цифр): ");
    char postal_id[15];
    scanf("%14s", postal_id);
    String_create(&mail->postal_id, postal_id);

    time_t now = time(NULL);
    mail->creation_time = *localtime(&now);

    mail->delivery_time.tm_year = 0;
    mail->delivery_time.tm_mon = 0;
    mail->delivery_time.tm_mday = 0;

    char delivery_time_str[20];
    printf("Введите дату доставки (формат: ДД:ММ:ГГГГ ЧЧ:ММ:СС): ");
    scanf("%19s", delivery_time_str);

    sscanf(delivery_time_str, "%d:%d:%d %d:%d:%d", 
           &mail->delivery_time.tm_mday, &mail->delivery_time.tm_mon, &mail->delivery_time.tm_year,
           &mail->delivery_time.tm_hour, &mail->delivery_time.tm_min, &mail->delivery_time.tm_sec);

    mail->delivery_time.tm_mon -= 1;  // В структуре tm месяцы от 0 до 11
    mail->delivery_time.tm_year -= 1900;  // В структуре tm год от 1900

    return STRING_SUCCESS;
}



int Post_add_mail(Post *post, const Mail *mail) {
    if (!post || !mail) {
        return STRING_ALLOCATION_ERROR;
    }

    Mail *new_mails = realloc(post->mails, (post->mail_count + 1) * sizeof(Mail));
    if (!new_mails) {
        return STRING_ALLOCATION_ERROR;
    }
    post->mails = new_mails;
    post->mails[post->mail_count] = *mail;
    post->mail_count++;

    return STRING_SUCCESS;
}

int Post_remove_mail(Post *post, int index) {
    if (!post || index < 0 || index >= post->mail_count) {
        return STRING_ALLOCATION_ERROR;
    }
    String_destroy(&post->mails[index].address.city);
    String_destroy(&post->mails[index].address.street);
    String_destroy(&post->mails[index].address.building);
    String_destroy(&post->mails[index].address.recipient_id);
    String_destroy(&post->mails[index].postal_id);

    for (int i = index; i < post->mail_count - 1; i++) {
        post->mails[i] = post->mails[i + 1];
    }

    post->mail_count--;
    post->mails = realloc(post->mails, post->mail_count * sizeof(Mail));

    return STRING_SUCCESS;
}

// Компаратор для сортировки посылок
int Mail_compare(const Mail *mail1, const Mail *mail2) {
    int recipient_cmp = String_compare(&mail1->address.recipient_id, &mail2->address.recipient_id);
    if (recipient_cmp != 0) {
        return recipient_cmp;
    }
    return String_compare(&mail1->postal_id, &mail2->postal_id);
}

// Сортировка посылок в посте
void Post_sort_mails(Post *post) {
    if (!post) {
        return;
    }
    for (int i = 0; i < post->mail_count - 1; i++) {
        for (int j = i + 1; j < post->mail_count; j++) {
            if (Mail_compare(&post->mails[i], &post->mails[j]) > 0) {
                Mail temp = post->mails[i];
                post->mails[i] = post->mails[j];
                post->mails[j] = temp;
            }
        }
    }
}

void Post_display_delivered(const Post *post) {
    printf("Доставленные посылки:\n");
    for (int i = 0; i < post->mail_count; i++) {
        // Если год доставки не равен 0, значит посылка доставлена
        if (post->mails[i].delivery_time.tm_year != 0) {
            printf("Получатель: %s, Почтовый идентификатор: %s\n", post->mails[i].address.recipient_id.data, post->mails[i].postal_id.data);
        }
    }
}

void Post_display_undelivered(const Post *post) {
    printf("Недоставленные посылки:\n");
    for (int i = 0; i < post->mail_count; i++) {
        // Если год доставки равен 0, значит посылка не доставлена
        if (post->mails[i].delivery_time.tm_year == 0) {
            printf("Получатель: %s, Почтовый идентификатор: %s\n", post->mails[i].address.recipient_id.data, post->mails[i].postal_id.data);
        }
    }
}


// Установить доставку для посылки
int Post_deliver_mail(Post *post, int index) {
    if (!post || index < 0 || index >= post->mail_count) {
        return STRING_ALLOCATION_ERROR;
    }

    time_t now = time(NULL);
    post->mails[index].delivery_time = *localtime(&now);

    printf("Посылка с почтовым идентификатором %s доставлена.\n", post->mails[index].postal_id.data);
    return STRING_SUCCESS;
}

void Post_destroy(Post *post) {
    for (int i = 0; i < post->mail_count; i++) {
        String_destroy(&post->mails[i].address.city);
        String_destroy(&post->mails[i].address.street);
        String_destroy(&post->mails[i].address.building);
        String_destroy(&post->mails[i].address.recipient_id);
        String_destroy(&post->mails[i].postal_id);
    }
    free(post->mails);
    post->mail_count = 0;
    post->mails = NULL;
}