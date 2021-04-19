#include <iostream>
#include<cstdlib>
#include <time.h>
#include<ctime>
#include <queue>
#include <fstream>
#include <windows.h>


using namespace std;
/*
    Trabalho de AEDES 2 - Classe Arvore

    Abraao Duarte Barbosa 
    Thiago Ramos Gomes

*/
template <class T>
class No
{

public:



    No *esq;
    No *dir;
    T info;

    No()
    {
        esq = NULL;
        dir = NULL;
        info = INT_MIN;
    }
    No(int x)
    {
        esq = NULL;
        dir = NULL;
        info = x;
    }
};



template <class T>
class arvore
{

private:

    No<T>* Raiz;

        No<T>* pesquisar(No<T>* v, int chave)
    {

        if( v == NULL){

            cout<<"\nValor "<<chave<<" NAO encontrado!!!";
            return v;
        }
        else if(v->info == chave){

            cout<<"\nvalor "<<v->info<< " encontrado!";
            return v;
        }
        else if(v->info < chave)

            return pesquisar(v->dir, chave);

        else

            return pesquisar(v->esq, chave);

    }
    bool verifica(No<T>* v, int chave)
    {

        if( v == NULL){


            return false;
        }
        else if(v->info == chave){


            return true;
        }
        else if(v->info < chave)

            return verifica(v->dir, chave);

        else

            return verifica(v->esq, chave);

    }

    No<T>* MenorDosMaiores(No<T>* &x)
    {

        No<T>*Menor = x;
        if(Menor->esq != NULL)
            MenorDosMaiores(Menor->esq);

        else if(Menor->esq == NULL)
            return Menor;

    }

    No<T>* MaiorDosMenores(No<T>* &x)
    {

        No<T> *Maior = x;
        if(Maior->dir !=NULL)
            MaiorDosMenores(Maior->dir);

        else if(Maior->dir == NULL)
            return Maior;
    }

    No<T>* deletaNo(No<T>*& a, int elemento)
    {

        if (a!=NULL)
        {
            if(elemento > a->info)
                a->dir = deletaNo(a->dir, elemento);
            else if(elemento < a->info)
                a->esq = deletaNo(a->esq, elemento);
            else
            {

                if(a->esq==NULL && a->dir==NULL)  //Folha
                {
                    delete a;
                    a = NULL;
                }
                else if(a->dir==NULL)  //Tem sub arvore esquerda
                {

                    No<T>* aux = MaiorDosMenores(a->esq);
                    a->info = aux->info;
                    aux = NULL;
                    a->esq = deletaNo(a->esq, a->info);
                }
                else if(a->esq==NULL)   //Tem sub arvore direita
                {
                    No<T>* aux = MenorDosMaiores(a->dir);
                    a->info = aux->info;
                    aux = NULL;
                    a->dir = deletaNo(a->dir, a->info);
                }
                else   //raiz de sub arvore
                {
                    No<T>* aux = MaiorDosMenores(a->esq);
                    a->info = aux->info;
                    aux = NULL;
                    a->esq = deletaNo(a->esq, a->info);
                }
            }
            return a;
        }
        else
            return a;
    }

    void inserir(No<T>* &a, int c)
    {
        if (a == NULL)
        {
            a = new No<T>(c);
        }


        else if (c > a->info)
            inserir(a->dir, c);
        else
            inserir(a->esq, c);

    }
    void imprimirArvore(No<T>* t,int n)
    {
        if (t)
        {
            int i;
            imprimirArvore(t->dir, n+1);
            for (i = 0; i < n; i++)
                cout << "    ";
            cout << t->info << endl;
            imprimirArvore(t->esq, n+1);
        }
    }
    void Ordem(No<T>* x)
    {

        if(x->esq != NULL)
            Ordem(x->esq);
        cout<<" "<<x->info;
        if(x->dir!=NULL)
            Ordem(x->dir);
    }

    int nivel(No<T>*& t,int x,int nv)
    {
        if(x==t->info)
        {
            return nv;
        }
        else if(x<t->info)
        {
            nivel(t->esq,x,nv+1);
        }
        else
        {
            nivel(t->dir,x,nv+1);
        }
    }
    int alturaa(No<T>* x)
    {

        int alturaesq = 0;
        int alturadir = 0;

        if(x->dir == NULL && x->esq == NULL)
            return 1;
        else if(x->esq != NULL)
            alturaesq = alturaa(x->esq);
        if(x->dir != NULL)
            alturadir = alturaa(x->dir);

        if(alturadir>alturaesq)
            return alturadir +1;
        else
            return alturaesq +1;

    }

public:

