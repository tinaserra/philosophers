#ifndef ERROR_H
# define ERROR_H

static char g_str_error[NUMBER][256] =
{
	[ARGS] = "Error\nInvalid arguments\n",
	[ARG1] = "Error\nInvalid [number_of_philosophers]\n",
	[ARG2] = "Error\nInvalid [time_to_die]\n",
	[ARG3] = "Error\nInvalid [time_to_eat]\n",
	[ARG4] = "Error\nInvalid [time_to_sleep]\n",
	[ARG5] = "Error\nInvalid [number_of_times_each_philosopher_must_eat]\n",

};

#endif