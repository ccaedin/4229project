#include "Sphere.h"

//adapted from https://songho.ca/opengl/gl_sphere.html
Sphere::Sphere(float radius, int numStacks, int numSlices): Mesh()
{
    // loadOBJ("sphere.obj", vertices, uvs, normals);
    this->radius = radius;
    this->numSlices = numSlices;
    this->numStacks = numStacks;
    numVertices = (numStacks + 1) * (numSlices + 1);
    
    float x;
    float y;
    float z;
    float xy;

    float nx;
    float ny;
    float nz;
    float lengthInv = 1.0f / radius;

    float s;
    float t;

    float sectorStep = 2 * M_PI / numSlices;
    float stackStep = M_PI / numStacks;

    for(int i=0; i<= numStacks; i++)
    {
        float stackAngle = M_PI / 2 - i * stackStep;
        xy = radius * cosf(stackAngle);
        z = radius * sinf(stackAngle);

        for(int j=0; j<=numSlices; j++)
        {
            float sectorAngle = j * sectorStep;

            x = xy * cosf(sectorAngle);
            y = xy * sinf(sectorAngle);

            vertices.push_back(glm::vec3(x, y, z));
            nx = x * lengthInv;
            ny = y * lengthInv;
            nz = z * lengthInv;
            normals.push_back(glm::vec3(nx, ny, nz));

            s = (float)j / numSlices;
            t = (float)i / numStacks;
            uvs.push_back(glm::vec2(s, t));
        }
    }

    unsigned int k1, k2;
    for(int i=0; i<numStacks; i++)
    {
        k1 = i * (numSlices + 1);
        k2 = k1 + numSlices + 1;

        for(int j=0; j<numSlices; j++, k1++, k2++)
        {
            if(i != 0)
            {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }

            if(i != (numStacks - 1))
            {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }

        }
    }
    // setupMesh(vertices, uvs, normals);
    this->vertices = vertices;
    this->uvs = uvs;
    this->normals = normals;
    tangents.resize(vertices.size());
    bitangents.resize(vertices.size());
    Sphere::computeTangentBasis(vertices, uvs, normals, tangents, bitangents);
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

    // glBindVertexArray(VAO);
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
}

void Sphere::draw()
{
    //print radius
    glBindVertexArray(VAO);
    setupDraw();
    //set the index buffer
    int temp_offset = 0;
    glDrawElements(GL_TRIANGLES, indices.size()-temp_offset, GL_UNSIGNED_INT, (void*)(temp_offset* sizeof(GLuint)));

    //draw normals tangents and bitangents for debugging
    // glDrawArrays(GL_LINES, 0, vertices.size());
    // glDrawArrays(GL_LINES, 0, vertices.size());
    // glDrawArrays(GL_LINES, 0, vertices.size());
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);
    glDisableVertexAttribArray(4);
    glBindVertexArray(0);

}

void Sphere::computeTangentBasis(
	// inputs
	std::vector<glm::vec3> & vertices,
	std::vector<glm::vec2> & uvs,
	std::vector<glm::vec3> & normals,
	// outputs
	std::vector<glm::vec3> & tangents,
	std::vector<glm::vec3> & bitangents
) {

    unsigned int k1, k2;
    for(int i=0; i<numStacks; i++)
    {
        k1 = i * (numSlices + 1);
        k2 = k1 + numSlices + 1;

        for(int j=0; j<numSlices; j++, k1++, k2++)
        {
            if(i != 0)
            {
                // indices.push_back(k1);
                // indices.push_back(k2);
                // indices.push_back(k1 + 1);
                		// Shortcuts for vertices
                glm::vec3 & v0 = vertices[k1];
                glm::vec3 & v1 = vertices[k2];
                glm::vec3 & v2 = vertices[k1+1];

                // Shortcuts for UVs
                // glm::vec2 & uv0 = uvs[i+0];
                // glm::vec2 & uv1 = uvs[i+1];
                // glm::vec2 & uv2 = uvs[i+2];
                glm::vec2 & uv0 = uvs[k1];
                glm::vec2 & uv1 = uvs[k2];
                glm::vec2 & uv2 = uvs[k1+1];

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
                std::cout << "Tangent: " << tangent.x << " " << tangent.y << " " << tangent.z << std::endl;
                #endif
                // Set the same tangent for all three vertices of the triangle.
                tangents.push_back(tangent);
                tangents.push_back(tangent);
                tangents.push_back(tangent);

                bitangents.push_back(bitangent);
                bitangents.push_back(bitangent);
                bitangents.push_back(bitangent);

            }

            if(i != (numStacks - 1))
            {
                // indices.push_back(k1 + 1);
                // indices.push_back(k2);
                // indices.push_back(k2 + 1);
                glm::vec3 & v0 = vertices[k1+1];
                glm::vec3 & v1 = vertices[k2];
                glm::vec3 & v2 = vertices[k2+1];

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
                float r = 1.0f/(uvDeterminant);
                glm::vec3 tangent = (deltaPos1 * deltaUV2.y   - deltaPos2 * deltaUV1.y)*r;
                glm::vec3 bitangent = (deltaPos2 * deltaUV1.x   - deltaPos1 * deltaUV2.x)*r;
                #ifdef DEBUG
                std::cout << "Tangent: " << tangent.x << " " << tangent.y << " " << tangent.z << std::endl;
                #endif
                // Set the same tangent for all three vertices of the triangle.
                tangents.push_back(tangent);
                tangents.push_back(tangent);
                tangents.push_back(tangent);

                bitangents.push_back(bitangent);
                bitangents.push_back(bitangent);
                bitangents.push_back(bitangent);
            }

        }
    }

	for (unsigned int i=0; i<indices.size(); i+=3 ){

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
		float r = 1.0f/(uvDeterminant);
		glm::vec3 tangent = (deltaPos1 * deltaUV2.y   - deltaPos2 * deltaUV1.y)*r;
		glm::vec3 bitangent = (deltaPos2 * deltaUV1.x   - deltaPos1 * deltaUV2.x)*r;
        #ifdef DEBUG
        std::cout << "Tangent: " << tangent.x << " " << tangent.y << " " << tangent.z << std::endl;
        #endif
		// Set the same tangent for all three vertices of the triangle.
		tangents.push_back(tangent);
		tangents.push_back(tangent);
		tangents.push_back(tangent);

		bitangents.push_back(bitangent);
		bitangents.push_back(bitangent);
		bitangents.push_back(bitangent);



	}

	// See "Going Further"
	// for (unsigned int i=0; i<vertices.size(); i+=1 )
	// {
	// 	glm::vec3 & n = normals[i];
	// 	glm::vec3 & t = tangents[i];
	// 	glm::vec3 & b = bitangents[i];
		
	// 	// Gram-Schmidt orthogonalize
	// 	t = glm::normalize(t - n * glm::dot(n, t));
		
	// 	// Calculate handedness
	// 	if (glm::dot(glm::cross(n, t), b) < 0.0f){
	// 		t = t * -1.0f;
	// 	}

	// }
}
