# JackOS C++

C++ implementation of JackOS

---

## How to run

### Docker

You can run the project in docker with the `docker/Dockerfile` file.

( You must be in the `cpp` folder )

#### Build:
```
docker build -t osdev ./docker
```

#### Run:
```
docker run -it -e DISPLAY=$DISPLAY \
    -v /tmp/.X11-unix:/tmp/.X11-unix \
    -v $PWD:/osdev osdev
```

### Manual

You can manual install the dependencies and run the project. Here is a link with a tutorial to install the main dependency: [Tutorial](https://wiki.osdev.org/GCC_Cross-Compiler).
You need to build the C++ cross compiler.
You have a current version of the cross compiler in the `./opt.zip` file.

---

## TODO

