// Simple Run-Length Encoding (RLE) file compression/decompression utility.
// Compiles with: g++ -std=c++17 rle.cpp -o rle

#include <iostream>
#include <fstream>
#include <string>

// Compress inputFile into outputFile using a simple byte-based RLE scheme.
// Encoding format: [count byte][data byte] repeated.
// 'count' is in range [1, 255] and represents how many times the following byte repeats.
void compressFile(const std::string &inputFile, const std::string &outputFile) {
    std::ifstream in(inputFile, std::ios::binary);
    if (!in) {
        std::cerr << "Error: Could not open input file \"" << inputFile << "\" for reading.\n";
        return;
    }

    std::ofstream out(outputFile, std::ios::binary);
    if (!out) {
        std::cerr << "Error: Could not open output file \"" << outputFile << "\" for writing.\n";
        return;
    }

    // Read the first byte; if file is empty, nothing to do.
    int first = in.get();
    if (!in) {
        std::cout << "Input file is empty. Nothing to compress.\n";
        return;
    }

    char current = static_cast<char>(first);

    // Process the file as runs of repeated bytes.
    while (true) {
        unsigned char runLength = 1;  // At least one occurrence of 'current' is already read.

        // Extend the run while the same byte repeats and runLength < 255.
        while (runLength < 255) {
            int nextInt = in.get();
            if (!in) {
                // Reached EOF or read error, end current run.
                break;
            }

            char next = static_cast<char>(nextInt);
            if (next == current) {
                ++runLength;
            } else {
                // We've read one byte too far for this run; put it back for the next run.
                in.unget();
                break;
            }
        }

        // Write the encoded run: [count][byte].
        out.put(static_cast<char>(runLength));
        out.put(current);

        // Start next run by reading the next byte after the current run.
        int nextFirst = in.get();
        if (!in) {
            // No more data to process.
            break;
        }
        current = static_cast<char>(nextFirst);
    }

    std::cout << "Compression completed successfully.\n";
}

// Decompress inputFile into outputFile, reversing the RLE encoding described above.
void decompressFile(const std::string &inputFile, const std::string &outputFile) {
    std::ifstream in(inputFile, std::ios::binary);
    if (!in) {
        std::cerr << "Error: Could not open input file \"" << inputFile << "\" for reading.\n";
        return;
    }

    std::ofstream out(outputFile, std::ios::binary);
    if (!out) {
        std::cerr << "Error: Could not open output file \"" << outputFile << "\" for writing.\n";
        return;
    }

    char countChar;
    char value;

    // Each iteration reads one (count, value) pair and writes 'count' copies of 'value'.
    while (in.get(countChar) && in.get(value)) {
        unsigned char count = static_cast<unsigned char>(countChar);

        // A count of zero would indicate a corrupted file; skip it defensively.
        if (count == 0) {
            std::cerr << "Warning: Encountered zero count in compressed file. Skipping.\n";
            continue;
        }

        for (unsigned int i = 0; i < count; ++i) {
            out.put(value);
        }
    }

    if (!in.eof()) {
        std::cerr << "Warning: Decompression ended due to a read error or malformed data.\n";
    } else {
        std::cout << "Decompression completed successfully.\n";
    }
}

int main() {
    std::cout << "Run-Length Encoding (RLE) File Utility\n";
    std::cout << "1 -> Compress\n";
    std::cout << "2 -> Decompress\n";
    std::cout << "Enter choice: ";

    int choice = 0;
    if (!(std::cin >> choice)) {
        std::cerr << "Invalid input. Exiting.\n";
        return 1;
    }

    std::string inputFile;
    std::string outputFile;

    std::cout << "Enter input file name: ";
    std::cin >> inputFile;
    std::cout << "Enter output file name: ";
    std::cin >> outputFile;

    if (choice == 1) {
        compressFile(inputFile, outputFile);
    } else if (choice == 2) {
        decompressFile(inputFile, outputFile);
    } else {
        std::cerr << "Invalid choice. Please run the program again and choose 1 or 2.\n";
        return 1;
    }

    return 0;
}

