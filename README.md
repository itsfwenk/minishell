# 🐚 Minishell

A simple shell implementation in C that recreates the basic functionality of bash. This project is part of the 42 School curriculum and demonstrates understanding of processes, file descriptors, pipes, redirections, and signal handling.

## 📋 Table of Contents

- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Built-in Commands](#built-in-commands)
- [Supported Features](#supported-features)
- [Project Structure](#project-structure)
- [Testing](#testing)
- [Memory Management](#memory-management)
- [Authors](#authors)

## ✨ Features

- **Interactive command line interface** with prompt display
- **Command execution** with PATH resolution
- **Built-in commands** implementation
- **Pipes** (`|`) for command chaining
- **Redirections** (`<`, `>`, `>>`, `<<`)
- **Environment variable** expansion (`$VAR`)
- **Quote handling** (single and double quotes)
- **Signal handling** (Ctrl+C, Ctrl+D, Ctrl+\)
- **Wildcard expansion** (`*`)
- **Subshell execution** with parentheses
- **Here documents** (`<<`)

## 🔧 Installation

### Prerequisites

- **GCC** compiler
- **GNU Readline** library
- **GNU Make**

### Ubuntu/Debian
```bash
sudo apt-get update
sudo apt-get install build-essential libreadline-dev
```

### macOS
```bash
# Install Xcode command line tools
xcode-select --install

# Install readline via Homebrew
brew install readline
```

### Building the Project

1. Clone the repository:
```bash
git clone <repository-url>
cd minishell
```

2. Compile the project:
```bash
make
```

3. Run the shell:
```bash
./minishell
```

## 🚀 Usage

### Basic Usage

```bash
$ ./minishell
skibidishell$ echo "Hello, World!"
Hello, World!
skibidishell$ ls -la
# Directory listing...
skibidishell$ exit
```

### Examples

#### Pipes
```bash
skibidishell$ ls | grep .c | wc -l
```

#### Redirections
```bash
skibidishell$ echo "Hello" > file.txt
skibidishell$ cat < file.txt
skibidishell$ echo "World" >> file.txt
```

#### Here Documents
```bash
skibidishell$ cat << EOF
> Line 1
> Line 2
> EOF
```

#### Environment Variables
```bash
skibidishell$ echo $HOME
skibidishell$ export MY_VAR="Hello"
skibidishell$ echo $MY_VAR
```

#### Subshells
```bash
skibidishell$ (echo "In subshell" && pwd)
```

## 🔨 Built-in Commands

| Command | Description | Usage |
|---------|-------------|-------|
| `echo` | Print arguments to stdout | `echo [-n] [arguments...]` |
| `cd` | Change directory | `cd [directory]` |
| `pwd` | Print working directory | `pwd` |
| `export` | Set environment variables | `export [VAR=value]` |
| `unset` | Unset environment variables | `unset [VAR]` |
| `env` | Display environment variables | `env` |
| `exit` | Exit the shell | `exit [code]` |

## 🎯 Supported Features

### ✅ Implemented
- Command execution with PATH resolution
- Built-in commands (echo, cd, pwd, export, unset, env, exit)
- Pipes (`|`)
- Input/Output redirections (`<`, `>`, `>>`)
- Here documents (`<<`)
- Environment variable expansion (`$VAR`)
- Quote handling (single `'` and double `"` quotes)
- Signal handling (Ctrl+C, Ctrl+D, Ctrl+\)
- Wildcard expansion (`*`)
- Subshell execution with parentheses `()`
- Command history (via readline)

### ❌ Not Implemented
- Background processes (`&`)
- Job control
- Advanced globbing patterns
- Command substitution with backticks

## 📁 Project Structure

```
minishell/
├── Makefile              # Build configuration
├── README.md             # Project documentation
├── run.sh               # Valgrind testing script
├── readline.supp        # Valgrind suppressions for readline
├── includes/            # Header files
│   ├── skibidishell.h   # Main header
│   ├── builtins.h       # Built-in commands
│   ├── exec.h           # Execution functions
│   ├── expander.h       # Variable expansion
│   ├── lexer.h          # Tokenization
│   ├── parser.h         # Syntax parsing
│   ├── signals.h        # Signal handling
│   └── utils.h          # Utility functions
├── libft/               # Custom C library
└── srcs/                # Source code
    ├── skibidishell.c   # Main program
    ├── builtins/        # Built-in command implementations
    ├── exec/            # Command execution
    ├── expander/        # Variable and wildcard expansion
    ├── lexer/           # Input tokenization
    ├── parser/          # Syntax analysis
    ├── signals/         # Signal handling
    └── utils/           # Utility functions
```

## 🧪 Testing

### Basic Testing
```bash
# Test basic commands
./minishell
skibidishell$ echo test
skibidishell$ pwd
skibidishell$ ls
```

### Memory Leak Testing
```bash
# Using the provided script
chmod +x run.sh
./run.sh
```

### Manual Valgrind Testing
```bash
valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all \
         --trace-children=yes --suppressions=readline.supp ./minishell
```

## 🔧 Memory Management

This project implements careful memory management:

- All allocated memory is properly freed
- File descriptors are closed appropriately
- Signal handlers are set up correctly
- Valgrind testing with readline suppressions
- No memory leaks in normal operation

## 🛠️ Development

### Compilation Flags
- `-Wall -Wextra -Werror`: Strict compilation warnings
- `-g3`: Debug information for debugging
- Links with custom `libft` library and `readline`

### Make Targets
- `make` or `make all`: Build the project
- `make clean`: Remove object files
- `make fclean`: Remove object files and executable
- `make re`: Clean and rebuild

## 📚 Learning Objectives

This project demonstrates understanding of:
- **Process management** and `fork()`/`exec()` family
- **File descriptor** manipulation
- **Pipe** creation and management
- **Signal handling** in Unix systems
- **Memory management** in C
- **Parsing** and **lexical analysis**
- **Environment variable** handling
- **Error handling** and edge cases

## 👥 Authors

- **mel-habi** - Developer
- **fli** - Developer

## 📄 License

This project is part of the 42 School curriculum.

---

*Happy shelling! 🐚*
