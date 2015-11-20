void shellsort(int * v, int s)
{
   int h, i, t, j;

   h = 1;

   while (h < (s - 1))
   {
      h = 3 * h + 1;
   }

   while (h > 0)
   {
      for (i = h; i < s; i++)
      {
         t = v[i];
         j = i - h;

         while ((j >= 0) && (t < v[j]))
         {
            v[j + h] = v[j];
            j = j - h;
         }

         v[j + h] = t;
      }

      h /= 3;
   }

   return;
}

