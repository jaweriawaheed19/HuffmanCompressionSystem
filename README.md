# 🗜️ Huffman Compression System

![C++](https://img.shields.io/badge/C%2B%2B-17-blue)
![DSA Project](https://img.shields.io/badge/DSA-Project-green)
![Algorithm](https://img.shields.io/badge/Algorithm-Huffman%20Coding-orange)
![Status](https://img.shields.io/badge/Status-Completed-success)

## 📖 Overview

A C++ implementation of the **Huffman Coding Algorithm** for lossless text compression and decompression.

This project demonstrates the practical application of **Greedy Algorithms**, **Binary Trees**, and **Priority Queues (Min-Heaps)** to efficiently compress text files by assigning variable-length binary codes based on character frequencies.

The system supports:

- Text file compression (Encoding)
- Text file decompression (Decoding)
- Character frequency analysis
- Huffman code generation
- Compression statistics
- Huffman Tree visualization

## ✨ Features

✔ Encode text files using Huffman Coding

✔ Decode compressed files back to original text

✔ Generate and display character frequency tables

✔ Generate Huffman codes for all characters

✔ Display compression statistics

✔ Export Huffman Tree structure to a text file

✔ Interactive menu-driven console interface

✔ Colored terminal output for improved readability

## 🧠 Data Structures & Concepts Used

### Data Structures

- Priority Queue (Min Heap)
- Binary Tree
- Unordered Map (Hash Table)
- String Manipulation
- File Handling

### Algorithms

- Huffman Coding
- Greedy Algorithm
- Tree Traversal
- Binary Encoding & Decoding

## ⚙️ How It Works

### Compression Process

1. Read text from the input file.
2. Calculate frequency of each character.
3. Build a Huffman Tree using a Min Heap.
4. Generate unique Huffman codes.
5. Encode the original text.
6. Save encoded data and frequency information.

### Decompression Process

1. Load encoded data and stored frequencies.
2. Reconstruct the Huffman Tree.
3. Decode the binary sequence.
4. Restore the original text.

## 📂 Project Structure

```text
.
├── source.cpp
├── DSA.sln
├── encoded.txt
├── decoded.txt
├── huffman_tree.txt
├── input1.txt
├── input2.txt
└── README.md
```

## 📋 Menu Options

```text
========================================
     HUFFMAN COMPRESSION SYSTEM
========================================

1) Encode (Compress)
2) Decode (Decompress)
3) Show Last Character Frequency Table
4) Show Last Huffman Codes
5) Exit
```

## 📄 Generated Files

### encoded.txt

Stores:

- Character frequency table
- Encoded binary data

### decoded.txt

Stores:

- Restored original text after decompression

### huffman_tree.txt

Stores:

- Visual representation of the Huffman Tree

Example:

```text
*(100)
/-- a(45)
\-- *(55)
    /-- b(25)
    \-- c(30)
```

## 📊 Compression Statistics

The system displays:

- Original file size (Bytes)
- Compressed file size (Bytes)
- Original bit count
- Compressed bit count
- Average bits per character
- Compression ratio (%)

## 🎯 Learning Outcomes

This project demonstrates:

- Huffman Coding
- Greedy Algorithm Design
- Binary Trees
- Priority Queues (Min Heaps)
- Hash Maps
- File Handling in C++
- Lossless Data Compression Techniques
- Time & Space Complexity Analysis

## 🔮 Future Enhancements

- Binary file compression support
- Graphical User Interface (GUI)
- Support for larger datasets
- Real-time tree visualization
- Performance benchmarking
- Compression of additional file formats

## Author

*Jaweria Waheed Satti*

- Student – BS Computer Science  
- [LinkedIn](https://www.linkedin.com/in/jaweriasatti19)  
- [Email](mailto:jaweriasatti19@gmail.com)

##  License

This project is released under the MIT License.
