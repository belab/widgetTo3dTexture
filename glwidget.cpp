#include "glwidget.h"
#include "form.h"

#include <QMouseEvent>
#include <QWheelEvent>
#include <QApplication>
//#include <qgraphicssceneevent.h>
#include <QGraphicsSceneEvent>
#include <QGraphicsItem>

#include <map>

// http://www.scratchapixel.com/lessons/3d-basic-lessons/lesson-9-ray-triangle-intersection/m-ller-trumbore-algorithm/
struct IsectData { float t; float u, v; };
bool intersect( const QVector3D& rayOrg,
                const QVector3D& rayDir,
                const QVector3D& v0,
                const QVector3D& v1,
                const QVector3D& v2,
                IsectData &isectData)
{
    QVector3D edge1 = v1 - v0;
    QVector3D edge2 = v2 - v0;
    QVector3D pvec = QVector3D::crossProduct(rayDir, edge2);
    float det = QVector3D::dotProduct(edge1, pvec);
    if (det == 0) return false;
    float invDet = 1 / det;
    QVector3D tvec = rayOrg - v0;
    isectData.u = QVector3D::dotProduct(tvec, pvec) * invDet;
    if (isectData.u < 0 || isectData.u > 1) return false;
    QVector3D qvec = QVector3D::crossProduct(tvec, edge1);
    isectData.v = QVector3D::dotProduct(rayDir, qvec) * invDet;
    if (isectData.v < 0 || isectData.u + isectData.v > 1) return false;
    isectData.t = QVector3D::dotProduct(edge2, qvec) * invDet;
    return true;
}

Cube::Cube()
    : pixmap(250, 250)
{
    vertices << QVector3D(-0.5, -0.5,  0.5) << QVector3D( 0.5, -0.5,  0.5) << QVector3D( 0.5,  0.5,  0.5) // Front
             << QVector3D( 0.5,  0.5,  0.5) << QVector3D(-0.5,  0.5,  0.5) << QVector3D(-0.5, -0.5,  0.5)
             << QVector3D( 0.5, -0.5, -0.5) << QVector3D(-0.5, -0.5, -0.5) << QVector3D(-0.5,  0.5, -0.5) // Back
             << QVector3D(-0.5,  0.5, -0.5) << QVector3D( 0.5,  0.5, -0.5) << QVector3D( 0.5, -0.5, -0.5)
             << QVector3D(-0.5, -0.5, -0.5) << QVector3D(-0.5, -0.5,  0.5) << QVector3D(-0.5,  0.5,  0.5) // Left
             << QVector3D(-0.5,  0.5,  0.5) << QVector3D(-0.5,  0.5, -0.5) << QVector3D(-0.5, -0.5, -0.5)
             << QVector3D( 0.5, -0.5,  0.5) << QVector3D( 0.5, -0.5, -0.5) << QVector3D( 0.5,  0.5, -0.5) // Right
             << QVector3D( 0.5,  0.5, -0.5) << QVector3D( 0.5,  0.5,  0.5) << QVector3D( 0.5, -0.5,  0.5)
             << QVector3D(-0.5,  0.5,  0.5) << QVector3D( 0.5,  0.5,  0.5) << QVector3D( 0.5,  0.5, -0.5) // Top
             << QVector3D( 0.5,  0.5, -0.5) << QVector3D(-0.5,  0.5, -0.5) << QVector3D(-0.5,  0.5,  0.5)
             << QVector3D(-0.5, -0.5, -0.5) << QVector3D( 0.5, -0.5, -0.5) << QVector3D( 0.5, -0.5,  0.5) // Bottom
             << QVector3D( 0.5, -0.5,  0.5) << QVector3D(-0.5, -0.5,  0.5) << QVector3D(-0.5, -0.5, -0.5);

    textureCoordinates << QVector2D(0, 0) << QVector2D(1, 0) << QVector2D(1, 1) // Front
                       << QVector2D(1, 1) << QVector2D(0, 1) << QVector2D(0, 0)
                       << QVector2D(0, 0) << QVector2D(1, 0) << QVector2D(1, 1) // Back
                       << QVector2D(1, 1) << QVector2D(0, 1) << QVector2D(0, 0)
                       << QVector2D(0, 0) << QVector2D(1, 0) << QVector2D(1, 1) // Left
                       << QVector2D(1, 1) << QVector2D(0, 1) << QVector2D(0, 0)
                       << QVector2D(0, 0) << QVector2D(1, 0) << QVector2D(1, 1) // Right
                       << QVector2D(1, 1) << QVector2D(0, 1) << QVector2D(0, 0)
                       << QVector2D(0, 0) << QVector2D(1, 0) << QVector2D(1, 1) // Top
                       << QVector2D(1, 1) << QVector2D(0, 1) << QVector2D(0, 0)
                       << QVector2D(0, 0) << QVector2D(1, 0) << QVector2D(1, 1) // Bottom
                       << QVector2D(1, 1) << QVector2D(0, 1) << QVector2D(0, 0);
}

