#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include <float.h>
#include <math.h>


#define MAX_STRING_LENGTH 256

typedef struct Stop {
    char transport_number[MAX_STRING_LENGTH];
    char stop_time[MAX_STRING_LENGTH];
    char departure_time[MAX_STRING_LENGTH];
    char stop_type[MAX_STRING_LENGTH];
    double latitude;
    double longitude;
    struct Stop* next;
} Stop;

typedef struct Route {
    char transport_number[MAX_STRING_LENGTH];
    Stop* stops;
    struct Route* next;
} Route;

Route* routes_head = NULL;

void free_stops(Stop* head) {
    Stop* current = head;
    while (current != NULL) {
        Stop* next = current->next;
        free(current);
        current = next;
    }
}

void free_routes(Route* head) {
    Route* current = head;
    while (current != NULL) {
        Route* next = current->next;
        free_stops(current->stops);
        free(current);
        current = next;
    }
}

Stop* create_stop(const char* transport_number, const char* stop_time, const char* departure_time, const char* stop_type) {
    Stop* new_stop = (Stop*)malloc(sizeof(Stop));
    if (new_stop == NULL) {
        return NULL;
    }
    strncpy(new_stop->transport_number, transport_number, MAX_STRING_LENGTH);
    strncpy(new_stop->stop_time, stop_time, MAX_STRING_LENGTH);
    strncpy(new_stop->departure_time, departure_time, MAX_STRING_LENGTH);
    strncpy(new_stop->stop_type, stop_type, MAX_STRING_LENGTH);
    new_stop->next = NULL;
    return new_stop;
}

Route* create_route(const char* transport_number) {
    Route* new_route = (Route*)malloc(sizeof(Route));
    if (new_route == NULL) {
        return NULL;
    }
    strncpy(new_route->transport_number, transport_number, MAX_STRING_LENGTH);
    new_route->stops = NULL;
    new_route->next = NULL;
    return new_route;
}

void sort_stops(Route* route);


void add_stop_to_route(Route* route, Stop* stop) {
    if (route->stops == NULL) {
        route->stops = stop;
    } else {
        Stop* current = route->stops;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = stop;
    }
    sort_stops(route);
}

void add_route(Route** routes_head, Route* route) {
    if (*routes_head == NULL) {
        *routes_head = route;
    } else {
        Route* current = *routes_head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = route;
    }
}

Route* find_route(Route* routes_head, const char* transport_number) {
    Route* current = routes_head;
    while (current != NULL) {
        if (strcmp(current->transport_number, transport_number) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

int read_file(const char* file_path, Route** routes_head) {
    FILE* file = fopen(file_path, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: failed to open file %s\n", file_path);
        return -1;
    }

    char line[MAX_STRING_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        char transport_number[MAX_STRING_LENGTH];
        char stop_time[MAX_STRING_LENGTH];
        char departure_time[MAX_STRING_LENGTH];
        char stop_type[MAX_STRING_LENGTH];

        if (sscanf(line, "%s %s %s %s", transport_number, stop_time, departure_time, stop_type) != 4) {
            fprintf(stderr, "Error: invalid line format in file %s. Line: %s\n", file_path, line);
            fclose(file);
            return -2;
        }

        Route* route = find_route(*routes_head, transport_number);
        if (route == NULL) {
            route = create_route(transport_number);
            if (route == NULL) {
                fclose(file);
                return -3;
            }
            add_route(routes_head, route);
        }

        Stop* stop = create_stop(transport_number, stop_time, departure_time, stop_type);
        if (stop == NULL) {
            fclose(file);
            return -3;
        }
        add_stop_to_route(route, stop);
    }

    fclose(file);
    return 0;
}

int parse_time(const char* time_str, struct tm* time_struct) {
    return sscanf(time_str, "%d.%d.%d %d:%d:%d",
            &time_struct->tm_mday, &time_struct->tm_mon, &time_struct->tm_year,
            &time_struct->tm_hour, &time_struct->tm_min, &time_struct->tm_sec) == 6;
}

int compare_stops(const void* a, const void* b) {
    Stop* stop_a = *(Stop**)a;
    Stop* stop_b = *(Stop**)b;

    struct tm time_a, time_b;
    if (parse_time(stop_a->stop_time, &time_a) != 0 || parse_time(stop_b->stop_time, &time_b) != 0) {
        return 0;
    }

    time_t t_a = mktime(&time_a);
    time_t t_b = mktime(&time_b);

    if (t_a < t_b) {
        return -1;
    } else if (t_a > t_b) {
        return 1;
    } else {
        return 0;
    }
}

void sort_stops(Route* route) {
    if (route == NULL || route->stops == NULL || route->stops->next == NULL) {
        return;
    }

    Stop* current = route->stops;
    Stop* next = NULL;
    int swapped;

    do {
        swapped = 0;
        current = route->stops;

        while (current != NULL && current->next != NULL) {
            struct tm time_a, time_b;
            if (parse_time(current->stop_time, &time_a) == 0 && parse_time(current->next->stop_time, &time_b) == 0) {
                time_t t_a = mktime(&time_a);
                time_t t_b = mktime(&time_b);

                if (t_a > t_b) {
                    char temp[MAX_STRING_LENGTH];
                    strncpy(temp, current->stop_time, MAX_STRING_LENGTH);
                    strncpy(current->stop_time, current->next->stop_time, MAX_STRING_LENGTH);
                    strncpy(current->next->stop_time, temp, MAX_STRING_LENGTH);

                    swapped = 1;
                }
            }
            current = current->next;
        }
    } while (swapped);
}

Route* find_vehicle_by_route_count(Route* routes_head, int find_max) {
    Route* target_route = NULL;
    int target_count = find_max ? -1 : INT_MAX;

    Route* current = routes_head;
    while (current != NULL) {
        int stop_count = 0;
        Stop* stop = current->stops;
        while (stop != NULL) {
            stop_count++;
            stop = stop->next;
        }

        if ((find_max && stop_count > target_count) || (!find_max && stop_count < target_count)) {
            target_count = stop_count;
            target_route = current;
        }

        current = current->next;
    }
    return target_route;
}

double haversine_distance(double lat1, double lon1, double lat2, double lon2) {
    const double PI = 3.14159265358979323846;
    const double R = 6371.0;
    double dlat = (lat2 - lat1) * PI / 180.0;
    double dlon = (lon2 - lon1) * PI / 180.0;
    
    lat1 = lat1 * PI / 180.0;
    lat2 = lat2 * PI / 180.0;
    
    double a = sin(dlat / 2) * sin(dlat / 2) +
               cos(lat1) * cos(lat2) * sin(dlon / 2) * sin(dlon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    
    return R * c;
}

Route* find_vehicle_by_route_length(Route* routes_head, int find_max) {
    Route* target_route = NULL;
    double target_length = find_max ? -1.0 : DBL_MAX;

    Route* current = routes_head;
    while (current != NULL) {
        double total_length = 0.0;
        Stop* stop = current->stops;
        Stop* previous_stop = NULL;

        while (stop != NULL) {
            if (previous_stop != NULL) {
                total_length += haversine_distance(
                    previous_stop->latitude, previous_stop->longitude,
                    stop->latitude, stop->longitude
                );
            }
            previous_stop = stop;
            stop = stop->next;
        }

        if ((find_max && total_length > target_length) || (!find_max && total_length < target_length)) {
            target_length = total_length;
            target_route = current;
        }

        current = current->next;
    }

    return target_route;
}


int calculate_stop_duration(const char* arrival_time, const char* departure_time) {
    struct tm arrival, departure;
    if (parse_time(arrival_time, &arrival) != 0 || parse_time(departure_time, &departure) != 0) {
        return -1;
    }
    time_t arr_time = mktime(&arrival);
    time_t dep_time = mktime(&departure);
    return difftime(dep_time, arr_time);
}

Route* find_vehicle_by_stop_duration(Route* routes_head, int find_max) {
    Route* target_route = NULL;
    int target_duration = find_max ? -1 : INT_MAX;

    Route* current = routes_head;
    while (current != NULL) {
        Stop* stop = current->stops;
        while (stop != NULL) {
            int duration = calculate_stop_duration(stop->stop_time, stop->departure_time);
            if ((find_max && duration > target_duration) || (!find_max && duration < target_duration)) {
                target_duration = duration;
                target_route = current;
            }
            stop = stop->next;
        }
        current = current->next;
    }
    return target_route;
}

Route* find_vehicle_by_total_idle_time(Route* routes_head, int find_max) {
    Route* target_route = NULL;
    int target_idle_time = find_max ? -1 : INT_MAX;

    Route* current = routes_head;
    while (current != NULL) {
        int total_idle_time = 0;
        Stop* stop = current->stops;
        while (stop != NULL) {
            int idle_time = calculate_stop_duration(stop->stop_time, stop->departure_time);
            if (idle_time >= 0) {
                total_idle_time += idle_time;
            }
            stop = stop->next;
        }

        if ((find_max && total_idle_time > target_idle_time) || (!find_max && total_idle_time < target_idle_time)) {
            target_idle_time = total_idle_time;
            target_route = current;
        }

        current = current->next;
    }
    return target_route;
}

int count_stops(Route* route) {
    int count = 0;
    Stop* stop = route->stops;
    while (stop != NULL) {
        count++;
        stop = stop->next;
    }
    return count;
}

int main(int argc, char* argv[]) {
    Route* routes_head = NULL;

    if (argc < 2) {
        fprintf(stderr, "Error: Please specify at least one file as input.\n");
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        if (read_file(argv[i], &routes_head) != 0) {
            fprintf(stderr, "Error processing file %s\n", argv[i]);
            return 1;
        }
    }

    int choice;

    while (1) {
        printf("\nSelect search criterion (or choose '0' to exit):\n");
        printf("1. Vehicle with the most routes\n");
        printf("2. Vehicle with the fewest routes\n");
        printf("3. Vehicle with the longest route\n");
        printf("4. Vehicle with the shortest route\n");
        printf("5. Vehicle with the longest stop\n");
        printf("6. Vehicle with the shortest stop\n");
        printf("7. Vehicle with the longest idle time\n");
        printf("0. Exit\n");
        printf("Your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            fprintf(stderr, "Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        if (choice == 0) {
            printf("Exiting the program.\n");
            break;
        }

        Route* result = NULL;
        switch (choice) {
            case 1:
                result = find_vehicle_by_route_count(routes_head, 1);
                break;
            case 2:
                result = find_vehicle_by_route_count(routes_head, 0);
                break;
            case 3:
                result = find_vehicle_by_route_length(routes_head, 1);
                break;
            case 4:
                result = find_vehicle_by_route_length(routes_head, 0);
                break;
            case 5:
                result = find_vehicle_by_stop_duration(routes_head, 1);
                break;
            case 6:
                result = find_vehicle_by_stop_duration(routes_head, 0);
                break;
            case 7:
                result = find_vehicle_by_total_idle_time(routes_head, 1);
                break;
            default:
                printf("Invalid choice. Please select a number between 1 and 7.\n");
                continue;
        }

        if (result != NULL) {
            printf("Vehicle found: %s\n", result->transport_number);
            printf("Number of stops: %d\n", count_stops(result));
        } else {
            printf("Result not found.\n");
        }
    }

    free_routes(routes_head);

    return 0;
}