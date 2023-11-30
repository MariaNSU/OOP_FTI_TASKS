
## Как тестировать локально

Собрать программу с помощью `cmake` и запустить `ctest`:

```bash
mkdir build; cd build
cmake ..; cmake --build .
ctest -V
```
