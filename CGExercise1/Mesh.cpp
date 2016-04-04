#include "Mesh.h"
#include <math.h>

#define PI			3.1415926
#define	COLORNUM		14


float	ColorArr[COLORNUM][3] = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, { 0.0,  0.0, 1.0}, 
								{1.0, 1.0,  0.0}, { 1.0, 0.0, 1.0},{ 0.0, 1.0, 1.0}, 
								 {0.3, 0.3, 0.3}, {0.5, 0.5, 0.5}, { 0.9,  0.9, 0.9},
								{1.0, 0.5,  0.5}, { 0.5, 1.0, 0.5},{ 0.5, 0.5, 1.0},
									{0.0, 0.0, 0.0}, {1.0, 1.0, 1.0}};


void Mesh::CreateCube(float	fSize)
{
	int i;

	numVerts=8;
	pt = new Point3[numVerts];
	pt[0].set(-fSize, fSize, fSize);
	pt[1].set( fSize, fSize, fSize);
	pt[2].set( fSize, fSize, -fSize);
	pt[3].set(-fSize, fSize, -fSize);
	pt[4].set(-fSize, -fSize, fSize);
	pt[5].set( fSize, -fSize, fSize);
	pt[6].set( fSize, -fSize, -fSize);
	pt[7].set(-fSize, -fSize, -fSize);


	numFaces= 6;
	face = new Face[numFaces];

	//Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 5;
	face[0].vert[2].vertIndex = 6;
	face[0].vert[3].vertIndex = 2;
	for(i = 0; i<face[0].nVerts ; i++)
		face[0].vert[i].colorIndex = 0;
	
	//Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 3;
	face[1].vert[2].vertIndex = 7;
	face[1].vert[3].vertIndex = 4;
	for(i = 0; i<face[1].nVerts ; i++)
		face[1].vert[i].colorIndex = 1;

	//top face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 1;
	face[2].vert[2].vertIndex = 2;
	face[2].vert[3].vertIndex = 3;
	for(i = 0; i<face[2].nVerts ; i++)
		face[2].vert[i].colorIndex = 2;

	//bottom face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 7;
	face[3].vert[1].vertIndex = 6;
	face[3].vert[2].vertIndex = 5;
	face[3].vert[3].vertIndex = 4;
	for(i = 0; i<face[3].nVerts ; i++)
		face[3].vert[i].colorIndex = 3;

	//near face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 4;
	face[4].vert[1].vertIndex = 5;
	face[4].vert[2].vertIndex = 1;
	face[4].vert[3].vertIndex = 0;
	for(i = 0; i<face[4].nVerts ; i++)
		face[4].vert[i].colorIndex = 4;

	//Far face
	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 3;
	face[5].vert[1].vertIndex = 2;
	face[5].vert[2].vertIndex = 6;
	face[5].vert[3].vertIndex = 7;
	for(i = 0; i<face[5].nVerts ; i++)
		face[5].vert[i].colorIndex = 5;

}

float Mesh::get_BS_radius()
{
	return this->_bsRadius;
}


void Mesh::CreateTetrahedron()
{
	int i;
	numVerts=4;
	pt = new Point3[numVerts];
	pt[0].set(0, 0, 0);
	pt[1].set(1, 0, 0);
	pt[2].set(0, 1, 0);
	pt[3].set(0, 0, 1);

	numFaces= 4;
	face = new Face[numFaces];

	face[0].nVerts = 3;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 2;
	face[0].vert[2].vertIndex = 3;
	for(i = 0; i<face[0].nVerts ; i++)
		face[0].vert[i].colorIndex = 0;
	

	face[1].nVerts = 3;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;	
	face[1].vert[1].vertIndex = 2;
	face[1].vert[2].vertIndex = 1;
	for(i = 0; i<face[1].nVerts ; i++)
		face[1].vert[i].colorIndex = 1;

	
	face[2].nVerts = 3;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 3;
	face[2].vert[2].vertIndex = 2;
	for(i = 0; i<face[2].nVerts ; i++)
		face[2].vert[i].colorIndex = 2;


	face[3].nVerts = 3;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 1;
	face[3].vert[1].vertIndex = 3;
	face[3].vert[2].vertIndex = 0;
	for(i = 0; i<face[3].nVerts ; i++)
		face[3].vert[i].colorIndex = 3;
}

