# Reconciliation Challenge

This project reads permissions from two CSV files, compares them, and writes the differences to an output file. The permissions are stored in a hash table for efficient lookup.

## Requirements

- GCC (or any C compiler)
- Make (optional, for using a Makefile)

## Files

- `main.c`: The main source code file containing the reconciliation logic.

## Compilation

To compile the code, you can use the following command:

```bash
gcc -o reconcile main.c
```

This will generate an executable named `reconcile`.

## Usage

To run the executable, use the following command:

```bash
./reconcile <app_csv_path> <idms_csv_path> <output_file_path>
```

- `<app_csv_path>`: Path to the CSV file containing the application permissions.
- `<idms_csv_path>`: Path to the CSV file containing the IDMS permissions.
- `<output_file_path>`: Path to the output file where the differences will be written.

## Example

```bash
./reconcile app_permissions.csv idms_permissions.csv differences.csv
```

## CSV File Format

The CSV files should have the following format:

```
group1,user1
group2,user2
...
```

## Error Handling

- If the input files cannot be opened, an error message will be displayed, and the program will exit.
- If the output file cannot be opened, an error message will be displayed, and the program will exit.
- If the number of arguments is incorrect, a usage message will be displayed.

## Code Overview

### Hash Function

The `hash` function calculates a hash value for a given group and user.

### Permission Structure

The `Permission` structure represents a permission entry with a group, user, and a pointer to the next entry.

### Functions

- `create_permission`: Creates a new permission node.
- `insert_permission`: Inserts a permission node into the hash table.
- `find_permission`: Finds a permission in the hash table.
- `read_permissions`: Reads permissions from a file and inserts them into the hash table.
- `compare_permissions`: Compares the permissions in the two hash tables and writes the differences to an output file.

### Main Function

The `main` function checks the command-line arguments, reads permissions from the input files, compares the permissions, and writes the differences to the output file.

## Notes

- The hash table size is defined as `HASH_SIZE` and set to 320003, which is double the expected list size.
- The code uses separate hash tables for application permissions (`app_table`) and IDMS permissions (`idms_table`).
