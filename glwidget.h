#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QGLShaderProgram>
#include <QPixmap>
#include <QGraphicsScene>
class Form;
class QGraphicsItem;

struct Cube
{
    QVector<QVector3D> vertices;
    QVector<QVector2D> textureCoordinates;
    GLuint texture;
    QPixmap pixmap;

    Cube();
    bool intersect(const QVector3D &rayOrg, const QVector3D &rayDir, QVector2D &texCoords);
};

class GlWidget : public QGLWidget
{
    Q_OBJECT

public:
    GlWidget(QWidget *parent = 0);
    ~GlWidget();
    QSize sizeHint() const;
    void init( QGraphicsScene* scene );
    void getMousePickRay(const QPointF &mouse, QVector3D& rayOrg, QVector3D& rayDir);
public slots:
    void updateTexture( const QList<QRectF>& );

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

private:
    QMatrix4x4 pMatrix;
    QGLShaderProgram shaderProgram;

    double alpha;
    double beta;
    double distance;
    QPoint lastMousePosition;
    Form* widget;
    QGraphicsScene* scene;
    QPointF lastSceneMousePosition;
    Cube cube;
};


#endif // GLWIDGET_H
