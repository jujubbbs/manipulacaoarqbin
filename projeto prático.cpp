//Equipe: Bianca Lima, Júlia Ribeiro e Larissa Rocha
//Tema: Ganhadores de Oscar

#include <iostream>
#include <fstream>
#include <cstring>
#include <stdio.h>

using namespace std;

struct ganhadores{
  char nome[23];
  char modalidade [30];
  char filme [40];
  int ano;
  char pais[16];
  int duracaoMin;
};
//Remoção para sobreescrever se dá por negativação da duração do filme.
//Remoção definitiva será feita ao reorganizar o arquivo.
void remover(ganhadores lista[], int tam, int remove){
  for (int i=0; i<tam; i++){
    if (i==remove){
      lista[i].duracaoMin = -1;
    }
  }
}

//Escreve no arquivo "oscar.dat" 

void inserir(ganhadores lista[], int i){
  ofstream novoArqbin ("oscar.dat", ios::binary);
  novoArqbin.write((char*)lista, sizeof(ganhadores)*i);
}

//Pede entrada do usuário para inserir novos dados no arquivo

void dadosNovos(ganhadores lista[], int i ){
    cin.ignore();
    cout<<"Digite o nome do ganhador: ";
        cin.getline(lista[i].nome,23);
        cout<<"Digite a modalidade do ganhador: ";
        cin.getline(lista[i].modalidade,30);
        cout<<"Digite o nome do filme: ";
        cin.getline(lista[i].filme,40);
        cout<<"Digite o ano de produção: ";
        cin>>lista[i].ano;
        cin.ignore();
        cout<< "Digite o país de origem do filme: ";
        cin.getline(lista[i].pais,16);
        cout<<"Digite a duração do filme em minutos: ";
        cin>>lista[i].duracaoMin;
}


void buscarAno( ganhadores lista[], int i , int buscaAno){	
  if (buscaAno==lista[i].ano){
    cout <<i+1<<" "<<lista[i].nome<< " "<<lista[i].modalidade<<" "<< lista[i].filme<<" "<<lista[i].ano<<" "<<lista[i].pais<<" "<<lista[i].duracaoMin<< endl;
  }
}

void imprimir(ganhadores lista[], int i)
{
  cout << lista[i].nome<< " "<<lista[i].modalidade<<" "<< lista[i].filme<<" "<<lista[i].ano<<" "<<lista[i].pais<<" "<<lista[i].duracaoMin<<endl;

}

int main()
{
  int escolha;
  int busca;
  int buscaAno;
  string buscaGanhador;
  int tam=0;
  int imp;
  int insere;
  int remove;

  ifstream arquivobinario("oscar.dat", ios::binary);
  ganhadores* lista = nullptr;
  ganhadores registro;

//Redimensionamento de vetor de registros para leitura completa do arquivo binário e acréscimo na variável tam para cada registro lido do arquivo 

  while (arquivobinario.read(reinterpret_cast<char*>(&registro), sizeof(ganhadores))) {
      tam++;
      ganhadores* temp = new ganhadores[tam];
      if (lista) {
          memcpy(temp, lista, (tam - 1) * sizeof(ganhadores));
          delete[] lista;
      }
      lista = temp;
      lista[tam - 1] = registro;
  }

//Primeira entrada

  cout << "Digite 1 para remover dados existentes" << endl << "Digite 2 para inserir um novo elemento no arquivo" <<endl<< "Digite 3 para buscar registro" << endl << "Digite 4 para imprimir arquivo" << endl;
  cin >> escolha;

//Pede entrada do usuário e marca com chave negativa lista[entrada].duracaoMin

  if(escolha==1){
    cout << "Digite o índice do vetor que deseja apagar:";
    cin>>remove;
    remover(lista, tam, remove);
    inserir(lista, tam);
  }

  else if(escolha==2){
    cout << "Caso tenha algum elemento marcado com chave negativa (removido) a inserção ocorrerá sobreescrevendo esse dado."<<endl<<"Caso contrário a inserção ocorrerá no fim do arquivo."<<endl;
    bool reescrever = false;

//Sobreescreve elemento marcado com chave negativa caso esse exista

    for (int i=0; i<tam; i++){
      if (lista[i].duracaoMin==-1){
        reescrever=true;
        dadosNovos(lista, i);
        inserir (lista, tam);
      }
    }

//Insere elemento novo no fim do arquivo

    if (reescrever==false){
      insere=1;
      ganhadores *temp = new ganhadores [tam+insere];
      memcpy(temp, lista, sizeof(ganhadores)*tam);
      delete [] lista;
      lista = temp;

      for (int i=tam; i<(tam+insere); i++){
      dadosNovos(lista, i);
      }
    tam= tam+insere;
    inserir (lista, tam);
    }
  }

//Busca em regitro de dois tipos diferentes (comparação de char e de inteiros)

  else if(escolha==3){
    cout << "Digite 1 para fazer busca por ano de premiação"<<endl<<"Digite 2 para fazer busca por nome do ganhador"<<endl;
    cin>>busca;
    if (busca==1){
      cout<<"Digite o ano de premiação: ";
      cin>>buscaAno;
      for (int i=0; i<tam; i++){
        buscarAno(lista, i, buscaAno);
      }
    }else if (busca==2){
      cout<< "Digite o nome do ganhador: ";
      cin.ignore();
      getline (cin, buscaGanhador);
      for (int i=0; i<tam; i++){
        if (strcmp(buscaGanhador.c_str(),lista[i].nome)==0){
            cout <<i+1<<" "<< lista[i].nome<< " "        
            <<lista[i].modalidade<<" "<<         
            lista[i].filme<<" "<<lista[i].ano<<" "  
          <<lista[i].pais<<" "<<lista[i].duracaoMin<<   
          endl;
        }
     }
    }
  }

//Imprime arquivo completo ou trecho, dependendo da entrada do usuário

  else if(escolha==4){
    cout<<"Digite 1 para imprimir arquivo completo"<<endl<<"Digite 2 para imprimir trecho de vetor"<<endl;
    cin>>imp;
    if (imp==1){
      for (int i=0; i<tam; i++){
        imprimir(lista, i);
      }
    }
    else{
      int inicio, fim;
      cout<< "Digite o inicio do vetor"<<endl;
      cin>>inicio;
      cout<<"Digite o fim do vetor"<<endl;
      cin>>fim;
      for (int i=inicio; i<=fim; i++){
        imprimir(lista, i);
      }
    }
  }

//Retorna função main() caso a entrada seja inválida

  else{
    cout << "Opção não encontrada" << endl;
    cout << main() << endl;
  }

  return 0;
}
