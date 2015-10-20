/*
** serveur.h for Serveur in /home/hoerte_f/rendu/PSU_2014_myftp
** 
** Made by Francois Hoertel
** Login   <hoerte_f@epitech.net>
** 
** Started on  Mon Mar  9 11:24:30 2015 Francois Hoertel
** Last update Sun Mar 22 18:35:29 2015 Francois Hoertel
*/

#ifndef CLIENT_H_
# define CLIENT_H_

typedef struct		s_client
{
  char			***func_name;
  char			*ip;
  char			*line;
  char			*srv_ret;
  char			*srv_data;
  int			last_com;
  struct protoent	*pe_data;
  struct protoent	*pe;
  struct sockaddr_in	sin;
  int			fd;
  struct sockaddr_in	sin_data;
  int			fd_data;
  int			port;
  int			log;
  char			*str;
}			t_client;

int			client_init(t_client *, char **);
int			init_func_name(t_client *);
void			init_server_name(t_client *);
int			init_data_port(t_client *, int);
int			init_data_connexion(t_client *, int);
int			client_get_data(t_client *);
int			client_loop(t_client *);
int			check_end(t_client *);
int			get_file(t_client *);
int			send_file(t_client *);

#endif /* CLIENT_H_ */
