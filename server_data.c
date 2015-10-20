/*
** server_data.c for FTP in /home/hoerte_f/rendu/PSU_2014_myftp
** 
** Made by Francois Hoertel
** Login   <hoerte_f@epitech.net>
** 
** Started on  Sun Mar 22 01:19:56 2015 Francois Hoertel
** Last update Sun Mar 29 19:13:09 2015 Francois Hoertel
*/

#include "system.h"

char	*data_send_info(int port, int i, char *ret)
{
  char	*tmp;
  int	j;

  if ((tmp = malloc(sizeof(char) * 60)) == NULL)
    return (verr_msg(": Malloc fail"));
  sprintf(tmp, "%d\n", port % 256);
  j = 0;
  while (tmp[j] && tmp[j] != '\n')
    ret[i++] = tmp[j++];
  ret[i++] = ',';
  sprintf(tmp, "%d\n", port / 256);
  j = 0;
  while (tmp[j] && tmp[j] != '\n')
    ret[i++] = tmp[j++];
  ret[i++] = ')';
  ret[i++] = '.';
  ret[i++] = '\n';
  ret[i++] = '\0';
  return (ret);
}

int	data_send_port(t_server *srv, int port)
{
  char	*ret;
  int	i;
  int	j;

  if ((ret = malloc(sizeof(char) * 60)) == NULL)
    return (err_msg(": Malloc fail"));
  ret = strcpy(ret, "227 Entering Passive Mode (");
  i = strlen(ret);
  j = -1;
  while (srv->ip[++j])
    ret[i++] = (srv->ip[j] != '.' ? srv->ip[j] : ',');
  ret[i++] = ',';
  if ((ret = data_send_info(port, i, ret)) == NULL)
    return (-1);
  write(srv->clt_fd, ret, strlen(ret));
  return (0);
}

int	init_data_sock(t_server *srv)
{
  int	i;

  srv->sin_clt_data.sin_family = AF_INET;
  srv->sin_clt_data.sin_port = htons(1024 + (rand() % 1000));
  srv->sin_clt_data.sin_addr.s_addr = INADDR_ANY;
  i = 0;
  while (i < 200 && bind(srv->in_data, (struct sockaddr *)&srv->sin_clt_data,
			 sizeof(srv->sin_clt_data)) == -1)
    {
      close(srv->in_data);
      srv->sin_clt_data.sin_port = htons(1024 + (rand() % 1000));
      i++;
    }
  if (i == 200)
    return (err_msg(": bind fail"));
  if (listen(srv->in_data, 42) == -1)
    {
      close(srv->in_data);
      return (err_msg(": listen fail"));
    }
  return (0);
}

int	creat_data_port(t_server *srv)
{
  if ((srv->in_data = socket(AF_INET, SOCK_STREAM, srv->pe->p_proto)) == -1)
    return (printf("Err: socket\n"));
  if (init_data_sock(srv) == -1)
    return (-1);
  if (data_send_port(srv, srv->sin_clt_data.sin_port) == -1)
    return (-1);
  srv->fd_data = accept(srv->in_data, (struct sockaddr *)&srv->sin_data,
			&srv->sin_data_s);
  if (srv->fd_data == -1)
    {
      close(srv->fd_data);
      return (err_msg(": accept fail"));
    }
  srv->ip = inet_ntoa(srv->sin_data.sin_addr);
  read(srv->clt_fd, srv->buff, 4096);
  get_comval(srv);
  srv->dataco = 1;
  return (0);
}