    void inicializa()
    {
        Raiz = NULL;
    }
    arvore()
    {
        inicializa();
    }
    void insere(int y)
    {
        if(verifica(Raiz,y))
            cout<<"Ja ta la\n";
        else inserir(Raiz,y);



    }
    void imprimeArvore()
    {

        imprimirArvore(Raiz,2);

    }

    void imprimeOrdem()
    {
        cout<<"\nEm ordem: ";
        Ordem(Raiz);
        cout<<endl;
    }
    void pesquisa(int x)
    {
        cout<<"Valor a ser pesquisado: "<<x;
        pesquisar(Raiz,x);
        cout<<endl;
    }
    void largura()
    {

        if(Raiz!=NULL)
        {
            queue <No<T>*> fila;
            queue <No<T>*> filaaux;

            fila.push(Raiz);

            No<T>* aux;

            while(fila.size()!=0)
            {


                while(fila.size()!=0)
                {
                    aux =fila.front();
                    fila.pop();
                    cout<<aux->info<<"  ";
                    filaaux.push(aux);
                }
                while(filaaux.size()!=0)
                {
                    if(filaaux.front()->esq!=NULL)
                        fila.push(filaaux.front()->esq);
                    if(filaaux.front()->dir!=NULL)
                        fila.push(filaaux.front()->dir);

                    filaaux.pop();
                }

                cout<<endl;
            }
        }
    }
    void altura()
    {
        cout<<"\nAltura da arvore: "<<alturaa(Raiz)<<endl;
    }

    void remover(int x)
    {
        if(verifica(Raiz,x))
        {
            cout<<"Deletando a chave: "<<x<<endl<<endl;
            deletaNo(Raiz,x);
        }
        else
        {
           cout<<"Elemento nao esta na arvore!"<<endl;
        }
    }
};
double PCFreq = 0.0;
__int64 CounterStart = 0;

void StartCounter()
{
    LARGE_INTEGER li;
    if(!QueryPerformanceFrequency(&li))
    cout << "QueryPerformanceFrequency failed!\n";

    PCFreq = double(li.QuadPart)/1000.0;

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}
double GetCounter()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart-CounterStart)/PCFreq;
}


int main()
{



    arvore<int>  batatinha;
    int op,y;
    do{

    cout << " Opcoes: " << endl;
    cout << " (0) - Fechar o programa "<<endl;
    cout << " (1) - Inserir um elemento " << endl;
    cout << " (2) - Remover um elemento." << endl;
    cout << " (3) - Imprimir arvore binaria" << endl;
    cout << " (4) - Imprimir arvore binaria em largura" << endl;
    cout << " (5) - Imprimir arvore em ordem" <<endl;
    cout << " (6) - Altura da arvore "<<endl;
    cout << " (7) - Pesquisar um elemento na arvore"<<endl;
    cout << " (8) - O tempo de uma insercao e: "<<endl;

    cin >> op;
    cout <<endl;

        if(op==1)
        {
            cout<<"Insira um elemento: ";
            cin>>y;

            batatinha.insere(y);

        }
        else if(op==2)
        {
            cout<<"Escolha o elemento a ser removido \n";
            cin>>y;
            batatinha.remover(y);
        }
       else if(op==3)
       {
            cout<<endl;
            batatinha.imprimeArvore();

       }
       else if(op==4)
       {
           cout<< "A arvore em largura e: "<<endl;
           batatinha.largura();
       }
       else if(op==5)
       {
           cout<<" A arvore em ordem e: ";
           batatinha.imprimeOrdem();
       }
       else if(op==6)
       {
           cout<<" A altura da arvore e: ";
           batatinha.altura();
       }
       else if (op==7)
       {
           cout<<" Insira o elemento a ser pesquisado: ";
           cin>>y;
           batatinha.pesquisa(y);
       }

        else if(op==8)
        {
            StartCounter();
            cout<<"Inserindo a chave 1";
            batatinha.insere(1);
            cout<<endl<<GetCounter()<<"ms\n";
            batatinha.remover(1);

        }
            system("pause");
            system("cls");
    }
    while(op!=0);



}
