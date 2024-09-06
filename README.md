## Тестовое задание

Имеются две отдельные программы: клиент и сервер, работающие независимо друг от друга. Клиент и сервер взаимодействуют через UNIX domain sockets. Ожидается, что программы будут запущены локально.

### Сборка 
Производится в директории `/async_prog`
=======
Сборка клиента производится в директории `/src/client`,
сервера в директории `/src/server`

Комманды для сборки:
```bash
mkdir build && cd build
cmake -DCMAKE_CXX_COMPILER=/usr/bin/g++ ..
make
```

### Запуск
Для запуска нужно указать один из флагов:
- `-client` для запуска клиента
- `-server` для запуска сервера

Пример запуска клиента:
```bash
./async_prog -client
```
=======
- `./client` клиент
- `./server` сервер

### Работа программы
Демонстрация работы клиента при неработающем сервере:
```bash
=======================================================================
Enter the line: test input
Line must be no longer than 64 characters and contain only numbers
=======================================================================
Enter the line: 1234
Processed data: KB3KB1
connect: Connection refused
=======================================================================
```
Демонстрация работы клиента при работающем сервере:
```bash
=======================================================================
Enter the line: test input
Line must be no longer than 64 characters and contain only numbers
=======================================================================
Enter the line: 1234
Processed data: KB3KB1
=======================================================================
Enter the line: 55555511
Processed data: 55555511
=======================================================================
```
Логи сервера:
```bash
SERVER | Server is listening...

SERVER | Invalid data, number must be more than two characters and a multiple of 32

SERVER | Received data: 32
```
