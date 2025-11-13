char	*find_path_in_envp(char **envp, char *var_name)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var_name);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var_name, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

static void	check_value(char **result, char *value, int i)
{
	if (value)
	{
		free(result[i]);
		result[i] = ft_strdup(value);
	}
	else
	{
		free(result[i]);
		result[i] = ft_strdup("");
	}
}
static int	expand_exit_status(char **simbol)
{
	char	*status_str;

	if ((*simbol)[1] == '?' && !(*simbol)[2])
	{
		status_str = ft_itoa(g_status);
		free(*simbol);
		*simbol = status_str;
		return (1);
	}
	return (0);
}

void	expand_amb_variables(char **envp, char **result)
{
	int		i;
	char	*value;

	i = -1;
	while (result[++i])
	{
		if (result[i][0] == '$' && result[i][1])
		{
			if (expand_exit_status(&result[i]))
				continue ;
			value = find_path_in_envp(envp, &result[i][1]);
			check_value(result, value, i);
		}
	}
}