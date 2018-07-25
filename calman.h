#ifndef CALMAN_H
#define CALMAN_H

#include<math.h>
#include<QString>
void save_data(unsigned char *arr,int legth);
QString prepare_str_for_textview(unsigned char *arr,int legth);
void SortFrom3648(unsigned char *data,unsigned char *target_data,int target_datasize);

class calman
{
public:
    calman();
    void KalmanFilterInit(void);
    double  KalmanFilter(double Measure);
    unsigned char otsu_algorithm(unsigned char *pixel, int pix_num);
    void  shift_win_filter(unsigned char* data, int size);   //滑动窗滤波
    int find_falling_edge(unsigned char* data, int legth); // 思路是将滑动的50个数据差相加，最大的中点就是下降沿
    unsigned char find_min(unsigned char* data, int legth);
    unsigned char find_min1(unsigned char* data, int legth);
    double liquid_pos(unsigned char minpixel);
private:
    double KalmanGain;//  ?????
    double EstimateCovariance;//?????
    double MeasureCovariance;//?????
    double EstimateValue;//???
};

#endif // CALMAN_H
