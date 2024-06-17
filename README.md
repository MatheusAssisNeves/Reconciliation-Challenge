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
