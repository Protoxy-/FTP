/*
** system.h for System in /home/hoerte_f/rendu/PSU_2014_myftp
** 
** Made by Francois Hoertel
** Login   <hoerte_f@epitech.net>
** 
** Started on  Tue Mar 10 14:40:00 2015 Francois Hoertel
** Last update Sat Mar 28 18:19:42 2015 Francois Hoertel
*/

#ifndef SYSTEM_H_
# define SYSTEM_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <dirent.h>

#include "server.h"
#include "client.h"

int	err_msg(char *);
void	*verr_msg(char *);
void	nerr_msg(char *);
void	exit_err(char *);
char	*add_to_end(char *, char *);
char	*get_param(char *, int);
int	check_command(char *, char *);
int	check_keycode(char *, char *);
int	check_file(char *, int);

#endif /* SYSTEM_H_ */
