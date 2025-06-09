/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:46:03 by yaycicek          #+#    #+#             */
/*   Updated: 2025/06/09 13:15:37 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h> // printf, perror
# include <errno.h> // errno
# include <fcntl.h> // open
# include <unistd.h> // isatty, ttyname, ttyslot, getcwd, chdir, unlink
# include <stdlib.h> // malloc, free, exit, getenv
# include <string.h> // strerror
# include <signal.h> // signal, sigaction, sigemptyset, sigaddset, kill
# include <dirent.h> // opendir, readdir, closedir
# include <stdbool.h> // true/false
# include <termcap.h> // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <termios.h> // tcgetattr, tcsetattr
# include <sys/wait.h> // wait, waitpid, wait3, wait4
# include <sys/stat.h> // stat, lstat, fstat
# include <sys/ioctl.h> // ioctl
#include "linux/limits.h" //! PATH_MAX
# include <readline/history.h> // add_history
# include <readline/readline.h> // rl_*

# include "../libft/libft.h"
# include "utils.h"
# include "env.h"
# include "builtin.h"
# include "lexer.h"

#endif
