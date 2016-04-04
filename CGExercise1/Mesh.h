#if !defined (_MESH_CLASS)
#define _MESH_CLASS

#include "supportClass.h"


class VertexID
{
public:
	int		vertIndex;
	int		colorIndex;
};

class Face
{
public:
	int		nVerts;
	VertexID*	vert;
	
	Face()
	{
		nVerts	= 0;
		vert	= NULL;
	}
	~Face()
	{
		if(vert !=NULL)
		{
			delete[] vert;
			vert = NULL;
		}
		nVerts = 0;
	}
};

typedef struct {
	float radius;
	float centre[3];
} BoundSphere;

class Mesh
{
private:
	BoundSphere* bound_sphere = NULL;

	float _bsRadius = 0.0f;
public:
	int			numVerts;
	Point3*		pt;
	
	int			numFaces;
	Face*		face;
	Point3*		position;


public:
	Mesh()
	{
		numVerts	= 0;
		pt		= NULL;
		numFaces	= 0;
		face		= NULL;
		position = new Point3(0, 0, 0);
	}
	~Mesh()
	{
		if (pt != NULL)
		{
			delete[] pt;
		}	
		if(face != NULL)
		{
			delete[] face;
		}
		numVerts = 0;
		numFaces = 0;

		if (this->position != NULL)
			delete position;
	}
	void CreateModel(float d, float R1, float R2, float fHeight);
	void CreateDonut(GLfloat R, GLfloat d);
	void DrawWireframe();
	void DrawPoint();
	void DrawColor();

	void CreateTetrahedron();
	void CreateCuboid(float fSizeX, float fSizeY, float fSizeZ);
	void CreateCylinder(int nSegment, float fHeight, float fRadius);
	void CreateSphere(int nSlides, int nStacks, float fRadius);
	void CreateCube(float	fSize);

	BoundSphere* getBoundingSphere() {
		return bound_sphere;
	}

	float get_BS_radius();
};

#endif