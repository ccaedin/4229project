#include "Sphere.h"

Sphere::Sphere(float radius, int numStacks, int numSlices): Mesh()
{
    this->radius = radius;
    this->numSlices = numSlices;
    this->numStacks = numStacks;
    numVertices = (numStacks + 1) * (numSlices + 1);
    
    const auto numSideStacks = numStacks - 2;
    const auto numSlidePrimitiveRestarts = std::max(0, numSideStacks - 1);
    numSideIndices = 2 * numSideStacks * (numSlices + 1) + numSlidePrimitiveRestarts;

    numPoleIndices = numSlices * 3;

    northPoleOffset = 0;
    sideOffset = numPoleIndices;
    southPoleOffset = sideOffset + numSideIndices;

    numIndices = 2 * numPoleIndices + numSideIndices;

    numPoleIndices = numSlices * 3;
    int primitiveRestartIndex = numVertices;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    

    const auto sliceAngleStep = 2.0f * glm::pi<float>() / numSlices;
    auto currentAngle = 0.0f;
    std::vector<float> sliceSines, sliceCosines;
    for (int i = 0; i <= numSlices; i++)
    {
        sliceSines.push_back(sin(currentAngle));
        sliceCosines.push_back(cos(currentAngle));
        currentAngle += sliceAngleStep;
    }

    const auto stackAngleStep = -glm::pi<float>() / (numStacks);
    currentAngle = glm::pi<float>() / 2.0f;
    std::vector<float> stackSines, stackCosines;
    for (int i = 0; i <= numStacks; i++)
    {
        stackSines.push_back(sin(currentAngle));
        stackCosines.push_back(cos(currentAngle));
        currentAngle += stackAngleStep;
    }

    //positions
    for(int i =0; i<= numStacks; i++)
    {
        for(int j = 0; j<= numSlices; j++)
        {
            const auto baseX = stackCosines[i] * sliceCosines[j];
            const auto baseY = stackSines[i];
            const auto baseZ = stackCosines[i] * sliceSines[j];
            vertices.push_back(glm::vec3(baseX * radius, baseY * radius, baseZ * radius));

            const auto u = 1.0f - static_cast<float>(j) / numSlices;
            const auto v = 1.0f - static_cast<float>(i) / numStacks;
            uvs.push_back(glm::vec2(u, v));

            normals.push_back(glm::vec3(baseX, baseY, baseZ));
        }
    }
    //generate indices north
    for(int i = 0; i <=numSlices; i++)
    {
        GLuint sliceIndex = i;
        GLuint nextSliceIndex = sliceIndex +numSlices + 1;
        indices.push_back(sliceIndex);
        indices.push_back(nextSliceIndex);
        indices.push_back(nextSliceIndex + 1);
    }
    //gen indices side
    GLuint currentVertexIndex = numSlices + 1;
    for(int i =0; i < numSideStacks; i++)
    {
        if(i > 0)
        {
            indices.push_back(primitiveRestartIndex);
        }
        for(int j = 0; j <= numSlices; j++)
        {
            GLuint sliceIndex = currentVertexIndex + j;
            GLuint nextSliceIndex = currentVertexIndex + numSlices + 1 + j;
            indices.push_back(sliceIndex);
            indices.push_back(nextSliceIndex);
        }
        currentVertexIndex += numSlices + 1;
    }

    //gen indices south
    GLuint beforeLastStackIndexOffset = numVertices - 2*(numSlices + 1);
    for(int i=0; i< numSlices; i++)
    {
        GLuint sliceIndex = beforeLastStackIndexOffset + i;
        GLuint nextSliceIndex = sliceIndex + numSlices + 1;
        indices.push_back(sliceIndex);
        indices.push_back(sliceIndex + 1);
        indices.push_back(nextSliceIndex);
    }

    setupMesh(vertices, uvs, normals);

    glBindVertexArray(VAO);
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
}

void Sphere::draw()
{
    setupDraw();

    glBindVertexArray(VAO);
    

    glEnable(GL_PRIMITIVE_RESTART);
    //north always starts at 0
    glDrawElements(GL_TRIANGLES, numPoleIndices, GL_UNSIGNED_INT, 0);

    glDrawElements(GL_TRIANGLE_STRIP, numSideIndices, GL_UNSIGNED_INT, (void*)(sideOffset * sizeof(GLuint)));

    glDrawElements(GL_TRIANGLES, numPoleIndices, GL_UNSIGNED_INT, (void*)(southPoleOffset * sizeof(GLuint)));

    glDisable(GL_PRIMITIVE_RESTART);
}

