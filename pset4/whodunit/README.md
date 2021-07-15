# Questions

## What's `stdint.h`?

It specifies new types of integers, for which you can specify the size you want your integer to have.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

To make sure that the integers you are declaring have a specific size.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

BYTE: 1
DWORD: 4
LONG: 4
WORD: 2

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

The letters B and M (in ASCII format).

## What's the difference between `bfSize` and `biSize`?

bfSize is the size of the bitmap file in bytes.
biSize is the number of bytes required by the structure.

## What does it mean if `biHeight` is negative?

It means that the bitmap is top-down, meaning that it originates in the top left corner.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

The pointer may be pointing to a file that does not exist.

## Why is the third argument to `fread` always `1` in our code?

Because we want to read one triple at a time

## What value does line 65 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

3

## What does `fseek` do?

Lets us move our file position indicator, or cursor.

## What is `SEEK_CUR`?

It is our current position in the file.

## Whodunit?

It was Professor Plum with the candlestick in the library.
