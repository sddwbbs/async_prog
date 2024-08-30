## Тестовое задание

Программа включает в себя две отдельные программы: клиент и сервер, работающие независимо друг от друга. Клиент и сервер взаимодействуют через UNIX domain sockets. Ожидается, что программа будет запущена локально.

### Сборка 
Производится в директории `/async_prog`
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
./test_task -client
```

### Работа программы
Рекомендуется запускать клиент и сервер в разных сессиях терминала.

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
