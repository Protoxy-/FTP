/*
** client_init.c for FTP in /home/hoerte_f/rendu/PSU_2014_myftp
** 
** Made by Francois Hoertel
** Login   <hoerte_f@epitech.net>
** 
** Started on  Thu Mar 19 13:14:01 2015 Francois Hoertel
** Last update Sun Mar 29 15:03:31 2015 Francois Hoertel
*/

#include "system.h"

void	init_server_name(t_client *clt)
{
  clt->func_name[0][0] = "USER";
  clt->func_name[1][0] = "PASS";
  clt->func_name[2][0] = "CWD";
  clt->func_name[3][0] = "CDUP";
  clt->func_name[4][0] = "QUIT";
  clt->func_name[5][0] = "RETR";
  clt->func_name[6][0] = "STOR";
  clt->func_name[7][0] = "DELE";
  clt->func_name[8][0] = "PWD";
  clt->func_name[9][0] = "LIST";
  clt->func_name[10][0] = "HELP";
  clt->func_name[11][0] = "NOOP";
}

int	init_func_name(t_client *clt)
{
  int	i;

  if ((clt->func_name = malloc(sizeof(char**) * 12)) == NULL)
    return (err_msg(": Malloc fail"));
  i = 0;
  while (i < 12)
    {
      if ((clt->func_name[i] = malloc(sizeof(char*) * 4)) == NULL)
	return (err_msg(": Malloc fail"));
      i++;
    }
  init_server_name(clt);
  clt->func_name[0][1] = "USER";
  clt->func_name[1][1] = "PASS";
  clt->func_name[2][1] = "cd";
  clt->func_name[3][1] = "cd-";
  clt->func_name[4][1] = "quit";
  clt->func_name[5][1] = "get";
  clt->func_name[6][1] = "put";
  clt->func_name[7][1] = "rm";
  clt->func_name[8][1] = "pwd";
  clt->func_name[9][1] = "ls";
  clt->func_name[10][1] = "man";
  clt->func_name[11][1] = "NOOP";
  return (0);
}

int	client_init(t_client *clt, char **av)
{
  clt->port = atoi(av[2]);
  clt->log = 0;
  if (!(clt->pe = getprotobyname("TCP")))
    return (err_msg("Err: getprotobyname\n"));
  if ((clt->fd = socket(AF_INET, SOCK_STREAM, clt->pe->p_proto)) == -1)
    return (err_msg("Err: socket\n"));
  clt->sin.sin_family = AF_INET;
  clt->sin.sin_port = htons(clt->port);
  clt->sin.sin_addr.s_addr = inet_addr(av[1]);
  clt->ip = av[1];
  if (connect(clt->fd, (const struct sockaddr *)&clt->sin, sizeof(clt->sin))
      == -1)
    return (err_msg("Err: connect\n"));
  if ((clt->line = malloc(sizeof(char) * 4096)) == NULL)
    return (err_msg(": Malloc fail"));
  if ((clt->srv_ret = malloc(sizeof(char) * 4096)) == NULL)
    return (err_msg(": Malloc fail"));
  if ((clt->srv_data = malloc(sizeof(char) * 4096)) == NULL)
    return (err_msg(": Malloc fail"));
  if (init_func_name(clt) == -1)
    return (-1);
  return (1);
}
