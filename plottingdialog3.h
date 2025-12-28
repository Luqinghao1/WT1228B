/*
 * 文件名: plottingdialog3.h
 * 文件作用: 压力导数曲线配置对话框头文件
 * 功能描述:
 * 1. 声明了用于配置曲线样式的对话框类。
 * 2. 提供获取用户设置（如曲线名称、图例、数据列索引、样式颜色等）的接口。
 * 3. 管理界面交互逻辑，如颜色选择、平滑参数的启用状态等。
 */

#ifndef PLOTTINGDIALOG3_H
#define PLOTTINGDIALOG3_H

#include <QDialog>
#include <QStandardItemModel>
#include <QColor>
#include "qcustomplot.h"

namespace Ui {
class PlottingDialog3;
}

class PlottingDialog3 : public QDialog
{
    Q_OBJECT

public:
    // 构造函数：初始化对话框，接收数据模型用于列选择
    explicit PlottingDialog3(QStandardItemModel* model, QWidget *parent = nullptr);
    // 析构函数：释放UI资源
    ~PlottingDialog3();

    // --- 基础信息获取接口 ---
    QString getCurveName() const;       // 获取曲线名称
    QString getPressLegend() const;     // 获取压力曲线图例
    QString getDerivLegend() const;     // 获取导数曲线图例

    // --- 数据源设置接口 ---
    int getTimeColumn() const;          // 获取时间列索引
    int getPressureColumn() const;      // 获取压力列索引
    bool isMeasuredPressure() const;    // 获取是否为实测压力（true=实测, false=压差）

    // --- 计算参数接口 ---
    double getLSpacing() const;         // 获取导数计算步长 L-Spacing
    bool isSmoothEnabled() const;       // 获取是否启用平滑处理
    int getSmoothFactor() const;        // 获取平滑因子

    // --- 坐标轴标签接口 ---
    QString getXLabel() const;          // 获取X轴标签文本
    QString getYLabel() const;          // 获取Y轴标签文本

    // --- 压力曲线样式接口 ---
    QCPScatterStyle::ScatterShape getPressShape() const; // 获取压力点形状
    QColor getPressPointColor() const;                   // 获取压力点颜色
    Qt::PenStyle getPressLineStyle() const;              // 获取压力线型
    QColor getPressLineColor() const;                    // 获取压力线颜色

    // --- 导数曲线样式接口 ---
    QCPScatterStyle::ScatterShape getDerivShape() const; // 获取导数点形状
    QColor getDerivPointColor() const;                   // 获取导数点颜色
    Qt::PenStyle getDerivLineStyle() const;              // 获取导数线型
    QColor getDerivLineColor() const;                    // 获取导数线颜色

    // 是否在新窗口中打开图表
    bool isNewWindow() const;

private slots:
    // 槽函数：响应“启用平滑”复选框的状态变化
    void onSmoothToggled(bool checked);

    // 槽函数：响应各颜色选择按钮的点击事件
    void selectPressPointColor();
    void selectPressLineColor();
    void selectDerivPointColor();
    void selectDerivLineColor();

private:
    Ui::PlottingDialog3 *ui;
    QStandardItemModel* m_dataModel; // 指向数据源模型的指针
    static int s_counter;            // 静态计数器，用于生成默认的曲线名称

    // 内部成员变量：存储当前选择的颜色
    QColor m_pressPointColor;
    QColor m_pressLineColor;
    QColor m_derivPointColor;
    QColor m_derivLineColor;

    // 私有辅助函数：填充下列列表框（ComboBox）
    void populateComboBoxes();
    // 私有辅助函数：初始化样式选项（点形、线型等）
    void setupStyleOptions();
    // 私有辅助函数：更新颜色按钮的背景显示
    void updateColorButton(QPushButton* btn, const QColor& color);
};

#endif // PLOTTINGDIALOG3_H
