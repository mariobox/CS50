# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

An artificial long word said to mean a lung disease caused by inhaling very fine ash and sand dust.

## According to its man page, what does `getrusage` do?

Returns resource usage statistics.

## Per that same man page, how many members are in a variable of type `struct rusage`?

Sixteen (16)

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

Perhaps to save memory, since that way we don't need to create a new variable and use more space than necessary.

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

It reads each character of a word in a text file, one by one, submitting it to a series of conditions to see if it is a valid character, and if so, places it in a word[] array that is then passed to the check function via a pointer.

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

Because fgetc reads each character as an int, which will help us place it in the hash table. Also, fgetc reads until the end of the file. With fscanf we need to know the exact layout of each file we're reading and rewrite the functin for each layout.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

Because you didn't want them to change. If they were allowed to change for any reason, that could affect the hash function results (e.g. calculating indexes or lowercase versus uppercase letters).
