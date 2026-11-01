#include "MonitorarQualidadeAmbiente.h"

QualidadeAr MonitorarQualidadeAmbiente::obterQualidadeGeral(IndicesQualidadeResultado indicesQualidadeResultado){
    QualidadeAr pior = BOA;

    QualidadeAr sensores[] = {
        indicesQualidadeResultado.QUALIDADE_CO2,
        indicesQualidadeResultado.QUALIDADE_COV,
        indicesQualidadeResultado.QUALIDADE_UMIDADE,
        indicesQualidadeResultado.QUALIDADE_PM01,
        indicesQualidadeResultado.QUALIDADE_PM01,
        indicesQualidadeResultado.QUALIDADE_PM25,
        indicesQualidadeResultado.QUALIDADE_PM10
    };

    for(QualidadeAr qualidadeAr: sensores){
        if (qualidadeAr > pior){
            pior = qualidadeAr;
        }
    }

    return pior;
}