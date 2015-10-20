/*
** server_core.c for FTP in /home/hoerte_f/rendu/PSU_2014_myftp
** 
** Made by Francois Hoertel
** Login   <hoerte_f@epitech.net>
** 
** Started on  Sun Mar 15 23:50:09 2015 Francois Hoertel
** Last update Sun Mar 29 19:22:10 2015 Francois Hoertel
*/

#include "system.h"

int	server_action(t_server *srv)
{
  int	chk;

  if ((chk = (srv->func[srv->last])(srv)) < 0)
    return (chk);
  if (srv->dataco == 1)
    {
      close(srv->fd_data);
      srv->dataco = 0;
    }
  return (0);
}

int	get_comval(t_server *srv)
{
  char	*func;
  int	i;

  func = get_param(srv->buff, 0);
  srv->param = get_param(srv->buff, 1);
  i = 0;
  while (i < 13)
    {
      if (check_command(func, srv->func_name[i]) == 0)
        break;
      i++;
    }
  srv->last = i;
  if (i == 13)
    {
      send_info(srv, "502 Command not implemented.", 0);
      return (-2);
    }
  return (0);
}

int	server_check(t_server *srv)
{
  if (srv->log == 0 && srv->last != 0 && srv->last != 4)
    {
      send_info(srv, "530 Please login with USER and PASS.\n", 0);
      return (-2);
    }
  if ((srv->log == 1 || srv->log == 2) && srv->last != 1 && srv->last != 4)
    {
      send_info(srv, "530 Please login with USER and PASS.\n", 0);
      return (-2);
    }
  if (srv->last == 12 && creat_data_port(srv) == -1)
    {
      send_info(srv, "425 Cannot open data connection.\n", 0);
      return (-2);
    }
  return (0);
}

int	server_event(t_server *srv)
{
  int	chk;

  bzero(srv->buff, 4096);
  if (read(srv->clt_fd, srv->buff, 4096) == -1)
    return (err_msg(": connection lose"));
  write(1, srv->buff, 4096);
  if (get_comval(srv) == -2)
    return (0);
  if ((chk = server_check(srv)) == -1)
    return (-1);
  if (chk == -2)
    return (0);
  if ((chk = server_action(srv)) == -1)
    return (-1);
  if (chk == -2)
    return (0);
  if (g_connected == 1)
    {
      err_msg(": connection lose");
      return (-1);
    }
  return (0);
}

int	server_loop(t_server *srv)
{
  while (42)
    {
      if (server_event(srv) == -1)
	return (-1);
    }
  return (0);
}
