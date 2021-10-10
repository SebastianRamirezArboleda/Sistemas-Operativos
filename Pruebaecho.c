#include <stdio.h>
#include <string.h>
#include <pwd.h>
#include <unistd.h>

int main()
{
  char acct[80], password[80];

  printf("Account: ");
  fgets(acct, 80, stdin);

  acct[strlen(acct)-1] = 0; /* remove carriage return */

  strncpy(password, getpass("Password: "), 80);
  printf("You entered acct %s and pass %s\n", acct, password);
}