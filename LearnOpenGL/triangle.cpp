//
//  triangle.cpp
//  LearnOpenGL
//
//  Created by Chiang on 2022/7/27.
//

#include "triangle.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void pipeline(){
    //    const char *vertexShaderSource = "#version 330 core\n"
    //        "layout (location = 0) in vec3 aPos;\n"
    //        "void main()\n"
    //        "{\n"
    //        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    //        "}\0";
    //
    //    unsigned int vertexShader;
    //    vertexShader = glCreateShader(GL_VERTEX_SHADER);//创建顶点着色器
    //    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);//将源码附加到着色器对象上
    //    glCompileShader(vertexShader);//编译着色器
    //
    //    int success;
    //    char infoLog[512];
    //    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);//检查是否编译成功
    //    if(!success) {
    //        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);//获取错误日志
    //        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    //    }
    //
    //    const char *fragmentShaderSource = "#version 330 core\n"
    //        "out vec4 FragColor;\n"
    //        "void main()\n"
    //        "{\n"
    //        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    //        "}\n\0";
    //
    //    unsigned int fragmentShader;
    //    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    //    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    //    glCompileShader(fragmentShader);
    //
    //    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    //    if(!success) {
    //        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    //        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    //    }
    //
    //    unsigned int shaderProgram;
    //    shaderProgram = glCreateProgram();//创建一个程序，并返回新创建程序对象的ID引用
    //    glAttachShader(shaderProgram, vertexShader);//顶点着色器附加到程序对象
    //    glAttachShader(shaderProgram, fragmentShader);//片段着色器附加到程序对象
    //    glLinkProgram(shaderProgram);//链接着色器程序
    //
    //    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);//检测链接着色器程序是否失败
    //    if(!success) {
    //        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    //        std::cout << "ERROR::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
    //    }
    //
    //    glUseProgram(shaderProgram);//激活程序
    //    glDeleteShader(vertexShader);//色器对象链接到程序对象以后，删除着色器对象，已经不再需要它们了
    //    glDeleteShader(fragmentShader);
    
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);//创建一个VAO
    glBindVertexArray(VAO);//绑定VAO，从绑定之后起，我们应该绑定和配置对应的VBO和属性指针，之后解绑VAO供之后使用
    
    //绘制三角形
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };
    
    //    //运用EBO绘制矩形
    //    float vertices[] = {
    //        0.5f, 0.5f, 0.0f,   // 右上角
    //        0.5f, -0.5f, 0.0f,  // 右下角
    //        -0.5f, -0.5f, 0.0f, // 左下角
    //        -0.5f, 0.5f, 0.0f   // 左上角
    //    };
    //
    //    unsigned int indices[] = {
    //        // 注意索引从0开始!
    //        // 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
    //        // 这样可以由下标代表顶点组合成矩形
    //
    //        0, 1, 3, // 第一个三角形
    //        1, 2, 3  // 第二个三角形
    //    };
    
    unsigned int VBO;
    glGenBuffers(1, &VBO);//创建VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);//绑定VBO，把新创建的缓冲绑定到GL_ARRAY_BUFFER目标上，从这一刻起，我们使用的任何（在GL_ARRAY_BUFFER目标上的）缓冲调用都会用来配置当前绑定的缓冲(VBO)
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//将顶点数据复制到缓冲的内存中
    
    
    //    unsigned int EBO;
    //    glGenBuffers(1, &EBO);//创建EBO
    //    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);//绑定EBO
    //    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);//复制我们的索引数组到一个索引缓冲中，供OpenGL使用
    
    /* 告诉OpenGL该如何解析顶点数据
     
     第一个参数指定我们要配置的顶点属性。还记得我们在顶点着色器中使用layout(location = 0)定义了position顶点属性的位置值(Location)吗？它可以把顶点属性的位置值设置为0。因为我们希望把数据传递到这一个顶点属性中，所以这里我们传入0。
     第二个参数指定顶点属性的大小。顶点属性是一个vec3，它由3个值组成，所以大小是3。
     第三个参数指定数据的类型，这里是GL_FLOAT(GLSL中vec*都是由浮点数值组成的)。
     第四个参数定义我们是否希望数据被标准化(Normalize)。如果我们设置为GL_TRUE，所有数据都会被映射到0（对于有符号型signed数据是-1）到1之间。我们把它设置为GL_FALSE。
     第五个参数叫做步长(Stride)，它告诉我们在连续的顶点属性组之间的间隔。由于下个组位置数据在3个float之后，我们把步长设置为3 * sizeof(float)。
     最后一个参数的类型是void*，所以需要我们进行这个奇怪的强制类型转换。它表示位置数据在缓冲中起始位置的偏移量(Offset)。由于位置数据在数组的开头，所以这里是0。我们会在后面详细解释这个参数。
     */
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);//以顶点属性位置值作为参数，启用顶点属性；顶点属性默认是禁用的
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}

void draw_now() {
    //1:OpenGL图元的类型,2:指定了顶点数组的起始索引,一般为0，3:指定绘制多少个顶点
    glDrawArrays(GL_TRIANGLES, 0, 3);//使用当前激活的着色器，之前定义的顶点属性配置，和VBO的顶点数据（通过VAO间接绑定）来绘制图元
    //    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);//使用EBO时需要用此函数还进行绘制
}
