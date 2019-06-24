#include <iostream>
#include <cstdlib>
#include <chrono>
#include "instancias_Reais_Trabalho_2.hpp"
using std::cout;
using std::cin;
using namespace std::chrono;

int tam_padrao(char* padrao)
{
	int i = 0;
	while(padrao[i] != '\0') i++;

	return i;
}

void forca_bruta(char* texto, char*  padrao, int* ocorrencias)
{
	int i=0;
	int j=0;
	int k;
	int n_ocorrencias=0;

	while (texto[i] != '\0')
	{
		j = 0;
		k = i;
		while (texto[k+j] == padrao[j])
		{ 
			j++;
			if (padrao[j] == '\0')
			{
				ocorrencias[n_ocorrencias] = i;
				n_ocorrencias++;
				cout<<"aumentou\n";
				break;
			}
		}
		i++; 
	}

	ocorrencias[n_ocorrencias] = -1;
}

void calcular_pi(char* padrao, int* pi)
{
	pi[0] = 0;
	int m = tam_padrao(padrao);
	int k, l;
	for (int i = 1; i <= m; i++)
	{
		k = i-1;
		while(true)
		{
			l = pi[k];
			if (l == 0)
			{
				if(padrao[0] == padrao[i])
				{
					pi[i] = 1;
					break;
				}
				else
				{
					pi[i] = 0;
					break;
				}
			}
			else if (padrao[i] == padrao[l])
			{
				pi[i] = l+1;
				break;
			}
			else{
				k = l-1;
			}
		}
	}
}

void kmp (char* texto, char*  padrao, int* ocorrencias)
{

	int t = tam_padrao(padrao);

	int *pi = new int[t];

	calcular_pi(padrao, pi);

	int i = 0;
	int j = 0;
	int n_ocorrencias = 0;

	while (texto[i] != '\0')
	{
		if (texto[i] != padrao[j]) 
		{
			if (j == 0) ++i;
			else j = pi[j-1];
		}
		else if (padrao[j+1] == '\0')
		{
			ocorrencias[n_ocorrencias] = i-j;
			n_ocorrencias++;
			j = pi[j];
			++i;
		}
		else
		{
			++j;
			++i;
		}
	}

	ocorrencias[n_ocorrencias] = -1;
}



void gera_aaaaaa(char* aaaa, int n)
{
	for (int i = 0; i < n; i++)
	{
		aaaa[i] = 'a';
	}
}

void gera_texto_aleatorio(char* aleatext, int n)
{
	srand(time(nullptr));
	for (int i = 0; i < n; i++)
	{
		aleatext[i] = 97 + rand() % 26 ;
	}

	aleatext[n] = '\0';
}

int main ()
{	
	// char * t = "beu nome eh barcos\0";
	// char * p = "barcos\0";
	// int o[20]; 
	// forca_bruta(t, p, o);

	// for (int i = 0; i < 20; i++){cout<<o[i]<<'\n';}
    int op;
    int n;
	int m;
	char continua = 's';
	while(continua != 'n')
	{
		cout<<"1. texto aleatorio\n2. pior caso 1\n3. pior caso 2\n4. texto real\n ";
		cin>>op;
		switch(op)
		{
			case 1:
			{
				cout<<"Entre com o tamanho do texto: ";
				cin>>n;
				cout<<"Entre com o tamanho do padrao: ";
				cin>>m;

				char *t = new char[n+1];
				char *p = new char[m+1];
				int *o = new int[n+1];

				gera_texto_aleatorio(t,n);
				gera_texto_aleatorio(p,m);

				auto start = high_resolution_clock::now();
				forca_bruta(t, p, o);
				auto stop = high_resolution_clock::now();

				auto duration = duration_cast<milliseconds>(stop-start);

				cout<<"Tempo tomado pelo algoritmo forca bruta: "<< duration.count()<<" ms\n";

				start = high_resolution_clock::now();
				kmp(t, p, o);
				stop = high_resolution_clock::now();

				auto duration_kmp = duration_cast<microseconds>(stop-start);

				cout<<"Tempo tomado pelo algoritmo kmp: "<< duration_kmp.count()<<" ms\n";

				cout<<"Deseja fazer nova tomada? s/n";
				cin>>continua;
			}
			case 2:
			{
				cout<<"Entre com o tamanho do texto: ";
				cin>>n;
				cout<<"Entre com o tamanho do padrao: ";
				cin>>m;

				char *t = new char[n+1];
				char *p = new char[m+1];
				int *o = new int[n+1];

				gera_aaaaaa(t, n);
				t[n] = '\0';
				gera_aaaaaa(p, m);
				p[m] = '\0';

				auto start = high_resolution_clock::now();
				forca_bruta(t, p, o);
				auto stop = high_resolution_clock::now();

				auto duration = duration_cast<microseconds>(stop-start);

				cout<<"Tempo tomado pelo algoritmo forca bruta: "<< duration.count()<<" ms\n";

				start = high_resolution_clock::now();
				kmp(t, p, o);
				stop = high_resolution_clock::now();

				duration = duration_cast<microseconds>(stop-start);

				cout<<"Tempo tomado pelo algoritmo kmp: "<< duration.count()<<" ms\n";

				cout<<"Deseja fazer nova tomada? s/n";
				cin>>continua;
			}
			case 3:
			{
				cout<<"Entre com o tamanho do texto: ";
				cin>>n;
				cout<<"Entre com o tamanho do padrao: ";
				cin>>m;

				char *t = new char[n+1];
				char *p = new char[m+1];
				int *o = new int[n+1];

				gera_aaaaaa(t, n);
				t[n] = '\0';
				gera_aaaaaa(p, m-1);
				p[m-1] = 'b';
				p[m] = '\0';

				auto start = high_resolution_clock::now();
				forca_bruta(t, p, o);
				auto stop = high_resolution_clock::now();

				auto duration = duration_cast<microseconds>(stop-start);

				cout<<"Tempo tomado pelo algoritmo forca bruta: "<< duration.count()<<" ms\n";

				start = high_resolution_clock::now();
				kmp(t, p, o);
				stop = high_resolution_clock::now();

				duration = duration_cast<microseconds>(stop-start);

				cout<<"Tempo tomado pelo algoritmo kmp: "<< duration.count()<<" ms\n";

				cout<<"Deseja fazer nova tomada? s/n";
				cin>>continua;
			}
			case 4:
			{
				cout<<"Escolha um número i ∈ [0..35129]: ";
				cin>>n;

				int *o = new int[35129];

				auto start = high_resolution_clock::now();
				forca_bruta((char*)Texto_Livros, (char*)Padroes_Palavras[n], o);
				auto stop = high_resolution_clock::now();

				auto duration = duration_cast<microseconds>(stop-start);

				cout<<"Tempo tomado pelo algoritmo forca bruta: "<< duration.count()<<" ms\n";

				start = high_resolution_clock::now();
				kmp((char*)Texto_Livros, (char*)Padroes_Palavras[n], o);
				stop = high_resolution_clock::now();

				duration = duration_cast<microseconds>(stop-start);

				cout<<"Tempo tomado pelo algoritmo kmp: "<< duration.count()<<" ms\n";

				cout<<"Deseja fazer nova tomada? s/n";
				cin>>continua;
			}
			default:
			{
				cout<<"opção invalida\n";
			}
			break;
		}
	}	
}