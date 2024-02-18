# LSB Digital Steganography

This project implements Least Significant Bit (LSB) digital steganography to hide a text message within a .bmp image file. The project includes a C program for encoding the message into the image and decoding the message from the image.

### How it Works
The LSB digital steganography technique involves replacing the least significant bit of each byte in the image with the bits of the message to be hidden. Since the least significant bit has the least impact on the visual appearance of the image, this method allows for hiding data without noticeably altering the image.

### Features
- Encoding: Embedding a text message into the least significant bits of a BMP image.
- We are using MAGIC_STRING as a password for authentication.
- Decoding: Extracting a hidden message from the least significant bits of a BMP image.
- Supports BMP Images: The program specifically works with BMP (Bitmap) images for steganography operations.

### Steps
1. Encoding :
- Run the encode.c program, providing the path to the input image file (.bmp) and the text file containing the message to be hidden.
- The program will create a copy of the input image with the message encoded into it.

2. Decoding :
- Run the decode.c program, providing the path to the encoded image file (the output of the encoding process).
- The program will extract the hidden message from the image and store to new file.

### File Structure
- `encode.c` : C program for encoding a text message into a .bmp image file.
- `decode.c` : C program for decoding a text message from a .bmp image file.
- `sample.bmp` : Sample input image file.
- `secret.txt` : Sample text file containing the message to be hidden.
- `output.bmp` : Output image file with the hidden message encoded.
- `Makefile` : File for running the code.

![Files](https://raw.githubusercontent.com/Sarangmp4/LSB-Digital-Image-Stegenography/0cb458d00879afda5c4c215508c638c125dd277f/Screenshots/files.png "Files")

### Requirements
1. C Compiler (e.g., GCC)
2. .bmp image file
3. Text file containing the message to be hidden

### Example

- Encoding
**Use command :-** *./final.exe -e sample.bmp secret.txt*

![Encoding command](https://raw.githubusercontent.com/Sarangmp4/LSB-Digital-Image-Stegenography/0cb458d00879afda5c4c215508c638c125dd277f/Screenshots/encoding%20command.png "Encoding command")

![Encoded Message](https://raw.githubusercontent.com/Sarangmp4/LSB-Digital-Image-Stegenography/0cb458d00879afda5c4c215508c638c125dd277f/Screenshots/Encode%20message.png "Encoded Message")

- Decoding
**Use command :-** *./final.exe -d output.bmp*
  
![Decoding Command](https://raw.githubusercontent.com/Sarangmp4/LSB-Digital-Image-Stegenography/0cb458d00879afda5c4c215508c638c125dd277f/Screenshots/decoding%20command.png "Decoding Command")

![Decoded Message](https://raw.githubusercontent.com/Sarangmp4/LSB-Digital-Image-Stegenography/0cb458d00879afda5c4c215508c638c125dd277f/Screenshots/decoding%20message.png "Decoded Message")



### Contributing
Contributions are welcome! Please open an issue or submit a pull request for any new features, enhancements, or bug fixes.

### Acknowledgments
This project was inspired by the concept of LSB steganography and aims to provide a simple implementation for educational purposes.
