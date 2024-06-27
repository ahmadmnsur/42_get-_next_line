![42 beirut](https://media.licdn.com/dms/image/D4E3DAQGxvimpQQFi_A/image-scale_191_1128/0/1695893480399/42_beirut_cover?e=2147483647&v=beta&t=oNrMR2IXjtfu3XXV-uSUW8wI98g19yUUHZ0XuhtX2NE)

---
## ¤ Introduction ¤

<p align="center">The "get_next_line" project introduces an essential concept in C programming: static variables. The goal is to create a program that reads a specified number of characters, defined by "buffer_size," from a line of text. When a "newline character" is found, the program should move on to the next line. In addition to static variables, "get_next_line" also touches on other C programming concepts that you will uncover as you work through the project.</p>

---

##  ¤ File descritpors (fd) ¤
To handle a file in C, we start by notifying the operating system of our intentions using the `open` function from the `fcntl.h` library. This system call requires us to specify the file path and the desired access mode through flags, for example:

```c
open("file.txt", O_RDONLY); // read only
open("file.txt", O_WRONLY); // write only
open("file.txt", O_RDWR);   // read/write
```

The system checks if the file exists and confirms that we have the appropriate permissions to open it. If successful, the system returns a non-negative integer called a file descriptor (or fd). From this point on, we will use this file descriptor instead of the file name.

It is important to note that file descriptors 0, 1, and 2 are reserved for standard input, standard output, and standard error output, respectively. Thus, our file will likely receive a file descriptor numbered 3 or higher, depending on the number of files already open.

If there is an issue, such as the file not existing or lacking the necessary permissions, the function will return -1.

Finally, once we are done working with the file, we should release the file descriptor using the `close()` function from the `<unistd.h>` library.

## ¤ Reading a file ¤
The  `read()` function from the unistd.h library allows us to load the contents of a file into memory using its file descriptor. 

Here’s how the `read()` function works with its parameters:

- **File descriptor (fd)**: The file descriptor provided as a parameter in the `get_next_line` function.
- **Buffer**: A pointer to a memory area where the read characters will be temporarily stored.
- **Number of bytes to read**: The amount of data to read, defined by `BUFFER_SIZE` in this project, which is specified at compilation time.

The `read()` function will return the number of characters it successfully read, or -1 if an error occurs.

## ¤ The BUFFER_SIZE Challenge ¤
In `get_next_line`, we can't read characters one by one until we hit a `\n`. Instead, we have to read a set number of characters at a time, determined by a `BUFFER_SIZE` that isn't known in advance. Consider a file with the following text, which has 34 characters:

```
1 = one
2 = two
3 = three
4 = four
```

If the `BUFFER_SIZE` is 1, the `read` function would need to be called 35 times to read the entire text. In this case, we can stop at the 8th call when we hit a `\n` and return the first line. The `read` function would then be correctly positioned for the next call to `get_next_line` to retrieve the second line.

However, if the `BUFFER_SIZE` is 100, a single call to the `read` function would read the entire text. We would then extract the characters before the `\n` from the buffer and return them. But this presents a problem: on the next call to `get_next_line`, the `read` function would be at the end of the file, with no more data to read, and the remaining characters in the buffer would be lost.

## ¤ Static Variables in C ¤
Static variable can be used to maintain the state of reading lines across multiple function calls. This is commonly used in functions that read input until a newline character ('\n') is encountered or until a specified delimiter is found.

## ¤ A Function Read from The File Descriptor ¤
The `ft_read_str` function reads from a file descriptor (fd) into a string (s) until it encounters a newline character ('\n') or reaches the end of the file

1. **Memory Allocation**:
   - `buff` is allocated memory to temporarily store data read from the file using `malloc((BUFFER_SIZE + 1) * sizeof(char))`. This ensures `buff` can hold up to `BUFFER_SIZE` characters plus a null terminator.

   - If `s` (the string) is `NULL`, it's initialized with `malloc(1)` to create an empty string.

2. **Reading Loop**:
   - The function enters a loop that continues as long as there's no newline (`'\n'`) in `s` and `bytes` is not 0.
   
   - Inside the loop:
     - `read(fd, buff, BUFFER_SIZE)` reads up to `BUFFER_SIZE` bytes from the file descriptor `fd` into `buff`. The number of bytes read is stored in `bytes`.
     
     - If `read` returns `-1`, indicating an error, the function frees `buff` and `s` before returning `NULL`.
     
     - `buff[bytes] = '\0'` ensures `buff` is null-terminated after reading.
     
     - `s = ft_free(s, buff)` calls a function  to concatenate `buff` into `s` and free `buff`. If `ft_free` fails (`s` becomes `NULL`), it frees `buff` and returns `NULL`.

3. **Return**:
   - Once the loop exits (due to finding `'\n'` in `s` or reaching end of file), the function frees `buff` and returns `s`, which contains the accumulated data read from the file.

## ¤ A Function to Get the Line to Return ¤

The `ft_get_line` function extracts a single line from a given string `s`, terminating at either a newline character (`'\n'`) or the end of the string. Here's a detailed explanation of how it works:
1. **Initialization and Input Check**:
   - If `s[0]` is `'\0'` (empty string), the function returns `NULL` indicating no line to extract.

2. **Finding the Line Length**:
   - The function iterates through `s` to find the length of the line until it encounters `'\n'` or reaches the end of the string (`s[i] && s[i] != '\n'`).

3. **Memory Allocation**:
   - `line` is allocated memory to store the extracted line. The size allocated is `i + 2` to accommodate the characters of the line and ensure space for `'\n'` and `'\0'`.

4. **Copying Characters**:
   - The characters from `s` are copied to `line` within a loop (`while (s[++i] && s[i] != '\n')`), stopping either at `'\n'` or the end of `s`.

5. **Handling `'\n'`**:
   - If `'\n'` is found in `s`, it is copied to `line`, and the index `i` is incremented to move past it.

6. **Null-Termination**:
   - The extracted line `line` is null-terminated (`line[i] = '\0'`) to ensure it is a valid C string.

7. **Return**:
   - Finally, `line`, which now contains the extracted line including `'\n'`, is returned.

## ¤ Function To Create A New String ¤ 
The `ft_new_str` function appears to aim at creating a new string by removing everything before the first newline character (`'\n'`) from the input string `s`. Here's a detailed explanation of how it works:

1. **Finding the '\n' Position**:
   - The function begins by iterating through `s` to find the position of the first `'\n'` (`while (s[i] && s[i] != '\n') i++;`).

2. **Handling End of String**:
   - If no `'\n'` is found (`!s[i]`), indicating the end of the string, the function frees `s` (assuming it is dynamically allocated) and returns `NULL`.

3. **Memory Allocation for new_str**:
   - Memory is allocated for `new_str` to hold the characters after the first `'\n'`, calculated as `ft_strlen(s) - i + 1` (including space for the null terminator).

4. **Copying Characters**:
   - Characters from `s` after the `'\n'` are copied to `new_str` using a loop (`while (s[i]) new_str[j++] = s[i++];`).

5. **Null-Termination**:
   - `new_str` is null-terminated after copying all characters (`new_str[j] = '\0';`).

6. **Freeing Original String**:
   - Before returning `new_str`, the original string `s` is freed (`return (free(s), new_str);`), ensuring proper memory management.
