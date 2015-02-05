# Simulations

In this repository I'm going to write math/physics based simulations and put them here.  Currently just the renderer is implemented, but I'm supporting Emscripten from the get-go, so whatever's the current build you can run in the browser.

I had difficulties with `emmake`, so I simply made another makefile with the changes necessary for it to build with Emscripten.  To use it, run `make -f Em.Makefile`.  Your HTML page lies within `dist`.
