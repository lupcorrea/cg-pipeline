# Computer Graphics Pipeline

### Brief Description and Credits
This is the source code used for the experiment described [here](https://tindied.wordpress.com/2016/10/20/from-vertex-to-pixel-an-evolutionary-tale). The experiment itself was based on an assignment for my Computer Graphics course, at the Federal University of Paraíba, in Brazil. The reference .obj loader, as well as the Matlab reference script were provided by the professor [Christian Pagot](https://github.com/capagot), as you can see in his documentation inside the folder, if you can understand Portuguese.

### How does it work?

#### obj_loader (Folder)
This is a reference model for what I had to achieve. My main goal was to load the same .obj that was given to this loader, but passing through all the graphics pipeline before drawing the final image onto the screen. More information at the blog post I referenced in the briefing.

#### Rasteriser classes
I reused - and improved - several of the classes I developed on a [former rasterisation project] (https://github.com/lupcorrea/raster-project), in order to actually draw the final pictures. 

#### loader.cpp
This is the responsible for reading the .obj file and translating its lines into usable data for the program. For this project, I only needed a list of vertices, and a list of triangles. If you need more structures than that, this is the file you'll want to fiddle with.

#### vertex.cpp and matrix.cpp
Mathematical classes I developed for this project. Nothing special to talk about this, but the fact that it took me more time than I am proud to admit to implement the dot product right. Absolutely nothing to regret. 

#### main.cpp
As in the rasteriser project, there is a callback function called MyGlDraw (void) in it. Put some code there and see the magic happening.

### General Stats
* As in version 1.1, approximately 20 hours were invested in total, including:
  * Research
  * Mathematics
  * Coding
  * Debugging
  * Struggling with matrix multiplications (yep, really)
  * Partially optimizing the code
  * Writing the post
* 5 lunchtimes spent on the Campus library
* Transistor Soundtrack addiction discovered
