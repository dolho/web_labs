//#include <fcgio.h>
#include <stdlib.h>
#include <fcgi_config.h>
#include <fcgi_stdio.h>
#include <string.h>
#include <stdio.h>

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
    char sPath[1024] = "";
    char *pTmp;
    char **initialEnv = environ;
    int count = 0;
    if (( pTmp =getenv( "PATH" )) != NULL )
        strncpy( sPath, pTmp, 1023 );           // Save a copy for our use.
    else
        fprintf( stderr, "No PATH variable set.\n") ;

    while(FCGI_Accept() == 0)
    {
        char sPath[1024] = "";
        char *pTmp;
        if ((pTmp = getenv("PATH_INFO")) != NULL)
            strncpy(sPath, pTmp, 1023); // Save a copy for our use.
        // char * path = "/";
        char ch;
        if (strcmp(sPath, "/") == 0) {
            FILE * index_fp = fopen("index.html", "r");
            if (index_fp == NULL)
            {
                printf("Content-type: text/html\r\n"
                       "\r\n"
                       "<title>FastCGI echo</title>"
                       "<h1>Not found</h1>\n"
                       "Request number %d,  Process ID: %d<p>\n",
                       ++count, getpid());
                continue;
            }
            printf("Content-type: text/html\r\n"
                       "\r\n"
                       "Request number %d,  Process ID: %d<p>\n",
                       ++count, getpid());
            while((ch = fgetc(index_fp)) != EOF)
            {
                printf("%c", ch);
            }
                
        }
        else if (strcmp(sPath, "/echo") == 0) {
            printf("Content-type: text/html\r\n"
                    "\r\n"
                    "<title>FastCGI echo</title>"
                    "<h1>My main fcgi application</h1>\n"
                    "Request number %d,  Process ID: %d<p>\n", ++count, getpid());
                    PrintEnv("Request environment", environ);
        }
            printf(sPath);
        printf("Content-type: text/html\r\n"
                "Not found\r\n"
                "Request number %d,  Process ID: %d<p>\n", ++count, getpid());
    }
}

// # echo "$(cgi-fcgi -connect 127.0.0.1:49311 example)"