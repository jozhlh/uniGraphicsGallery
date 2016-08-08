// Josh Hale - 1402439
// Graphics Programming Coursework Gallery
// Model.cpp
// A class which handles model importing and rendering

#include "model.h"

// loads the model and texture data
bool Model::Load(char* modelFilename, char* textureFilename)
{
	bool result;

	// Load in the model data,
	result = LoadModel(modelFilename);
	if(!result)
	{
		MessageBox(NULL, "Model failed to load", "Error", MB_OK);
		return false;
	}

	// Load the texture for this model.
	texture.LoadTexture(textureFilename);
	
	return true;
}

// renders model to scene using vertex arrays
void Model::Render()
{
	// make sure correct texture is bound
	glBindTexture(GL_TEXTURE_2D, texture.texture);

	// enable vertex array rendering
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	// get model data
	glNormalPointer(GL_FLOAT, 0, normals.data());
	glTexCoordPointer(2, GL_FLOAT, 0, tex_coords.data());
	glVertexPointer(3, GL_FLOAT, 0, vertex.data());

	// draw model
	glDrawArrays(GL_TRIANGLES, 0, (vertex.size() / 3));

	// disable vertex array rendering
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

// loads model in from file
bool Model::LoadModel(char* filename)
{
	std::ifstream fileStream;
    int fileSize = 0;

	// try to open file
    fileStream.open( filename, std::ifstream::in );
   
	// check if file opened
    if( fileStream.is_open() == false )
        return false;

	// check file length
    fileStream.seekg( 0, std::ios::end );
    fileSize = ( int )fileStream.tellg( );
    fileStream.seekg( 0, std::ios::beg );

	// return if file size is 0 or less
    if( fileSize <= 0 )
        return false;

	// create string
    char *buffer = new char[fileSize];

    if( buffer == 0 )
        return false;

    memset( buffer, '\0', fileSize );

	// create token streams
	// these will hold model data
    TokenStream tokenStream, lineStream, faceStream;
    string tempLine, token;

	// read file into buffer then in the tokenStream
    fileStream.read( buffer, fileSize );
    tokenStream.SetTokenStream( buffer );

	// free up memory
    delete[] buffer;

    tokenStream.ResetStream();

	// stores vertex information from model file
	float tempx, tempy, tempz;
    vector<Vector3> verts, norms, texC;
    vector<int> faces;
	
    char lineDelimiters[2] = { '\n', ' ' };

	// while there is still more data
    while( tokenStream.MoveToNextLine( &tempLine ) )
    {
        // get next line of data
		lineStream.SetTokenStream( ( char* )tempLine.c_str( ) );
        tokenStream.GetNextToken( 0, 0, 0 );

		// check we have received the line
        if( !lineStream.GetNextToken( &token, lineDelimiters, 2 ) )
            continue;

		// for vertices
        if( strcmp( token.c_str( ), "v" ) == 0 )
        {
            // push back the vertex data to the vertex array
			lineStream.GetNextToken( &token, lineDelimiters, 2 );
			tempx = (float)atof(token.c_str());

            lineStream.GetNextToken( &token, lineDelimiters, 2 );
			tempy = (float)atof(token.c_str());

            lineStream.GetNextToken( &token, lineDelimiters, 2 );
			tempz = (float)atof(token.c_str());

			verts.push_back(Vector3(tempx, tempy, tempz));
        }
		// for normals
        else if( strcmp( token.c_str( ), "vn" ) == 0 )
        {
            // push back the normal information to the normal array
			lineStream.GetNextToken( &token, lineDelimiters, 2 );
			tempx = (float)atof(token.c_str());

            lineStream.GetNextToken( &token, lineDelimiters, 2 );
			tempy = (float)atof(token.c_str());

            lineStream.GetNextToken( &token, lineDelimiters, 2 );
			tempz = (float)atof(token.c_str());

			norms.push_back(Vector3(tempx, tempy, tempz));
        }
		// for texture coordinates
        else if( strcmp( token.c_str( ), "vt" ) == 0 )
        {
			// push back the texture coord information to the texture coord array
			lineStream.GetNextToken( &token, lineDelimiters, 2 );
			tempx = (float)atof(token.c_str());

            lineStream.GetNextToken( &token, lineDelimiters, 2 );
			tempy = (float)atof(token.c_str());

			texC.push_back(Vector3(tempx, tempy, 0));
        }
		// for face data
        else if( strcmp( token.c_str( ), "f" ) == 0 )
        {
            char faceTokens[3] = { '\n', ' ', '/' };
            std::string faceIndex;

            faceStream.SetTokenStream( ( char* )tempLine.c_str( ) );
            faceStream.GetNextToken( 0, 0, 0 );

            for( int i = 0; i < 3; i++ )
            {
                faceStream.GetNextToken( &faceIndex, faceTokens, 3 );
                faces.push_back( ( int )atoi( faceIndex.c_str( ) ) );

                faceStream.GetNextToken( &faceIndex, faceTokens, 3 );
                faces.push_back( ( int )atoi( faceIndex.c_str( ) ) );

                faceStream.GetNextToken( &faceIndex, faceTokens, 3 );
                faces.push_back( ( int )atoi( faceIndex.c_str( ) ) );
            }
        }
        else if( strcmp( token.c_str( ), "#" ) == 0 )
        {
           // skip
        }

        token[0] = '\0';
    }

    // "Unroll" the loaded obj information into a list of triangles.
	
    int numFaces = ( int )faces.size( ) / 9;
	vertex_count = numFaces * 3;
	
	// model data is stored in stored in vectors verts, norms, texC and faces

	Vector3 temp;

	// loop for number of faces
	for (int i = 0; i < faces.size(); i += 3)
	{
		// use first face value
		// vertex index
		temp = verts.at(faces.at(i) - 1);
		
		// store x, y, z for vertex in another vector
		vertex.push_back(temp.getX());
		vertex.push_back(temp.getY());
		vertex.push_back(temp.getZ());
		
		// use second face value
		// texture Coordinates
		temp = texC.at(faces.at(i + 1) - 1);
		
		// store u, v in tex_coords vector
		tex_coords.push_back(temp.getX());
		tex_coords.push_back(temp.getY());
		tex_coords.push_back(temp.getZ());

		// use third face value
		// normals
		temp = norms.at(faces.at(i + 2) - 1);

		// Store x, y, z in normals vector
		normals.push_back(temp.getX());
		normals.push_back(temp.getY());
		normals.push_back(temp.getZ());
	}
	
	// delete data to free up memory
    verts.clear( );
    norms.clear( );
    texC.clear( );
    faces.clear( );

    return true;
}


