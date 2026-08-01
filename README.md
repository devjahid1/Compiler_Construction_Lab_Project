# Compiler Construction Lab Project

> A mini compiler developed for the Compiler Construction Lab course that performs lexical analysis, syntax analysis, abstract syntax tree generation, semantic analysis, symbol table management, and three-address code generation.

![Language](https://img.shields.io/badge/Language-C-blue.svg)
![Flex](https://img.shields.io/badge/Flex-Lexical%20Analyzer-orange.svg)
![Bison](https://img.shields.io/badge/Bison-Parser-green.svg)
![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20Ubuntu-lightgrey.svg)
![License](https://img.shields.io/badge/License-Educational-blue)

---

# 📌 Project Overview

This project is a simplified compiler developed for the **Compiler Construction Lab** course. It demonstrates the fundamental phases of compiler design using **Flex** and **Bison**.

The compiler accepts source code written in a simplified programming language and processes it through multiple compilation phases, including lexical analysis, syntax analysis, semantic analysis, Abstract Syntax Tree (AST) generation, Symbol Table management, and Three Address Code (TAC) generation.

---

# ✨ Features

- Lexical Analysis
- Syntax Analysis
- Abstract Syntax Tree (AST)
- Symbol Table Management
- Semantic Analysis
- Three Address Code (TAC) Generation
- Error Detection and Reporting

---

# ⚙️ Compiler Phases

## 1. Lexical Analysis

- Tokenizes source code
- Identifies keywords
- Detects identifiers
- Recognizes operators
- Processes constants
- Handles delimiters

---

## 2. Syntax Analysis

- Validates grammar rules
- Parses statements
- Builds Abstract Syntax Tree
- Reports syntax errors

---

## 3. Abstract Syntax Tree (AST)

- Generates Abstract Syntax Tree
- Represents program hierarchy
- Simplifies parsing output

---

## 4. Symbol Table

Maintains information such as:

- Variable Name
- Data Type
- Scope
- Declaration Line

---

## 5. Semantic Analysis

Performs semantic checking including:

- Variable declaration checking
- Undeclared variable detection
- Assignment validation

---

## 6. Three Address Code (TAC)

Generates intermediate code using temporary variables.

Example:

```text
a = 5
b = 10
t1 = a + b
c = t1
```

---

# 🛠 Technologies Used

- C Programming Language
- Flex (Lex)
- Bison (Yacc)
- GCC Compiler
- Ubuntu Linux

---

# 📂 Project Structure

```text
Compiler_Construction_Lab_Project/
│
├── src/
│   ├── ast/
│   │   ├── ast.c
│   │   ├── ast.h
│   │   └── ast_print.c
│   │
│   ├── lexer/
│   │   ├── lexer.l
│   │   ├── lexer_backup.l
│   │   └── lex.yy.c
│   │
│   ├── parser/
│   │   ├── parser.y
│   │   ├── parser.tab.c
│   │   ├── parser.tab.h
│   │   └── token.h
│   │
│   ├── semantic/
│   │   ├── semantic.c
│   │   └── semantic.h
│   │
│   ├── symbol_table/
│   │   ├── symbol_table.c
│   │   └── symbol_table.h
│   │
│   └── tac/
│       ├── tac.c
│       └── tac.h
│
├── tests/
├── CHANGELOG.md
├── FAQ.md
├── INSTALL.md
├── LICENSE
├── README.md
```

---

> The actual project structure may vary depending on implementation.

---

# 🚀 How to Run

## Step 1

Clone the repository

```bash
git clone https://github.com/devjahid1/Compiler_Construction_Lab_Project.git
```

---

## Step 2

Move into the project directory

```bash
cd Compiler_Construction_Lab_Project
```

---

## Step 3

Install dependencies

```bash
sudo apt update
sudo apt install flex bison gcc
```

---

## Step 4

Generate the parser

```bash
bison -d -o src/parser/parser.tab.c src/parser/parser.y
```

---

## Step 5

Generate the lexer

```bash
flex -o src/lexer/lex.yy.c src/lexer/lexer.l
```

---

## Step 6

Compile the project

```bash
gcc \
src/parser/parser.tab.c \
src/lexer/lex.yy.c \
src/ast/ast.c \
src/ast/ast_print.c \
src/semantic/semantic.c \
src/symbol_table/symbol_table.c \
src/tac/tac.c \
-lfl \
-o compiler
```

---

## Step 7

Run the compiler

```bash
./compiler
```

---

# 💻 Sample Input

```c
int a;
int b;
int c;

a = 5;
b = 10;
c = a + b;
```

---

# 📤 Sample Output

```text
PROGRAM (PROGRAM)
    DECLARATION (DECLARATION)
        IDENTIFIER (int)
        IDENTIFIER (a)
    DECLARATION (DECLARATION)
        IDENTIFIER (int)
        IDENTIFIER (b)
    DECLARATION (DECLARATION)
        IDENTIFIER (int)
        IDENTIFIER (c)
    ASSIGNMENT (=)
        IDENTIFIER (a)
        INTEGER (5)
    ASSIGNMENT (=)
        IDENTIFIER (b)
        INTEGER (10)
    ASSIGNMENT (=)
        BINARY_EXPR (+)
            IDENTIFIER (a)
            IDENTIFIER (b)

Symbol Table

Identifier       Type       Scope   Line
------------------------------------------------
c                int        0       3
b                int        0       2
a                int        0       1

Semantic Analysis Result: successful

Three Address Code

a = 5
b = 10
t1 = a + b
c = t1
```

---

# 📋 Project Output

The compiler successfully demonstrates:

- Lexical Analysis
- Syntax Analysis
- Abstract Syntax Tree (AST)
- Symbol Table Generation
- Semantic Analysis
- Three Address Code (TAC)
- Error Detection and Reporting

---

# 👨‍💻 Team Members

| Name | Student ID |
|------|------------|
| MD JAHID MIAH SUYEB | 231-115-281 |
| Hussain Adnan | 231-115-314 |
| Junaed Ahmed | 231-115-319 |

---

# 👨‍🏫 Course Information

**Course:** Compiler Construction Lab

**Department:** Computer Science & Engineering

**University:** Metropolitan University, Bangladesh

---

# ⭐ Acknowledgements

We sincerely express our gratitude to our respected course teacher for his valuable guidance, continuous support, and constructive feedback throughout the development of this project.
