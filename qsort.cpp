#include <iostream>
#include <cstdlib>
using std::cout;

void troca(int *a, int *b)
{
	int swap;

	swap = *a;
	*a = *b;
	*b = swap;
}

int *particao_ptr(int *pivo, int *inicio, int *fim)
{
	int *i = inicio;
	int *j = inicio;

	for (j; j != fim; ++j)
	{
		if (*j < *pivo)
		{
			troca(i,j);
			i++;
		}
	}
	troca(i, pivo);

	return i;
}

void qsort_ptr(int *inicio, int * fim)
{
	if(inicio != fim)
	{
		int *p = particao_ptr(fim-1, inicio, fim);
		qsort_ptr(inicio, p);
		qsort_ptr(p+1, fim);
	}
}

int particao_vanilla(int *v, int inicio, int fim)
{
	int i = inicio-1;
	int j = inicio;

	for (j; j < fim-1; ++j)
	{
		if (*(v+j) <= *(v + (fim-1)))
		{
			i++;
			troca((v+j), (v+i));
		}
	}
	troca((v+i+1), (v + (fim-1)));

	return i+1;
}

void qsort_vanilla(int *v, int inicio, int fim)
{
	if(inicio < fim)
	{
		int p = particao_vanilla(v, inicio, fim);
		qsort_vanilla(v, inicio, p);
		qsort_vanilla(v, p+1, fim);
	}

}

void qsort_iter(int *v, int inicio, int fim)
{
	int i = inicio;
	int j = fim;
	int p;
	
	for(;;)
	{
		cout<< "\n"<<i<<"//"<<j<<"\n";
		if (i >= j)
		{
			break;
		}

		p = particao_vanilla(v,i, j);
		if (((j-i)/2) >= p)
		{
			j = p;
			qsort_vanilla(v, p, fim);
			break;
		}
		else
		{
			i = p;
			qsort_vanilla(v, inicio, p);
			break;
		}
	}
}

int p_hoare(int *v, int inicio, int fim)
{
	int i = inicio-1;
	int j = inicio;

	for (j; j < fim-1; ++j)
	{
		if (*(v+j) <= *(v + (fim-1)))
		{
			i++;
			troca((v+j), (v+i));
		}
	}
	troca((v+i+1), (v + (fim-1)));

	return i+1;
}

int hoare(int *v, int inicio, int fim, int i)
{
	if(inicio < fim)
	{
		int p = p_hoare(v, inicio, fim);

		if(i == p)
			return *(v+p);
		if(i < p)
			return hoare(v, inicio, p, i);
		if(i > p)
			return hoare(v, p+1, fim, i);
	}
}

int *tripart(int *v, int inicio, int fim)
{
	int *i = new int[2];
	int j = inicio;
	int p = *(v+fim-1);

	i[0] = inicio;
	i[1] = fim-1;

	while (j <= i[1])
	{
		if (*(v+j) < p)
		{
			troca(v+j, v+i[0]);
			i[0]++;
			j++;
		}
		else if (*(v+j) > p)
		{
			troca(v+j, v+i[1]);
			i[1]--;
		}
		else j++;		
	}

	return i;	
}



void bfprt(int *v, int inicio, int fim, int i)
{
	int fim_intervalo, mediana5, *m;

	if (inicio - fim < 5)
		int l = hoare(v, inicio, fim, (fim-inicio)/2);
		return;

	for (int j = inicio; j < fim; j+=5)
	{
		fim_intervalo = j + 4;
		if (fim_intervalo > fim)
			fim_intervalo = fim;
		mediana5 = hoare(v, j, fim_intervalo, (j - fim_intervalo)/2);
		troca(v+mediana5, v+inicio+((j-inicio)/5));
	}
	bfprt(v, inicio, (fim-inicio)/5, i);

	m = tripart(v, inicio, fim);

	if (i < m[0])
	{
		bfprt(v, inicio, m[0]-1, i);
	}
	else if (i > m[1])
	{
		bfprt(v, m[1]+1, fim, i);
	}
	else return;
}

/*int *bfprt(int *v, int inicio, int fim, int i)
{
		int fim_intervalo, mediana5, *m;

	if (inicio - fim < 5)
		int l = hoare(v, inicio, fim, (fim-inicio)/2);
		return;

	for (int j = inicio; j < fim; j+=5)
	{
		fim_intervalo = j + 4;
		if (fim_intervalo > fim)
			fim_intervalo = fim;
		mediana5 = hoare(v, j, fim_intervalo, (j - fim_intervalo)/2);
		troca(v+mediana5, v+inicio+((j-inicio)/5));
	}
	bfprt(v, inicio, (fim-inicio)/5, i);

	m = tripart(v, inicio, fim);

	if (i < m[0])
	{
		bfprt(v, inicio, m[0]-1, i);
	}
	else if (i > m[1])
	{
		bfprt(v, m[1]+1, fim, i);
	}
	else return;
}*/

void qsort_bfprt(int *v, int inicio, int fim)
{
	if(inicio < fim)
	{
		bfprt(v, inicio, fim, inicio+((fim - inicio)/2));
		qsort_bfprt(v, inicio, (inicio+((fim - inicio)/2))-1);
		qsort_bfprt(v, (inicio+((fim - inicio)/2))+1, fim-1);
	}
}

void rand_array(int size, int* arr)
{
	srand(time(nullptr));
	for (int i = 0; i<size; i++)
	{
		arr[i] = rand() % 50;
	}
}

int main()
{
	int *v = new int[30];

	rand_array(30, v);
	for (int *i = v; i != v+30; ++i)
	{
		cout << *i << "\n";
	}


	cout << "\n";

	//bfprt(v, 0, 10000000, 5000000);

	qsort_bfprt(v,  0, 30);

	for (int *i = v; i != v+30; ++i)
	{
		cout << *i << "\n";
	}

	//cout << h << "\n";
}