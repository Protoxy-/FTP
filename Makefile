##
## Makefile for LemiPC in /home/hoerte_f/rendu/PSU_2014_lemipc
## 
## Made by Francois Hoertel
## Login   <hoerte_f@epitech.net>
## 
## Started on  Mon Mar  2 09:18:26 2015 Francois Hoertel
## Last update Sun Mar 29 18:56:35 2015 Francois Hoertel
##

NAMES	= serveur

NAMEC	= client

SERVER	= err_sys.c \
	  parsing.c \
	  server_init.c \
	  server_core.c \
	  server_action.c \
	  server_data.c \
	  sys_func.c \
	  dir_func.c \
	  file_func.c \
	  path_func.c \
	  server.c

CLIENT	= err_sys.c \
	  parsing.c \
	  client_init.c \
	  client_core.c \
	  client_data.c \
	  client_file.c \
	  client.c

CFLAGS	= -Werror -Wextra -Wall -W -I.

OBJS	= $(SERVER:.c=.o)

OBJC	= $(CLIENT:.c=.o)

CC	= gcc

RM	= rm -f

all:		$(NAMES) $(NAMEC)

$(NAMES):	 $(OBJS)
	$(CC) -o $(NAMES) $(OBJS)

$(NAMEC):	 $(OBJC)
	$(CC) -o $(NAMEC) $(OBJC)

clean:
	$(RM) $(OBJS) $(OBJC)

fclean:		clean
	$(RM) $(NAMES) $(NAMEC)

re:		fclean all

.PHONY:		all clean re fclean