bool Cube::intersect( const QVector3D& rayOrg,
                      const QVector3D& rayDir,
                      QVector2D& texCoords )
{
    if(vertices.size()!=textureCoordinates.size())
    {
        return false;
    }
    std::map<float,QVector2D> hitData;
    IsectData interSectData;
    for( int i = 0; i < vertices.size(); i=i+3 )
    {
        if( ::intersect( rayOrg, rayDir, vertices.at(i), vertices.at(i+1), vertices.at(i+2), interSectData ) )
        {
            float u = interSectData.u;
            float v = interSectData.v;
            float w = 1.0f - u -v;
            QVector2D tc1(textureCoordinates.at(i));tc1.setY(1.0f-tc1.y());
            QVector2D tc2(textureCoordinates.at(i+1));tc2.setY(1.0f-tc2.y());
            QVector2D tc3(textureCoordinates.at(i+2));tc3.setY(1.0f-tc3.y());
            hitData[interSectData.t] = w*tc1 + u*tc2 + v*tc3;
        }
    }
    if( !hitData.empty() )
    {
        texCoords=hitData.begin()->second;
        return true;
    }
    return false;
}


GlWidget::GlWidget(QWidget *parent)
    : QGLWidget(QGLFormat(/* Additional format options */), parent)
{
    alpha = 25;
    beta = -25;
    distance = 2.5;
    widget = new Form(0, this);
    this->setMouseTracking(true);
    scene = new QGraphicsScene;
    scene->addWidget(widget);
    connect( scene, SIGNAL(changed(const QList<QRectF>&)), this, SLOT( updateTexture(const QList<QRectF>&)) );
}

GlWidget::~GlWidget()
{
}

QSize GlWidget::sizeHint() const
{
    return QSize(250, 250);
}

void GlWidget::updateTexture( const QList<QRectF>& )
{
    QPainter painter( &(cube.pixmap) );
    scene->render( &painter );
    painter.setBrush(Qt::green);
    QRect highLight(lastSceneMousePosition.toPoint()-QPoint(5,5),QSize(10,10));
    painter.drawEllipse(highLight);
    cube.texture = bindTexture(cube.pixmap);
    updateGL();
}

void GlWidget::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    qglClearColor(QColor(Qt::black));

    shaderProgram.addShaderFromSourceFile(QGLShader::Vertex, ":/vertexShader.vsh");
    shaderProgram.addShaderFromSourceFile(QGLShader::Fragment, ":/fragmentShader.fsh");
    shaderProgram.link();

    cube.texture = bindTexture(cube.pixmap);

    // Set nearest filtering mode for texture minification
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // Set bilinear filtering mode for texture magnification
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}
void GlWidget::resizeGL(int width, int height)
{
    if (height == 0) {
        height = 1;
    }

    pMatrix.setToIdentity();
    pMatrix.perspective(60.0f, (float) width / (float) height, 0.001f, 1000);

    glViewport(0, 0, width, height);
}

void GlWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 mMatrix;
    QMatrix4x4 vMatrix;

    QMatrix4x4 cameraTransformation;
    cameraTransformation.rotate(alpha, 0, 1, 0);
    cameraTransformation.rotate(beta, 1, 0, 0);

    QVector3D cameraPosition = cameraTransformation * QVector3D(0, 0, distance);
    QVector3D cameraUpDirection = cameraTransformation * QVector3D(0, 1, 0);

    vMatrix.lookAt(cameraPosition, QVector3D(0, 0, 0), cameraUpDirection);

    shaderProgram.bind();

    shaderProgram.setUniformValue("mvp_matrix", pMatrix * vMatrix * mMatrix);

    shaderProgram.setUniformValue("texture", 0);

    shaderProgram.setAttributeArray("vertex", cube.vertices.constData());
    shaderProgram.enableAttributeArray("vertex");

    shaderProgram.setAttributeArray("textureCoordinate", cube.textureCoordinates.constData());
    shaderProgram.enableAttributeArray("textureCoordinate");

    glDrawArrays(GL_TRIANGLES, 0, cube.vertices.size());

    shaderProgram.disableAttributeArray("vertex");

    shaderProgram.disableAttributeArray("textureCoordinate");

    shaderProgram.release();
}
void GlWidget::getMousePickRay(const QPointF& mouse, QVector3D& rayOrg, QVector3D& rayDir)
{
    float normX = 2.0f * mouse.x() / width() - 1.0f;
    float normY = 1.0f - 2.0f * mouse.y() / height();
    // note the y pos is inverted, so +y is at the top of the screen

    QMatrix4x4 cameraTransformation;
    cameraTransformation.rotate(alpha, 0, 1, 0);
    cameraTransformation.rotate(beta, 1, 0, 0);

    QVector3D cameraPosition = cameraTransformation * QVector3D(0, 0, distance);
    QVector3D cameraUpDirection = cameraTransformation * QVector3D(0, 1, 0);
    QMatrix4x4 modelViewMat;
    modelViewMat.lookAt(cameraPosition, QVector3D(0, 0, 0), cameraUpDirection);

    QMatrix4x4 unviewMat = (pMatrix * modelViewMat).inverted();

    QVector4D nearPoint = unviewMat * QVector4D(normX, normY, 0, 1);
    QVector4D camera_pos = modelViewMat.inverted().column(3);
    rayOrg = camera_pos.toVector3DAffine();
    rayDir = nearPoint.toVector3DAffine() - rayOrg;
}

