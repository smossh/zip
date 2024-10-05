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

Here is the pseudocode for encode: 

“main” Function:
1) Reads the file and creates a node by determining the frequency of each different character
2) Runs it by sending the nodes and the number of nodes to the build_tree function
3) Sends the head node to the create_code function
4) Calls the convert_binary function to convert text to binary text
5) Calls the print function to write the binary text to the output file in a reduced size format
6) Returns 0 to indicate successful execution

“build_tree” Function:
1) Finds the two smallest nodes by calling fin_min function
2) As long as the function gives a value of 1, it creates a new node and defines the two smallest nodes to their right and left values. If the function gives a value of 0, it returns the nodes and stops.

“find_min” Function:
1) Determines the smallest unmarked node among the nodes and marks it by setting the flag value to 1
2) If there is no other unmarked node, it returns 0 and stops.
3) Finds the second smallest unmarked node and stops by returning 1. 

“create_code” Function:
1) If the node is not marked, the code of the node is determined as "0", otherwise it adds the  code sent with it to the end of the node code
2) If the node has a right node, it calls the create_code function again by sending the right node  with the code "1". If the node has a left node, it repeats the same process with the code "0"
3) If the node does not have a right and left value, the function ends.

“convert_binary” Function:
1) Replaces the characters in the main text with the huffman code equivalent and creates a binary text
2) Returns the binary text and stops

“print” Function:
1) Takes every 8 characters in the binary text and defines them as a new character.
2) Writes each newly defined character to the output file.
3) When the binary text is finished, it ends the process
