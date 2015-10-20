/*
** path_func.c for FTP in /home/hoerte_f/rendu/PSU_2014_myftp
** 
** Made by Francois Hoertel
** Login   <hoerte_f@epitech.net>
** 
** Started on  Wed Mar 18 21:05:01 2015 Francois Hoertel
** Last update Wed Mar 18 21:05:36 2015 Francois Hoertel
*/

#include "system.h"

char	*cut_path(char *str)
{
  int	i;

  i = strlen(str) - 1;
  while (i > 0 && str[i] != '/')
    i--;
  if (i == 0)
    return (NULL);
  str[i] = '\0';
  return (str);
}

char	*add_path(char *str, char *add)
{
  char	*new;
  int	i;
  int	j;

  if ((new = malloc(sizeof(char) * (strlen(str) + strlen(add) + 3))) == NULL)
    return (verr_msg(": Malloc fail"));
  new = strcpy(new, str);
  i = strlen(str) + 1;
  new[i - 1] = '/';
  j = 0;
  while (add[j])
    {
      new[i + j] = add[j];
      j++;
    }
  new[i + j] = '\0';
  return (new);
}
