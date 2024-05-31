#include <stdio.h>
#include <stdlib.h>
#include "luis.h"
// cantidad de registros automaticos
#define N 100
// regsitros maximos
#define M 500
typedef struct _talum
{
    int status;
    long matricula;
    char appat[20];
    char apmat[20];
    char nombre[20];
    int edad;
    char sexo[7];
} Talum;

//*** PROTOTIPOS DE FUNCIONES  ******
int msges();
void menu();
Talum Generar_reg(void);
Talum Reg_manual(void);
int Buscar(Talum registros[], int m, int matri, bool ordenado = 0);
void Eliminar(Talum registros[], int m);
int Ordenar(Talum registros[], int m);
void Print_reg(Talum registros[], int m);

//****  main principal  *********
int main()
{
    srand(time(NULL));
    menu();
    return 0;
}
//  *** DESARROLLO DE LAS FUNCIONES  ******
//*********************
int msges()
{
    int op;
    system("CLS");
    printf("   M  E   N   U \n");
    printf("1.- Agregar \n");
    printf("2.- Agregar manualmente \n");
    printf("3.- Eliminar registro \n");
    printf("4.- Buscar \n");
    printf("5.- Ordenar \n");
    printf("6.- Imprimir \n");
    printf("0.- SALIR  \n");
    op = valinum(0, 6, "ESCOGE UNA OPCION: ");

    return op;
}

