#include "VTKCoordinateTransform.h"

#include <vtkBYUReader.h>
#include <vtkNamedColors.h>
#include <vtkTransform.h>
#include <vtkTransformFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkCamera.h>
#include <vtkRenderWindow.h>

VTKCoordinateTransform::VTKCoordinateTransform(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    this->_pVTKWidget = new QVTKOpenGLNativeWidget();
    this->setCentralWidget(_pVTKWidget);
    // this->showMaximized();

    vtkNew<vtkRenderer> renderer;
    this->_pVTKWidget->renderWindow()->AddRenderer(renderer);
    this->_pVTKWidget->renderWindow()->Render();

    this->_widgetCamOrien = vtkCameraOrientationWidget::New();
    this->_widgetCamOrien->SetParentRenderer(renderer);
    this->_widgetCamOrien->On();

    vtkNew<vtkNamedColors> colors;

    vtkNew<vtkBYUReader> cow;
    cow->SetFileName("cow.g");

    vtkNew<vtkPolyDataMapper> mapper;
    mapper->SetInputConnection(cow->GetOutputPort());

    vtkNew<vtkActor> actor;
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(colors->GetColor3d("Gold").GetData());
    // actor->RotateY(45);

    renderer->AddActor(actor);
    renderer->SetBackground(colors->GetColor3d("DarkSlateGray").GetData());

    // renderer->GetActiveCamera()->Azimuth(90);
    // renderer->ResetCamera();

    vtkNew<vtkTransform> transform;
    transform->Translate(10, 0, 0);
    transform->RotateY(90);
    transform->Translate(-10, 0, 0);

    vtkNew<vtkTransformFilter> transFilter;
    transFilter->SetInputConnection(cow->GetOutputPort());
    transFilter->SetTransform(transform);

    vtkNew<vtkPolyDataMapper> transMapper;
    transMapper->SetInputConnection(transFilter->GetOutputPort());

    vtkNew<vtkActor> transActor;
    transActor->SetMapper(transMapper);
    transActor->GetProperty()->SetColor(colors->GetColor3d("Silver").GetData());

    renderer->AddActor(transActor);
}

VTKCoordinateTransform::~VTKCoordinateTransform()
{
    delete this->_pVTKWidget;
    this->_widgetCamOrien->Delete();
}
