# App-Mensajeria
Un programa en desarrollo que usa la tecnología de los WebSockets para enviar y recibir mensajes entre clientes gracias a un servidor.
## Compilación
#### Dependencias
* Qt 5.15. Módulos GUI, NETWORK y WEBSOCKETS
* Un compilador que soporte C++14
#### Instrucciones
##### Windows
En Windows, la mejor manera de compilar es usar Qt Creator
##### Linux / Derivados
1. Primero generamos el `Makefile`
```
mkdir build && cd build
qmake ..
```
2. Compilamos:
```
make
```
