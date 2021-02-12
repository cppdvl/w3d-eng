
//First STL
#include <string>
#include <sstream>

//Then 3rd
#include <spdlog/spdlog.h>

//Then Engine's
#include <dge/dge.h>
#include <dge/dge_primitive/dge_primitive.h>
#include <dge/dge_shader/dge_shader.h>


unsigned int triangleVBO;
unsigned int triangleVAO;
unsigned int shaderProgram;

void init(){

    auto tri = DGE::Primitive::Triangle {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };
    tri.LogInfo();
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    float colors[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f
    };


    auto vertexShaderSource = std::string{
        R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        void main()
        {
            gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
        })"
    };
    auto vertexShaderSource_cstr = vertexShaderSource.c_str();

    auto fragmentShaderSource = std::string {
        R"(
        #version 330 core
        out vec4 FragColor;
        void main()
        {
            FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
        })"
    };
    auto fragmentShaderSource_cstr = fragmentShaderSource.c_str();

    auto shader = DGE::Shader(vertexShaderSource, fragmentShaderSource);
    
    auto vertexShader = glCreateShader(GL_VERTEX_SHADER);

    auto fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource_cstr, nullptr);
    glCompileShader(vertexShader);

    glShaderSource(fragmentShader, 1, &fragmentShaderSource_cstr, NULL);
    glCompileShader(fragmentShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success){
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        auto ss = std::stringstream{};
        ss << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n\n\t" << infoLog;
        spdlog::critical("{:s}:{:d} => {:s}",__FILE__, __LINE__, ss.str());
    }    

    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        auto ss = std::stringstream{};
        ss << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n\n\t" << infoLog;
        spdlog::critical("{:s}:{:d} => {:s}",__FILE__, __LINE__, ss.str());        
    }

    // link shaders
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        auto ss = std::stringstream{};
        ss << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n\n\t" << infoLog;
        spdlog::critical("{:s}:{:d} => {:s}",__FILE__, __LINE__, ss.str());        
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    

    glGenVertexArrays(1, &triangleVAO);
    glGenBuffers(1, &triangleVBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(triangleVAO);

    glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);     
    return;
}
void draw(){

    glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shaderProgram);
    glBindVertexArray(triangleVAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawArrays(GL_TRIANGLES, 0, 3);

    return;

}

void finish(){
    glDeleteVertexArrays(1, &triangleVAO);
    glDeleteBuffers(1, &triangleVBO);
    glDeleteProgram(shaderProgram);
    return;
}

int main(){

    auto e = DGE::Engine::sGetInstance();
    e.Start();

    auto s = DGE::Scene{};
    s.mfInit = init;
    s.mfRender = draw;
    s.mfFinish = finish;
    e.PushScene(&s);


    e.Run();


    e.ShutDown();
    return 0;

}
