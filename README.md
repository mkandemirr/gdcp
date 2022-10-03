# GDCP


Geant4 Detector Construction Pattern (GDCP) is a C++ package that provides developers with a set of useful classes they can utilize during the detector construction phase of a Geant4 application. 
             
## The package structure:

*gdcp/*                  : This includes elements of the Builder Design Pattern.

*scntDetector/*          : This includes utility classes for the implementation of scintillation detectors.       
                          
*g4Example/*             : This is an example Geant4 application that uses the classes in gdcp and scntDetector directories for geometry 
                         construction. The SOLID and PANDA experiments are chosen as example detector setups. It also uses the NuSD  
                         framework to simplify the geomtry construction process.

*g4Example/testRun*     : It includes several figures obtained from sample runs of g4Example.
                  
*g4Example/gdcp*         : It includes header and source files of the gdcp library.

*g4Example/scntDetector* : It includes header and source files of the scntDetector library.

*g4Example/NuSD*         : It includes header and source files of NuSD framework.

*g4Example/include*      : it includes header files of the application.

*g4Example/src*          : it includes source files of the application.

*g4Example/data*         : It includes experimental input data for optical photon simulation. For example, scintillator emission spectrum, 
                         refractive index, absorption length, photosensor quantum efficiency, reflector reflectivity. 

*g4Example/materials*    : It includes numerous example concreate material builder classes derived from the VMaterialBuilder class.
                                                  
*g4Example/macros*       : It includes several macro files for the configuration of: <br>
- detector components such as size and material choice.  
  - *g4Example/macros/BoxComponent* 
  - *g4Example/macros/TubsComponent* 
  - *g4Example/macros/TrdComponent* 
- optical properties of materials and surfaces 
  - *g4Example/macros/matPropTable* 
  - *g4Example/macros/opticalSurface* 
- optical readout components such as PMT and SiPM 
  - *g4Example/macros/readout* 
- detector components visualization.   
  - *g4Example/macros/vis*  
                              
*g4Example/CMakeList*    : It contains commands which describe how to build the g4Example application.

*g4Example/Main.cc*      : It contains main() for the application.


##  Tested on 

Os: Linux (Ubuntu 20.04.4 LTS )
Architecture: x86_64
Compiler: gcc 9.4.0
Geant4.11.0.0     
                  
##  How to run the g4Example application?   

**Step 1** <br>
  Go in your home directory and create a subdirectory named g4Example
  $ cd ~
  $ mkdir g4Example

**Step 2** <br>
  Copy the GDCP.zip archive into the g4Example folder you created and extract it in this location.
  $ cp ~/Downloads/GDCP.zip ./ (assuming GDCP.tar.gz is in the ~/Downloads folder)
  $ unzip GDCP.zip

**Step 3** <br>
  Create a g4Example-build folder in the same directory with g4Example (in this example it is your home directory).
  $ mkdir g4Example-build

**Step 4** <br>
  Now go inside this build directory and run CMake to generate the Makefiles needed to build the application. Two arguments are 
  passed to CMake. The first argument to CMake is the path to the source directory that includes the CMakeList.txt file. The second    
  argument is the path to the build directory which the generated make files will be located. CMake will now run to configure the build 
  and generate Makefiles.
  $ cd g4Example-build
  $ cmake -S path/To/Source -B . 
  
**Step 5** <br>
  With the Makefile available, we can now build by simply running make: 
  $ make -jN
  CMake generated Makefiles support parallel builds, so N can be set to the number of cores on your machine (e.g. if you have four core 
  processor, you could set N to 4).

**Step 6** <br>
  The application is now ready to run. If you now list the contents of your build directory, you will notice that the executable Main has 
  been created. The program can be executed in two modes: interactive and batch. The first is for visualization, and the second is for 
  collecting statistics.
 
    "-b": run in batch mode,  need an argument to specify the macro file corresponding to the selected detector.
    "-i": run in interactive, need an argument to specify the macro file corresponding to the selected detector.
    "-r": Set the seed
    "-t": specify the number of threads (note: -t option is available only for multi-threaded mode.) 

   Two types of detectors are available. Arrange the g4Example/macros/detectorBuilder.mac file for setting 
   up the selected detector at desired configuration. If you change the detector type, for example, from panda to solid or vice-versa, 
   do not forget to change photosensor type in the detectorBuilder.mac. PANDA uses PMTs and SOLID uses SiPMs. Default is SOLID 
   experiment. Followings are some examples: 
    ./Main -i solid
    ./Main -b solid 
    ./Main -i panda 
    ./Main -b panda
    ./Main       

##  Contacts 

If you have any questions or wish to notify of updates and/or modification please contact:
 	
Mustafa Kandemir (mustafa.kandemir@erdogan.edu.tr)

  
