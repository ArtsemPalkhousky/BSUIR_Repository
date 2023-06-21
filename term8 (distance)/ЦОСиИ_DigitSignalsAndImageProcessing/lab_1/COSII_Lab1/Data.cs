using System;
using System.Numerics;


namespace COSII_Lab1
{
    public class Data 
    {

        public const int N = 8;                                                //Число отсчетов
        public static int DFT_QUANTITY = 0;                                     //Число операций умножения для ДПФ
        public static int FFT_QUANTITY = 0;                                     //ЧИсло операций умножнеия для БПФ
        public static double function(double x)
        {
            double y = 0;
            y = Math.Cos(x) + Math.Sin(x);
            return y;
        }                              //Исследуемая функция
        public static double[] ACCOUNT_FUNCTION()
        {
            double[] coord = new double[Data.N];
            for (int i = 0; i < N; i++)
            {
                double x = i * 2 * Math.PI / Data.N;
                coord[i] = function(x);
            }
            return coord;
        }                            //Получение выборки
    }

}