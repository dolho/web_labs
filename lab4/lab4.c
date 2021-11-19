//#include <fcgio.h>
#include <fcgi_config.h>
#include <fcgi_stdio.h>
#include <string.h>

extern char **environ;

static void PrintEnv(char *label, char **envp)
{
    printf("%s:<br>\n<pre>\n", label);
    for ( ; *envp != NULL; envp++) {
        printf("%s\n", *envp);
    }
    printf("</pre><p>\n");
}

int main()
{
    char **initialEnv = environ;
    int count = 0;

    while(FCGI_Accept() == 0)
    {
    printf("Content-type: text/html\r\n"
                "\r\n"
                "<title>FastCGI echo</title>"
                "<h1>FastCGI echo</h1>\n"
                "Request number %d,  Process ID: %d<p>\n", ++count, getpid());
    PrintEnv("Request environment", environ);

    }
    

}