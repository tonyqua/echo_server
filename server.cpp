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

    int bind_value = bind(sock, (struct sockaddr*)&address, sizeof(address));




}