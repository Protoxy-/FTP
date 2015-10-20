/*
** server_init.c for FTP in /home/hoerte_f/rendu/PSU_2014_myftp
** 
** Made by Francois Hoertel
** Login   <hoerte_f@epitech.net>
** 
** Started on  Fri Mar 13 17:37:22 2015 Francois Hoertel
** Last update Sun Mar 29 19:16:05 2015 Francois Hoertel
*/

#include "system.h"

int	assign_func(t_server *srv)
{
  if ((srv->func = malloc(sizeof(srv->func) * 12)) == NULL)
    return (err_msg(": Malloc fail"));
  if ((srv->buff = malloc(sizeof(char) * 4096)) == NULL)
    return (err_msg(": Malloc fail"));
  if ((srv->clt_ret = malloc(sizeof(char) * 4096)) == NULL)
    return (err_msg(": Malloc fail"));
  if ((srv->clt_data = malloc(sizeof(char) * 4096)) == NULL)
    return (err_msg(": Malloc fail"));
  srv->func[0] = &user;
  srv->func[1] = &pass;
  srv->func[2] = &cwd;
  srv->func[3] = &cdup;
  srv->func[4] = &quit;
  srv->func[5] = &retr;
  srv->func[6] = &stor;
  srv->func[7] = &dele;
  srv->func[8] = &pwd;
  srv->func[9] = &list;
  srv->func[10] = &help;
  srv->func[11] = &noop;
  return (0);
}

int	assign_func_name(t_server *srv)
{
  int	i;

  if ((srv->func_name = malloc(sizeof(char *) * 15)) == NULL)
    return (err_msg(": Malloc fail"));
  i = 0;
  while (i < 14)
    {
      if ((srv->func_name[i] = malloc(sizeof(char) * 6)) == NULL)
	return (err_msg(": Malloc fail"));
      i++;
    }
  srv->func_name[0] = "USER";
  srv->func_name[1] = "PASS";
  srv->func_name[2] = "CWD";
  srv->func_name[3] = "CDUP";
  srv->func_name[4] = "QUIT";
  srv->func_name[5] = "RETR";
  srv->func_name[6] = "STOR";
  srv->func_name[7] = "DELE";
  srv->func_name[8] = "PWD";
  srv->func_name[9] = "LIST";
  srv->func_name[10] = "HELP";
  srv->func_name[11] = "NOOP";
  srv->func_name[12] = "PASV";
  return (0);
}

int	init_response(t_server *srv)
{
  srv->dataco = 0;
  srv->path_pos = 0;
  if ((srv->path = getenv("PWD")) == NULL)
    return (err_msg(": getenv fail"));
  g_connected = 0;
  if ((srv->resp_clt = malloc(sizeof(char *) * 10)) == NULL)
    return (err_msg(": Malloc fail"));
  srv->resp_clt[0] = "220 (vsFTPd 3.0.0)";
  srv->resp_clt[1] = "530 Please login with USER and PASS.";
  srv->resp_clt[2] = "331 Please specify the password.";
  srv->resp_clt[3] = "230 Login successful.";
  srv->resp_clt[4] = "530 Login incorrect.";
  srv->resp_clt[5] = "221 Goodbye.";
  srv->resp_clt[6] = "150 Here comes the directory listing.";
  srv->resp_clt[7] = NULL;
  srv->resp_clt[8] = NULL;
  return (0);
}

int	server_init(t_server *srv)
{
  if (!(srv->pe = getprotobyname("TCP")))
    return (printf("Err: getproto\n"));
  if ((srv->fd = socket(AF_INET, SOCK_STREAM, srv->pe->p_proto)) == -1)
    return (printf("Err: socket\n"));
  srv->log = 0;
  srv->sin.sin_family = AF_INET;
  srv->sin.sin_port = htons(srv->port);
  srv->sin.sin_addr.s_addr = INADDR_ANY;
  if (bind(srv->fd, (struct sockaddr *)&srv->sin, sizeof(srv->sin)) == -1)
    {
      close(srv->fd);
      return (err_msg("Err: bind\n"));
    }
  if (listen(srv->fd, 42) == -1)
    {
      close(srv->fd);
      return (err_msg("Err: listen\n"));
    }
  if (assign_func(srv) == -1)
    return (-1);
  if (assign_func_name(srv) == -1)
    return (-1);
  if (init_response(srv) == -1)
    return (-1);
  return (0);
}
