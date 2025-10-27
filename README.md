# 🔐 File Encryptor-Decrypter (C Program)
A simple command-line tool written in C that encrypts and decrypts text files using two basic cipher techniques.<br>
It demonstrates concepts of **file handling**, **string manipulation**, and **basic cryptography** in C.

---

## 📘 Project Overview
This program allows you to **encrypt** or **decrypt** any `.txt` file using two methods:<br>
- **Method A:** Offset (Caesar) cipher — shifts every character by a fixed offset value.  
- **Method B:** Substitution cipher — performs character substitution (customizable).  

It automatically identifies whether a file is already encrypted by checking its filename and performs the appropriate operation (encryption or decryption).<br>
Example:  
`notes.txt → notes-encrypted-a.txt → notes.txt`  

---

## ⚙️ Features
✔️ Supports both **encryption** and **decryption** modes.<br>
✔️ Detects encryption tags in filenames (`-encrypted-a`, `-encrypted-b`).<br>
✔️ Handles file renaming automatically after each operation.<br>
✔️ Demonstrates modular C programming (separate functions for each task).<br>
✔️ Uses file I/O operations (`fopen`, `fgetc`, `fputc`, `rename`, `remove`).<br>
✔️ Beginner-friendly and easy to understand.<br>

---

## 🧩 Encryption Methods

### 🔸 Method A — Offset Cipher
- Each character in the file is shifted by a user-defined offset value.  
- Example: with offset = 2  
  - A → C  
  - B → D  
  - a → c  
- To decrypt, the same offset is subtracted.

### 🔸 Method B — Substitution Cipher
- Each character is replaced by another based on a mapping array.  
- Currently, it uses an identity map (no actual substitution).  
- You can easily modify it to create your own substitution logic.

---

## 💻 How to Compile
Run the following command in your terminal:
```bash
gcc main.c -o encryptor.exe

