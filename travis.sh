#!/bin/bash

cd Reckless_Chasing
qmake Reckless_Chasing.pro
make

cd ..
cd simple_socket
qmake simple_socket.pro
make
