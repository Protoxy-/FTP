/*
** file_func.c for FTP in /home/hoerte_f/rendu/PSU_2014_myftp
** 
** Made by Francois Hoertel
** Login   <hoerte_f@epitech.net>
** 
** Started on  Fri Mar 13 17:29:13 2015 Francois Hoertel
** Last update Sun Mar 29 19:09:53 2015 Francois Hoertel
*/

#include "system.h"

long long int	get_file_info(t_server *srv)
{
  struct stat	st;
  char		*size;
  char		*msg;

  if ((size = malloc(sizeof(char) * 2000)) == NULL)
    return (err_msg(": Malloc fail"));
  if ((msg = malloc(sizeof(char) * 2000)) == NULL)
    return (err_msg(": Malloc fail"));
  stat(srv->param, &st);
  sprintf(size, "%lld", (long long int)st.st_size);
  msg = strcpy(msg, "150 Opening ASCII mode data connection for ");
  msg = add_to_end(msg, srv->param);
  msg = add_to_end(msg, " (");
  msg = add_to_end(msg, size);
  msg = add_to_end(msg, " bytes).\n");
  send_info(srv, msg, 0);
  free(size);
  free(msg);
  return (st.st_size);
}

int		retr(t_server *srv)
{
  char		*buff;
  int		fd;
  int		chk;
  long long int	size;
  long long int	i;

  if ((size = get_file_info(srv)) == -1)
    return (-1);
  fd = open(srv->param, O_RDONLY, S_IRUSR | S_IWUSR);
  if (fd == -1)
    return (send_info(srv, "550 Permission denied.\n", 0));
  i = 0;
  while ((chk = read(fd, &buff, 1)) > 0 && i < size)
    {
      if (write(srv->fd_data, &buff, 1) == -1)
	{
	  send_info(srv, "426 Connection closed; transfer aborted.\n", 0);
	  return (0);
	}
      i++;
    }
  close(srv->fd_data);
  send_info(srv, (chk == -1 ? "550 err Folder" : "226 Transfer complete."), 1);
  close(fd);
  return (0);
}

int	stor(t_server *srv)
{
  int	fd;
  int	chk;
  char	buff;

  send_info(srv, "150 Opening ASCII mode data connection.\n", 0);
  if (check_file(srv->param, 0) < 0)
    {
      send_info(srv, "550 Permission denied.\n", 0);
      close(srv->fd_data);
      return (0);
    }
  fd = open(srv->param, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IXUSR);
  while (srv->fd_data != -1 && (chk = read(srv->fd_data, &buff, 1)) > 0)
    {
      if (write(fd, &buff, 1) == -1)
	{
	  send_info(srv, "550 Permission denied.\n", 0);
	  close(srv->fd_data);
	  return (0);
	}
    }
  close(fd);
  send_info(srv, (chk == -1 ? "550 Permission denied.\n"
		  : "226 Transfer complete.\n"), 0);
  return (0);
}

int	dele(t_server *srv)
{
  if (remove(srv->param) == -1)
    {
      send_info(srv, "232 This file does not exist", 1);
      return (-2);
    }
  send_info(srv, "450 The file is rm", 1);
  return (0);
}
