/*
** server_data.c for FTP in /home/hoerte_f/rendu/PSU_2014_myftp
** 
** Made by Francois Hoertel
** Login   <hoerte_f@epitech.net>
** 
** Started on  Sat Mar 21 14:10:01 2015 Francois Hoertel
** Last update Sun Mar 29 18:35:29 2015 Francois Hoertel
*/

#include "system.h"

int	init_data_port(t_client *clt, int port)
{
  if (!(clt->pe_data = getprotobyname("TCP")))
    return (err_msg("Err: getprotobyname\n"));
  if ((clt->fd_data = socket(AF_INET, SOCK_STREAM, clt->pe_data->p_proto))
      == -1)
    return (err_msg("Err: socket\n"));
  clt->sin_data.sin_family = AF_INET;
  clt->sin_data.sin_port = htons(port);
  clt->sin_data.sin_addr.s_addr = inet_addr(clt->ip);
  if (connect(clt->fd_data, (const struct sockaddr *)&clt->sin_data,
	      sizeof(clt->sin_data)) == -1)
    {
      close(clt->fd_data);
      return (err_msg("Err: connect\n"));
    }
  return (0);
}

int	data_get_port(t_client *clt)
{
  char	*tmp;
  int	port;
  int	i;
  int	j;

  if ((tmp = malloc(sizeof(char) * 10)) == NULL)
    return (err_msg(": Malloc fail"));
  i = strlen(clt->srv_ret) - 1;
  while (i > 0 && clt->srv_ret[i] != ',')
    i--;
  i--;
  while (i > 0 && clt->srv_ret[i - 1] != ',')
    i--;
  j = 0;
  while (clt->srv_ret[i] && clt->srv_ret[i] != ',')
    tmp[j++] = clt->srv_ret[i++];
  tmp[j] = '\0';
  port = atoi(tmp) * 256;
  j = 0;
  while (clt->srv_ret[i + 1] && clt->srv_ret[i + 1] != ')')
    tmp[j++] = clt->srv_ret[1 + (i++)];
  tmp[j] = '\0';
  port += atoi(tmp);
  return (port);
}

int	init_data_connexion(t_client *clt, int command)
{
  int	port;

  if (clt->log == 0 || (command != 5 && command != 6 && command != 9))
    return (0);
  if (write(clt->fd, "PASV\n", 5) == -1)
    return (err_msg(": Write to server fail"));
  bzero(clt->srv_ret, 4096);
  if (read(clt->fd, clt->srv_ret, 4096) == -1)
    return (err_msg(": Read to server fail"));
  write(1, clt->srv_ret, 4096);
  if (check_keycode(clt->srv_ret, "425") == 0)
    return (-1);
  if ((port = data_get_port(clt)) == -1)
    return (-1);
  if (init_data_port(clt, port) == -1)
    return (-1);
  return (0);
}

int	client_get_data(t_client *clt)
{
  int	chk;

  if (clt->last_com == 5)
    if ((chk = get_file(clt)) < 2)
      return (chk);
  if (clt->last_com == 6)
    if ((chk = send_file(clt)) < 2)
      return (chk);
  bzero(clt->srv_data, 4096);
  while ((chk = read(clt->fd_data, clt->srv_data, 4096)) > 0)
    {
      if (clt->last_com == 9)
	write(1, clt->srv_data, 4096);
      bzero(clt->srv_data, 4096);
    }
  if (chk == -1)
    return (err_msg(": can't read on server data port"));
  bzero(clt->srv_ret, 4096);
  if (read(clt->fd, clt->srv_ret, 4096) == -1)
    return (-1);
  if (check_keycode(clt->srv_ret, "226") == -1)
    return (-1);
  return (0);
}
