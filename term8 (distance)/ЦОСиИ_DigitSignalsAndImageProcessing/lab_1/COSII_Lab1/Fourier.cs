using System;
using System.Numerics;

namespace COSII_Lab1
{
    class FFT
    {
        public static Complex[] imageSignal;
        public static Complex[] MAKE_FFT(Complex[] c = null)
        {
            int N = c.Length;
            if (c.Length == 1)
                return c;
            Complex[] first = new Complex[N / 2];
            Complex[] second = new Complex[N / 2];
            Complex w = 1;
            Complex wN = Complex.Exp(-2 * Math.PI * Complex.ImaginaryOne / N);
            for (int i = 0; i < N / 2; ++i)
            {
                first[i] = c[i] + c[i + N / 2];
                second[i] = (c[i] - c[i + N / 2]) * w;
                //wN = Complex.Pow(Complex.Exp(2 * Math.PI * Data.i / (N)), i + 1);  
                Data.FFT_QUANTITY += 2;
                w = w * wN;
            }
            Complex[] firstImage = MAKE_FFT(first);                                 //Находим изображения для первой половины сигнала
            Complex[] secondImage = MAKE_FFT(second);                               //Находим изображения для второй половины сигнала
            Complex[] image = new Complex[N];
            for (int k = 0; k < N / 2; k++)                                         //Собираем наш сигнал из двух половин
            {
                image[2 * k] = firstImage[k];
                image[2 * k + 1] = secondImage[k];
            }
            imageSignal = image;
            return image;
        }
        public static Complex[] RESTORE(Complex[] c)
        {
            int N = c.Length;
            if (c.Length == 1)
                return c;
            Complex[] first = new Complex[N / 2];
            Complex[] second = new Complex[N / 2];
            Complex w = 1;
            Complex wN = Complex.Exp(2 * Math.PI * Complex.ImaginaryOne / N);
            for (int i = 0; i < N / 2; ++i)
            {
                first[i] = c[i] + c[i + N / 2];
                second[i] = (c[i] - c[i + N / 2]) * w;
                //wN = Complex.Pow(Complex.Exp(2 * Math.PI * Data.i / (N)), i + 1);  
                w = w * wN;
            }
            Complex[] firstImage = RESTORE(first);                                 //Находим изображения для первой половины сигнала
            Complex[] secondImage = RESTORE(second);                               //Находим изображения для второй половины сигнала
            Complex[] image = new Complex[N];
            for (int k = 0; k < N / 2; k++)                                         //Собираем наш сигнал из двух половин
            {
                image[2 * k] = firstImage[k];
                image[2 * k + 1] = secondImage[k];
                
            }
            return image;
        }
    }
    class DFT                                                           //Класс, реализующий дискретное преобращование Фурье
    {
        public static double[] signal;                                  //Исходный сигнал
        public static Complex[] MAKE_DFT()
        {
            Complex[] image = new Complex[Data.N];

            for (int k = 0; k < Data.N; k++)
            {
                for (int n = 0; n < Data.N; n++)
                {
                    image[k] += signal[n] * Complex.Exp(-Complex.ImaginaryOne * 2 * Math.PI / Data.N * n * k);
                    Data.DFT_QUANTITY++;
                }
                image[k] /= Convert.ToDouble(Data.N);
            }
            return image;
        }
        public static Complex[] RESTORE(Complex[] image)                        //Восстановление первоначального сигнала
        {
            Complex[] original = new Complex[Data.N];                           //Восстановленный сигнал           
            for (int n = 0; n < Data.N; n++)
            {
                for (int k = 0; k < Data.N; k++)
                {
                    original[n] += image[k] * Complex.Exp(Complex.ImaginaryOne * 2 * Math.PI / Data.N * k * n);
                }
            }
            return original;
        }
    }
}
