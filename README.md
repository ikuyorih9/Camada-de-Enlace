# Camada-de-Enlace
Projeto implementado como segundo trabalho da disciplina Redes de Computadores (SSC0641), ministrada pelo professor Rodolfo Ipolito Meneguette.

## Hierarquia das camadas.

<p align="center">
    <img width=600 src="img/Figura - hierarquia camadas.png">
</p>

### Aplicação transmissora.

### Camada de aplicação transmissora.

### Camada de enlace de dados transmissora.

### Meio de transmissão.

### Camada de enlace de dados receptora.

A camada de aplicação **receptora** recebe o quadro do *Meio de Transmissão* e recupera a informação original, sem as mudanças feitas no controle de erro. A recuperação do quadro original depende de qual controle de erro foi feito:

* **Paridade**: a quantidade de bits '1' no quadro deve corresponder ao bit de paridade (último bit do quadro). Caso contrário, é detectado um erro. O último bit pode ser de paridade ímpar ou par, dependendo do booleano 'controlePar'.

```
void CamadaEnlace::controlaParidadeRecepcao(bool controlePar){
    int tamanho = this->tamanho;

    //Copia o quadro sem o bit de paridade para um novo quadro.

    int * novoQuadro = (int*) malloc(sizeof(int) * (tamanho - 1));
    memcpy(novoQuadro, this->quadro, sizeof(int) * (tamanho - 1));

    //Verifica o erro através da quantidade de '1's e da paridade do quadro.
    bool paridade = retornaSePar(novoQuadro, tamanho-1);

    //Verificação de ERRO caso a não correspondência de paridade.
    if(this->quadro[tamanho - 1] != paridade)
        //ERRO

    //Atualização do quadro.
    free(this->quadro);
    this->quadro = novoQuadro;
    this->tamanho = tamanho - 1;
}
```

* **CRC**: 

### Camada de aplicação receptora.


### Aplicação receptora.