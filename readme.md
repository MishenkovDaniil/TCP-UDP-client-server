# TCP/UDP client-server model

## Сборка 

Склонируйте репозиторий и соберите проект с помощью команды `make`. 

## Запуск

Общий вид запуска: `./<protocol>/<protocol>_<server or client> <port number>`.
В качестве протоколов используются сокращенные названия: `udp` и `tcp`.
Например: `./tcp/tcp_client 4460` или `./udp/udp_server 4455`.

## Пример использования 

- Для начала создадим клиента и сервер:

|  <!-- -->      |     <!-- -->            |
| ------------- |:------------------:|
| ![](/res/client_start.png?raw=true "Старт клиента.")     | ![](/res/server_start.png?raw=true "Старт сервера.")    |

Заметим также, что сервер время от времени спрашивает о желании прекратить поиск клиентов, если таковых долго нет.

- Немного пообщаемся: