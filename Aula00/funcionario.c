#include <stdio.h>

#define CUSTO_VALE 6
#define DIAS_UTEIS 22
#define VALOR_PLANO_ENFERMARIA 89.90
#define VALOR_PLANO_QUARTO 119.90

int main()
{
    int qtnDepentes , valeTransporte;
    float salarioBruto , salarioExtra , valorValeTransporte;
    float valorMaximoDesconteVT , salarioLiquido , valorFGTS , valorINSS;
    char planoSaude;

    printf("Digite a quantidade de Dependentes: ");
    scanf("%d" , &qtnDepentes);
    printf("Digite o Salario Bruto: ");
    scanf("%f" , &salarioBruto);
    printf("Digite o Salario Extra: ");
    scanf("%f" , &salarioExtra);
    printf("Digite a quantidade de onibus para se deslocar para a empresa: ");
    printf("(Coloque 0 se nao quer vale)");
    scanf("%d" , &valeTransporte);
    printf("Digite (N) se nao quer o plano de Saude | Digite (E) se quer Enfermaria");
    printf("Digite (Q) se quer quarto: ");
    scanf("%c" , &planoSaude);

    //VALE TRANSPORTE
    if ( valeTransporte > 0)
    {
        valorMaximoDesconteVT = salarioBruto * 0.06;
        valorValeTransporte = valeTransporte * CUSTO_VALE * DIAS_UTEIS;

        if ( valorValeTransporte > valorMaximoDesconteVT)
        {
            salarioLiquido = salarioBruto - valorMaximoDesconteVT;
        }
        else
        {
            salarioLiquido = salarioBruto - valorValeTransporte;
        }
    }
    
    //PLANO DE SAÚDE
    if ( planoSaude == 'E')
    {
        salarioLiquido = ( qtnDepentes + 1 ) * VALOR_PLANO_ENFERMARIA;
    }
    else if ( planoSaude == 'Q')
    {
        salarioLiquido = ( qtnDepentes + 1 ) * VALOR_PLANO_QUARTO;
    }

    //FGTS
    valorFGTS = ( salarioBruto + salarioExtra) * 0.08;
    printf("Valor a ser depositado para o FGTS = %.2f" , valorFGTS);

    //INSS
    valorINSS = (salarioBruto + salarioExtra);

    if ( valorINSS < 1100.01)
    {
        valorINSS = valorINSS * 0.075;
        
    }
    else if ( valorINSS > 1100 && valorINSS < 2203.49)
    {
        valorINSS = valorINSS * 0.09;
    }
    else if ( valorINSS > 2203.48 && valorINSS < 3305.23)
    {
        valorINSS = valorINSS * 0.12;
    }
    else
    {
        valorINSS = valorINSS * 0.14;
    }

    salarioLiquido = salarioLiquido - valorINSS;
}
