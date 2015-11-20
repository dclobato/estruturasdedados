void heapsort(int * v, int s)
{
   int inicio, fim;
   int t;

   /* heapify */
   for (inicio = (s - 1) / 2; inicio >= 0; inicio--)
   {
      criaHeap(v, inicio, s);
   }

   for (fim = s - 1; fim > 0; fim--)
   {
      t = v[fim];
      v[fim] = v[0];
      v[0] = t;
      criaHeap(v, 0, fim);
   }
}

void criaHeap(int * v, int i, int f)
{
   int raiz, filho;
   int t;

   raiz = i;

   while ((raiz * 2 + 1) < f)
   {
      filho = 2 * raiz + 1;

      if (((filho + 1) < f) && (v[filho + 1] > v[filho]))
      {
         filho = filho + 1;
      }

      if (v[raiz] < v[filho])
      {
         t = v[filho];
         v[filho] = v[raiz];
         v[raiz] = t;
         raiz = filho;
      }
      else
      {
         return;
      }
   }
}

