using System;

namespace Punto1So
{
    class Program
    {
        static void Main(string[] args)
        {
            int[] var = new int[100];
            array Arreglo1 = new array(var);

            Arreglo1.printarray(var);
        }
    }
    class array
    {
        
        public array(int [] Arreglo)
        {
            for(int i = 0;i<100;i++)
            {
                Arreglo [i] = i;
            }
        }
        public void printarray(int [] Arreglo)
        {
            for (int i = 0; i < 100; i++)
            {
                Console.WriteLine(Arreglo [i]);
            }                       
        }

        ~array()
        {
            Console.WriteLine("Se ha limpiado el array");
        }    
    }
}
