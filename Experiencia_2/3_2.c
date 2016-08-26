//coleccion de los array
int x1[] = {0,1,2};
int x2[] = {3,4,5};
int x3[] = {6,7,8};
int x4[] = {9,10,11};
int x5[] = {-1,-2,-3};
int x6[] = {-4,-5,-6};
int n = 3;

int f1(int *a1, int *a2, int *a3, int *a4, int *a5, int *a6, int n)
{
	int i, res;

	for(i = 0, res = 0; i < n; i++, a1++, a2++, a3++, a4++, a5++, a6++)
  {
  //modificacion de la operacion
	*a4 = (*a1) - 2*(*a2);
	*a3 = *a6 = *a4 + 2*(*a5);
	res += *a3;  
  }
	return res;
}

int main(void)
{
  int n = 5;
  int suma;

  suma = f1(x1,x2,x3,x4,x5,x6,n);
  return(suma);
}


