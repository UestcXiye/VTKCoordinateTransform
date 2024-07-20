#include "VTKCoordinateTransform.h"

#include <vtkLineSource.h>
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
    renderer->ResetCamera();

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
    renderer->ResetCamera();

    vtkNew<vtkLineSource> lineX;
    lineX->SetPoint1(0, 0, 0);
    lineX->SetPoint2(10, 0, 0);
    vtkNew<vtkPolyDataMapper> mapperX;
    mapperX->SetInputConnection(lineX->GetOutputPort());
    vtkNew<vtkActor> actorX;
    actorX->SetMapper(mapperX);
    actorX->GetProperty()->SetLineWidth(5);
    actorX->GetProperty()->SetColor(255, 0, 0);

    vtkNew<vtkLineSource> lineY;
    lineY->SetPoint1(0, 0, 0);
    lineY->SetPoint2(0, 10, 0);
    vtkNew<vtkPolyDataMapper> mapperY;
    mapperY->SetInputConnection(lineY->GetOutputPort());
    vtkNew<vtkActor> actorY;
    actorY->SetMapper(mapperY);
    actorY->GetProperty()->SetLineWidth(5);
    actorY->GetProperty()->SetColor(0, 255, 0);

    vtkNew<vtkLineSource> lineZ;
    lineZ->SetPoint1(0, 0, 0);
    lineZ->SetPoint2(0, 0, 10);
    vtkNew<vtkPolyDataMapper> mapperZ;
    mapperZ->SetInputConnection(lineZ->GetOutputPort());
    vtkNew<vtkActor> actorZ;
    actorZ->SetMapper(mapperZ);
    actorZ->GetProperty()->SetLineWidth(5);
    actorZ->GetProperty()->SetColor(0, 0, 255);

    renderer->AddActor(actorX);
    renderer->AddActor(actorY);
    renderer->AddActor(actorZ);

    vtkNew<vtkLineSource> lineA;
    lineA->SetPoint1(10, 0, 0);
    lineA->SetPoint2(10, 10, 0);
    vtkNew<vtkPolyDataMapper> mapperA;
    mapperA->SetInputConnection(lineA->GetOutputPort());
    vtkNew<vtkActor> actorA;
    actorA->SetMapper(mapperA);
    actorA->GetProperty()->SetLineWidth(5);
    actorA->GetProperty()->SetColor(0, 255, 255);

    renderer->AddActor(actorA);
}

VTKCoordinateTransform::~VTKCoordinateTransform()
{
    delete this->_pVTKWidget;
    this->_widgetCamOrien->Delete();
}
