#include "glWidget.h"
#include <iostream>
#include <fstream>
#include <string>
#include <QMatrix4x4>
#include <QTime>

ShaderSourceString glWidget::PraseShaderSource(const std::string &file)
{
    std::ifstream source(file);
    if(!source.is_open())
    {
        std::cout<<"the given file path maybe wrong"<<std::endl;
        return {};
    }

    std::string vertex_source;
    std::string fragment_source;
    int type = -1; //specifies the shader mode
    std::string line;
    while(getline(source, line))
    {
        if(line.find("#shader") != std::string::npos) //need to prase
        {
            if(line.find("vertex")!= std::string::npos)
                type = 0;
            else if(line.find("fragment") != std::string::npos)
                type = 1;
        }
        else{ //start prase
            if(type == 0) //vertex mode
            {
                vertex_source += line;
                vertex_source += "\n";
            }
            else if(type == 1) //fragment mode
            {
                fragment_source += line;
                fragment_source += "\n";
            }
        }
    }
    return {vertex_source, fragment_source};
}
unsigned int glWidget::CompileShader(unsigned int type, const std::string &shader_source)
{
    unsigned int shader;
    //before create shader, we need to check if the type given is right
    if(type != GL_VERTEX_SHADER && type != GL_FRAGMENT_SHADER)
    {
        std::cout<<"give the wrong type of shader"<<std::endl;
        return 0;
    }

    shader = glCreateShader(type);
    const char* c_src = shader_source.c_str();
    glShaderSource(shader, 1, &c_src, NULL);
    glCompileShader(shader);

    //check if compiling successfully
    int res;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &res);
    if(res == GL_FALSE)
    {
        int len;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
        char *info=new char(len);
        glGetShaderInfoLog(shader, len, &len, info);
        std::cout<<info<<std::endl;
        delete info;
    }
    return shader;
}
unsigned int glWidget::CreateShaderProgram(
    const std::string &vertex_shader_source, const std::string &fragment_shader_source)
{
    unsigned int program = glCreateProgram();
    unsigned int vertex_shader = CompileShader(GL_VERTEX_SHADER, vertex_shader_source);
    unsigned int fragment_shader = CompileShader(GL_FRAGMENT_SHADER, fragment_shader_source);

    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program); //link the two shader together
    glValidateProgram(program); //validate the program

    glDeleteShader(vertex_shader); //now we don't need the shader object
    glDeleteShader(fragment_shader);

    return program;
}

glWidget::glWidget(QWidget *parent) : QOpenGLWidget(parent), vbo(), ibo()
{
    timer = new QTimer(this);
    timer->setInterval(100);
    connect(timer, SIGNAL(timeout()), this, SLOT(repaint()));
    timer->start();

    setFocusPolicy(Qt::StrongFocus);
}

glWidget::~glWidget()
{

}

static QMatrix4x4 mat;
static QMatrix4x4 spin;
void glWidget::repaint()
{
    spin.rotate(-6.0f, 0.0f, 0.0f, 1.0f);
    mat.rotate(-5.0f, 0.0f, 1.0f, 0.0f);
    update(); //we need to call update to repaint GL rather than call paintGL
}



//static QOpenGLTexture *texture2;

void glWidget::initializeGL()
{
    initializeOpenGLFunctions();

    float vertex_position[16] = {
        -0.5f, -0.5f, 0.0f, 0.0f,
         0.5f, -0.5f, 1.0f, 0.0f,
         0.5f,  0.5f, 1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 1.0f
    };
    unsigned int indices[6] = { //index buffer
        0, 1, 2,
        2, 3, 0
    };

    float vertex_position2[20] = {
        -0.4, -0.4, 0.71, 0.0, 0.0,
        0.4, -0.4, 0.71, 1.0, 0.0,
        0.4, 0.4, 0.71, 1.0, 1.0,
        -0.4, 0.4, 0.71, 0.0, 1.0
    };
    unsigned int indices2[6] = {
        0, 1, 2,
        2, 3, 0
    };

    float vertex_position3[20] = {
        -0.7, -0.7, 0.7, 0.0, 0.0,
        0.7, -0.7, 0.7, 1.0, 0.0,
        0.7, 0.7, 0.7, 1.0, 1.0,
        -0.7, 0.7, 0.7, 0.0, 1.0
    };


    VertexBufferLayout vblayout1;
    vblayout1.push<float>(2); //position 2D
    vblayout1.push<float>(2); //texture coordinate 2D

    VertexBufferLayout vblayout2;
    vblayout2.push<float>(3); //position 2D
    vblayout2.push<float>(2); //texture coordinate 2D

    //cube
    Item box("./resource/items/box.item", vblayout2);
    SetVertexBuffer(box.vertex_position, box.vertexes_count * sizeof(float));
    SetIndexBuffer(box.indices, box.indices_count);
    SetVertexBufferLayout(vblayout2);

    //clock dial
    SetVertexBuffer(vertex_position3, 4 * 5 * sizeof(float));
    SetIndexBuffer(indices, 6);
    SetVertexBufferLayout(vblayout2);
    //clock pointer
    SetVertexBuffer(vertex_position2, 4 * 5 * sizeof(float));
    SetIndexBuffer(indices2, 6);
    SetVertexBufferLayout(vblayout2);

    //use blending
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    QOpenGLTexture *t = new QOpenGLTexture(QImage("./resource/textures/2.png").mirrored());
    texture.push_back(t);
    t = new QOpenGLTexture(QImage("./resource/textures/5_2.png").mirrored());
    texture.push_back(t);
    t = new QOpenGLTexture(QImage("./resource/textures/6.png").mirrored());
    texture.push_back(t);

    ShaderSourceString ss = PraseShaderSource("./resource/shader/base.shader");

    program = CreateShaderProgram(ss.vertex_source, ss.fragment_source);
    glUseProgram(program);

    int location = glGetUniformLocation(program, "texture_1");
    glUniform1i(location, 0);  //we use texture channel 1

    QMatrix4x4 projection;
    projection.perspective(45, (float)width()/height(), 0.1, 100);
    glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, projection.constData());
}


