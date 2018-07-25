#include "calman.h"
#include<QDebug>
#include<QFile>
calman::calman(){}
void calman:: KalmanFilterInit(void)
{
 EstimateValue=0;
//  EstimateCovariance=0.1;
 // MeasureCovariance=0.02;
EstimateCovariance=10;
MeasureCovariance=2;
}

double calman:: KalmanFilter( double Measure)
{
//???????

KalmanGain=EstimateCovariance*sqrt(1/(EstimateCovariance*EstimateCovariance+MeasureCovariance*MeasureCovariance));
//?????????
EstimateValue=EstimateValue+KalmanGain*(Measure-EstimateValue);
//???????
//EstimateCovariance +=sqrt(1-KalmanGain)*EstimateCovariance;
EstimateCovariance +=(1-KalmanGain)*EstimateCovariance;
//??????
//MeasureCovariance +=sqrt(1-KalmanGain)*MeasureCovariance;
MeasureCovariance +=(1-KalmanGain)*MeasureCovariance;
//?????
    qDebug() << EstimateCovariance <<endl;
return EstimateValue;
}
//    for(int i = 0; i < real_receive_size; i++){    //阈值划分
//       if (view_re [i] > yuzhi)
//           view_re [i] = 190;
//       else
//           view_re [i] = 50;
//    }

unsigned char calman:: otsu_algorithm(unsigned char *pixel, int pix_num)
{
    unsigned char T = 0; //Otsu算法阈值
    double varValue = 0; //类间方差中间值保存
    double w0 = 0; //前景像素点数所占比例
    double w1 = 0; //背景像素点数所占比例
    double u0 = 0; //前景平均灰度
    double u1 = 0; //背景平均灰度
    double Histogram[256] = { 0 }; //灰度直方图，下标是灰度值，保存内容是灰度值对应的像素点总数

    for (int i = 0; i < pix_num; i++)
    {
        Histogram[pixel[i]] += 1;
    }
    for (int i = 0; i<255; i++)
    {
        //每次遍历之前初始化各变量
        w1 = 0;       u1 = 0;       w0 = 0;       u0 = 0;
        //***********背景各分量值计算**************************
        for (int j = 0; j <= i; j++) //背景部分各值计算
        {
            w1 += Histogram[j];  //背景部分像素点总数
            u1 += j*Histogram[j]; //背景部分像素总灰度和
        }
        if (w1 == 0) //背景部分像素点数为0时退出
        {
            continue;//break;
        }
        u1 = u1 / w1; //背景像素平均灰度
        w1 = w1 / pix_num; // 背景部分像素点数所占比例
                            //***********背景各分量值计算**************************

                            //***********前景各分量值计算**************************
        for (int k = i + 1; k<255; k++)
        {
            w0 += Histogram[k];  //前景部分像素点总数
            u0 += k*Histogram[k]; //前景部分像素总灰度和
        }
        if (w0 == 0) //前景部分像素点数为0时退出
        {
            continue;//break;
        }
        u0 = u0 / w0; //前景像素平均灰度
        w0 = w0 / pix_num; // 前景部分像素点数所占比例

        //***********前景各分量值计算**************************
        //***********类间方差计算******************************
        double varValueI = w0*w1*(u1 - u0)*(u1 - u0); //当前类间方差计算
        if (varValue<varValueI)
        {
            varValue = varValueI;
            T = i;
        }
    }
    return T;
}
#define win_size 3  //窗大小
//unsigned char win_temp[win_size];
void calman:: shift_win_filter(unsigned char* data, int size)   //滑动窗滤波
{
    double sum = 0;
    int state;
    for ( state = 0; state < size - win_size+1; state++)
    {
        sum = 0;
        for (int i = state; i < win_size + state; i++)
        {
            //win_temp[i] = data[i];
            //sum += win_temp[i];
            sum += data[i];
        }
        sum /= win_size;   //平均值
        data[state] = sum; //将均值赋值给当前位置的信号。
    }
    for (int i = state; i <size; i++)
    {
        data[i] = sum;
    } //最后剩下的统一等于最后一次的平均
}
#define find_falling_num 10
int calman::find_falling_edge(unsigned char *data, int legth)
{
        int fifty_sum = 0;
        int max_sum = 0;
        int mark_state = 0;
        for(int i = 0;i < legth-find_falling_num;i++)
        {
            for(int j = i; j < i+find_falling_num;j++)
            {
                fifty_sum += (data[j] - data[j+1]);
            }
            if (fifty_sum > max_sum)
            {
               max_sum = fifty_sum;
                mark_state = i;
            }
        }
        return mark_state+find_falling_num/2;
}

unsigned char calman::find_min(unsigned char *data, int legth)
{
    unsigned char min = data[0],min_pos = 0;
    for(int i=1;i<legth;i++)
    {
      if(data[i]<min){
          min=data[i] ;
          min_pos =i;
      }
    }
    return min_pos;
}
unsigned char calman::find_min1(unsigned char *data, int length)
{
    int sum  = 0,max_num = 0;
    int min = data[find_min(data,length)];
    for(int j =0;j<length;j++)
        if(min == data[j])
        {
            sum += j;
            max_num++;
        }
    return sum/max_num;
}
double calman::liquid_pos(unsigned char minpixel)
{
    double temp = (-0.0468*minpixel +3.2429)*10;
    temp*=10;   //第二个小数点进行四舍五入
    if((temp-(int)temp)<0.5)
        temp = temp/10;
    else
        temp = (temp+1)/10;
    return temp;
}
void save_data(unsigned char *arr,int legth)
{
    QFile data("save_data.txt");
    if (data.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream out(&data);
        //out << "Result: " << qSetFieldWidth(10) << left << 3.14 << 2.7;
        // writes "Result: 3.14      2.7       "
        for(int i= 0;i<legth;i++)
            out << arr[i]<<' ';
    }
}
QString prepare_str_for_textview(unsigned char *arr,int legth)
{
    QString tmp;
    for(int i=0;i<legth;i++)
    {
        tmp+=QString::number(arr[i],10);//调用这个函数即可
        tmp+= " ";
    }
    return tmp;
}
void SortFrom3648(uchar* data,uchar* target_data,int target_datasize)
{
    short frequency_demultiplication =3648/target_datasize;
    for(int i = 1 ;i < 3648;i+=frequency_demultiplication) //将第0个抛弃
    {
        target_data[i/frequency_demultiplication]= data[i];
    }
}


