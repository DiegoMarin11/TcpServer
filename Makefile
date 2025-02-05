# Compiler and Flags
CC = gcc
CFLAGS = -Wall -g -IAPI $(shell pkg-config --cflags libmongoc-1.0)
LIBS = $(shell pkg-config --libs libmongoc-1.0)

# Directories
API_DIR = API
CLIENT_DIR = Clients
SERVER_DIR = Server

# Object files
OBJ = $(SERVER_DIR)/server.o $(API_DIR)/MongoInterface.o $(API_DIR)/parser.o
CLIENT_OBJ = $(CLIENT_DIR)/client.o

# Server executable
my_server: $(OBJ)
	$(CC) $(OBJ) -o s $(LIBS)

# Client executable
my_client: $(CLIENT_OBJ)
	$(CC) $(CLIENT_OBJ) -o c $(LIBS)

# Rule to compile .c files into .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJ) $(CLIENT_OBJ) s c
#gcc -o client ./Clients/client.c
# netsh advfirewall set allprofiles state off