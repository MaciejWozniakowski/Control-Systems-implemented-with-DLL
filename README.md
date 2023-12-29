# Control-Systems-implemented-with-DLL
This repo contains C code for control systems, for our Power Converters class. 
Step by step instructions to launch this code.
    1. In Plecs's DLL block, there should be a specified filepath (mine inlcuded in the filepath file)
    to a compiled .dll file. In this case it is main.dll. The DAB converter plecs model is included within the repo.
    The DLL block is included in the model
    2. To build the project, run te shell script with with the command
        sh c_to_dll.sh main.c 
        It should output main.o and main.dll files. 
    3. In some cases an error might occur, that initialization commands cannot be evaluated. To fix that,
    simply copy the model and initialization parameters to a new Plecs file. 
    4. Run the simulation. 
