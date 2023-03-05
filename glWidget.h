#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLTexture>
#include <QTimer>
#include <QKeyEvent>
#include <vector>
#include "Item.h"

struct ShaderSourceString
{
    std::string vertex_source;
    std::string fragment_source;
};
class Camera{
public:
    float x;
    float y;
    float z;

    float direct_x;
    float direct_y;
    float direct_z;

    Camera() : x(0.0f), y(0.0f), z(3.0f), direct_x(0.0f), direct_y(0.0f), direct_z(-1.0f) {}
};

class glWidget : public QOpenGLWidget, QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    glWidget(QWidget *parent = nullptr);
    ~glWidget();
protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;

    unsigned int CreateShaderProgram(
            const std::string &vertex_shader_source,
            const std::string &fragment_shader_source);
    unsigned int CompileShader(unsigned int type, const std::string &shader_source);
    ShaderSourceString PraseShaderSource(const std::string &file);

    //data: vertex data array, size: the size of data array
    void SetVertexBuffer(const void *data, unsigned int size);

    //data: index data array, count: the number of data in the array
    void SetIndexBuffer(const unsigned int *data, unsigned int count);

    void BindVertexBuffer(unsigned int i);
    void BindIndexBuffer(unsigned int i);
    void UnbindVertexBuffer();
    void UnbindIndexBuffer();

    void SetVertexBufferLayout(VertexBufferLayout vblayout);


public slots:
    void repaint();

    void drewItem(const Item &item);

    void stopTimer();
    void startTimer();
    void keyPressEvent(QKeyEvent *event) override;

signals:
    void camera_Coordinate_Changed(char msg);
private:
    QTimer *timer;
    unsigned int program;
    std::vector<unsigned int> vao;
    std::vector<unsigned int> vbo; //vertex buffer id
    std::vector<unsigned int> ibo; //index buffer id

    std::vector<QOpenGLTexture*> texture;

public:
    Camera cam;
};


#endif // GLWIDGET_H
