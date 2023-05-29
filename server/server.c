/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:22:15 by imurugar          #+#    #+#             */
/*   Updated: 2023/05/22 15:22:16 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

typedef struct {
    int socket;
    struct sockaddr_in address;
} Client;

int main() {
    int serverSocket, newSocket;
    struct sockaddr_in serverAddress, clientAddress;
    socklen_t clientAddressLength;
    Client clients[MAX_CLIENTS];
    int numClients = 0;
    char buffer[BUFFER_SIZE];

    // Crear el socket del servidor
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Error al crear el socket del servidor");
        exit(1);
    }

    // Configurar la dirección del servidor
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(12345); // Puerto a utilizar

    // Vincular el socket a la dirección del servidor
    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
        perror("Error al vincular el socket del servidor");
        exit(1);
    }

    // Escuchar por nuevas conexiones
    if (listen(serverSocket, MAX_CLIENTS) == -1) {
        perror("Error al escuchar por nuevas conexiones");
        exit(1);
    }

    printf("Servidor en ejecución. Esperando conexiones...\n");

    while (1) {
        // Aceptar una nueva conexión
        clientAddressLength = sizeof(clientAddress);
        newSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLength);
        if (newSocket == -1) {
            perror("Error al aceptar una nueva conexión");
            exit(1);
        }

        printf("Cliente conectado: %s:%d\n", inet_ntoa(clientAddress.sin_addr), ntohs(clientAddress.sin_port));

        // Agregar el nuevo cliente a la lista
        clients[numClients].socket = newSocket;
        clients[numClients].address = clientAddress;
        numClients++;

        // Recibir la posición del cliente
        int bytesRead = recv(newSocket, buffer, BUFFER_SIZE, 0);
        if (bytesRead <= 0) {
            // Error o cliente desconectado
            printf("Cliente desconectado: %s:%d\n", inet_ntoa(clientAddress.sin_addr), ntohs(clientAddress.sin_port));
            close(newSocket);
            continue;
        }

        // Reenviar la posición a los demás clientes
        for (int i = 0; i < numClients; i++) {
            if (clients[i].socket != newSocket) {
                send(clients[i].socket, buffer, bytesRead, 0);
            }
        }
    }

    // Cerrar los sockets de los clientes y el servidor
    for (int i = 0; i < numClients; i++) {
        close(clients[i].socket);
    }
    close(serverSocket);

    return 0;
}
