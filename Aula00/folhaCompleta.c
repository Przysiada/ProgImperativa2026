#include <stdio.h>

#define CUSTO_VALE 6.0
#define DIAS_UTEIS 22
#define VALOR_PLANO_ENFERMARIA 89.90
#define VALOR_PLANO_QUARTO 119.90
#define DEDUCAO_DEPENDENTE_IR 189.59

typedef struct
{
    int dependentes;
    float salarioBruto;
    float salarioExtra;
    char usaVT;
    int qtdOnibus;
    char planoSaude;

} Funcionario;


float calcularVT(Funcionario f)
{
    if(f.usaVT != 'S')
        return 0;

    float valorVale = f.qtdOnibus * 2 * DIAS_UTEIS * CUSTO_VALE;
    float maxDesconto = f.salarioBruto * 0.06;

    if(valorVale > maxDesconto)
        return maxDesconto;
    else
        return valorVale;
}


float calcularPlanoSaude(Funcionario f)
{
    int totalPessoas = f.dependentes + 1;

    if(f.planoSaude == 'E')
        return totalPessoas * VALOR_PLANO_ENFERMARIA;

    else if(f.planoSaude == 'Q')
        return totalPessoas * VALOR_PLANO_QUARTO;

    else
        return 0;
}


float calcularFGTS(Funcionario f)
{
    return (f.salarioBruto + f.salarioExtra) * 0.08;
}


float calcularINSS(float salarioTotal)
{
    if (salarioTotal <= 1100)
        return salarioTotal * 0.075;

    else if (salarioTotal <= 2203.48)
        return salarioTotal * 0.09;

    else if (salarioTotal <= 3305.22)
        return salarioTotal * 0.12;

    else
        return salarioTotal * 0.14;
}


float calcularSalarioFamilia(float salarioTotal, int dependentes)
{
    if(salarioTotal <= 1503.25)
        return dependentes * 51.27;

    return 0;
}


float calcularIR(Funcionario f, float inss)
{
    float base = f.salarioBruto + f.salarioExtra - inss - (f.dependentes * DEDUCAO_DEPENDENTE_IR);

    if(base <= 1903.98)
        return 0;

    else if(base <= 2826.65)
        return (base * 0.075) - 142.80;

    else if(base <= 3751.05)
        return (base * 0.15) - 354.80;

    else if(base <= 4664.68)
        return (base * 0.225) - 636.13;

    else
        return (base * 0.275) - 869.36;
}


Funcionario menu(Funcionario f)
{
    int opcao;

    do
    {
        printf("\n===== MENU =====\n");
        printf("1 - Informar dependentes\n");
        printf("2 - Informar salario bruto\n");
        printf("3 - Informar salario extra\n");
        printf("4 - Informar vale transporte\n");
        printf("5 - Informar plano de saude\n");
        printf("6 - Calcular folha\n");
        printf("0 - Sair\n");

        printf("Opcao: ");
        scanf("%d", &opcao);

        switch(opcao)
        {
            case 1:
                printf("Quantidade de dependentes: ");
                scanf("%d", &f.dependentes);
                break;

            case 2:
                printf("Salario bruto: ");
                scanf("%f", &f.salarioBruto);
                break;

            case 3:
                printf("Salario extra: ");
                scanf("%f", &f.salarioExtra);
                break;

            case 4:
                printf("Usa vale transporte (S/N): ");
                scanf(" %c", &f.usaVT);

                if(f.usaVT == 'S')
                {
                    printf("Quantidade de onibus por trajeto: ");
                    scanf("%d", &f.qtdOnibus);
                }
                break;

            case 5:
                printf("Plano de saude (N - nenhum, E - enfermaria, Q - quarto): ");
                scanf(" %c", &f.planoSaude);
                break;

            case 6:
            {
                float vt = calcularVT(f);
                float plano = calcularPlanoSaude(f);
                float fgts = calcularFGTS(f);
                float salarioTotal = f.salarioBruto + f.salarioExtra;
                float inss = calcularINSS(salarioTotal);
                float salarioFamilia = calcularSalarioFamilia(salarioTotal, f.dependentes);
                float ir = calcularIR(f, inss);

                float salarioLiquido = salarioTotal - vt - plano - inss + salarioFamilia - ir;

                printf("\n===== RESULTADO =====\n");
                printf("Vale Transporte: R$ %.2f\n", vt);
                printf("Plano de Saude: R$ %.2f\n", plano);
                printf("FGTS: R$ %.2f\n", fgts);
                printf("INSS: R$ %.2f\n", inss);
                printf("Salario Familia: R$ %.2f\n", salarioFamilia);
                printf("Imposto de Renda: R$ %.2f\n", ir);
                printf("Salario Liquido: R$ %.2f\n", salarioLiquido);
                break;
            }
        }

    } while(opcao != 0);

    return f;
}


int main()
{
    Funcionario funcionario = {0};

    menu(funcionario);

    return 0;
}
