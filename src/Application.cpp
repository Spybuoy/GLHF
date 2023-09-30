#include<glew\glew.h>
#include<glfw\glfw3.h>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

#include"Renderer.h"
#include"VertexBuffer.h"
#include"VertexBufferLayout.h"
#include"IndexBuffer.h"
#include"VertexArray.h"
#include"Shader.h"
#include"Texture.h"


int main(void)
{

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    //Setting the OpenGL Version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);



    if (glewInit() != GLEW_OK)
        std::cout << "Error!!" << std::endl; // Calling glew once
    std::cout << glGetString(GL_VERSION) << std::endl;

    {

        float positions[] = {
            -0.5f, -0.5f, 0.0f, 0.0f, // 0
            0.5f, -0.5f,  1.0f, 0.0f, // 1
            0.5f, 0.5f,  1.0f, 1.0f, //2
            -0.5f, 0.5f, 0.0f, 1.0f, //3
        };
        unsigned int indices[] = {
            0,1,2,
            2,3,0

        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        

        //unsigned int vao;
        //GLCall(glGenVertexArrays(1, &vao));
        //GLCall(glBindVertexArray(vao));

        VertexArray va;
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));
        
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);
        
        //GLCall(glEnableVertexAttribArray(0));
        //GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));

        IndexBuffer ib(indices, 6);

        //unsigned int ibo; // Index buffer
        //GLCall(glGenBuffers(1, &ibo)); // Need to use unsigned
        //GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
        //GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW));
         // 6 posititons, 2 repeated

        //std::cout << "Vertex" << std::endl;
        //std::cout << source.VertexSource << std::endl;
        //std::cout << "Fragment" << std::endl;
        //std::cout << source.FragmentSource << std::endl;

        Shader shader("resources/shaders/Basic.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.7822f, 0.8353f, 0.7843f, 1.0f);

        //ShaderProgramSource source = ParseShader("resources/shaders/Basic.shader");
        //unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
        //glUseProgram(shader);

        //GLCall(int location = glGetUniformLocation(shader, "u_Color"));
        //ASSERT(location != -1);
        //glUniform4f(location, 0.7822f, 0.8353f, 0.7843f, 1.0f);
        /*GLCall(glBindVertexArray(0));*/

        Texture texture("resources/textures/arm.png");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);


        va.Unbind();
        // GLCall(glUseProgram(0));
        vb.Unbind();
        ib.Unbind();
        shader.Unbind();

        //GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
        //GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

        Renderer renderer;

        float r = 0.0f;
        float increment = 0.05f;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();

            //GLCall(glUseProgram(shader));
            //glUniform4f(location, r, 0.3353f, 0.7843f, 1.0f);
            shader.Bind();
            shader.SetUniform4f("u_Color", r, 0.3353f, 0.7843f, 1.0f);
            renderer.Draw(va, ib, shader);


            // GLCall(glBindVertexArray(vao));
            //va.Bind();
            //ib.Bind();

            // glDrawArrays(GL_TRIANGLES, 0, 6); 

            GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr)); // for idx buffer
            // _ASSERT(GLLogCall());

            if (r > 1.0f)
                increment = -0.05f;
            else if (r < 0.0f)
                increment = 0.05f;

            r += increment;


            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

        // glDeleteProgram(shader);
    }    glfwTerminate();
    return 0;
}