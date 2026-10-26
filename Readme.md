# Address Book System in C

A modular, console-based contact management application written in C. This program provides full CRUD (Create, Read, Update, Delete) functionality with strict real-time input validation, duplicate prevention, file persistence, and an aligned, minimalist ASCII terminal interface.

---

## Table of Contents

- [Features](#features)
- [Architecture & Design](#architecture--design)
- [Project Structure](#project-structure)
- [Validation Rules](#validation-rules)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Compilation](#compilation)
  - [Running the Application](#running-the-application)
- [Usage & Workflow](#usage--workflow)
- [File Storage Format](#file-storage-format)
- [License](#license)

---

## Features

- **Create Contact**: Add entries with multi-stage input validation for names, phone numbers, and email addresses.
- **Search Contact**: Flexible lookup by name, 10-digit phone number, or email address.
- **Edit Contact**: Modify existing contact attributes without altering unedited fields.
- **Delete Contact**: Remove entries with memory/index reordering.
- **List All Contacts**: Formatted tabular overview of all saved records with column spacing and contact count.
- **File Persistence**: Automatic disk storage and loading (`Address_data.txt`) to preserve contact data across sessions.
- **Minimalist Terminal UI**: Clean ASCII formatting, clear status indicators (`[-]`, `[!]`), and distraction-free prompts.

---

## Architecture & Design

The project is structured using clean separation of concerns:
- **Modular Design**: Business logic, file I/O operations, mock data generation, and driver execution are split across dedicated translation units.
- **Memory Safety**: Uses bounded buffer readers (`%49[^\n]`, `%19[^\n]`) to prevent buffer overflow vulnerabilities.
- **Data Encapsulation**: Contacts are encapsulated within standard C structures (`Contact` and `AddressBook`) passed via pointers to minimize memory overhead.

---

## Project Structure

```text
.
├── contact.c          # Core business logic, validation routines, and CRUD routines
├── contact.h          # Data structures (Contact, AddressBook) and function declarations
├── file.c             # Persistent storage handlers (saveContactsToFile, loadContactsFromFile)
├── file.h             # Prototypes for file operations
├── main.c             # Entry point and interactive command-line loop
├── populate.c         # Sample/mock contact generator for initial bootstrapping
├── populate.h         # Declaration for default contact population
├── Address_data.txt   # File-based database storage
└── README.md          # Project documentation
```

---

## Validation Rules

To prevent corrupted records and ensure high data integrity, the system enforces the following constraints:

1. **Name**:
   - Must contain only alphabetic letters and single spaces.
   - Cannot be blank or contain numbers/special symbols.
2. **Phone Number**:
   - Must be exactly 10 numeric digits.
   - Duplicate phone numbers are rejected.
3. **Email Address**:
   - Must follow standard format (`username@domain.extension`).
   - Requires valid placement of `@` and `.` delimiters.
   - Enforces lowercase transformation and checks for uniqueness against existing records.

---

## Getting Started

### Prerequisites

You need a C compiler supporting the C99 standard or higher (such as GCC, Clang, or MinGW).

Check your installation:
```bash
gcc --version
```

### Compilation

Compile all translation units together using GCC:

```bash
gcc *.c -o addressbook
```

*On Windows PowerShell / Command Prompt:*
```powershell
gcc *.c -o addressbook.exe
```

### Running the Application

Execute the compiled binary:

**Linux / macOS:**
```bash
./addressbook
```

**Windows:**
```powershell
.\addressbook.exe
```

---

## Usage & Workflow

Upon launching the application, you are greeted by the main interface:

```text
  =====================================
              ADDRESS BOOK             
  =====================================
    1. Create contact
    2. Search contact
    3. Edit contact
    4. Delete contact
    5. List all contacts
    6. Save and Exit
  -------------------------------------
  Select an option > 
```

### Typical Workflow
1. **List Records**: Press `5` to view existing contacts loaded from file or seed data.
2. **Add Entry**: Press `1` and follow step-by-step prompts. If an invalid value is supplied, the terminal provides immediate feedback and prompts for re-entry.
3. **Search & Update**: Use option `2` to find records or options `3` and `4` to update/delete specific entries.
4. **Persist & Quit**: Select `6` to serialize your changes to disk and terminate safely.

---

## File Storage Format

Contacts are serialized in a plain-text structure (`Address_data.txt`) using the following layout:

```text
#<total_count>#
<Name>,<Phone>,<Email>
<Name>,<Phone>,<Email>
```

**Example:**
```text
#2#
John Doe,9876543210,john.doe@example.com
Jane Smith,9123456780,jane.smith@example.com
```

This format ensures simple parsing, stream safety, and backward compatibility.

---

## License

This project is open-source and available under the [MIT License](LICENSE).