void Mesh::CreateCuboid(float	fSizeX, float fSizeY, float fSizeZ)
{
	int i;

	numVerts = 8;
	pt = new Point3[numVerts];
	pt[0].set(-fSizeX, fSizeY, fSizeZ);
	pt[1].set(fSizeX, fSizeY, fSizeZ);
	pt[2].set(fSizeX, fSizeY, -fSizeZ);
	pt[3].set(-fSizeX, fSizeY, -fSizeZ);
	pt[4].set(-fSizeX, -fSizeY, fSizeZ);
	pt[5].set(fSizeX, -fSizeY, fSizeZ);
	pt[6].set(fSizeX, -fSizeY, -fSizeZ);
	pt[7].set(-fSizeX, -fSizeY, -fSizeZ);


	numFaces = 6;
	face = new Face[numFaces];

	//Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 5;
	face[0].vert[2].vertIndex = 6;
	face[0].vert[3].vertIndex = 2;
	for (i = 0; i<face[0].nVerts; i++)
		face[0].vert[i].colorIndex = 0;

	//Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 3;
	face[1].vert[2].vertIndex = 7;
	face[1].vert[3].vertIndex = 4;
	for (i = 0; i<face[1].nVerts; i++)
		face[1].vert[i].colorIndex = 1;

	//top face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 1;
	face[2].vert[2].vertIndex = 2;
	face[2].vert[3].vertIndex = 3;
	for (i = 0; i<face[2].nVerts; i++)
		face[2].vert[i].colorIndex = 2;

	//bottom face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 7;
	face[3].vert[1].vertIndex = 6;
	face[3].vert[2].vertIndex = 5;
	face[3].vert[3].vertIndex = 4;
	for (i = 0; i<face[3].nVerts; i++)
		face[3].vert[i].colorIndex = 3;

	//near face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 4;
	face[4].vert[1].vertIndex = 5;
	face[4].vert[2].vertIndex = 1;
	face[4].vert[3].vertIndex = 0;
	for (i = 0; i<face[4].nVerts; i++)
		face[4].vert[i].colorIndex = 4;

	//Far face
	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 3;
	face[5].vert[1].vertIndex = 2;
	face[5].vert[2].vertIndex = 6;
	face[5].vert[3].vertIndex = 7;
	for (i = 0; i<face[5].nVerts; i++)
		face[5].vert[i].colorIndex = 5;

}

void Mesh::CreateCylinder(int nSegment, float fHeight, float fRadius) {
	int i;

	numVerts = nSegment * 2 + 2;
	pt = new Point3[numVerts];
	float phi = 0;
	pt[nSegment * 2].set(0, fHeight / 2, 0);
	pt[nSegment * 2 + 1].set(0, - fHeight / 2, 0);
	for (int i = 0; i < nSegment; i++, phi += 2.0f * PI / nSegment)
	{
		float x, y, z;
		x = fRadius * cos(phi);
		z = fRadius * sin(phi);
		y = fHeight / 2.0f;
		pt[i].set(x, y, z);
		pt[i + nSegment].set(x, -y, z);
	}

	numFaces = (nSegment+1) * 3;
	face = new Face[numFaces];

	for (i = 0; i <= nSegment; i++)
	{
		int t = i;
		//Top face
		face[i].nVerts = 3;
		face[i].vert = new VertexID[face[i].nVerts];
		face[i].vert[0].vertIndex = 2 * nSegment;
		face[i].vert[1].vertIndex = (i) % nSegment;
		face[i].vert[2].vertIndex = (i + 1) % nSegment;
		for (int j = 0; j<face[i].nVerts; j++)
			face[i].vert[j].colorIndex = rand() % NUMCOLORS;
		t = i + nSegment + 1;
		//Top face
		face[t].nVerts = 3;
		face[t].vert = new VertexID[face[t].nVerts];
		face[t].vert[0].vertIndex = 2*nSegment + 1;
		face[t].vert[1].vertIndex = i % nSegment + nSegment;
		face[t].vert[2].vertIndex = (i+1)%nSegment + nSegment;
		for (int j = 0; j<face[i].nVerts; j++)
			face[t].vert[j].colorIndex = rand() % NUMCOLORS;
	}

	for (int i = 0; i < nSegment; i++)
	{
		int t = i;
		t = i + 2 * (nSegment+1);
		//Top face
		face[t].nVerts = 4;
		face[t].vert = new VertexID[face[t].nVerts];
		face[t].vert[0].vertIndex = i;
		face[t].vert[1].vertIndex = (i + 1) % nSegment;
		face[t].vert[2].vertIndex = (i + 1) % nSegment + nSegment;
		face[t].vert[3].vertIndex = i + nSegment;
		for (int j = 0; j < face[i].nVerts; j++)
			face[t].vert[j].colorIndex = rand() % NUMCOLORS;
	}
	
}

