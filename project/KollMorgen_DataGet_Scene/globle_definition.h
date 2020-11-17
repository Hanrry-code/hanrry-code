#ifndef GLOBLE_DEFINITION_H
#define GLOBLE_DEFINITION_H
#include<QString>

//参数设置模块结构体 一些设置的元素
struct TargetParameters
{
    QString label_name;
    bool  checkBox_ishide_state[6];//隐藏置位
    bool  checkBox_Filter_state[6];//滤波器置位
    int color_index;//颜色索引
    int aisle_index;//通道索引
    QString id_name;//通道id名
    double Filter_frequency[6];//滤波器频率数

    double record_time;      //时间基准和触发器栏目中 记录时间数
    double collect_frequency;//时间基准和触发器栏目中 采集频率数
    int signal_source_index; //时间基准和触发器栏目中 信号源索引值
    double simple_number;    //时间基准和触发器栏目中 样本数目
    double collect_interval; //时间基准和触发器栏目中 采集间隔
    double grade_number;     //时间基准和触发器栏目中 级别
    int Slope_index;         //时间基准和触发器栏目中 斜度combobox的索引值
    double position_number;  //时间基准和触发器栏目中 位置

    bool checkbox_show_cursor;       //光标栏目中 显示光标

    bool checkbox_showprograma[6];   //显示栏目中的checkbox
    int background_color_index;      //显示栏目中 背景颜色combobox的索引值
    bool checkbox_history;           //显示栏目中 历史记录的checkbbox
    bool checkbox_record_AxleScale;  //显示栏目中 记住轴比例checkbox

};



#endif // GLOBLE_DEFINITION_H
