/*
** serveur.h for Serveur in /home/hoerte_f/rendu/PSU_2014_myftp
** 
** Made by Francois Hoertel
** Login   <hoerte_f@epitech.net>
** 
** Started on  Mon Mar  9 11:24:30 2015 Francois Hoertel
** Last update Sun Mar 29 19:15:26 2015 Francois Hoertel
*/

#ifndef SERVEUR_H_
# define SERVEUR_H_

int			g_connected;

typedef struct		s_server
{
  int			(**func)(struct s_server *);
  char			**func_name;
  char			**resp_clt;
  char			*ip;
  char			*path;
  int			path_pos;
  struct protoent	*pe;
  struct protoent	*pe_data;
  struct sockaddr_in	sin;
  struct sockaddr_in	sin_clt_data;
  int			last;
  int			log;
  int			dataco;
  int			port;
  struct sockaddr_in	sin_clt;
  socklen_t		sin_size;
  struct sockaddr_in	sin_data;
  socklen_t		sin_data_s;
  int			clt_fd;
  int			fd;
  int			in_data;
  int			fd_data;
  char			*clt_ip;
  char			*buff;
  char			*clt_ret;
  char			*clt_data;
  char			*param;
}			t_server;

int	server_init(t_server *);
int	assign_func(t_server *);
int	assign_func_name(t_server *);
char	*cut_path(char *);
char	*add_path(char *, char *);
int	user(t_server *);
int	pass(t_server *);
int	cwd(t_server *);
int	cdup(t_server *);
int	quit(t_server *);
int	retr(t_server *);
int	stor(t_server *);
int	dele(t_server *);
int	pwd(t_server *);
int	list(t_server *);
int	help(t_server *);
int	noop(t_server *);
int	send_info(t_server *, char *, int);
int	send_keymsg(t_server *, char *);
int     creat_data_port(t_server *);
int	data_send_port(t_server *, int);
int	server_send_data(t_server *);
char	*get_param(char *, int);
int	get_comval(t_server *);
int	server_action(t_server *);
int	server_loop(t_server *);

#endif /* SERVEUR_H_ */
