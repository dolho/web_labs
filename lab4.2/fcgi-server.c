#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char ** environ;

#include "fcgi_config.h"
#include "fcgi_stdio.h"

static void PrintEnv(char * label, char ** envp) {
  printf("%s:<br>\n<pre>\n", label);
  for (;* envp != NULL; envp++) {
    printf("%s\n", * envp);
  }
  printf("</pre><p>\n");
}

int main() {
  char ** initialEnv = environ;
  int count = 0;

  while (FCGI_Accept() >= 0) {
    char * contentLength = getenv("CONTENT_LENGTH");
    int len;

    char * documentURI = getenv("DOCUMENT_URI");
                if (strcmp(documentURI, "/api/mpstat") == 0) {
                        printf("Content-type: text/plain\r\n"
                                        "\r\n");

      FILE * fp;
      char var[40];
      fp = popen("mpstat", "r");
      while (fgets(var, sizeof(var), fp) != NULL) {
        printf("%s", var);
      }
      pclose(fp);
                }
                else if (strcmp(documentURI, "/api/iostat") == 0) {
      printf("Content-type: text/plain\r\n"
          "\r\n");

      FILE * fp;
      char var[40];
      fp = popen("iostat", "r");
      while (fgets(var, sizeof(var), fp) != NULL) {
        printf("%s", var);
      }
      pclose(fp);
                }
                else if (strcmp(documentURI, "/api/free") == 0) {
      printf("Content-type: text/plain\r\n"
          "\r\n");

      FILE * fp;
      char var[40];
      fp = popen("free", "r");
      while (fgets(var, sizeof(var), fp) != NULL) {
        printf("%s", var);
      }
      pclose(fp);
                }
                else if (strcmp(documentURI, "/") == 0) {
                        printf("Content-type: text/html\r\n"
                "\r\n");

                        int c;
                        FILE * file;
                        file = fopen("./pages/index.html", "r");
                        if (file) {
                                while ((c = getc(file)) != EOF)
                                        putchar(c);
                                fclose(file);
                        }
      printf("<br><br>Request number %d,  Process ID: %d<p>\n", ++count, getpid());
                }
    else if (strcmp(documentURI, "/echo") == 0) {
                        printf("Content-type: text/html\r\n"
                "\r\n");

      printf("<title>FastCGI echo</title>"
        "<h1>FastCGI echo</h1>\n"
                                "<a href=\"/~kp9221/fcgi/\">Back to the index page</a>"
                                "<br><br>"
        "Request number %d,  Process ID: %d<p>\n", ++count, getpid());

      if (contentLength != NULL) {
        len = strtol(contentLength, NULL, 10);
      } else {
        len = 0;
      }

      if (len <= 0) {
        printf("No data from standard input.<p>\n");
      } else {
        int i, ch;

        printf("Standard input:<br>\n<pre>\n");
        for (i = 0; i < len; i++) {
          if ((ch = getchar()) < 0) {
            printf("Error: Not enough bytes received on standard input<p>\n");
            break;
          }
          putchar(ch);
        }
        printf("\n</pre><p>\n");
      }

      PrintEnv("Request environment", environ);
      PrintEnv("Initial environment", initialEnv);
    }
                else {
                        printf("Content-type: text/html\r\n"
                "\r\n");

                        int c;
                        FILE * file;
                        file = fopen("./pages/404.html", "r");
                        if (file) {
                                while ((c = getc(file)) != EOF)
                                        putchar(c);
                                fclose(file);
                        }
      printf("<br><br>Request number %d,  Process ID: %d<p>\n", ++count, getpid());
                }
  }

  return 0;
}