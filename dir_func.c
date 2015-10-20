/*
** dir_func.c for FTP in /home/hoerte_f/rendu/PSU_2014_myftp
** 
** Made by Francois Hoertel
** Login   <hoerte_f@epitech.net>
** 
** Started on  Fri Mar 13 17:26:04 2015 Francois Hoertel
** Last update Sun Mar 29 18:47:22 2015 Francois Hoertel
*/

#include "system.h"

int	cwd_up(t_server *srv)
{
  char	*pwd;

  pwd = getenv("PWD");
  if ((pwd = cut_path(pwd)) == NULL || srv->path_pos == 0)
    {
      send_info(srv, "550 Failed to change directory.", 1);
      return (0);
    }
  if (chdir(pwd) == -1)
    return (err_msg("Error chdir fail"));
  srv->path_pos--;
  setenv("PWD", pwd, 1);
  send_info(srv, "200 Directory successfully changed.", 1);
  return (0);
}

int	cwd(t_server *srv)
{
  int	chk;
  char	*pwd;
  char	*new_pwd;

  pwd = getenv("PWD");
  if (srv->param[0] == '.' && srv->param[1] == '.')
    if ((chk = cwd_up(srv)) <= 0)
      return (chk);
  if (chdir(srv->param) == -1)
    {
      send_info(srv, "550 Failed to change directory.", 1);
      return (0);
    }
  if (srv->param[0] != '/')
    new_pwd = add_path(pwd, srv->param);
  else
    new_pwd = srv->param;
  setenv("PWD", new_pwd, 1);
  send_info(srv, "250 Directory successfully changed.", 1);
  srv->path_pos++;
  return (0);
}

int	cdup(t_server *srv)
{
  if (chdir(srv->path) == -1)
    {
      send_info(srv, "550 Failed to change directory.", 1);
      return (0);
    }
  setenv("PWD", srv->path, 1);
  send_info(srv, "250 Directory successfully changed.", 1);
  srv->path_pos = 0;
  return (0);
}

int	pwd(t_server *srv)
{
  char	*pwd;

  pwd = getenv("PWD");
  if (send_info(srv, "257 \"", 0) == -1)
    return (-1);
  if (send_info(srv, pwd, 0) == -1)
    return (-1);
  if (send_info(srv, "\"", 1) == -1)
    return (-1);
  return (0);
}

int	list(t_server *srv)
{
  int	pid;

  if (send_info(srv, "150 Here comes the directory listing.\n", 0) == -1)
    return (-1);
  if ((pid = fork()) == -1)
    return (err_msg(": fork fail"));
  if (pid == 0)
    {
      dup2(srv->fd_data, 1);
      if (execlp("ls", "ls", "-l", (char*)NULL) == -1)
	{
	  err_msg("LS fail");
	  return (-2);
	}
      return (0);
    }
  close(srv->fd_data);
  if (send_info(srv, "226 Here comes the directory listing.\n", 0) == -1)
    return (-1);
  return (0);
}
