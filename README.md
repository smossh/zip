Huffman Coding - Text Compression and Decompression

This project implements Huffman Coding, a method of lossless data compression that reduces the size of text files by encoding frequently used characters with shorter codes and less frequent ones with longer codes. The project includes two main functionalities: encoding a text file into compressed format and decoding the compressed file back into its original form.

Features

Encoding: Compresses a given text file using Huffman coding.
Decoding: Decompresses the encoded file back into the original text.
Efficiency: Reduces file size by utilizing variable-length prefix codes based on the frequency of characters.
How It Works

Build Frequency Table: Analyze the input text to count how often each character appears.
Construct Huffman Tree: Create a binary tree where each leaf node represents a character, with the most frequent characters having shorter paths from the root.
Generate Huffman Codes: Assign binary codes to each character based on the tree structure.
Encode: Convert the original text into a binary string using the generated Huffman codes.
Decode: Rebuild the original text from the binary string by traversing the Huffman tree.
