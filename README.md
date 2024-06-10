# [C](<https://en.wikipedia.org/wiki/C_(programming_language)>)nake

```console
$ docker build . --tag gcc_boiler
$ docker run -it --detach --name cnake -v $(pwd):/home/foo/project gcc_boiler
$ docker exec -it cnake /bin/bash
$ ./build.sh; ./build/main
```

gcc version 14.1.0 (GCC)

---

№107 in [programming-challenges](https://github.com/kombarowo/programming-challenges)
