//
// Created by Admin on 19.08.2025.
//

#include <iostream>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main (int argc, char **argv) {

    // Проверяем передан ли хотя бы один аргумент
    if(argc < 2) {
        std::cout << "Usage: " << argv[0] << "server <port>" << std::endl;
    }

    // Преобразуем строку в целое число
    // В данном случае у нас тут будет наш порт для сервера. Сервер будет на localhost
    int port = atoi(argv[1]);

    // 1 socket
    // Создаем переменную sock и сохраняем в неё декскриптор с функции socket();
    // AF_INET это у нас IPv4. В нашем случае это 192.168.0.1 (другими словами localhost)
    // SOCK_STREAM это у нас потоковое соединение. В нашем случае SOCK_STREAM это TCP соединение
    // 0 в нашем случае это протокол
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    // 2 bind
    // Привязываем наш сокет к определённому адресу и порту на локальной машине
    struct sockaddr_in address;
    address.sin_family = AF_INET; // Присваиваем IPv4 нашему адресу
    address.sin_addr.s_addr = INADDR_LOOP; // Делаем так чтобы адресс работал на всех IPv4 интерфейсах
    address.sin_port = htons(port); // Присваиваем порт к нашему адрессу

    // Связываем наш сокет с адрессом и портом.
    int bind_value = bind(sock, (struct sockaddr*)&address, sizeof(address));

    if (bind_value < 0) {
        perror("bind failed. Error!");
        return -1;
    }

    // 3 listen
    // Ставим сокет в режим прослушивания входящих подключений
    // listen(sock, 1) - мы слушаем данный сокет,
    // 1 - значит, что мы слушаем сокет в одной очереди
    int listen_value = listen(sock, 1);
    if (listen_value < 0) {
        perror("listen failed.");
    }

    // 4 accept
    // Принимаем новое соединение
    struct sockaddr_in remote_address;
    // Беззнаковое целое число, которое сохраняет в себя длину нашего адреса
    socklen_t remote_addrlen = sizeof(address);
    // Функция accept() ждёт пока появится что-то для принятия в client_socket
    int client_socket = accept(sock, (struct sockaddr*)&remote_address, &remote_addrlen);
    // Сохраняем IP клиента
    std::string client_ip = inet_ntoa(address.sin_addr);
    // Сохраняем port клиента
    int remote_port = ntohs(address.sin_port);

    std::cout << "New client! @ " << client_ip << ":" << remote_port << std::endl;

    int BUFFLEN = 1024;
    char buffer[BUFFLEN];

    while (true) {
        // Очистка буффера от возможного мусора для принятия данных для клиента
        memset(buffer, 0, BUFFLEN);
        // 5 recv
        // recv() функция, которая получает данные из сокета
        // sock - место откуда мы читаем сокет. buffer - место в памяти, куда будут записаны данные,
        // BUFFLEN - длина буффера, максимальное количство байт которое мы можем сохранить
        int bytes_received = recv(client_socket, buffer, BUFFLEN-1, 0);

    }

}