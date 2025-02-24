#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <wctype.h>

#define MAX_WORD_LENGTH 100

typedef struct Node {
    char word[MAX_WORD_LENGTH];
    int count;
    struct Node *left;
    struct Node *right;
} Node;

typedef enum {
    SUCCESS = 0,
    ERROR_MEMORY_ALLOCATION = 1,
    ERROR_FILE_OPEN = 2,
    ERROR_FILE_READ = 3,
    ERROR_FILE_WRITE = 4,
    ERROR_INVALID_ARGUMENT = 5,
    ERROR_INVALID_INPUT = 6,
    ERROR_FILE_NOT_FOUND = 7
} Status;


Status create_node(const char *word, Node **new_node) {
    *new_node = (Node *)malloc(sizeof(Node));
    if (!*new_node) {
        return ERROR_MEMORY_ALLOCATION;
    }
    strncpy((*new_node)->word, word, MAX_WORD_LENGTH);
    (*new_node)->count = 1;
    (*new_node)->left = (*new_node)->right = NULL;
    return SUCCESS;
}

Node *insert(Node *root, const char *word) {
    if (root == NULL) {
        Node *new_node = NULL;
        Status status = create_node(word, &new_node);
        if (status != SUCCESS) {
            return NULL;
        }
        if (!new_node) {
            return NULL;
        }
        return new_node;
    }

    int cmp = strcmp(word, root->word);
    if (cmp < 0) {
        root->left = insert(root->left, word);
    } else if (cmp > 0) {
        root->right = insert(root->right, word);
    } else {
        root->count++;
    }

    return root;
}

Node *search(Node *root, const char *word) {
    if (root == NULL) {
        return NULL;
    }

    int cmp = strcmp(word, root->word);
    if (cmp < 0) {
        return search(root->left, word);
    } else if (cmp > 0) {
        return search(root->right, word);
    } else {
        return root;
    }
}

void print_tree(Node *root) {
    if (root != NULL) {
        print_tree(root->left);
        printf("%s: %d\n", root->word, root->count);
        print_tree(root->right);
    }
}

void free_tree(Node *root) {
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

void clean_word(char *word) {
    int i = 0, j = 0;
    while (word[i] != '\0') {
        if (iswalpha(word[i])) {
            word[j++] = tolower(word[i]);
        }
        i++;
    }
    word[j] = '\0';
}

Status process_file(const char *filename, Node **root, char **separators, int sep_count) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        return ERROR_FILE_OPEN;
    }

    char word[MAX_WORD_LENGTH];
    while (fscanf(file, "%s", word) != EOF) {
        clean_word(word);
        if (strlen(word) > 0) {
            *root = insert(*root, word);
        }
    }

    fclose(file);
    return SUCCESS;
}


void query_word(Node *root) {
    char word[MAX_WORD_LENGTH];
    printf("Enter the word to search: ");
    scanf("%s", word);
    clean_word(word);

    Node *node = search(root, word);
    if (node) {
        printf("The word '%s' appears %d times.\n", word, node->count);
    } else {
        printf("The word '%s' was not found.\n", word);
    }
}

void collect_words(Node *root, Node **words_array, int *index) {
    if (root != NULL) {
        collect_words(root->left, words_array, index);
        words_array[*index] = root;
        (*index)++;
        collect_words(root->right, words_array, index);
} }

int compare(const void *a, const void *b) {
    Node *nodeA = *(Node **)a;
    Node *nodeB = *(Node **)b;
    return nodeB->count - nodeA->count;
}

void print_top_n(Node *root, int n) {
    Node *words_array[1000];
    int index = 0;
    collect_words(root, words_array, &index);
    qsort(words_array, index, sizeof(Node *), compare);
    printf("Displaying the top %d most frequent words:\n", n);
    for (int i = 0; i < n && i < index; i++) {
        printf("%s: %d\n", words_array[i]->word, words_array[i]->count);
    }
}

void find_longest_and_shortest(Node *root) {
    if (root == NULL) {
        printf("The tree is empty.\n");
        return;
    }

    Node *longest = root, *shortest = root;

    void find_words(Node *node) {
        if (node != NULL) {
            find_words(node->left);
            if (strlen(node->word) > strlen(longest->word)) {
                longest = node;
            }
            if (strlen(node->word) < strlen(shortest->word)) {
                shortest = node;
            }
            find_words(node->right);
        }
    }

    find_words(root);

    printf("The longest word: %s (length: %lu)\n", longest->word, strlen(longest->word));
    printf("The shortest word: %s (length: %lu)\n", shortest->word, strlen(shortest->word));
}

