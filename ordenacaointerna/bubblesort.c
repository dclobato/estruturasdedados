void bubblesort(int * v, int s)
{
   int i, j, t;

   for (i = (s - 1); i > 0; i--)
   {
      for (j = 0; j < i; j++)
      {
         if (v[j + 1] < v[j])
         {
            t = v[j + 1];
            v[j + 1] = v[j];
            v[j] = t;
         }
      }
   }

   return;
}

