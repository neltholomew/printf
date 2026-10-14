*This project has been created as part of the 42 curriculum by pcellar.*

# ft_printf

## Description

`ft_printf` is a recreation of the C standard library function `printf()`. It is
packaged as a static library, `libftprintf.a`, that can be linked into any C
project.

The goal of the project is to learn how **variadic functions** work in C, meaning
functions that accept a variable number of arguments, using the `<stdarg.h>`
macros `va_start`, `va_arg` and `va_end`.

The function prototype is:

```c
int	ft_printf(const char *format, ...);
```

Like the original, it prints the format string to standard output, replaces
each conversion with the matching argument, and returns the total number of
characters printed.

### Supported conversions

| Conversion | Prints |
|---|---|
| `%c` | a single character |
| `%s` | a string (`(null)` for a NULL pointer) |
| `%p` | a pointer address in lowercase hexadecimal with a `0x` prefix (`(nil)` for NULL) |
| `%d` | a signed decimal integer |
| `%i` | a signed decimal integer |
| `%u` | an unsigned decimal integer |
| `%x` | an unsigned integer in lowercase hexadecimal |
| `%X` | an unsigned integer in uppercase hexadecimal |
| `%%` | a literal percent sign |

The buffer management of the original `printf()` is intentionally not
reproduced: every character is written immediately with `write()`.

## Instructions

### Compilation

```sh
make        # builds libftprintf.a
make clean  # removes object files
make fclean # removes object files and the library
make re     # rebuilds everything from scratch
```

Sources are compiled with `cc -Wall -Wextra -Werror` and archived with `ar rcs`.

### Usage

Include the header and link against the library:

```c
#include "ft_printf.h"

int	main(void)
{
	ft_printf("Hello %s, you are %d years old (%x in hex)\n", "world", 42, 42);
	return (0);
}
```

```sh
cc -Wall -Wextra -Werror main.c -L. -lftprintf -o main
./main
```

## Algorithm and data structure

### Parsing the format string

`ft_printf` walks through the format string one character at a time with a
pointer:

- A normal character is printed as it is.
- When the current character is `%`, the pointer moves one step forward and the
  next character (the conversion specifier) is passed to `ft_parse`.

`ft_parse` is a dispatcher. It matches the specifier, reads **exactly one**
argument from the `va_list` with the type the caller actually passed, and
forwards it to the right printing helper. Consuming exactly one argument per
conversion keeps the argument list in step with the format string. If a
conversion skipped its argument, every conversion after it would read the wrong
value.

| Specifier | Type read with `va_arg` | Helper |
|---|---|---|
| `c` | `int` (a `char` is promoted to `int` when passed through `...`) | `ft_putchar` |
| `s` | `char *` | `ft_putstr` |
| `d`, `i` | `int` | `ft_putnbr` |
| `u`, `x`, `X` | `unsigned int` | `ft_putnbr_base` |
| `p` | `void *` | `ft_putptr` |

### Counting printed characters

The return value is tracked with a single `int` counter owned by `ft_printf`.
A pointer to it is passed down to every helper, and **only `ft_putchar`
increments it**. Every other helper prints through `ft_putchar`, except for the
`(null)` and `(nil)` special cases, which add the return value of `write()`.
Because printing and counting happen in the same place, they cannot drift apart.

I chose this over having each helper return its own length because new
conversions get correct counting automatically, with no extra arithmetic in the
dispatcher.

### One function for every unsigned base

`%u`, `%x`, `%X` and the digits of `%p` are all "print an unsigned number in a
given base". Instead of four separate functions, `ft_putnbr_base` takes the
**digit string** as a parameter:

- `"0123456789"` for `%u`
- `"0123456789abcdef"` for `%x` and `%p`
- `"0123456789ABCDEF"` for `%X`

The string does two jobs at once. Its **length** is the base used for `/` and
`%`, and its **characters** are the digits, so `base[n]` directly gives the
character for a digit value. Uppercase and lowercase need no extra logic.

The number parameter is an `unsigned long` so that it can hold a 64-bit pointer
address. Values read as `unsigned int` for `%u`, `%x` and `%X` are widened to
`unsigned long` automatically when they are passed in, which never changes the
value.

`%p` goes through a small wrapper, `ft_putptr`, which handles what is specific
to pointers: printing `(nil)` for NULL, printing the `0x` prefix, and casting
the `void *` to `unsigned long` before calling `ft_putnbr_base`.

### Files

| File | Role |
|---|---|
| `ft_printf.c` | `ft_printf` (the main loop) and `ft_parse` (the dispatcher) |
| `ft_putchar.c` | writes one character and increments the counter |
| `ft_putstr.c` | prints a string, or `(null)` |
| `ft_putnbr.c` | prints a signed `int`, including `INT_MIN` |
| `ft_putnbr_base.c` | prints an unsigned number in any base given by a digit string |
| `ft_putptr.c` | prints a pointer as `0x...`, or `(nil)` |
| `ft_strlen.c` | string length, used to find the base |
| `ft_printf.h` | includes and prototypes |

## Resources

- `man 3 printf`: the reference behavior for every conversion and the return value
- `man 3 stdarg`: `va_start`, `va_arg`, `va_copy` and `va_end`
- [cppreference: Variadic functions](https://en.cppreference.com/w/c/variadic)
- [cppreference: Implicit conversions](https://en.cppreference.com/w/c/language/conversion),
  including default argument promotion
- The 42 Norm and the project subject

### Use of AI

I used an AI assistant as a tutor and reviewer. Following the subject's AI guidelines, I wrote every function
myself. The assistant was used to:

- explain concepts I was stuck on
- review my code and point out bugs and compiler errors as hints
  and questions, without giving solutions
- run comparison tests of my `ft_printf` against the real `printf`
- check the Makefile and draft this README, which I reviewed afterwards
