# c_password_manager

## Setup

### Install libaries:

```
	sudo apt install libcrypto++-dev libcrypto++-doc libcrypto++-utils
```
Header files are installed to /usr/include/crypto++/

The .so and .a files are installed to /usr/lib/x86_64-linux-gnu/

The .a (archive) file is a "static" library

.so (shared object) files are shared objects or dynamic libraries, similar to DLL on Windows.

Static libraries are compiled into the binary.

Dynamic libraries are accessed at runtime.

### Library documentation:

```
	firefox /usr/share/doc/libcrypto++-doc/html/index.html &
```
### Compile

```
	make
```

### VS Code Setup

Get ligatures:
```
	sudo apt install fonts-firacode
```
In VS Code, hit
```
	ctrl+,
```
to open settings. Search for "font", and then replace the contents of "font family"
with
```
	'Fira Code'
```
and check the box to use ligatures.

#### Command palette
To open the command palette, hit:
```
	ctrl+shift+p
```

You can change the theme, git push, etc. with the palette.

#### Opening workspace from terminal
Navigate to ProjectMunro and then use:
```
	code .
```
This keeps everything together including config files, rather than opening
files individually.

#### Debugging
Configure gdb to debug, make is already configured with -g flag.

```
launch.json
```
contains debugger configurations.