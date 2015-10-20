/*
** server_action.c for FTP in /home/hoerte_f/rendu/PSU_2014_myftp
** 
** Made by Francois Hoertel
** Login   <hoerte_f@epitech.net>
** 
** Started on  Sun Mar 15 23:21:35 2015 Francois Hoertel
** Last update Sun Mar 29 19:16:57 2015 Francois Hoertel
*/

#include "system.h"

int	send_info(t_server *srv, char *str, int n)
{
  char	*new;
  int	i;

  if ((new = malloc(sizeof(char) * (strlen(str) + 4))) == NULL)
    return (err_msg(": malloc fail"));
  new = strcpy(new, str);
  i = strlen(new);
  if (new[i - 1] == '\n')
    {
      new[i - 1] = '\r';
      new[i] = '\n';
      new[i + 1] = '\0';
    }
  if (n == 1)
    {
      new[i] = '\r';
      new[i + 1] = '\n';
      new[i + 2] = '\0';
    }
  if (write(srv->clt_fd, new, strlen(new)) == -1)
    g_connected = 1;
  free(new);
  return (0);
}

int	send_keymsg(t_server *srv, char *str)
{
  int	i;
  int	j;
  int	k;

  i = 0;
  while (srv->resp_clt[i])
    {
      j = 0;
      k = 0;
      while (str[j])
	{
	  if (str[j] == srv->resp_clt[i][j])
	    k++;
	  j++;
	}
      if (j == k)
	break ;
      i++;
    }
  if (send_info(srv, srv->resp_clt[i], 1) == -1)
    return (-1);
  return (0);
}
