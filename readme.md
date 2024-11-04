# TCP/UDP client-server model

## Сборка 

Склонируйте репозиторий и соберите проект с помощью команды `make`. 

## Запуск

Общий вид запуска: `./<protocol>/<protocol>_<server or client> <port number>`.
В качестве протоколов используются сокращенные названия: `udp` и `tcp`.
Например: `./tcp/tcp_client 4460` или `./udp/udp_server 4455`.

## Пример использования 

- Для начала создадим клиента и сервер:

![](/res/client_start.png?raw=true "Старт клиента.") 
![](/res/server_start.png?raw=true "Старт сервера.")

Заметим также, что сервер время от времени спрашивает о желании прекратить поиск клиентов, если таковых долго нет.

- Немного пообщаемся:

|  CLIENT      |     SERVER            |
| ------------- |:------------------:|
| ![](/res/client_simple1.png?raw=true "Сбщение: клиент.")     | ![](/res/server_simple1.png?raw=true "Сбщение: сервер.")    |
| ![](/res/client_simple2.png?raw=true "Сбщение: клиент.")     | ![](/res/server_simple2.png?raw=true "Сбщение: сервер.")    |

- Передадим большое сообщение (на самом деле, большим оно является, только потому, что намеренно размер буффера был уменьшен до 8 символов, в общем случае, можно представить себе буффер обычного размера (несколько кБайт) и сообщение в сотни кБайт):

|  CLIENT      |
| ------------- |
| ![](/res/large_msg_clent.png?raw=true "длинное сообщение: клиент.")  |
 
|  SERVER      |
| ------------- |
| ![](/res/large_msg_server.png?raw=true "длинное сообщение: сервер.")    |

- завершим работу на клиенте с помощью команды `exit`, а на сервере остановим поиск новых соединений:

|  CLIENT      |
| ------------- |
| ![](/res/client_full.png?raw=true "фул клиента.")     |
 
|  SERVER      |
| ------------- |
| ![](/res/server_full.png?raw=true "фул сервера.")    |