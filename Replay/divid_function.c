#include "parsing.h"

char	*delete_quote_off(t_parse *parse, char *line, int *i, int *j)
{
	if (line[*j] == '\\')
	{
		parse->cp ++;
		line[(*i)++] = line[++(*j)];
	}
	else
	{
		if (line[*j] == '"' && parse->cp  % 2 == 0)
			parse->smbl->d_quote = ON;
		else if (line[*j] == '\'' && parse->cp  % 2 == 0)
			parse->smbl->s_quote = ON;
		else
			line[(*i)++] = line[*j];
	}
}

char	*delete_quote_on(t_parse *parse, char *line, int *i, int *j)
{
	if (parse->smbl->d_quote == ON)
	{
		if (line[*j] == '"')
			parse->smbl->d_quote = OFF;
		else if (line[*j] == '\\' && line[(*j) + 1] == '\\')
			line[(*i)++] = line[++(*j)];
		else if (line[*j] == '\\' && line[(*j) + 1] < 0 && line[(*j) + 1] != '\'' * -1)
			line[(*i)++] = line[++(*j)];
		else
			line[(*i)++] = line[*j];
	}
	else if (parse->smbl->s_quote == ON)
	{
		while (line[*j] != '\'')
			line[(*i)++] = line[(*j)++];
		parse->smbl->s_quote = OFF;
	}
	return (line);
}

char	*check_f_cmd(t_parse *parse, char *line)
{
	int i;
	int j;

	i = 0;
	j = -1;
	parse->cp = 0;
	while (line[++j])
	{

		if (parse->smbl->d_quote == OFF && parse->smbl->s_quote == OFF)
		{
			line = delete_quote_off(parse, line, &i, &j);
			/* if (line[j] == '\\')
			{
				cp++;
				line[i++] = line[++j];
			}
			else
			{
				if (line[j] == '"' && cp % 2 == 0)
					parse->smbl->d_quote = ON;
				else if (line[j] == '\'' && cp % 2 == 0)
					parse->smbl->s_quote = ON;
				else
					line[i++] = line[j];
			} */
		}
		else
		{
			line = delete_quote_on(parse, line, &i, &j);
			/* if (parse->smbl->d_quote == ON)
			{
				if (line[j] == '"')
					parse->smbl->d_quote = OFF;
				else if (line[j] == '\\' && line[j + 1] == '\\')
					line[i++] = line[++j];
				else if (line[j] == '\\' && line[j + 1] < 0 && line[j + 1] != '\'' * -1)
					line[i++] = line[++j];
				else
					line[i++] = line[j];
			}
			else if (parse->smbl->s_quote == ON)
			{
				while (line[j] != '\'')
					line[i++] = line[j++];
				parse->smbl->s_quote = OFF;
			} */
		}
		if (line[j] != '\\')
			parse->cp = 0;
	}
	line[i] = 0;
	return inverse_line(line);
}

