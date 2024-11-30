#ifndef POST_H
#define POST_H

#include "my_string.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct {
    String city;        
    String street;
    int house_number;
    String building;
    int apartment;
    String recipient_id;
} Address;

typedef struct {
    Address address;
    String postal_id;
    double weight;
    struct tm creation_time;
    struct tm delivery_time;
} Mail;

typedef struct {
    Mail *mails;
    int mail_count;
    struct tm current_time;
} Post;


int Mail_create(Mail *mail);
int Post_add_mail(Post *post, const Mail *mail);
int Post_remove_mail(Post *post, int index);
int Post_deliver_mail(Post *post, int index);
void Post_sort_mails(Post *post);
void Post_display_delivered(const Post *post);
void Post_display_undelivered(const Post *post);
void Post_destroy(Post *post);
void Post_init(Post *post);

#endif