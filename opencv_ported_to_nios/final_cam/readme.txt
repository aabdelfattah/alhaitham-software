Readme 

Porting OpenCV to NIOS II using brute force :

o Output expected from this part is an embedded C++ code which is applicable on NIOS II processor.
o OpenCV on desktop platforms contains I/O instructions that are platform specific (ex: show images, control images using a slider, windows error messages and so on..) 
o On an embedded platform code must not contain any platform specific instructions.
o OpenCV on Visual studio give GUI capabilities by including "highgui" core.
GUI instructions Example:
	o cvNamedWindow("pic") ;
	o cvShowImage("pic",img_IN) ;
So porting task is to extract all windows platform instructions which doesn't work on an embedded platform, then generate an embedded C++ code valid for execution on Nios II’s IDE (Eclipse).


OpenCV consist of 4 main cores:
A) CV Component contains the basic image processing and higher-level computer vision algorithms.
B) ML Is the machine learning library, which includes many statistical classifiers and clustering tools
C) HighGUI Contains I/O routines and functions for storing and loading video and images.
D) CXCORE Contains the basic data structures and content.
So we find that
-  CV and CXCORE is the used cores .
-  ML is not used in our algorithm (can be neglected ) .
-  HIGHGUI core must be excluded.

Steps that where done to produce this port
a. Remove any I/O instructions from your algorithm.
b. Create empty project in NIOS II eclipse.
c. Add your main file.
d. Add OpenCV sources to your project but exclude the files that are not used by the algorithm in OpenCV which is done by tracing every function in the algorithm to know which files are needed and which are not.
e. Include all opencv files (.c, .cpp, .h, .hpp) in this project.
f. Build project.
g. You will get linking errors from inside OpenCV srcs itself, comment the parts that generate these errors or remove the files (if possible)

To use this port
a. Import the project to NIOS II eclipse.
b. replace our algorithm with yours and carefully track the dependencies and add OpenCV srcs that your algorithm relies on (if needed).

for inquries:
email: mo.kamal2012@gmail.com
email: a.abfattah@gmail.com
