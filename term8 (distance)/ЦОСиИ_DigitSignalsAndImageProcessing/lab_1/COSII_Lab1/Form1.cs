using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Forms.DataVisualization.Charting;
using System.Numerics;

namespace COSII_Lab1
{
    public partial class Form1 : Form                  
    {
        Double[] y;                                                     //Значение функции в момент дескритезации
        Double[] x;                                                     //Моменты дискретизации
        Complex[] FR_D;                                                 //Сигнал в частотной области
        public Form1()
        {
            InitializeComponent();
           
            y = Data.ACCOUNT_FUNCTION();                                //Формирование дискретной выборки
            DFT.signal = y;
            x = new Double[Data.N];
            
            for (int i = 0; i < Data.N; i++)                            //Формирование моментов дискретизации
            {
                x[i] = i * 2 * Math.PI / Data.N;
                chart1.Series[0].Points.AddXY(x[i], y[i]);              //Добавление точки на график
            }

            
            FR_D = new Complex[Data.N];
            FR_D = DFT.MAKE_DFT();                                      //Получение сигнала в частотной области   
            for (int i = 0; i < Data.N; i++)                            //Отображение амплитудного спектра на графике
            {
                x[i] = i * 2 * Math.PI / Data.N;
                chart2.Series[0].Points.AddXY(x[i], FR_D[i].Magnitude);
            }
     
            for (int i = 0; i < Data.N; i++)                            //Отображение фазового спектра на графике
            {
                x[i] = i * 2 * Math.PI / Data.N;
                chart3.Series[0].Points.AddXY(x[i], FR_D[i].Phase);
            }

            FR_D = DFT.RESTORE(FR_D);                                   //Восстановление сигнала по образу
            for (int i = 0; i < Data.N; i++)                            //Отображение восстановленого сигнала
            {
                x[i] = i * 2 * Math.PI / Data.N;
                chart4.Series[0].Points.AddXY(x[i], FR_D[i].Real);
            }

            Complex[] signal = new Complex[DFT.signal.Length];          //Переводим массив чисел в комплексный массив
            for (int i = 0; i < DFT.signal.Length; i++)
                signal[i] = DFT.signal[i];  

            FR_D = FFT.MAKE_FFT(signal);                                //Быстрое преобразование фурье с прореживанием по частоте
            for (int i = 0; i < FR_D.Length; i++)
                FR_D[i] /= Data.N;
            for (int i = 0; i < Data.N; i++)
            {
                x[i] = i * 2 * Math.PI / Data.N;
                chart5.Series[0].Points.AddXY(x[i], FR_D[i].Magnitude); //Рисуем амплитудный спектр
            }
            
            for (int i = 0; i < Data.N; i++)                            //Рисуем фазовый спектр
            {
                x[i] = i * 2 * Math.PI / Data.N;
                chart6.Series[0].Points.AddXY(x[i], FR_D[i].Phase);
            }
            FR_D = FFT.RESTORE(FFT.imageSignal);
            
            for (int i = 0; i < Data.N; i++)                            //Рисуем восстановленный сигнал
            {
                x[i] = i * 2 * Math.PI / Data.N;
                chart7.Series[0].Points.AddXY(x[i], FR_D[i].Real);
            }
            this.textBox1.Text = Convert.ToString(Data.FFT_QUANTITY);
            this.textBox3.Text = Convert.ToString(Data.DFT_QUANTITY / (Data.FFT_QUANTITY )) + ":1";
            this.textBox2.Text = Data.DFT_QUANTITY.ToString();
        }
        #region hide
        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void tabPage1_Click(object sender, EventArgs e)
        {

        }

        private void chart1_Click(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void label4_Click(object sender, EventArgs e)
        {

        }

        private void label5_Click(object sender, EventArgs e)
        {

        }

        private void chart2_Click(object sender, EventArgs e)
        {

        }
        #endregion
    }
}
