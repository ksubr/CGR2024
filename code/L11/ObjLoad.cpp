#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "image.h"


// Simple 3D vector to store vertex positions and normals
struct Vec3 {
    float x, y, z;
};

// Simple 2D vector to store texture coordinates
struct Vec2 {
    float u, v;
};

// Function to load an OBJ file
bool loadOBJ(const std::string& path, 
             std::vector<Vec3>& outVertices,
             std::vector<Vec2>& outTexCoords,
             std::vector<Vec3>& outNormals) {

    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open OBJ file: " << path << std::endl;
        return false;
    }

    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<Vec3> tempVertices;
    std::vector<Vec2> tempTexCoords;
    std::vector<Vec3> tempNormals;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream lineStream(line);
        std::string prefix;
        lineStream >> prefix;

        if (prefix == "v") {
            Vec3 vertex;
            lineStream >> vertex.x >> vertex.y >> vertex.z;
            tempVertices.push_back(vertex);
        } else if (prefix == "vt") {
            Vec2 texCoord;
            lineStream >> texCoord.u >> texCoord.v;
            tempTexCoords.push_back(texCoord);
        } else if (prefix == "vn") {
            Vec3 normal;
            lineStream >> normal.x >> normal.y >> normal.z;
            tempNormals.push_back(normal);
        } else if (prefix == "f") {
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            char slash;  // To handle '/' characters in face definitions

            for (int i = 0; i < 3; i++) {
                lineStream >> vertexIndex[i] >> slash >> uvIndex[i] >> slash >> normalIndex[i];
                vertexIndices.push_back(vertexIndex[i]);
                uvIndices.push_back(uvIndex[i]);
                normalIndices.push_back(normalIndex[i]);
            }
        }
    }

    // Populate the output vectors
    for (unsigned int i = 0; i < vertexIndices.size(); i++) {
        outVertices.push_back(tempVertices[vertexIndices[i] - 1]);
        outTexCoords.push_back(tempTexCoords[uvIndices[i] - 1]);
        outNormals.push_back(tempNormals[normalIndices[i] - 1]);
    }

    file.close();
    return true;
}

int main() {
    std::vector<Vec3> vertices;
    std::vector<Vec2> texCoords;
    std::vector<Vec3> normals;

    std::string objFilePath = "suzsubdiv2.obj";
    if (loadOBJ(objFilePath, vertices, texCoords, normals)) {
        std::cout << "OBJ file loaded successfully!" << std::endl;
        std::cout << "Number of vertices: " << vertices.size() << std::endl;
    } else {
        std::cerr << "Failed to load OBJ file." << std::endl;
    }

    // Create a 100x100 image with a white background
    const int Rx(512), Ry(512);
    Image img(Rx, Ry);

    double scale(.25);

    for (int i = 0; i < vertices.size(); ++i){
        int xi=scale*(Rx*vertices[i].x)  + Rx/2 ;
        int yi=scale*(-Ry*vertices[i].y) + Ry/2 ;
        img.setPixel(xi,yi, 0, 0, 0); 
    }
    

    // Write the image to a file
    if (img.writePPM("output.ppm")) {
        std::cout << "Image saved as output.ppm" << std::endl;
    } else {
        std::cerr << "Failed to save image." << std::endl;
    }



    return 0;
}
