/**********************************************************/
/*                                                        */
/*                  ����� QWheelZoomSvc                   */
/*                      ������ 1.0.3                      */
/*                                                        */
/* ������������ ��������� ����������� ��������� ��������  */
/* �������� ��������� ������ ����, �������� �����������   */
/* � ������ QwtChartZoom, ������� � ������ 1.5.0.         */
/*                                                        */
/* ���������� ��������� ������ ���������,                 */
/* �. �������-��������� ������������ ���., 2012 �.,       */
/* ��� ��������� �. �. ����������, �. �����������.        */
/*                                                        */
/* ����������� ��������� ������������� � ���������������. */
/* ���������� ������ �����������.                         */
/*                                                        */
/**********************************************************/

#ifndef QWHEELZOOMSVC_H
#define QWHEELZOOMSVC_H

#include "qwtchartzoom.h"

class QWheelZoomSvc : public QObject
{
    Q_OBJECT

public:
    // �����������
    explicit QWheelZoomSvc();

    // ������������ ���������� � ��������� ���������������
    void attach(QwtChartZoom *);

    // ������� ������������ ��������������� �������
    // ��� �������� ������ ����
    void setWheelFactor(double);

protected:
    // ���������� ���� �������
    bool eventFilter(QObject *,QEvent *);

private:
    QwtChartZoom *zoom;     // ��������� �������� ���������������
    double sfact;           // �����������, ������������ ��������� �������� �������
                            // ��� �������� ������ ���� (�� ��������� ����� 1.2)

    // ���������� �������/���������� ������� Ctrl
    void switchWheel(QEvent *);
    // ���������� ��������� �� �������� ������ ����
    void applyWheel(QEvent *,bool,bool);
    // ���������� �������� ������ ����
    void procWheel(QEvent *);
};

#endif // QWHEELZOOMSVC_H