void Sphere::computeTangentBasis(std::vector<glm::vec3> &vertices, std::vector<glm::vec2> &uvs, std::vector<glm::vec3> &normals, std::vector<glm::vec3> &tangents, std::vector<glm::vec3> &bitangents)
{
    // //call the parent class
    // for (int i=0; i<=numSideVertices; i+=3 ){

    //     // Shortcuts for vertices
    //     glm::vec3 & v0 = vertices[i+0];
    //     glm::vec3 & v1 = vertices[i+1];
    //     glm::vec3 & v2 = vertices[i+2];

    //     // Shortcuts for UVs
    //     glm::vec2 & uv0 = uvs[i+0];
    //     glm::vec2 & uv1 = uvs[i+1];
    //     glm::vec2 & uv2 = uvs[i+2];

    //     // Edges of the triangle : postion delta
    //     glm::vec3 deltaPos1 = v1-v0;
    //     glm::vec3 deltaPos2 = v2-v0;

    //     // UV delta
    //     glm::vec2 deltaUV1 = uv1-uv0;
    //     glm::vec2 deltaUV2 = uv2-uv0;


    //     float uvDeterminant = deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x;
    //     float r = (uvDeterminant);
    //     glm::vec3 tangent = (deltaPos1 * deltaUV2.y   - deltaPos2 * deltaUV1.y)*r;
    //     glm::vec3 bitangent = (deltaPos2 * deltaUV1.x   - deltaPos1 * deltaUV2.x)*r;
    //     std::cout << "Cylinder Tangent: " << tangent.x << " " << tangent.y << " " << tangent.z << std::endl;
    //     // Set the same tangent for all three vertices of the triangle.
    //     tangents.push_back(tangent);
    //     tangents.push_back(tangent);
    //     tangents.push_back(tangent);

    //     bitangents.push_back(bitangent);
    //     bitangents.push_back(bitangent);
    //     bitangents.push_back(bitangent);

    // }
    // glm::vec3 top = vertices[numSideVertices];
    // for(int i =0; i<=numCapVertices/2; i++)
    // {
    //     glm::vec3 & v0 = vertices[numSideVertices + i];
    //     glm::vec3 & v1 = vertices[numSideVertices + i + 1];
    //     glm::vec3 & v2 = top;

    //     // Shortcuts for UVs
    //     glm::vec2 & uv0 = uvs[numSideVertices + i];
    //     glm::vec2 & uv1 = uvs[numSideVertices + i + 1];
    //     glm::vec2 & uv2 = uvs[numSideVertices];

    //     // Edges of the triangle : postion delta
    //     glm::vec3 deltaPos1 = v1-v0;
    //     glm::vec3 deltaPos2 = v2-v0;

    //     // UV delta
    //     glm::vec2 deltaUV1 = uv1-uv0;
    //     glm::vec2 deltaUV2 = uv2-uv0;

    //     float uvDeterminant = deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x;
    //     float r = (uvDeterminant);
    //     glm::vec3 tangent = (deltaPos1 * deltaUV2.y   - deltaPos2 * deltaUV1.y)*r;
    //     glm::vec3 bitangent = (deltaPos2 * deltaUV1.x   - deltaPos1 * deltaUV2.x)*r;

    //     tangents.push_back(tangent);
    //     tangents.push_back(tangent);
    //     tangents.push_back(tangent);

    //     bitangents.push_back(bitangent);
    //     bitangents.push_back(bitangent);
    //     bitangents.push_back(bitangent);
    // }
    // glm::vec3 bottom = vertices[numSideVertices + numCapVertices/2];
    // for(int i =0; i<=numCapVertices/2; i++)
    // {
    //     glm::vec3 & v0 = vertices[numSideVertices + numCapVertices + i];
    //     glm::vec3 & v1 = vertices[numSideVertices + numCapVertices + i + 1];
    //     glm::vec3 & v2 = bottom;

    //     // Shortcuts for UVs
    //     glm::vec2 & uv0 = uvs[numSideVertices + numCapVertices + i];
    //     glm::vec2 & uv1 = uvs[numSideVertices + numCapVertices + i + 1];
    //     glm::vec2 & uv2 = uvs[numSideVertices + numCapVertices];

    //     // Edges of the triangle : postion delta
    //     glm::vec3 deltaPos1 = v1-v0;
    //     glm::vec3 deltaPos2 = v2-v0;

    //     // UV delta
    //     glm::vec2 deltaUV1 = uv1-uv0;
    //     glm::vec2 deltaUV2 = uv2-uv0;

    //     float uvDeterminant = deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x;
    //     float r = (uvDeterminant);
    //     glm::vec3 tangent = (deltaPos1 * deltaUV2.y   - deltaPos2 * deltaUV1.y)*r;
    //     glm::vec3 bitangent = (deltaPos2 * deltaUV1.x   - deltaPos1 * deltaUV2.x)*r;

    //     tangents.push_back(tangent);
    //     tangents.push_back(tangent);
    //     tangents.push_back(tangent);

    //     bitangents.push_back(bitangent);
    //     bitangents.push_back(bitangent);
    //     bitangents.push_back(bitangent);
    // }
}
