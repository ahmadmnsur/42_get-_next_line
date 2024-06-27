![42 beirut](https://media.licdn.com/dms/image/D4E3DAQGxvimpQQFi_A/image-scale_191_1128/0/1695893480399/42_beirut_cover?e=2147483647&v=beta&t=oNrMR2IXjtfu3XXV-uSUW8wI98g19yUUHZ0XuhtX2NE)

---
<h2><b>¤ Introduction ¤</b></h2>

<p align="center">The "get_next_line" project introduces an essential concept in C programming: static variables. The goal is to create a program that reads a specified number of characters, defined by "buffer_size," from a line of text. When a "newline character" is found, the program should move on to the next line. In addition to static variables, "get_next_line" also touches on other C programming concepts that you will uncover as you work through the project.</p>

---

<h2><b></b>¤ File descritpors (fd) ¤</b></h2>
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

<h2><b>¤ Reading a file ¤</b></h2>
The  `read()` function from the `<unistd.h>` library allows us to load the contents of a file into memory using its file descriptor. 

Here’s how the `read()` function works with its parameters:

- **File descriptor (fd)**: The file descriptor provided as a parameter in the `get_next_line` function.
- **Buffer**: A pointer to a memory area where the read characters will be temporarily stored.
- **Number of bytes to read**: The amount of data to read, defined by `BUFFER_SIZE` in this project, which is specified at compilation time.

The `read()` function will return the number of characters it successfully read, or -1 if an error occurs.
