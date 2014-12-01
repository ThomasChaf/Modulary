# Modulary

Modulary is a C library that help you to use some features of Object-Oriented Programming in C programming.

## Requirements ##

 * No requirements are needed. Modulary is an unix library.

## Install

    $ git clone https://github.com/ThomasChaf/Modulary.git
    $ cd Modulary
    $ make re
    $ make install

## Usage

### Overview

```c
#include <unistd.h>
#include "modulary.h"

int main() {
 Stream st = new(__Stream, STDOUT_FILENO);

 st->write(st, "Hello world!");
 return (EXIT_SUCCESS);
}
```

### Documentation
  A full documentation is available here :

  http://t-chafiol.fr/en/modulary

## Credits

  - [Thomas Chafiol](http://github.com/ThomasChaf) <[t-chafiol.fr](http://t-chafiol.fr)>
