# Simple Shell

A basic shell implementation in C that can execute commands and handle process control.

## Prerequisites

To build and run this project on macOS, you need to have the following installed:

- **Clang** - C compiler (typically included with macOS)
- **Command Line Tools for Xcode** - Required for development tools

## Installation

### 1. Install Command Line Tools

If you don't have the Command Line Tools installed yet, run:

```bash
xcode-select --install
```

This will prompt you to install the Command Line Tools, which include clang and other necessary development tools.

### 2. Clone this repository

```bash
git clone git@github.com:zminsc/simple-shell.git
cd simple-shell
```

### 3. Build the shell

```bash
make
```

This will compile the source code and create an executable named `simple-shell`.

## Running the shell

After building, run the shell:

```bash
./simple-shell
```

## Usage

The simple shell accepts standard Unix commands. To exit the shell, press Ctrl+D (EOF).

Sample commands:

```bash
ls -la
echo "Hello, world!"
```
