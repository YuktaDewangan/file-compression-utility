# File Compression Utility (Run-Length Encoding) – C++

## 📌 Overview

This project implements a simple file compression and decompression utility using the Run-Length Encoding (RLE) algorithm in C++.

Run-Length Encoding is a lossless compression technique that reduces file size by replacing consecutive repeated characters with a single character followed by its count.

This project demonstrates:
- File handling using C++ streams
- Implementation of a basic compression algorithm
- String processing and frequency counting
- Error handling
- Time complexity analysis

---

## 🚀 How It Works

### 🔹 Compression

Example:

Input file content:
aaabbbbccdddddd

Compressed output:
a3b4c2d6

The program:
1. Reads characters sequentially.
2. Counts consecutive repetitions.
3. Writes character + count to output file.

---

### 🔹 Decompression

Compressed file:
a3b4c2d6

Decompressed output:
aaabbbbccdddddd

The program:
1. Reads character-count pairs.
2. Expands each character according to its frequency.
3. Writes reconstructed data to output file.

---

## 🛠 Technologies Used

- C++17
- iostream
- fstream
- string
- sstream

---

## ⚙️ Compilation

g++ -std=c++17 rle.cpp -o rle

---

## ▶️ Execution

./rle

Then choose:
1 → Compress
2 → Decompress

Enter input and output file names when prompted.

---

## 📊 Time Complexity

Compression: O(n)  
Decompression: O(n)  

Where n is the number of characters in the file.

The algorithm processes the file in a single pass.

---

## 📁 Project Structure

RLE_Compressor/
│
├── rle.cpp
├── input.txt
├── compressed.txt
├── decompressed.txt
└── README.md

---

## ⚠️ Limitations

- Best suited for text files with repeated characters.
- Not efficient for highly random data.
- Currently supports character-based encoding only.

---

## 🎯 Learning Outcomes

- Understanding of lossless compression techniques
- Practical implementation of frequency encoding
- Efficient file input/output handling
- Algorithm complexity analysis

---

## 🔮 Future Improvements

- Add compression ratio calculation
- Support binary file compression
- Implement advanced algorithms (e.g., Huffman Coding)
- Add command-line argument support

---

## 👩‍💻 Author

Yukta Dewangan  
M.Tech – Computer Science and Engineering  
VIT Chennai
