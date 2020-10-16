# App-Mensajeria
Un programa en desarrollo que usa la tecnología de los WebSockets para enviar y recibir mensajes entre clientes gracias a un servidor.
## Compilación
### Dependencias
* Qt 5.15. Módulos GUI, NETWORK y WEBSOCKETS
* Un compilador que soporte C++14
### Instrucciones
#### Descargar
Este proyecto usa submódulos. Es necesario clonarlos para poder compilar. Si no los clonas, la carpeta de `third_party` estará vacía.
```
git clone --recurse-submodules https://github.com/GrageraE/App-Mensajeria.git
```
Si ya has clonado el proyecto, usa
```
git submodule update --init --recursive
```
#### Windows
En Windows, la mejor manera de compilar es usar Qt Creator
#### Linux / Derivados
1. Primero generamos el `Makefile`
```
mkdir build && cd build
qmake ..
```
2. Compilamos:
```
make
```
## Créditos a librerias
* [JSON For Modern C++](https://github.com/nlohmann/json) - Intérprete de JSON que usa el servidor para guardar las IPs de los usuarios baneados.
* Qt - Framework con el que se desarrolla la GUI y con el que se manejan los websockets.
