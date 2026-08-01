# Compiler Construction Lab Project

> A mini compiler developed for the Compiler Construction Lab course that performs lexical analysis, syntax analysis, abstract syntax tree generation, semantic analysis, symbol table management, and three-address code generation.

![Language](https://img.shields.io/badge/Language-C-blue.svg)
![Flex](https://img.shields.io/badge/Flex-Lexical%20Analyzer-orange.svg)
![Bison](https://img.shields.io/badge/Bison-Parser-green.svg)
![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20Ubuntu-lightgrey.svg)
![License](https://img.shields.io/badge/License-Educational-blue)

---

## 📌 Project Overview

This project is a simplified compiler built as part of the **Compiler Construction Lab** course. It demonstrates the major phases of compilation, starting from lexical analysis to intermediate code generation.

The compiler accepts source code written in a simplified programming language and processes it through multiple compiler phases while reporting lexical, syntax, and semantic errors.

---

## ✨ Features

- Lexical Analysis
- Syntax Analysis
- Abstract Syntax Tree (AST)
- Symbol Table Management
- Semantic Analysis
- Type Checking
- Three-Address Code (TAC) Generation
- Error Detection and Reporting

---

## ⚙️ Compiler Phases

### 1. Lexical Analysis
- Tokenizes source code
- Identifies keywords
- Detects identifiers
- Recognizes operators
- Processes constants
- Handles delimiters

---

### 2. Syntax Analysis
- Validates grammar rules
- Parses statements
- Builds parse structure
- Reports syntax errors

---

### 3. Abstract Syntax Tree (AST)
- Generates AST
- Represents program hierarchy
- Simplifies parsing output

---

### 4. Symbol Table
Maintains information such as:

- Variable Name
- Data Type
- Scope
- Declaration Status
- Memory Information

---

### 5. Semantic Analysis

Performs semantic checking including:

- Variable declaration checking
- Multiple declaration detection
- Undeclared variable detection
- Type mismatch detection
- Assignment validation

---

### 6. Three Address Code (TAC)

Generates intermediate code using quadruple-style instructions.

Example:

```
t1 = b * c
t2 = a + t1
x = t2
```

---

## 🛠 Technologies Used

- C Programming Language
- Flex (Lex)
- Bison (Yacc)
- GCC
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
├── Makefile
├── README.md
└── Project_Report.pdf
```

---


> The actual project structure may vary depending on implementation.

---

## 🚀 How to Run

### Step 1

Clone the repository

```bash
git clone https://github.com/devjahid1/Compiler_Construction_Lab_Project.git
```

### Step 2

Move into project directory

```bash
ccd Compiler_Construction_Lab_Project
```

### Step 3

Generate lexer

```bash
flex lexer.l
```

### Step 4

Generate parser

```bash
bison -d parser.y
```

### Step 5

Compile

```bash
gcc parser.tab.c lex.yy.c *.c -o compiler
```

### Step 6

Run

```bash
./compiler
```

---

## 💻 Sample Input

```c
int x;
float y;

y = 5.5;

x = y;
```

---

## 📤 Sample Output

```
Lexical Analysis Successful

Syntax Analysis Successful

Abstract Syntax Tree Generated

Semantic Error:
Type mismatch in assignment.

Three Address Code:

t1 = 5.5
y = t1
x = y
```

---

## 📸 Screenshots

Add screenshots of:

- Lexical Analysis
- AST
- Symbol Table
- Semantic Analysis
- TAC Output

---


## 👨‍💻 Team Members

| Name | ID |
|------|------|
| MD JAHID MIAH SUYEB | 231-115-281 |
| Hussain Adnan | 231-115-314 |
| Junaed Ahmed | 231-115-319 |

---

## 👨‍🏫 Course Information

**Course:** Compiler Construction Lab

**Department:** Computer Science & Engineering

**University:** Metropolitan University

---


## ⭐ Acknowledgements

Special thanks to our course teacher for guidance and support throughout the project.
