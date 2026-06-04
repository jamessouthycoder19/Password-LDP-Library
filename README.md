# LDPasswd
LDPasswd is a C library providing functions to achieve ϵ-LDP protection when collecting passwords in a simulated Red vs. Blue cybersecurity competition
# Instructions

1. Clone repository

```bash
git clone https://github.com/jamessouthycoder19/LDPasswd.git
```

2. Edit trie generation script
a. Modify the `IMPORTANT_WORDS` variable to meet the needs of your competition.
b. This is used to ensure that any words that are not common in the english language that may be common in your environment are treated correctly in passwords

3. Run the trie generation script
```bash
cd data/scripts
python3 create-trie.py
```
4. Install compiling prerequisites

```bash
sudo apt install mingw-w64 cmake build-essential pkg-config
```
5. Compiling library for Linux

```bash
cmake  -B  build
cmake  --build  build
```
6. Compiling library for Windows

```bash
cmake  -B  build-windows  -DCMAKE_TOOLCHAIN_FILE=toolchains/mingw-w64-x86_64.cmake
cmake  --build  build-windows
```
7. Install the compiled library with its header (optional, you can also just retrieve the now compiled library from the build directory to do what you want with it)
```bash
# Linux
sudo  cmake  --install  build

# Windows
sudo  cmake  --install  build-windows
```
5. Clean up environment

```bash
rm  -rf  build/
rm  -rf  build-windows/
```