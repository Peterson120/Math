g++ $1 -std=c++11 -I/usr/include/python3.10 -lpython3.10 -g -o $(echo "$1" | cut -f 1 -d '.') && ./$(echo "$1" | cut -f 1 -d '.')