//****************
void menu()
{
    int op, no_reg = 0, num, resul;
    bool ordenado = 0;
    Talum registros[M];
    do
    {
        op = msges();
        switch (op)
        {
        case 1:
            system("CLS");
            if (no_reg <= (M - N))
            {
                for (int i = 0; i < N; i++)
                {
                    registros[no_reg] = Generar_reg();
                    no_reg++;
                }
                ordenado = 0;
                printf("Se han agregado 10 registros\n");
            }
            else
            {
                printf("No caben mas registros");
            }
            system("PAUSE");
            break;
        case 2:
            system("CLS");
            if (no_reg < M)
            {
                registros[no_reg] = Reg_manual();
                no_reg++;
                ordenado = 0;
                printf("Registro completo\n");
            }
            else
            {
                printf("No caben mas registros");
            }
            system("PAUSE");
            break;
        case 3:
            system("CLS");
            Eliminar(registros, no_reg);
            system("PAUSE");

            break;
        case 4:
            system("CLS");

            num = valilong(300000, 399999, "Matricula que busca: ");
            resul = Buscar(registros, no_reg, num, ordenado);
            if (resul == -1)
            {
                printf("No se encontro la matricula\n");
            }
            else
            {
                printf("La matricula esta en: %d\n", (resul + 1));
                printf("No.   Matricula  Nombre   Apellidos               Edad    Sexo\n");
                printf("%3d.- %6ld %10s %10s %10s %8d %8s\n", (resul + 1), registros[resul].matricula, registros[resul].nombre, registros[resul].appat, registros[resul].apmat, registros[resul].edad, registros[resul].sexo);
            }
            system("PAUSE");

            break;
        case 5:
            system("CLS");
            ordenado = Ordenar(registros, no_reg);
            system("PAUSE");

            break;
        case 6:
            system("CLS");
            Print_reg(registros, no_reg);
            system("PAUSE");

            break;
        }

    } while (op != 0);
}
//*********************
Talum Generar_reg(void)
{
    Talum reg;
    reg.status = 1;
    char nombres[20][20] = {"JUAN", "LUIS", "DANIEL", "SAUL", "JACOB", "ANGEL", "ALAN", "YAHIR", "GABRIEL", "ISRAEL", "WALTER"};
    char mujeres[20][20] = {"ANGELA", "SOFIA", "VIVIANA", "ANA", "MARIA", "PAOLA", "PAULA", "SONIA", "VANESSA", "HANNA", "LOLA"};
    char appat[20][20] = {"SOTO", "VILLALOBOS", "VICTORIO", "PEREZ", "PINEDA", "HERNANDEZ", "LEAL", "ESPINOZA", "IBARRA", "DIAZ", "DOMINGUEZ", "MARTINEZ"};
    char apmat[20][20] = {"WAYNE", "CRUZ", "CHAVEZ", "CARMINE", "RUIZ", "ORTIZ", "TORRES", "OROZCO", "GARCIA", "PAREDES", "ACOSTA", "CASAS"};
    int sexo;
    reg.edad = (rand() % 12) + 18;

    copystr(reg.appat, appat[rand() % 12]);
    copystr(reg.apmat, apmat[rand() % 12]);
    sexo = (rand() % 2) + 1;
    if (sexo == 1)
    {
        copystr(reg.sexo, "HOMBRE");
        copystr(reg.nombre, nombres[rand() % 11]);
    }
    else
    {
        copystr(reg.sexo, "MUJER");
        copystr(reg.nombre, mujeres[rand() % 11]);
    }
    reg.matricula = (rand() % 99999) + 300000;
    return reg;
}
//*************************
Talum Reg_manual(void)
{
    Talum reg;
    int sexo;
    //  VARIALES LOCALES
    //  AQUI DESARROLLO PROGRAMA
    // status para saber si esta activo el registro
    reg.status = 1;
    // nombres y apellidos
    printf("Ingrese nombre: ");
    fflush(stdin);
    gets(reg.nombre);
    printf("Ingrese apellido paterno: ");
    fflush(stdin);
    gets(reg.appat);
    printf("Ingrese apellido materno: ");
    fflush(stdin);
    gets(reg.apmat);
    valichar(reg.nombre);
    valichar(reg.appat);
    valichar(reg.apmat);
    // edad y matricula
    reg.edad = valinum(18, 40, "Ingrese edad: ");
    reg.matricula = valilong(300000, 399999, "Ingrese matricula: ");
    // Sexo
    sexo = valinum(1, 2, "(1)Mujer\n(2)Hombre\nIndique el sexo: ");
    if (sexo == 1)
    {
        copystr(reg.sexo, "MUJER");
        reg.sexo[5] = '\0';
    }
    else
    {
        copystr(reg.sexo, "HOMBRE");
    }
    return reg;
}
//****************************
int Buscar(Talum registros[], int m, int matri, bool ordenado)
{
    int i;

    if (ordenado)
    {
        int bajo = 0, centro, alto = m - 1;
        do
        {
            centro = (bajo + alto) / 2;
            if (registros[centro].matricula < matri)
            {
                bajo = centro + 1;
            }
            else
            {
                if (registros[centro].matricula == matri)
                {
                    return centro;
                }
                else
                {
                    alto = centro - 1;
                }
            }
        } while (alto >= bajo);
    }
    else
    {
        for (i = 0; i < m; i++)
        {
            if (registros[i].matricula == matri)
            {
                return i;
            }
        }
    }
    return -1;
}
void Eliminar(Talum registros[], int m)
{
    long num;
    int resul;
    bool eliminar;

    num = valilong(300000, 399999, "Matricula que busca: ");
    resul = Buscar(registros, m, num);
    if (resul == -1)
    {
        printf("No se encontro la matricula\n");
    }
    else
    {
        printf("La matricula esta en: %d\n", (resul + 1));
        printf("No.   Matricula  Nombre   Apellidos               Edad    Sexo\n");
        printf("%3d.- %6ld %10s %10s %10s %8d %8s\n", (resul + 1), registros[resul].matricula, registros[resul].nombre, registros[resul].appat, registros[resul].apmat, registros[resul].edad, registros[resul].sexo);
        eliminar = valinum(0, 1, "(0)Cancelar\n(1)Eliminar\nSeleccione: ");
        if (eliminar)
        {
            registros[resul].status = 0;
            printf("Se elimino el registro\n");
        }
        else
        {
            printf("Cancelando\n");
        }
    }
}
int Ordenar(Talum registros[], int m)
{
    int j;
    Talum temp;
    for (int i = 0; i < m - 1; i++)
    {
        for (j = i + 1; j < m; j++)
        {
            if (registros[j].matricula < registros[i].matricula)
            {
                temp = registros[i];
                registros[i] = registros[j];
                registros[j] = temp;
            }
        }
    }
    return 1;
}
void Print_reg(Talum registros[], int m)
{
    for (int i = 0; i < m; i++)
    {
        if (registros[i].status == 1)
        {
            printf("No.   Matricula  Nombre   Apellidos               Edad    Sexo\n");
            printf("%3d.- %6ld %10s %10s %10s %8d %8s\n", (i + 1), registros[i].matricula, registros[i].nombre, registros[i].appat, registros[i].apmat, registros[i].edad, registros[i].sexo);
        }
    }
}