void glWidget::paintGL()
{
    QMatrix4x4 view;
    view.lookAt(QVector3D(cam.x, cam.y, cam.z),
                QVector3D(cam.x + cam.direct_x, cam.y + cam.direct_y, cam.z + cam.direct_z),
                QVector3D(0.0f, 1.0f, 0.0f));

    glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, mat.constData());
    glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, view.constData());

    glClearColor(174.0/255.0, 219.0/255.0, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    //we need to bind texture in paintGL()
    //cube
    BindVertexBuffer(0);
    BindIndexBuffer(0);
    texture[2]->bind(0);
    glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_INT, NULL);

    //clock dial
    BindVertexBuffer(1);
    BindIndexBuffer(1);
    texture[1]->bind(0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

    //clock pointer
    QMatrix4x4 m=mat*spin; //spin is independent of revolution, so these two matrices need to be computered independently
    glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, m.constData());
    BindVertexBuffer(2);
    BindIndexBuffer(2);
    texture[0]->bind(0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

//    glUniformMatrix4fv(location, 1, GL_FALSE, mat.constData());


}

void glWidget::resizeGL(int width, int height)
{

}

void glWidget::SetVertexBuffer(const void *data, unsigned int size)
{
    unsigned int _vao;
    unsigned int _vbo;
    glGenVertexArrays(1,&_vao);
    glBindVertexArray(_vao);
    glGenBuffers(1, &_vbo); //get a buffer
    glBindBuffer(GL_ARRAY_BUFFER, _vbo); //bind
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW); //fill the buffer with our data

    vao.push_back(_vao);
    vbo.push_back(_vbo);
}
void glWidget::SetIndexBuffer(const unsigned int *data, unsigned int count)
{
    unsigned int _ibo;
    glGenBuffers(1, &_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);

    ibo.push_back(_ibo);
}
void glWidget::BindVertexBuffer(unsigned int i)
{
    glBindVertexArray(vao[i]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);
}
void glWidget::BindIndexBuffer(unsigned int i)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo[i]);
}
void glWidget::UnbindVertexBuffer()
{
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void glWidget::UnbindIndexBuffer()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void glWidget::SetVertexBufferLayout(VertexBufferLayout vblayout)
{
    unsigned int offset = 0;
    std::vector<VertexElementLayout> elements = vblayout.elements;
    for(unsigned int i = 0; i < elements.size(); i++)
    {
        //don't forget to call enable before set vertex attribute pointer
        glEnableVertexAttribArray(i);
        //tell the structure of the given data
        glVertexAttribPointer(i, elements[i].count, elements[i].type,
            elements[i].normalized, vblayout.stride, (const void*)(offset * sizeof(float)));
        offset += elements[i].count;
    }
}


void glWidget::drewItem(const Item &item)
{
    //you must call makecurrent() and donecurrent() when you need to use opengl functions outside
    //the three functions: initializeGL(), paintGL() and resizeGL()
    //or what you've done can be meaningless
    makeCurrent();
    SetVertexBuffer(item.vertex_position, item.vertexes_count * sizeof(float));
    SetIndexBuffer(item.indices, item.indices_count);
    SetVertexBufferLayout(item.layout);
    doneCurrent();
    update();
}

void glWidget::stopTimer()
{
    timer->stop();
}
void glWidget::startTimer()
{
    timer->start();
}

void glWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_W)
    {
        cam.y+=0.1;
        emit camera_Coordinate_Changed('y');
    }
    else if(event->key() == Qt::Key_S)
    {
        cam.y-=0.1;
        emit camera_Coordinate_Changed('y');
    }
    else if(event->key() == Qt::Key_A)
    {
        cam.x-=0.1;
        emit camera_Coordinate_Changed('x');
    }
    else if(event->key() == Qt::Key_D)
    {
        cam.x+=0.1;
        emit camera_Coordinate_Changed('x');
    }
    else if(event->key() == Qt::Key_BracketLeft)
    {
        cam.z-=0.1;
        emit camera_Coordinate_Changed('z');
    }
    else if(event->key() == Qt::Key_BracketRight)
    {
        cam.z+=0.1;
        emit camera_Coordinate_Changed('z');
    }
    else if(event->key() == Qt::Key_Up)
    {
        cam.direct_y+=0.1;
    }
    else if(event->key() == Qt::Key_Down)
    {
        cam.direct_y-=0.1;
    }
    else if(event->key() == Qt::Key_Right)
    {
        cam.direct_x+=0.1;
    }
    else if(event->key() == Qt::Key_Left)
    {
        cam.direct_x-=0.1;
    }
    else
        return;

    std::cout<<"coordinate changed"<<std::endl;
    update();
}
