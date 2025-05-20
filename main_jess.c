/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_jess.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesssanc <jesssanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:19:52 by jesssanc          #+#    #+#             */
/*   Updated: 2025/05/20 12:22:29 by jesssanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redir *parse_heredoc(char **argv, int *argc) {
    t_redir *redir = NULL;
    for (int i = 0; argv[i]; ++i) {
        if (strcmp(argv[i], "<<") == 0 && argv[i + 1]) {
            redir = calloc(1, sizeof(t_redir));
            redir->type = REDIR_HEREDOC;
            redir->target = strdup(argv[i + 1]);
            // Elimina << y DELIM de argv
            free(argv[i]);
            free(argv[i + 1]);
            for (int j = i; argv[j + 2]; ++j)
                argv[j] = argv[j + 2];
            argv[*argc - 2] = NULL;
            argv[*argc - 1] = NULL;
            *argc -= 2;
            break;
        }
    }
    return redir;
}

t_cmd *parse_mock(const char *line) {
    t_cmd *first = NULL, *last = NULL;
    char *input = strdup(line);
    char *saveptr1 = NULL, *saveptr2 = NULL;

    char *token = strtok_r(input, "|", &saveptr1);
    while (token) {
        t_cmd *cmd = calloc(1, sizeof(t_cmd));
        // Trocea en espacios
        int argc = 0;
        char *tmp = strdup(token);
        char *arg = strtok_r(tmp, " \t\n", &saveptr2);
        while (arg) { argc++; arg = strtok_r(NULL, " \t\n", &saveptr2); }
        free(tmp);

        tmp = strdup(token);
        cmd->argv = calloc(argc + 1, sizeof(char *));
        int i = 0;
        arg = strtok_r(tmp, " \t\n", &saveptr2);
        while (arg) {
            cmd->argv[i++] = strdup(arg);
            arg = strtok_r(NULL, " \t\n", &saveptr2);
        }
        cmd->argv[argc] = NULL;
        free(tmp);

        // Heredoc (solo uno por comando)
        cmd->redirections = parse_heredoc(cmd->argv, &argc);

        // Detecta builtins (ajusta según tu minishell)
        if (cmd->argv[0] &&
            (!strcmp(cmd->argv[0], "echo")
            || !strcmp(cmd->argv[0], "pwd")
            || !strcmp(cmd->argv[0], "cd")
            || !strcmp(cmd->argv[0], "export")
            || !strcmp(cmd->argv[0], "unset")
            || !strcmp(cmd->argv[0], "env")
            || !strcmp(cmd->argv[0], "exit")))
            cmd->is_builtin = 1;
        else
            cmd->is_builtin = 0;

        cmd->full_path = NULL; // Se debe rellenar fuera con find_executable si es externo

        cmd->next = NULL;
        if (!first) first = cmd;
        if (last) last->next = cmd;
        last = cmd;
        token = strtok_r(NULL, "|", &saveptr1);
    }
    free(input);
    return first;
}

void free_cmds(t_cmd *cmds) {
    t_cmd *tmp;
    while (cmds) {
        tmp = cmds->next;
        if (cmds->argv) {
            for (int i = 0; cmds->argv[i]; i++)
                free(cmds->argv[i]);
            free(cmds->argv);
        }
        if (cmds->full_path)
            free(cmds->full_path);
        // Libera redirecciones si existen
        t_redir *redir = cmds->redirections;
        while (redir) {
            t_redir *next = redir->next;
            if (redir->target)
                free(redir->target);
            free(redir);
            redir = next;
        }
        free(cmds);
        cmds = tmp;
    }
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;

    t_shell shell;
    shell.envp = envp;
    shell.exit_status = 0;

    char *line;
    while ((line = readline("minishell> ")) != NULL)
    {
        if (*line)
            add_history(line);

        // Usa el parser de pruebas
        t_cmd *cmds = parse_mock(line);

        // Rellena full_path para comandos externos
        for (t_cmd *c = cmds; c; c = c->next) {
            if (!c->is_builtin && !c->full_path && c->argv[0])
                c->full_path = find_executable(c->argv[0], shell.envp);
        }

        // Decide si es comando simple o pipeline
        if (cmds && cmds->next == NULL)
            execute_command(cmds, &shell);
        else if (cmds)
            execute_pipeline(cmds, &shell);

        free_cmds(cmds);
        free(line);
    }
    printf("\nBye!\n");
    return 0;
}
