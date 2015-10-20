/*
** client.c for Client in /home/hoerte_f/rendu/PSU_2014_myftp
** 
** Made by Francois Hoertel
** Login   <hoerte_f@epitech.net>
** 
** Started on  Mon Mar  9 11:28:21 2015 Francois Hoertel
** Last update Sun Mar 29 18:26:24 2015 Francois Hoertel
*/

#include "system.h"

int		main(int ac, char **av)
{
  t_client	*clt;

  if ((clt = malloc(sizeof(t_client))) == NULL)
    return (err_msg(": malloc fail"));
  if (ac != 3)
    {
      printf("Usage: ./client <ip server> <port nb>\n");
      return (-1);
    }
  if (client_init(clt, av) == -1)
    return (-1);
  if (client_loop(clt) == -1)
    return (-1);
  close(clt->fd);
  free(clt->line);
  free(clt->srv_ret);
  return (1);
}
