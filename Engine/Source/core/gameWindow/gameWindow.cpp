
#include "gameWindow.h"
#include "Shader.h"
#include "core/elements/mesh/kubyk_voxel.h"

GLuint VBO, VAO;
Shader* shader;
GLint window;

std::vector<voxel*> VOXELS;


float deltaTime = 0.0f;
float lastFrame = 0.0f;

float cameraSpeed = 0.05f;
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
float yaw = -90.0f;
float pitch = 0.0f;
bool rightMouseButtonPressed = false;
int lastX = 400, lastY = 300;

void addVoxelVec(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl)
{
    voxel* buffer_voxel = new voxel("testCube", pos, rot, scl);
    VOXELS.push_back(buffer_voxel);
}
void addVoxelFloat(float pos[3], float rot[3], float scl[3])
{
    glm::vec3 cpp_pos = glm::vec3(pos[0], pos[1], pos[2]);
    glm::vec3 cpp_rot = glm::vec3(rot[0], rot[1], rot[2]);
    glm::vec3 cpp_scl = glm::vec3(scl[0], scl[1], scl[2]);

    addVoxelVec(cpp_pos, cpp_rot, cpp_scl);
}



void processInput(unsigned char key, int x, int y) {
    glm::vec3 cameraRight = glm::normalize(glm::cross(cameraFront, cameraUp));
    switch (key) {
    case 'w':
        cameraPos += cameraSpeed * cameraFront;
        break;
    case 's':
        cameraPos -= cameraSpeed * cameraFront;
        break;
    case 'a':
        cameraPos -= cameraSpeed * cameraRight;
        break;
    case 'd':
        cameraPos += cameraSpeed * cameraRight;
        break;
    }
    glutPostRedisplay();
}

void mouseButton(int button, int state, int x, int y) {
    if (button == GLUT_RIGHT_BUTTON) {
        if (state == GLUT_DOWN) {
            rightMouseButtonPressed = true;
            lastX = x;
            lastY = y;
        }
        else if (state == GLUT_UP) {
            rightMouseButtonPressed = false;
        }
    }
}

void mouseMove(int x, int y) {
    if (rightMouseButtonPressed) {
        int xoffset = x - lastX;
        int yoffset = lastY - y; // Reversed since y-coordinates go from bottom to top

        float sensitivity = 0.1f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw += xoffset;
        pitch += yoffset;

        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFront = glm::normalize(front);

        lastX = x;
        lastY = y;

        glutPostRedisplay();
    }
}

void setupCube(float size) {
    float vertices[] = {
        // positions         // normals
        -size, -size, size,  0.0f, 0.0f, 1.0f,
         size, -size, size,  0.0f, 0.0f, 1.0f,
         size,  size, size,  0.0f, 0.0f, 1.0f,
         size,  size, size,  0.0f, 0.0f, 1.0f,
        -size,  size, size,  0.0f, 0.0f, 1.0f,
        -size, -size, size,  0.0f, 0.0f, 1.0f,

         size, -size, -size, 0.0f, 0.0f, -1.0f,
        -size, -size, -size, 0.0f, 0.0f, -1.0f,
        -size,  size, -size, 0.0f, 0.0f, -1.0f,
        -size,  size, -size, 0.0f, 0.0f, -1.0f,
         size,  size, -size, 0.0f, 0.0f, -1.0f,
         size, -size, -size, 0.0f, 0.0f, -1.0f,

        -size,  size,  size, -1.0f, 0.0f, 0.0f,
        -size,  size, -size, -1.0f, 0.0f, 0.0f,
        -size, -size, -size, -1.0f, 0.0f, 0.0f,
        -size, -size, -size, -1.0f, 0.0f, 0.0f,
        -size, -size,  size, -1.0f, 0.0f, 0.0f,
        -size,  size,  size, -1.0f, 0.0f, 0.0f,

         size,  size,  size,  1.0f, 0.0f, 0.0f,
         size, -size,  size,  1.0f, 0.0f, 0.0f,
         size, -size, -size,  1.0f, 0.0f, 0.0f,
         size, -size, -size,  1.0f, 0.0f, 0.0f,
         size,  size, -size,  1.0f, 0.0f, 0.0f,
         size,  size,  size,  1.0f, 0.0f, 0.0f,

        -size, -size, -size, 0.0f, -1.0f, 0.0f,
         size, -size, -size, 0.0f, -1.0f, 0.0f,
         size, -size,  size, 0.0f, -1.0f, 0.0f,
         size, -size,  size, 0.0f, -1.0f, 0.0f,
        -size, -size,  size, 0.0f, -1.0f, 0.0f,
        -size, -size, -size, 0.0f, -1.0f, 0.0f,

        -size,  size, -size, 0.0f, 1.0f, 0.0f,
        -size,  size,  size, 0.0f, 1.0f, 0.0f,
         size,  size,  size, 0.0f, 1.0f, 0.0f,
         size,  size,  size, 0.0f, 1.0f, 0.0f,
         size,  size, -size, 0.0f, 1.0f, 0.0f,
        -size,  size, -size, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader->use();

    glutKeyboardFunc(processInput);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);


    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    shader->setMat4("view", view);
    shader->setMat4("projection", projection);

    // Set directional light properties
    shader->setFloat("dirLight.strength", 0.1f);
    shader->setVec3("dirLight.color", glm::vec3(1.0f, 1.0f, 1.0f));
    shader->setVec3("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
    shader->setVec3("dirLight.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
    shader->setVec3("dirLight.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
    shader->setVec3("dirLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    shader->setVec3("viewPos", glm::vec3(0.0f, 0.0f, -3.0f));


    for (size_t i = 0; i < VOXELS.size(); ++i) {

        shader->setMat4("model", VOXELS[i]->model);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        std::cout << i << std::endl;
    }



    glutSwapBuffers();
}


int gameInit(int argc, char** argv, const char* gameName) {

    float pos[3] = { 1.0f, 1.0f, 1.0f };
    addVoxelFloat(pos, pos, pos);
    //addVoxel(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(1920, 1080);
    window = glutCreateWindow(gameName);



    glewInit();
    glEnable(GL_DEPTH_TEST);

    shader = new Shader("Source/core/shaders/vertex_shader.vs", "Source/core/shaders/fragment_shader.fs");

    GLclampf R = 0.2;
    GLclampf G = 0.3;
    GLclampf B = 1;
    GLclampf A = 1;
    glClearColor(R, G, B, A);

    setupCube(0.5);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMainLoop();

    delete shader;
    return 0;
}

void loadAdditionVoxels(std::vector<addVoxel*> nodes)
{
    for (size_t i = 0; i < nodes.size(); ++i) {

        addVoxelFloat(nodes[i]->position, nodes[i]->rotation, nodes[i]->scale);
    }
}



