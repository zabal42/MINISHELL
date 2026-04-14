# minishell

> Una implementación ligera de shell Unix escrita en C — proyecto de 42 Urduliz.

---

## Tabla de contenidos

- [Acerca del proyecto](#acerca-del-proyecto)
- [Características](#características)
- [Arquitectura](#arquitectura)
- [Estructura del proyecto](#estructura-del-proyecto)
- [Estructuras de datos](#estructuras-de-datos)
- [Comandos integrados](#comandos-integrados)
- [Primeros pasos](#primeros-pasos)
- [Ejemplos de uso](#ejemplos-de-uso)
- [Detalles técnicos](#detalles-técnicos)
- [Habilidades demostradas](#habilidades-demostradas)

---

## Acerca del proyecto

**minishell** es una shell Unix simplificada desarrollada como parte del currículo de la escuela 42. Reproduce el comportamiento principal de `bash`, implementando el ciclo de vida completo de una shell: leer la entrada del usuario, tokenizarla, parsearla en comandos, expandir variables, gestionar redirecciones y tuberías, y finalmente ejecutar los comandos.

El proyecto está escrito íntegramente en C, usando únicamente llamadas al sistema POSIX, y se apoya en una biblioteca C propia ([libft](./libft)) para todas las operaciones de cadenas y memoria.

---

## Características

| Característica | Descripción |
|---|---|
| **Prompt** | Prompt interactivo con `readline` — soporta movimiento del cursor e historial de entrada |
| **Ejecución de comandos** | Ejecuta cualquier binario encontrado en `$PATH` mediante `fork` + `execve` |
| **Pipes** | Encadena múltiples comandos con `\|` — profundidad ilimitada |
| **Redirección de entrada** | `< fichero` — lee stdin desde un fichero |
| **Redirección de salida** | `> fichero` / `>> fichero` — escribe/añade stdout a un fichero |
| **Heredoc** | `<< DELIM` — lee entrada multilínea hasta el delimitador |
| **Expansión de variables** | `$VAR` y `$?` — expande variables de entorno y código de salida |
| **Manejo de comillas** | Las comillas simples suprimen la expansión; las dobles la permiten |
| **Manejo de señales** | `Ctrl+C` limpia la entrada, `Ctrl+\` ignorado, `Ctrl+D` cierra la shell |
| **7 comandos integrados** | Implementados de forma nativa en el proceso de la shell |

---

## Arquitectura

La shell procesa cada línea de entrada a través de una cadena secuencial de etapas:

```
readline()
    │
    ▼
Tokenizador        ← análisis léxico: divide la entrada en tokens tipados
    │
    ▼
Validador          ← comprobación sintáctica: comillas sin cerrar, operadores mal colocados
    │
    ▼
Parser             ← construye una lista enlazada de t_cmd a partir del flujo de tokens
    │
    ▼
Expansor           ← sustitución de $VAR / $? en los argumentos
    │
    ▼
Gestor de heredoc  ← preprocesa << antes de la ejecución
    │
    ▼
Resolvedor de ruta ← busca $PATH para cada comando que no sea integrado
    │
    ▼
Ejecutor           ← fork/execve para externos, llamada directa para integrados
    │
    ▼
Limpieza           ← libera tokens y lista de comandos, vuelve al prompt
```

---

## Estructura del proyecto

```
minishell/
├── main.c                    # Punto de entrada y bucle principal read-eval
├── utils_main.c              # Helpers de configuración y limpieza de la shell
├── minishell.h               # Cabecera principal — todas las declaraciones e includes
├── parser.h                  # Definiciones de estructuras de datos (token, cmd, redir)
│
├── builtins/
│   ├── builtin_cd.c          # cd — con soporte para ~ y - (OLDPWD)
│   ├── builtin_echo.c        # echo — con flag -n
│   ├── builtin_env.c         # env — imprime el entorno actual
│   ├── builtin_exit.c        # exit — con código de salida opcional
│   ├── builtin_export.c      # export — añade/actualiza variables de entorno
│   ├── builtin_pwd.c         # pwd — imprime el directorio de trabajo actual
│   ├── builtin_unset.c       # unset — elimina variables de entorno
│   ├── builtin_utils.c       # Validación y utilidades compartidas
│   └── path.c                # Resolución de rutas de ejecutables mediante $PATH
│
├── executor/
│   ├── execute_command.c     # Lógica de ejecución de un único comando
│   ├── execute_pipeline.c    # Ejecución de pipelines con múltiples comandos
│   ├── exec_builtin.c        # Despachador de comandos integrados
│   ├── redirections.c        # Configuración de fd para <, >, >>, <<
│   ├── heredoc.c             # Procesamiento de entrada heredoc
│   └── signals.c             # Manejadores de SIGINT / SIGQUIT
│
├── tokenizer.c               # Análisis léxico — produce la lista de tokens
├── token_operator.c          # Parseo de tokens de operador (|, <, >, <<, >>)
├── token_classify.c          # Clasificación del tipo de token
├── quoted.c                  # Parseo de cadenas entre comillas
├── parser.c                  # Flujo de tokens → lista de comandos
├── parser_tokens.c           # Helpers de conversión token-a-comando
├── token_operator.c          # Despacho de operadores durante el parseo
├── utils_parser.c            # Funciones de utilidad del parser
├── validator.c               # Validación sintáctica
├── expander.c                # Expansión de $VAR y $?
├── init_cmd.c                # Inicialización de la estructura t_cmd
├── free.c                    # Liberación de la lista de tokens
├── free_cmds.c               # Liberación de la lista de comandos
├── debug.c / debug_cmds.c    # Utilidades de impresión para depuración
│
└── libft/                    # Biblioteca C estándar personalizada
    ├── src/ft_str/           # Funciones de cadenas (split, join, dup…)
    ├── src/ft_mem/           # Funciones de memoria (calloc, memcpy…)
    ├── src/ft_lst/           # Funciones de listas enlazadas
    ├── src/ft_printf/        # Implementación de ft_printf
    └── src/gnl/              # Implementación de get_next_line
```

---

## Estructuras de datos

La shell se construye en torno a tres estructuras principales de lista enlazada definidas en `parser.h`:

### `t_token` — Token léxico

```c
typedef struct s_token {
    t_token_type    type;    // T_WORD | T_PIPE | T_REDIR_IN | T_REDIR_OUT
                             // T_REDIR_APPEND | T_HEREDOC
    char            *value;  // Valor de cadena en bruto del token
    t_quote_type    quote;   // Q_NONE | Q_SINGLE | Q_DOUBLE
    struct s_token  *next;
} t_token;
```

### `t_redir` — Descriptor de redirección

```c
typedef struct s_redir {
    t_redir_type    type;    // REDIR_IN | REDIR_OUT | REDIR_APPEND | REDIR_HEREDOC
    char            *target; // Nombre del fichero destino o delimitador de heredoc
    int             fd;      // Descriptor de fichero (extremo de lectura del pipe heredoc)
    struct s_redir  *next;
} t_redir;
```

### `t_cmd` — Nodo de comando

```c
typedef struct s_cmd {
    char        **argv;          // Vector de argumentos terminado en NULL
    int         argc;            // Número de argumentos
    char        *full_path;      // Ruta resuelta al ejecutable
    int         is_builtin;      // 1 si el comando es un integrado de la shell
    int         input_fd;        // Descriptor de fichero de stdin
    int         output_fd;       // Descriptor de fichero de stdout
    t_redir     *redirections;   // Lista enlazada de redirecciones
    char        *error_message;  // Se establece en caso de error de parseo/resolución
    struct s_cmd *next;          // Siguiente comando en la tubería
} t_cmd;
```

### `t_shell` — Estado global de la shell

```c
typedef struct s_shell {
    char        **envp;       // Copia de trabajo del entorno
    int         exit_status;  // Código de salida del último comando ($?)
    t_token     *tokens;      // Lista de tokens (tras la tokenización)
    t_cmd       *cmds;        // Lista de comandos (tras el parseo)
} t_shell;
```

---

## Comandos integrados

Estos comandos se ejecutan directamente en el proceso de la shell (sin fork):

| Comando | Comportamiento |
|---|---|
| `echo [-n] [args]` | Imprime los argumentos en stdout. `-n` suprime el salto de línea final. |
| `cd [ruta]` | Cambia de directorio. Soporta `~` (home) y `-` (directorio anterior). |
| `pwd` | Imprime el directorio de trabajo actual. |
| `export [VAR=valor]` | Añade o actualiza una variable de entorno. Sin argumentos, lista todos los exports. |
| `unset VAR` | Elimina una variable de entorno. |
| `env` | Imprime todas las variables de entorno. |
| `exit [n]` | Cierra la shell con el código de salida opcional `n`. |

---

## Primeros pasos

### Requisitos

- GCC o Clang
- GNU Make
- Biblioteca `readline`

**macOS:**
```bash
brew install readline
```

**Linux (Debian/Ubuntu):**
```bash
sudo apt-get install libreadline-dev
```

### Compilación

```bash
git clone <repo-url> minishell
cd minishell
make
```

Esto compila `libft` y a continuación el ejecutable `minishell`.

### Ejecución

```bash
./minishell
```

### Objetivos del Makefile

| Objetivo | Acción |
|---|---|
| `make` / `make all` | Compila `minishell` |
| `make clean` | Elimina los ficheros objeto |
| `make fclean` | Elimina los ficheros objeto y el binario `minishell` |
| `make re` | Limpieza completa y recompilación |

---

## Ejemplos de uso

```bash
# Comando simple
minishell$ ls -la

# Tubería
minishell$ cat /etc/hosts | grep localhost | wc -l

# Redirecciones
minishell$ echo "hello world" > out.txt
minishell$ cat < out.txt >> log.txt

# Heredoc
minishell$ cat << EOF
> linea uno
> linea dos
> EOF

# Expansión de variables
minishell$ export NAME=mundo
minishell$ echo "Hola $NAME"        # → Hola mundo
minishell$ echo '$NAME'             # → $NAME  (las comillas simples suprimen la expansión)

# Código de salida
minishell$ ls inexistente
minishell$ echo $?                  # → 1 (o 2, según el SO)

# Integrados
minishell$ cd ~
minishell$ pwd
minishell$ export PATH=$PATH:/usr/local/bin
minishell$ unset NAME
minishell$ exit 0
```

---

## Detalles técnicos

### Modos de ejecución

**Comando único no integrado**
```
fork()
  └─ hijo: restaurar señales → aplicar redirecciones → execve()
padre: waitpid() → capturar código de salida
```

**Comando único integrado**
```
guardar fds de stdin/stdout
aplicar redirecciones mediante dup2()
llamar a la función integrada directamente (sin fork)
restaurar fds originales
```

**Pipe (n comandos)**
```
por cada comando:
    pipe()                      ← crear pipe hacia el siguiente comando
    fork()
      └─ hijo: dup2 stdin/stdout → cerrar fds → execve() / integrado
padre: cerrar extremos del pipe → waitpid() para todos los hijos
código de salida = código de salida del último hijo
```

### Manejo de señales

| Señal | Interactivo (padre) | Proceso hijo |
|---|---|---|
| `SIGINT` (Ctrl+C) | Imprime nueva línea, limpia entrada de readline | Por defecto — termina el hijo |
| `SIGQUIT` (Ctrl+\\) | Ignorado | Por defecto — core dump |
| Heredoc | Ctrl+C sale del heredoc con estado 130 | — |

### Gestión del entorno

La shell copia el entorno del proceso padre al iniciarse (`dup_env`). Todas las modificaciones mediante `export` y `unset` operan sobre esta copia interna. Los procesos hijos heredan el entorno modificado a través de `execve`. El entorno del padre nunca se modifica.

### Reglas de expansión de variables

| Contexto | `$VAR` | `$?` |
|---|---|---|
| Sin comillas | Se expande | Se expande |
| Comillas dobles `"..."` | Se expande | Se expande |
| Comillas simples `'...'` | **No se expande** | **No se expande** |

---

## Habilidades demostradas

- Gestión de procesos: `fork`, `execve`, `waitpid`, `pipe`
- Manipulación de descriptores de fichero: `dup2`, `open`, `close`
- Manejo de señales: `sigaction`, `signal`
- Gestión de memoria: `malloc`/`free` manual sin fugas
- Diseño de lexer/parser: tokenización, parseo recursivo, AST con listas enlazadas
- Entorno Unix: resolución de `$PATH`, gestión de `envp`
- Integración POSIX de readline con soporte de historial
- Makefile multiplataforma (macOS arm64/x86\_64 + Linux)

---

*Proyecto desarrollado en [42 Urduliz](https://www.42urduliz.com/) — 2024/2025.*
