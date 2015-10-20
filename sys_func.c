/*
** sys_func.c for FTP in /home/hoerte_f/rendu/PSU_2014_myftp
** 
** Made by Francois Hoertel
** Login   <hoerte_f@epitech.net>
** 
** Started on  Fri Mar 13 17:27:37 2015 Francois Hoertel
** Last update Sun Mar 29 16:07:49 2015 Francois Hoertel
*/

#include "system.h"

int	user(t_server *srv)
{
  srv->log = 1;
  if (check_command(srv->param, "anonymous") == 0)
    srv->log = 2;
  send_info(srv, "331 Please specify the password.\n", 0);
  return (0);
}

int	pass(t_server *srv)
{
  if (srv->log == 2)
    {
      srv->log = 3;
      if (send_info(srv, "230 Login successful.", 1) == -1)
	return (-1);
    }
  else if (srv->log != 0)
    {
      srv->log = 0;
      if (send_info(srv, "530 Login incorrect.", 1) == -1)
	return (-1);
    }
  else
    if (send_info(srv, "332 Need account for login.", 1) == -1)
      return (-1);
  return (0);
}

int	quit(t_server *srv)
{
  if (send_keymsg(srv, "221") == -1)
    return (-1);
  return (-2);
}

int	help(t_server *srv)
{
  send_info(srv, "214-The following commands are recognized.", 1);
  send_info(srv, "ABOR ACCT ALLO APPE CDUP CWD  DELE EPRT EPSV ", 0);
  send_info(srv, "FEAT HELP LIST MDTM MKD  MODE NLST NOOP OPTS ", 0);
  send_info(srv, "PASS PASV PORT PWD  QUIT REIN REST RETR RMD  ", 0);
  send_info(srv, "RNFR RNTO SITE SIZE SMNT STAT STOR STOU STRU ", 0);
  send_info(srv, "SYST TYPE USER XCUP XCWD XMKD XPWD XRMD ", 1);
  send_info(srv, "214 Help OK.", 1);
  return (0);
}

int	noop(t_server *srv)
{
  if (send_info(srv, "200 NOOP ok.", 1) == -1)
    return (-1);
  return (0);
}
