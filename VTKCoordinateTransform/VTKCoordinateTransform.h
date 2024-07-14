#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_VTKCoordinateTransform.h"

#include <QVTKOpenGLNativeWidget.h>
#include <vtkCameraOrientationWidget.h>

class VTKCoordinateTransform : public QMainWindow
{
    Q_OBJECT

public:
    VTKCoordinateTransform(QWidget *parent = nullptr);
    ~VTKCoordinateTransform();

private:
    Ui::VTKCoordinateTransformClass ui;

    QVTKOpenGLNativeWidget* _pVTKWidget = Q_NULLPTR;
    vtkCameraOrientationWidget* _widgetCamOrien = Q_NULLPTR;
};
