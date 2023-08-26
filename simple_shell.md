.TH SIMPLE_SHELL 1 "August 2023" "Version 1.0" "User Manual"

.SH NAME
simple_shell \- a simple UNIX command-line interpreter, also known as a shell

.SH SYNOPSIS
.B simple_shell
[\fIcommand\fP]

.SH DESCRIPTION
The \fBsimple_shell\fP is a command-line interpreter for UNIX-based operating systems. It is capable of reading commands from standard input, parsing them, and executing them.

.SH OPTIONS
The \fBsimple_shell\fP does not accept any command-line options.

.SH COMMANDS
The \fBsimple_shell\fP accepts the following commands:

.TP
\fBcd [DIRECTORY]\fP
changes the current working directory to \fIDIRECTORY\fP

.TP
\fBexit [STATUS]\fP
exits the shell with a status code of \fISTATUS\fP (default is 0)

.TP
\fBhelp\fP
displays help information for the shell

.TP
\fBenv\fP
prints the current environment variables

.TP
\fBsetenv [NAME] [VALUE]\fP
sets the environment variable \fINAME\fP to \fIVALUE\fP

.TP
\fBunsetenv [NAME]\fP
unsets the environment variable \fINAME\fP

.SH ENVIRONMENT
The \fBsimple_shell\fP program does not set or use any environment variables.

.SH EXIT STATUS
The \fBsimple_shell\fP program returns the following exit codes:

.TP
0
successful termination

.TP
1
general error

.TP
2
incorrect usage

.SH EXAMPLES
To change the current working directory to /usr/local/bin:

.B
$ cd /usr/local/bin

To exit the shell with a status code of 1:

.B
$ exit 1

To print help information for the shell:

.B
$ help

To print the current environment variables:

.B
$ env

To set an environment variable:

.B
$ setenv MY_VAR my_value

To unset an environment variable:

.B
$ unsetenv MY_VAR

.SH AUTHORS
This project was created by FourtyThree43 and Kemboiray as part of the curriculum for Alx Software Engineering.

.SH REPORTING BUGS
Report any bugs or issues to GitHub at https://github.com/fourtythree43 or https://github.com/kemboiray.

.SH COPYRIGHT
This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

