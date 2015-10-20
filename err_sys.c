/*
** err_sys.c for FTP in /home/hoerte_f/rendu/PSU_2014_myftp
** 
** Made by Francois Hoertel
** Login   <hoerte_f@epitech.net>
** 
** Started on  Fri Mar 13 19:06:10 2015 Francois Hoertel
** Last update Sat Mar 28 17:39:05 2015 Francois Hoertel
*/

#include "system.h"

int	err_msg(char *msg)
{
  if (msg[0] == ':')
    {
      write(1, "Error ", 6);
      write(1, msg, strlen(msg));
      write(1, "\n", 1);
    }
  else
    {
      write(1, msg, strlen(msg));
      write(1, "\n", 1);
    }
  return (-1);
}

void	*verr_msg(char *msg)
{
  err_msg(msg);
  return (NULL);
}

void	exit_err(char *msg)
{
  if (msg[0] == ':')
    {
      printf("Error %s\n", msg);
      exit(EXIT_FAILURE);
    }
  else
    {
      printf("%s\n", msg);
      exit(EXIT_SUCCESS);
    }
}

int	check_file(char *file_name, int type)
{
  int	fd;

  if (type == 0 && (fd = open(file_name, O_RDONLY)) != -1)
    {
      close(fd);
      if ((fd = open(file_name, O_WRONLY | O_CREAT,
		     S_IRUSR | S_IWUSR | S_IXUSR)) == -1)
	{
	  write(1, "Can't creat the file !\n", 23);
	  return (-1);
	}
      close(fd);
      remove(file_name);
      write(1, "This file already exist\n", 24);
      return (-2);
    }
  if (type == 1 && (fd = open(file_name, O_RDONLY)) == -1)
    {
      write(1, "This file not exist\n", 24);
      return (-1);
    }
  if (type == 1)
    close(fd);
  return (0);
}
