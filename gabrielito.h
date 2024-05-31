#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int valinum(int ri = 0, int rf = 64000, char msge[] = "Numero entero: ");
long valilong(long ri, long rf, char msge[] = "Numero: ");
void printstr(char palabra[]);
void copystr(char copia[], char palabra[]);
void upcstr(char palabra[]);
void lowcstr(char palabra[]);
void capstr(char palabra[]);
int tamstr(char palabra[]);
void invstr(char palabra[]);
void nospace(char palabra[]);
void valichar(char palabra[]);

// funcines--------------------------
// valor incial , valor final, mensaje
int valinum(int ri, int rf, char msge[])
{
  char xnum[30];
  int num;
  do
  {
    printf("%s", msge);
    fflush(stdin);
    gets(xnum);
    num = atoi(xnum);
    if (num < ri or num > rf)
    {
      printf("Error\nvalor debe ser entre (%d-%d)\n", ri, rf);
      system("PAUSE");
    }
  } while (num < ri or num > rf);
  return num;
}
long valilong(long ri, long rf, char msge[])
{
  char xnum[30];
  long num;
  do
  {
    printf("%s", msge);
    fflush(stdin);
    gets(xnum);
    num = atol(xnum);
    if (num < ri or num > rf)
    {
      printf("Error\nvalor debe ser entre (%ld-%ld)\n", ri, rf);
      system("PAUSE");
    }
  } while (num < ri or num > rf);
  return num;
}
// imprimir cadena
void printstr(char palabra[])
{
  int i = 0;
  while (palabra[i] != '\0')
  {
    printf("%c", palabra[i]);
    i++;
  }

  printf("\n");
}
// 2da se copia en la 1era
void copystr(char copia[], char palabra[])
{
  int i = 0;
  while (palabra[i] != '\0')
  {
    copia[i] = palabra[i];
    i++;
  }
  copia[i] = '\0';
}
// pasar a mayusculas
void upcstr(char palabra[])
{
  int i = 0;
  // Inicio el programa
  while (palabra[i] != '\0')
  {
    if (palabra[i] >= 'a')
    {
      if (palabra[i] <= 'z')
      {
        palabra[i] = (palabra[i] - 32);
      }
    }
    i++;
  }
}
// pasar a minusculas
void lowcstr(char palabra[])
{
  int i = 0;

  while (palabra[i] != '\0')
  {
    if (palabra[i] >= 'A')
    {
      if (palabra[i] <= 'Z')
      {
        palabra[i] = (palabra[i] + 32);
      }
    }
    i++;
  }
}
// mayuscula despues del espacio
void capstr(char palabra[])
{
  //  AQUI DESARROLLO PROGRAMA
  int i = 0;
  while (palabra[i] != '\0')
  {
    if ((palabra[i - 1] == 32) or (i == 0))
    {
      if (palabra[i] >= 'a')
      {
        if (palabra[i] <= 'z')
        {
          palabra[i] = (palabra[i] - 32);
        }
      }
    }
    i++;
  }
}
// numero de letras
int tamstr(char palabra[])
{
  int i;
  for (i = 0; palabra[i] != '\0'; i++)
    ;
  return (i);
}
// invertir letras
void invstr(char palabra[])
{
  //  VARIALES LOCALES
  int i;
  char pivote[30];
  //  AQUI DESARROLLO PROGRAMA

  i = tamstr(palabra) - 1;
  copystr(pivote, palabra);
  while (i >= 0)
  {
    palabra[i] = pivote[(tamstr(palabra) - 1) - i];
    i--;
  }
}
// quitar espacios
void nospace(char palabra[])
{
  int i = 0, j = 0;
  while (palabra[i] != '\0')
  {
    if (palabra[i] == 32)
    {
      j = i;
      while (palabra[j] != '\0')
      {
        palabra[j] = palabra[j + 1];
        j++;
      }
    }
    else
    {
      i++;
    }
  }
}
// No espacios inicio ni final, ni doble, Aa-Zz
void valichar(char palabra[])
{
  int i;
  bool band;
  do
  {
    band = 0;
    // espacio al inicio o final
    if (palabra[0] == 32 || palabra[tamstr(palabra) - 1] == 32)
    {
      band = 1;
      printf("No espacios al inicio o final\n");
    }
    i = 0;
    // caracteres invalidos
    while (band == 0 && palabra[i] != '\0')
    {
      if (palabra[i] > 90)
      {
        if (palabra[i] > 122)
        {
          printf("Solo letras Aa-Zz\n");
          band = 1;
        }
        else
        {
          if (palabra[i] < 97)
          {
            printf("Solo letras Aa-Zz\n");
            band = 1;
          }
        }
      }
      else
      {
        if (palabra[i] >= 32)
        {
          if (palabra[i] < 65)
          {
            if (palabra[i] == 32)
            {
              if (palabra[i + 1] == 32)
              {
                printf("No espacios dobles\n");
                band = 1;
              }
            }
            else
            {
              printf("Solo letras Aa-Zz\n");
              band = 1;
            }
          }
        }
      }

      i++;
    }
    if (band)
    {

      printf("Cadena no valida, intente otra: ");
      fflush(stdin);
      gets(palabra);
    }
  } while (band);
}
