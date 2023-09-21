NAME = webserv

CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98 -fsanitize=address -g3

SRC = parseConfig/config_parsing.cpp Utils/utils.cpp\
      parseConfig/Server.cpp parseConfig/parse_server.cpp parseConfig/Location.cpp\
      parseConfig/parse_location.cpp parseRequest/Request.cpp\
      main.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o:%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
