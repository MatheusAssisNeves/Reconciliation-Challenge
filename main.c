#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 128
#define HASH_SIZE 320003    //set to double the expected list size

typedef struct Permission {
    char group[64];
    char user[64];
    struct Permission *next;
} Permission;

//Calculates the hash value for a given group and user.
unsigned int hash(char *group, char *user) {
    unsigned int hash_value = 0;
    while (*group) hash_value = (hash_value << 5) + *group++;
    while (*user) hash_value = (hash_value << 5) + *user++;
    return hash_value % HASH_SIZE;
}

//Creates a new node for  given group and user.
Permission* create_permission(char *group, char *user) {
    Permission *new_perm = (Permission*) malloc(sizeof(Permission));
    strcpy(new_perm->group, group);
    strcpy(new_perm->user, user);
    new_perm->next = NULL;
    return new_perm;
}


//Inserts permission node into the hash table.
void insert_permission(Permission **table, char *group, char *user) {
    unsigned int index = hash(group, user);
    Permission *new_perm = create_permission(group, user);
    new_perm->next = table[index];
    table[index] = new_perm;
}

//Finds a permission in the hash table.
int find_permission(Permission **table, char *group, char *user) {
    unsigned int index = hash(group, user);
    Permission *current = table[index];
    while (current) {
        if (strcmp(current->group, group) == 0 && strcmp(current->user, user) == 0) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

//Reads permissions from a file and inserts them into the hash table.
void read_permissions(const char *file_path, Permission **table) {
    FILE *file = fopen(file_path, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        char group[64], user[64];
        if (sscanf(line, "%63[^,],%63s", group, user) == 2) {
            insert_permission(table, group, user);
        }
    }

    fclose(file);
}

//Compares the permissions in the two hash tables and writes the differences to an output file.
void compare_permissions(Permission **app_table, Permission **idms_table, FILE *output) {
    for (int i = 0; i < HASH_SIZE; i++) {
        Permission *current = app_table[i];
        while (current) {
            if (!find_permission(idms_table, current->group, current->user)) {
                fprintf(output, "%s,%s,REMOVE\n", current->group, current->user);
            }
            current = current->next;
        }
    }

    for (int i = 0; i < HASH_SIZE; i++) {
        Permission *current = idms_table[i];
        while (current) {
            if (!find_permission(app_table, current->group, current->user)) {
                fprintf(output, "%s,%s,ADD\n", current->group, current->user);
            }
            current = current->next;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <app_csv_path> <idms_csv_path> <output_file_path>\n", argv[0]);
        return EXIT_FAILURE;
    }

    Permission *app_table[HASH_SIZE] = {0};
    Permission *idms_table[HASH_SIZE] = {0};

    read_permissions(argv[1], app_table);
    read_permissions(argv[2], idms_table);

    FILE *output = fopen(argv[3], "w");
    if (!output) {
        perror("Error opening output file");
        return EXIT_FAILURE;
    }

    compare_permissions(app_table, idms_table, output);

    return EXIT_SUCCESS;
}
