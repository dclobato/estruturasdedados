void selectsort(int * v, int s)
{
   int i, j, t, min;

   for (i = 0; i < (s - 1); i++)
   {
      min = i;

      for (j = i + 1; j < s; j++)
      {
         if (v[j] < v[min])
         {
            min = j;
         }
      }

      if (min != i)
      {
         t = v[i];
         v[i] = v[min];
         v[min] = t;
      }
   }

   return;
}

