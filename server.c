/*
** serveur.c for Serveur in /home/hoerte_f/rendu/PSU_2014_myftp
** 
** Made by Francois Hoertel
** Login   <hoerte_f@epitech.net>
** 
** Started on  Mon Mar  9 11:28:53 2015 Francois Hoertel
** Last update Sun Mar 29 19:03:15 2015 Francois Hoertel
*/

#include "system.h"

void		server_close(t_server *srv)
{
  close(srv->fd);
  close(srv->clt_fd);
  free(srv);
}

int		init_connect(t_server *srv)
{
  while (42)
    {
      srv->clt_fd = accept(srv->fd, (struct sockaddr *)&srv->sin_clt,
			   &srv->sin_size);
      if (srv->clt_fd == -1)
	{
	  close(srv->fd);
	  return (printf("Err: accept\n"));
	}
      if (fork() == 0)
	{
	  srv->clt_ip = inet_ntoa(srv->sin_clt.sin_addr);
	  if (send_keymsg(srv, "220") == -1)
	    return (-1);
	  if (server_loop(srv) == -1)
	    return (-1);
	  return (0);
	}
    }
  return (0);
}

int		main(int ac, char **av)
{
  t_server	*srv;

  if ((srv = malloc(sizeof(t_server))) == NULL)
    return (err_msg(": Malloc fail"));
  if (ac != 2)
    return (err_msg("Usage: ./server <port_nb>"));
  srv->port = atoi(av[1]);
  if (server_init(srv) == -1)
    return (-1);
  srv->ip = "128.0.0.8";
  init_connect(srv);
  server_close(srv);
  return (0);
}