void GlWidget::mousePressEvent(QMouseEvent *event)
{
    QVector3D rayOrg;
    QVector3D rayDir;
    getMousePickRay(event->localPos(), rayOrg, rayDir);
    QVector2D texCoords;
    if( cube.intersect(rayOrg, rayDir, texCoords))
    {
        QPointF scenePos(texCoords.x()*widget->width(), texCoords.y()*widget->height());
        QGraphicsSceneMouseEvent mouseEvent(QEvent::GraphicsSceneMousePress);
        mouseEvent.setWidget(this);
        mouseEvent.setButtonDownScenePos(event->button(), scenePos);
//        mouseEvent.setButtonDownScreenPos(event->button(), event->globalPos());
        mouseEvent.setScenePos(scenePos);
//        mouseEvent.setScreenPos(event->globalPos());
        mouseEvent.setLastScenePos(scenePos);
//        mouseEvent.setLastScreenPos(event->globalPos());
        mouseEvent.setButtons(event->buttons());
        mouseEvent.setButton(event->button());
        mouseEvent.setModifiers(event->modifiers());

        mouseEvent.setAccepted(false);

        lastSceneMousePosition = scenePos;
        QApplication::sendEvent( scene, &mouseEvent );
    }
    lastMousePosition = event->pos();

    QGLWidget::mousePressEvent(event);
}

void GlWidget::mouseReleaseEvent(QMouseEvent *event)
{
    QVector3D rayOrg;
    QVector3D rayDir;
    getMousePickRay(event->localPos(), rayOrg, rayDir);
    QVector2D texCoords;
    if( cube.intersect(rayOrg, rayDir, texCoords))
    {
        QPointF scenePos(texCoords.x()*widget->width(), texCoords.y()*widget->height());
        QGraphicsSceneMouseEvent mouseEvent(QEvent::GraphicsSceneMouseRelease);
        mouseEvent.setWidget(this);
        mouseEvent.setScenePos(scenePos);
//        mouseEvent.setScreenPos(event->globalPos());
        mouseEvent.setLastScenePos(scenePos);
//        mouseEvent.setLastScreenPos(event->globalPos());
        mouseEvent.setButtons(event->buttons());
        mouseEvent.setButton(event->button());
        mouseEvent.setModifiers(event->modifiers());
        mouseEvent.setAccepted(false);

        lastSceneMousePosition = scenePos;
        QApplication::sendEvent( scene, &mouseEvent );
    }
    lastMousePosition = event->pos();

    QGLWidget::mouseReleaseEvent(event);
}


void GlWidget::mouseMoveEvent(QMouseEvent *event)
{
    QVector3D rayOrg;
    QVector3D rayDir;
    getMousePickRay(event->localPos(), rayOrg, rayDir);
    QVector2D texCoords;
    if( cube.intersect(rayOrg, rayDir, texCoords))
    {
        QPointF scenePos(texCoords.x()*widget->width(), texCoords.y()*widget->height());
        QGraphicsSceneMouseEvent mouseEvent(QEvent::GraphicsSceneMouseMove);
        mouseEvent.setWidget(this);
        mouseEvent.setScenePos(scenePos);
        //mouseEvent.setScreenPos(event->globalPos());
        mouseEvent.setLastScenePos(scenePos);
        //mouseEvent.setLastScreenPos(event->globalPos());
        mouseEvent.setButtons(event->buttons());
        mouseEvent.setButton(event->button());
        mouseEvent.setModifiers(event->modifiers());
        mouseEvent.setAccepted(false);

        lastSceneMousePosition = scenePos;
        QApplication::sendEvent( scene, &mouseEvent );
        updateTexture(QList<QRectF>());
    }
//    QGLWidget::mouseMoveEvent(event);
//    return;

    int deltaX = event->x() - lastMousePosition.x();
    int deltaY = event->y() - lastMousePosition.y();

    if (event->buttons() & Qt::LeftButton) {
        alpha -= deltaX;
        while (alpha < 0) {
            alpha += 360;
        }
        while (alpha >= 360) {
            alpha -= 360;
        }

        beta -= deltaY;
        if (beta < -90) {
            beta = -90;
        }
        if (beta > 90) {
            beta = 90;
        }

        updateGL();
    }
    lastMousePosition = event->pos();

    event->accept();
}

void GlWidget::wheelEvent(QWheelEvent *event)
{
    int delta = event->delta();

    if (event->orientation() == Qt::Vertical) {
        if (delta < 0) {
            distance *= 1.1;
        } else if (delta > 0) {
            distance *= 0.9;
        }

        updateGL();
    }

    event->accept();
}


