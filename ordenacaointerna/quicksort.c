void quicksort(int * v, int s)
{
   particao(v, 0, s - 1);
   return;
}

void particao(int * v, int inicio, int final)
{
   int p, i, j, t;


   p = v[inicio + ((final - inicio) / 2)];
   i = inicio;
   j = final;

   do
   {
      while (v[i] < p)
      {
         i++;
      }

      while (v[j] > p)
      {
         j--;
      }

      if (i <= j)
      {
         t = v[i];
         v[i] = v[j];
         v[j] = t;
         i++;
         j--;
      }
   }
   while (i <= j);

   if (inicio < j)
   {
      particao(v, inicio, j);
   }

   if (i < final)
   {
      particao(v, i, final);
   }

   return;
}

