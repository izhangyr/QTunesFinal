#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QTimer>

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:

    explicit GLWidget(QWidget *parent = 0);
    void limitCircle();


protected:
    void initializeGL();

    void paintGL();

    void resizeGL(int width, int height);

private:
    int color;

    QTimer* timer;

    double circRad;

private slots:

public slots:

    void repaint();

    void startTime();

    void endTime();



};

#endif // GLWIDGET_H
