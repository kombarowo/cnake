# Cnake

```console
$ docker build . --tag gcc_boiler
$ docker run -it --detach --name cnake -v $(pwd):/home/foo/project gcc_boiler
$ docker exec -it cnake /bin/bash
$ ./build.sh; ./build/main
```