void Mesh::CreateSphere(int nSlides, int nStacks, float fRadius) {
	// Create sphere
	if (this->bound_sphere != NULL)
		delete this->bound_sphere;

	bound_sphere = new BoundSphere();
	bound_sphere->radius = fRadius;
	bound_sphere->centre[0] = 0.0f;
	bound_sphere->centre[1] = 0.0f;
	bound_sphere->centre[2] = 0.0f;
	// Set radius for bounding sphere
	this->_bsRadius = fRadius;

	float radius = fRadius;
	int nSlice = nSlides;
	int nStack = nStacks;
	numVerts = nSlice * (nStack + 1);
	numFaces = nSlice * nStack;
	pt = new Point3[numVerts];
	face = new Face[numFaces];
	int i = 0;
	float phir, thetar, x, y, z;
	for (i = 0; i < nSlice; i++) {
		phir = 2 * PI*i / nSlice;
		for (int j = 0; j <= nStack; j++) {
			thetar = PI / 2 - PI*j / nStack;
			x = radius*cos(phir)*cos(thetar);
			y = radius*sin(phir)*cos(thetar);
			z = radius*sin(thetar);
			pt[i*(nStack + 1) + j].set(z, y, x);
		}
	}

	for (i = 0; i < nSlice; i++) {
		for (int j = 0; j < nStack; j++) {
			face[i*nStack + j].nVerts = 4;
			face[i*nStack + j].vert = new VertexID[4];
			face[i*nStack + j].vert[0].vertIndex = i*(nStack + 1) + j + 1;
			face[i*nStack + j].vert[1].vertIndex = i*(nStack + 1) + j;
			face[i*nStack + j].vert[2].vertIndex = (i == nSlice - 1) ? j : (i + 1)*(nStack + 1) + j;
			face[i*nStack + j].vert[3].vertIndex = (i == nSlice - 1) ? j + 1 : (i + 1)*(nStack + 1) + j + 1;
			for (int k = 0; k < face[i*nStack + j].nVerts; k++)
				face[i*nStack + j].vert[k].colorIndex = k%COLORNUM;
		}
	}
}

