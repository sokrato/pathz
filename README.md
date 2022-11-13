# pathz
`pathz` remove duplicate entries from $PATH variable for Linux and OS X.
You may put all your $PATH directories in `~/.paths` file, which is read by `pathz`,
ignoring lines starting with `#`.

The following pages helped me use stdlib utilities.
- https://cplusplus.com/reference/set/set/set/
- https://en.cppreference.com/w/cpp/container/vector
- https://en.cppreference.com/w/cpp/string

# build
``g++ -Wall --std=c++20 main.cpp -o pathz``

# use
You may want to put the following line in your shell init script:
```shell
PATH=$(pathz)
```
