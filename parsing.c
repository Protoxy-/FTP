/*
** parsing.c for FTP in /home/hoerte_f/rendu/PSU_2014_myftp
** 
** Made by Francois Hoertel
** Login   <hoerte_f@epitech.net>
** 
** Started on  Thu Mar 19 14:10:37 2015 Francois Hoertel
** Last update Sun Mar 29 18:20:51 2015 Francois Hoertel
*/

#include "system.h"

char	*get_param(char *buff, int pos)
{
  char	*param;
  int	i;
  int	j;
  int	k;

  if ((param = malloc(sizeof(char) * strlen(buff))) == NULL)
    return (verr_msg(": Malloc fail"));
  k = 0;
  j = 0;
  i = 0;
  while (buff[i] && buff[i] != '\n' && j < pos + 1)
    {
      while (buff[i] && buff[i] == ' ')
	i++;
      while (buff[i] && buff[i] != '\n' && buff[i] != ' ')
	{
	  if (j == pos)
	    param[k++] = buff[i];
	  i++;
	}
      if (j == pos)
	param[k] = '\0';
      j++;
    }
  return (param);
}

int	check_command(char *entry, char *func)
{
  int	i;
  int	j;

  if (strlen(entry) > strlen(func) + 1)
    return (-1);
  j = 0;
  i = 0;
  while (entry[i] && func[i])
    {
      if (entry[i] == func[i])
        j++;
      if (entry[i] >= 'a' && entry[i] <= 'z' && entry[i] - 32 == func[i])
	j++;
      if (entry[i] >= 'A' && entry[i] <= 'Z' && entry[i] + 32 == func[i])
	j++;
      i++;
    }
  if (j != i)
    return (-1);
  return (0);
}

int	check_keycode(char *entry, char *func)
{
  int	i;
  int	j;

  if (strlen(entry) < strlen(func))
    return (-1);
  j = 0;
  i = 0;
  while (entry[i] && func[i])
    {
      if (entry[i] == func[i])
	j++;
      i++;
    }
  if (j != i)
    return (-1);
  return (0);
}

char	*add_to_end(char *str, char *add)
{
  int	i;
  int	j;

  i = strlen(str);
  j = 0;
  while (add[j])
    str[i++] = add[j++];
  str[i] = '\0';
  return (str);
}
