void insertsort(int * v, int s)
{
   int i, j, t;

   for (i = 1; i < s; i++)
   {
      t = v[i];
      j = i;

      while ((j > 0) && (t < v[j - 1]))
      {
         v[j] = v[j - 1];
         j--;
      }

      v[j] = t;
   }

   return;
}