void Mesh::CreateModel(float d, float R1, float R2, float fHeight) {
	float xO1 = - R1 / (R1 + R2) * d;
	float xO2 = R2 / (R1 + R2) * d;

	float phi = acos((R1 - R2) / d);
	//float phi = PI / 2;
	int N = 10;
	float step1 = (2 * PI - 2 * phi) / N;
	float step2 = (2 * phi) / N;
	numVerts = 2 * 2 * N;
	pt = new Point3[numVerts];
	int t = 0;
	for (float i = phi; i < 2 * PI - phi; i += step1)
	{
		float x = R1 * cos(i) + xO1;
		float z = R1 * sin(i);
		float y = fHeight / 2;
		pt[t++].set(x, y, z);
	}

	for (float i = -phi; i < phi; i+=step2)
	{
		float x = R2 * cos(i) + xO2;
		float z = R2 * sin(i);
		float y = fHeight / 2;
		pt[t++].set(x, y, z);
	}

	for (int i = 0; i < 2 * N; i++)
	{
		pt[t++].set(pt[i].x, -pt[i].y, pt[i].z);
	}

	// Init face
	numFaces = 2 * N + 2;
	face = new Face[numFaces];
	for (int i = 0; i < 2 * N; i++)
	{
		face[i].nVerts = 4;
		face[i].vert = new VertexID[face[i].nVerts];
		face[i].vert[0].vertIndex = i;
		face[i].vert[1].vertIndex = (i + 1) % (2 * N);
		face[i].vert[2].vertIndex = (i + 1) % (2 * N) + 2 * N;
		face[i].vert[3].vertIndex = i + 2 * N;
		for (int j = 0; j < face[i].nVerts; j++)
			face[i].vert[j].colorIndex = rand() % NUMCOLORS;
	}

	for (int i = 0; i < 2 * N; i++)
	{
		face[2 * N].nVerts = 2 * N;
		face[2 * N].vert = new VertexID[face[2 * N].nVerts];

		face[2 * N + 1].nVerts = 2 * N;
		face[2 * N + 1].vert = new VertexID[face[2 * N + 1].nVerts];
		for (int j = 0; j < 2 * N; j++)
		{
			face[2 * N].vert[j].vertIndex = j;
			face[2 * N + 1].vert[j].vertIndex = j + 2 * N;
		}

		for (int k = 0; k < 2 * N; k++)
			face[2 * N].vert[k].colorIndex = rand() % NUMCOLORS;
			//face[(2 * N + 1)].vert[k].colorIndex = rand() % NUMCOLORS;
	}
}

void Mesh::CreateDonut(GLfloat R, GLfloat d) {
	int n = 100;
	GLfloat step = 360.0f / n;
	GLfloat x, y, z;
	GLfloat** arr = new GLfloat*[n];
	int t = 0;
	for (GLfloat i = 0.0f; i < 360.0f; i += step)
	{
		x = d * cos(i * PI / 180) + R + d / 2;
		y = d * sin(i * PI / 180) + R + d / 2;
		z = 0;
		arr[t] = new GLfloat[3];
		arr[t][0] = x;
		arr[t][1] = y;
		arr[t][2] = z;
		t++;
	}
	t = 0;

	numVerts = n * n;
	pt = new Point3[numVerts];
	int m = 0;

	for (GLfloat k = 0.0f; k < 360.0f; k += step)
	{
		for (int j = 0; j < n ; j++) {
			GLfloat* xyz = arr[j];
			GLfloat R1 = xyz[0];
			GLfloat y = xyz[1];
			GLfloat x = R1 * cos(k * PI / 180);
			z = R1 * sin(k * PI / 180);
			pt[m++].set(x, y, z);
		}
	}
	numFaces = n * n;
	face = new Face[numFaces];

	t = 0;
	for (int i = 0; i < n ; i++)
	{
		for (int j = 0; j < n; j++)
		{
			face[t].nVerts = 4;
			face[t].vert = new VertexID[4];
			face[t].vert[0].vertIndex = j + n*i;
			face[t].vert[1].vertIndex = (j + 1) % n +  n*i;
			face[t].vert[2].vertIndex = ((j+1)%n + n*((i + 1)% n));
			face[t].vert[3].vertIndex = j + n * ((i + 1) % n );
			for (int k = 0; k < face[t].nVerts; k++)
				face[t].vert[k].colorIndex = k%COLORNUM;
			t++;
		}
	}
}

void Mesh::DrawWireframe()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;

			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::DrawPoint()
{
	glPointSize(2);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POINT);
		glColor3f(1, 1, 0);
		glVertex3f(pt[f].x, pt[f].y, pt[f].z);
		glEnd();
	}
}

void Mesh::DrawColor()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;
			int		ic = face[f].vert[v].colorIndex;
			
			ic = f % COLORNUM;

			glColor3f(ColorArr[ic][0], ColorArr[ic][1], ColorArr[ic][2]); 
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}



