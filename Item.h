#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <QOpenGLFunctions_3_3_Core>
#include <fstream>

static float strToFloat(const std::string str)
{
    std::stringstream ss(str);
    float n;
    ss >> n;
    return n;
}

struct VertexElementLayout{
    unsigned int count; //refer to size
    unsigned int type;
    unsigned char normalized;
};
struct VertexBufferLayout{
    std::vector<VertexElementLayout> elements;
    unsigned int stride;

    VertexBufferLayout() : stride(0) {}
    ~VertexBufferLayout() {
        //std::cout << "destroy vertex buffer layout" <<std::endl;
    }

    template<typename> void push(unsigned int count)
    {
        return;
    }
    template<> void push<float>(unsigned int count)
    {
        stride += count * sizeof(float);
        elements.push_back({ count, GL_FLOAT, GL_FALSE});
    }
    template<> void push<unsigned int>(unsigned int count)
    {
        stride += count * sizeof(unsigned int);
        elements.push_back({ count, GL_UNSIGNED_INT, GL_FALSE});
    }
    template<> void push<int>(unsigned int count)
    {
        stride += count * sizeof(int);
        elements.push_back({ count, GL_INT, GL_FALSE});
    }
};

class Item{
public:
    Item() : vertex_position(nullptr), indices(nullptr) {}
    Item(const unsigned int ver_count, const float *vertex_pos,
         const unsigned int ind_count, const unsigned int *indices,
         const VertexBufferLayout &layout) :
        vertexes_count(ver_count), indices_count(ind_count)
    {
        vertex_position = new float[ver_count];
        if(!vertex_position)
        {
            std::cout<<"new vertex_position fail"<<std::endl;
            return;
        }
        for(unsigned int i = 0; i <ver_count; i++)
            vertex_position[i] = vertex_pos[i];

        this->indices = new unsigned int[ind_count];
        if(!this->indices)
        {
            std::cout<<"new indices fail"<<std::endl;
            return;
        }
        for(unsigned int i = 0; i <ind_count; i++)
            this->indices[i] = indices[i];

        for(unsigned int i = 0; i < layout.elements.size(); i++)
        {
            this->layout.elements.push_back(layout.elements[i]);
        }
    }
    Item(const std::string filename, const VertexBufferLayout &layout)
    {
        std::ifstream infile(filename);
        if (!infile.is_open())
            std::cout << "open file error" << std::endl;
        char c = 's';
        std::vector<float> vertexes;
        std::vector<unsigned int> indices;

        std::string line;
        getline(infile, line);
        while (line.find("#vertex") == std::string::npos)
            getline(infile, line);
        if (line.find("#vertex") != std::string::npos)
        {
            while (c != '[')
                infile >> c;
            infile >> c;
            while (c != ']')
            {
                std::string str;
                while (c != ',' && c != ']')
                {
                    str += c;
                    infile >> c;
                }
                float value = strToFloat(str);
                vertexes.push_back(value);
                if (c == ']')
                    break;
                infile >> c;
            }
        }
        getline(infile, line);
        while (line.find("#index") == std::string::npos)
            getline(infile, line);
        if (line.find("#index") != std::string::npos)
        {
            while (c != '[')
                infile >> c;
            infile >> c;
            while (c != ']')
            {
                unsigned int value = 0;
                while (c != ',' && c != ']')
                {
                    value *= 10;
                    value += (c - 48);
                    infile >> c;
                }
                indices.push_back(value);
                if (c == ']')
                    break;
                infile >> c;
            }
        }
        this->vertexes_count=vertexes.size();
        vertex_position=new float[this->vertexes_count];
        for (int i = 0; i < vertexes.size(); i++)
            vertex_position[i]=vertexes[i];
        this->indices_count=indices.size();
        this->indices=new unsigned int[this->indices_count];
        for (int i = 0; i < indices.size(); i++)
            this->indices[i]=indices[i];

        for(unsigned int i = 0; i < layout.elements.size(); i++)
        {
            this->layout.elements.push_back(layout.elements[i]);
        }
    }
    ~Item()
    {
        if(vertex_position)
            delete vertex_position;
        if(indices)
            delete indices;
    }

    void showDetail() const
    {
        for(unsigned int i = 0; i < vertexes_count; i++)
            std::cout<<vertex_position[i]<< " ";
        std::cout<<std::endl;
        for(unsigned int i = 0; i < indices_count; i++)
            std::cout<<indices[i]<< " ";

    }

    unsigned int vertexes_count;
    float *vertex_position;

    unsigned int indices_count;
    unsigned int *indices;

    VertexBufferLayout layout;
};

#endif // ITEM_H
