/*
** client_core.c for FTP in /home/hoerte_f/rendu/PSU_2014_myftp
** 
** Made by Francois Hoertel
** Login   <hoerte_f@epitech.net>
** 
** Started on  Thu Mar 19 13:36:15 2015 Francois Hoertel
** Last update Sun Mar 29 19:23:45 2015 Francois Hoertel
*/

#include "system.h"

char	*replace_command(t_client *clt, char *new, int pos)
{
  int	i;
  int	j;

  new = strcpy(new, clt->func_name[pos][0]);
  j = strlen(new);
  i = 0;
  while (clt->line[i] && clt->line[i] != ' ')
    i++;
  while (clt->line[i] && clt->line[i] == ' ')
    i++;
  new[j++] = ' ';
  while (clt->line[i] && clt->line[i] != ' ')
    {
      new[j] = clt->line[i];
      i++;
      j++;
    }
  if (new[j] != '\n')
    new[j++] = '\n';
  new[j++] = '\0';
  return (new);
}

int	send_check_command(t_client *clt)
{
  char	*func;
  int	pos;

  func = get_param(clt->line, 0);
  pos = 0;
  while (pos < 12 && check_command(func, clt->func_name[pos][1]) == -1 &&
	 check_command(func, clt->func_name[pos][0]) == -1)
    pos++;
  clt->last_com = pos;
  if (pos == 12)
    {
      err_msg("501 Syntax error in parameters or arguments.");
      return (-2);
    }
  if (pos == 5)
    if (check_file(get_param(clt->line, 1), 0) < 0)
      return (-2);
  if (pos == 6)
    if (check_file(get_param(clt->line, 1), 1) < 0)
      return (-2);
  return (0);
}

int	send_command(t_client *clt)
{
  char	*new;

  if ((new = malloc(sizeof(char) * (strlen(clt->line) + 100))) == NULL)
    return (err_msg(": Malloc fail"));
  if (send_check_command(clt) == -2)
    return (-2);
  new = replace_command(clt, new, clt->last_com);
  if (init_data_connexion(clt, clt->last_com) == -1)
    return (-2);
  write(clt->fd, new, strlen(new));
  free(new);
  return (0);
}

int     server_interpret(t_client *clt)
{
  bzero(clt->srv_ret, 4096);
  read(clt->fd, clt->srv_ret, 4096);
  write(1, clt->srv_ret, strlen(clt->srv_ret));
  if (check_keycode(clt->srv_ret, "150") == 0)
    if (client_get_data(clt) == -1)
      return (-1);
  if (check_keycode(clt->srv_ret, "230") == 0)
    clt->log = 1;
  if (check_keycode(clt->srv_ret, "221") == 0 ||
      check_keycode(clt->srv_ret, "421") == 0)
    return (-2);
  return (0);
}

int	client_loop(t_client *clt)
{
  int	chk;

  read(clt->fd, clt->srv_ret, 4096);
  write(1, clt->srv_ret, strlen(clt->srv_ret));
  while (42)
    {
      write(1, "<~§~> ", 7);
      bzero(clt->line, 4096);
      if (read(1, clt->line, 4096) > 0)
	{
	  if ((chk = send_command(clt)) == -1)
	    return (-1);
	  if (chk != -2)
	    {
	      if ((chk = server_interpret(clt)) == -1)
		return (-1);
	      if (chk == -2)
		return (0);
	    }
	}
    }
  return (0);
}