int find_depth(Node *root) {
    if (root == NULL) {
        return 0;
    }

    int left_depth = find_depth(root->left);
    int right_depth = find_depth(root->right);

    return (left_depth > right_depth ? left_depth : right_depth) + 1;
}

void save_tree_to_file(Node *root, FILE *file) {
    if (root == NULL) {
        fprintf(file, "NULL\n");
        return;
    }

    if (fprintf(file, "%s %d\n", root->word, root->count) < 0) {
        printf("Error: failed to write node to file.\n");
        return;
    }

    save_tree_to_file(root->left, file);
    save_tree_to_file(root->right, file);
}



Node *load_tree_from_file(FILE *file) {
    char word[MAX_WORD_LENGTH];
    int count;

    if (fscanf(file, "%s", word) != 1 || strcmp(word, "NULL") == 0) {
        return NULL;
    }

    if (fscanf(file, "%d", &count) != 1) {
        printf("Error: failed to read count for word '%s'.\n", word);
        return NULL;
    }

    Node *node = NULL;
    Status status = create_node(word, &node);
    if (status != SUCCESS) {
        return NULL;
    }

    if (!node) {
        return NULL;
    }
    node->count = count;
    node->left = load_tree_from_file(file);
    node->right = load_tree_from_file(file);

    return node;
}



Status save_to_file(Node *root, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        return ERROR_FILE_OPEN;
    }

    save_tree_to_file(root, file);
    fclose(file);
    printf("Tree saved to file: %s\n", filename);
    return SUCCESS;
}


void load_from_file(Node **root, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file for loading.\n");
        return;
    }

    *root = load_tree_from_file(file);
    fclose(file);
    printf("Tree loaded from file: %s\n", filename);
}

int check_file_exists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: unable to open file '%s'\n", filename);
        return -1;
    }
    fclose(file);
    return 0;
}

int validate_arguments(int argc) {
    if (argc < 3) {
        printf("Error: insufficient arguments. Usage: <program> <input_file> <separator1> [separator2 ...]\n");
        return -1;
    }
    return 0;
}


int main(int argc, char *argv[]) {
    Status status;

    if (validate_arguments(argc) != 0) {
        return 1;
    }

    const char *input_filename = argv[1];
    status = check_file_exists(input_filename);
    if (status != SUCCESS) {
        return 1;
    }

    Node *root = NULL;
    int sep_count = argc - 2;
    char **separators = argv + 2;

    status = process_file(input_filename, &root, separators, sep_count);
    if (status != SUCCESS) {
        printf("Error processing the file\n");
        return 1;
    }

    int choice;
    do {
        printf("Select an action:\n");
        printf("1. Search for a word\n");
        printf("2. Display top N words\n");
        printf("3. Find the longest and shortest word\n");
        printf("4. Find the depth of the tree\n");
        printf("5. Save the tree to file\n");
        printf("6. Load the tree from file\n");
        printf("0. Exit\n");
        
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Invalid input! Please enter a number between 0 and 6.\n");
            continue;
        }

        switch (choice) {
            case 1: {
                char word[MAX_WORD_LENGTH];
                printf("Enter the word to search: ");
                scanf("%s", word);
                clean_word(word);

                Node *node = search(root, word);
                if (node) {
                    printf("The word '%s' appears %d times.\n", word, node->count);
                } else {
                    printf("The word '%s' was not found.\n", word);
                }
                break;
            }
            case 2: {
                printf("Enter N: ");
                int n;
                scanf("%d", &n);
                print_top_n(root, n);
                break;
            }
            case 3: {
                find_longest_and_shortest(root);
                break;
            }
            case 4: {
                int depth = find_depth(root);
                printf("The depth of the tree is: %d\n", depth);
                break;
            }
            case 5: {
                char filename[MAX_WORD_LENGTH];
                printf("Enter filename to save the tree: ");
                scanf("%s", filename);
                status = save_to_file(root, filename);
                if (status != SUCCESS) {
                    printf("Error: unable to save tree to file.\n");
                }
                break;
            }
            case 6: {
                char filename[MAX_WORD_LENGTH];
                printf("Enter filename to load the tree: ");
                scanf("%s", filename);
                load_from_file(&root, filename);
                if (status != SUCCESS) {
                    printf("Error: unable to load tree from file.\n");
                }
                break;
            }

            case 0: {
                printf("Exiting\n");
                break;
            }
            default:
                printf("Invalid choice\n");
        }
    } while (choice != 0);

    free_tree(root);
    return 0;
}
