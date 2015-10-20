/*
** client_file.c for FTP in /home/hoerte_f/rendu/PSU_2014_myftp
** 
** Made by Francois Hoertel
** Login   <hoerte_f@epitech.net>
** 
** Started on  Sat Mar 21 19:00:14 2015 Francois Hoertel
** Last update Sun Mar 29 18:44:18 2015 Francois Hoertel
*/

#include "system.h"

int		send_read_ret(t_client *clt)
{
  if (clt->fd_data != -1)
    close(clt->fd_data);
  bzero(clt->srv_ret, 4096);
  if (read(clt->fd, clt->srv_ret, 4096) == -1)
    return (err_msg(": read fail"));
  write(1, clt->srv_ret, 4096);
  return (0);
}

int		send_file(t_client *clt)
{
  struct stat	st;
  int		fd;
  int		c;
  char		buff;
  long int	i;

  stat(get_param(clt->line, 1), &st);
  if ((fd = open(get_param(clt->line, 1), O_RDONLY)) == -1)
    return (err_msg(": open fail"));
  c = 0;
  i = 0;
  while (clt->fd_data != -1 && i < st.st_size && (c = read(fd, &buff, 1)) > 0)
    {
      if (write(clt->fd_data, &buff, 1) == -1)
	break;
      i++;
    }
  if (c == -1)
    return (err_msg(": Read fail"));
  if (send_read_ret(clt) == -1)
    return (-1);
  close(fd);
  return (0);
}

int	get_file(t_client *clt)
{
  char	bu;
  int	f;
  int	c;

  f = open(get_param(clt->line, 1), O_WRONLY | O_CREAT,
	   S_IRUSR | S_IWUSR | S_IXUSR);
  c = 0;
  while (f != -1 && clt->fd_data != -1 && (c = read(clt->fd_data, &bu, 1)) > 0)
    {
      if (write(f, &bu, 1) == -1)
	return (-1);
    }
  if (c == -1)
    return (err_msg(": Read fail"));
  bzero(clt->srv_ret, 4096);
  if (read(clt->fd, clt->srv_ret, 4096) == -1)
    return (err_msg(": read fail"));
  write(1, clt->srv_ret, 4096);
  if (f == -1)
    {
      err_msg(": Open fail");
      return (-2);
    }
  close(f);
  return (0);
}
