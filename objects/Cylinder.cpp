#include "Cylinder.h"

Cylinder::Cylinder(float len, float wid): Mesh()
{

    int slizeSize = 30;
    int numSlices = 360 / slizeSize;
    float high = len;
    float radius = wid;

    std::vector<float> sines, cosines;
    for(int th = 0; th <= 360; th += slizeSize)
    {
        sines.push_back(Sin(th));
        cosines.push_back(Cos(th));
    }

    //calculate the position
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> positions;

    for(int i = 0; i <= numSlices; i++)
    {
        positions.push_back(glm::vec2(radius * cosines[i], radius * sines[i]));
    }

    //side vertices
    for(int i = 0; i <= numSlices; i++)
    {
        glm::vec3 top = glm::vec3(positions[i].x, high, positions[i].y);
        glm::vec3 bottom = glm::vec3(positions[i].x, 0, positions[i].y);
        vertices.push_back(top);
        vertices.push_back(bottom);
    }

        glm::vec3 top = glm::vec3(0, high, 0);
        vertices.push_back(top);
        for(int i = 0; i <= numSlices; i++)
        {
            vertices.push_back(glm::vec3(positions[i].x, high, positions[i].y));
        }

        glm::vec3 bottom = glm::vec3(0, 0, 0);
        vertices.push_back(bottom);

        for(int i = 0; i <= numSlices; i++)
        {
            vertices.push_back(glm::vec3(positions[i].x, 0, positions[i].y));
        }

    //texture coords
    std::vector<glm::vec2> uvs;
    float reps = 3;
    float uvSliceStep = reps / numSlices;

    float currentUVCoord = 0;

    for(int i = 0; i <= numSlices; i++)
    {
        uvs.push_back(glm::vec2(currentUVCoord, 1));
        uvs.push_back(glm::vec2(currentUVCoord, 0));
        currentUVCoord += uvSliceStep;
    }

    uvs.push_back(glm::vec2(0.5, 0.5));
    for(int i = 0; i <= numSlices; i++)
    {
        uvs.push_back(glm::vec2(0.5 + sines[i] * 0.5, 0.5 + cosines[i] * 0.5));
    }
    uvs.push_back(glm::vec2(0.5, 0.5));
    for(int i = 0; i <= numSlices; i++)
    {
        uvs.push_back(glm::vec2(0.5 + sines[i] * 0.5, 0.5 - cosines[i] * 0.5));
    }

    //normals
    std::vector<glm::vec3> normals;
    for(int i = 0; i <= numSlices; i++)
    {
        normals.push_back(glm::vec3(cosines[i], 0, sines[i]));
    }

    for(int i = 0; i <= numSlices; i++)
    {
        normals.push_back(glm::vec3(0, 1, 0));
    }
    for(int i = 0; i <= numSlices; i++)
    {
        normals.push_back(glm::vec3(0, -1, 0));
    }
    
    numSideVertices = (numSlices+1) * 2;
    numCapVertices = numSlices + 2;
    numVertices = numSideVertices + numCapVertices*2;

    // setupMesh(vertices, uvs, normals);
        this->vertices = vertices;
    this->uvs = uvs;
    this->normals = normals;
    computeTangentBasis(vertices, uvs, normals, tangents, bitangents);
    std::vector<unsigned short> indices;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &uvBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

    glGenBuffers(1, &normalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);

    glGenBuffers(1, &tangentBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, tangentBuffer);
    glBufferData(GL_ARRAY_BUFFER, tangents.size() * sizeof(glm::vec3), &tangents[0], GL_STATIC_DRAW);

    glGenBuffers(1, &bitangentBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, bitangentBuffer);
    glBufferData(GL_ARRAY_BUFFER, bitangents.size() * sizeof(glm::vec3), &bitangents[0], GL_STATIC_DRAW);
}
void Cylinder::computeTangentBasis(
	// inputs
	std::vector<glm::vec3> & vertices,
	std::vector<glm::vec2> & uvs,
	std::vector<glm::vec3> & normals,
	// outputs
	std::vector<glm::vec3> & tangents,
	std::vector<glm::vec3> & bitangents
) {
    //depending on the vertices we will have to change because triangle fan reuses vertices
	for (int i=0; i<=numSideVertices; i+=3 ){

		// Shortcuts for vertices
		glm::vec3 & v0 = vertices[i+0];
		glm::vec3 & v1 = vertices[i+1];
		glm::vec3 & v2 = vertices[i+2];

		// Shortcuts for UVs
		glm::vec2 & uv0 = uvs[i+0];
		glm::vec2 & uv1 = uvs[i+1];
		glm::vec2 & uv2 = uvs[i+2];

		// Edges of the triangle : postion delta
		glm::vec3 deltaPos1 = v1-v0;
		glm::vec3 deltaPos2 = v2-v0;

		// UV delta
		glm::vec2 deltaUV1 = uv1-uv0;
		glm::vec2 deltaUV2 = uv2-uv0;


        float uvDeterminant = deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x;
		float r = (uvDeterminant);
		glm::vec3 tangent = (deltaPos1 * deltaUV2.y   - deltaPos2 * deltaUV1.y)*r;
		glm::vec3 bitangent = (deltaPos2 * deltaUV1.x   - deltaPos1 * deltaUV2.x)*r;
        #ifdef DEBUG
        std::cout << "Cylinder Tangent: " << tangent.x << " " << tangent.y << " " << tangent.z << std::endl;
		#endif
        // Set the same tangent for all three vertices of the triangle.
		tangents.push_back(tangent);
		tangents.push_back(tangent);
		tangents.push_back(tangent);

		bitangents.push_back(bitangent);
		bitangents.push_back(bitangent);
		bitangents.push_back(bitangent);

	}
    glm::vec3 top = vertices[numSideVertices];
    for(int i =0; i<=numCapVertices/2; i++)
    {
        glm::vec3 & v0 = vertices[numSideVertices + i];
        glm::vec3 & v1 = vertices[numSideVertices + i + 1];
        glm::vec3 & v2 = top;

        // Shortcuts for UVs
        glm::vec2 & uv0 = uvs[numSideVertices + i];
        glm::vec2 & uv1 = uvs[numSideVertices + i + 1];
        glm::vec2 & uv2 = uvs[numSideVertices];

        // Edges of the triangle : postion delta
        glm::vec3 deltaPos1 = v1-v0;
        glm::vec3 deltaPos2 = v2-v0;

        // UV delta
        glm::vec2 deltaUV1 = uv1-uv0;
        glm::vec2 deltaUV2 = uv2-uv0;

        float uvDeterminant = deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x;
        float r = (uvDeterminant);
        glm::vec3 tangent = (deltaPos1 * deltaUV2.y   - deltaPos2 * deltaUV1.y)*r;
        glm::vec3 bitangent = (deltaPos2 * deltaUV1.x   - deltaPos1 * deltaUV2.x)*r;

        tangents.push_back(tangent);
        tangents.push_back(tangent);
        tangents.push_back(tangent);

        bitangents.push_back(bitangent);
        bitangents.push_back(bitangent);
        bitangents.push_back(bitangent);
    }
    glm::vec3 bottom = vertices[numSideVertices + numCapVertices/2];
    for(int i =0; i<=numCapVertices/2; i++)
    {
        glm::vec3 & v0 = vertices[numSideVertices + numCapVertices + i];
        glm::vec3 & v1 = vertices[numSideVertices + numCapVertices + i + 1];
        glm::vec3 & v2 = bottom;

        // Shortcuts for UVs
        glm::vec2 & uv0 = uvs[numSideVertices + numCapVertices + i];
        glm::vec2 & uv1 = uvs[numSideVertices + numCapVertices + i + 1];
        glm::vec2 & uv2 = uvs[numSideVertices + numCapVertices];

        // Edges of the triangle : postion delta
        glm::vec3 deltaPos1 = v1-v0;
        glm::vec3 deltaPos2 = v2-v0;

        // UV delta
        glm::vec2 deltaUV1 = uv1-uv0;
        glm::vec2 deltaUV2 = uv2-uv0;

        float uvDeterminant = deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x;
        float r = (uvDeterminant);
        glm::vec3 tangent = (deltaPos1 * deltaUV2.y   - deltaPos2 * deltaUV1.y)*r;
        glm::vec3 bitangent = (deltaPos2 * deltaUV1.x   - deltaPos1 * deltaUV2.x)*r;

        tangents.push_back(tangent);
        tangents.push_back(tangent);
        tangents.push_back(tangent);

        bitangents.push_back(bitangent);
        bitangents.push_back(bitangent);
        bitangents.push_back(bitangent);
    }
}
void Cylinder::draw() {
    glBindVertexArray(VAO);
    setupDraw();

    glDrawArrays(GL_TRIANGLE_STRIP, 0, numSideVertices);

    glDrawArrays(GL_TRIANGLE_FAN, numSideVertices, numCapVertices);

    glDrawArrays(GL_TRIANGLE_FAN, numSideVertices + numCapVertices, numCapVertices);
    

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);
    glDisableVertexAttribArray(4);
    glBindVertexArray(0);
}