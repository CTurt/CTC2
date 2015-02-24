CTC2
====
A lossless compression algorithm based on LZ77, written in C.

### How does it work?
Compression is based on the assumption that enough data will be repeated in order to make storing references, instead of repeated data, decrease the file size.

Firstly, a character is written from the input to the output.

The next set of characters are looked for in the data already processed, if it is found, a reference to the best match and a length is written; otherwise a 0 byte is written.

This process is repeated until the end of the file.

### Results
The main.c of the compressor is reduced by about 55% when compressed.