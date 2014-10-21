# CADMesh for g4py

## How to use

- Copy the contents of this folder to <geant4srcdir>/environments/g4py
- _cd_ to <geant4srcdir>/environments/g4py
- Apply the patch pyCADmesh to source/CMakeLists.txt: 
 	patch -p0 < pyCADMesh.patch
- Create CMake build folder in g4py directory  as usual
- Configure and make:
	cmake .. -DCMAKE_PREFIX_PATH=${PATH_TO_CADMESH_INSTALLATION}
	make
 
This should successfully build g4py with CADMesh extensions.
