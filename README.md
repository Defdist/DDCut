# DDCut

DDCut is easy-to-use, cross-platform software provided by Defense Distributed for use with their Ghost Gunner CNC mill. For more information, visit the Ghost Gunner website (https://ghostgunner.net) or read the Ghost Gunner 2 operator's manual (https://cdn.shopify.com/s/files/1/0206/7642/files/GG2_Manual_2017.pdf?16884723091915665092).

## Build
For instructions on how to compile and build the code, see docs/BUILD.md.

## Design
DDCut2 is a cross-platform C++ application that runs as a daemon and communicates via USB with Ghost Gunner CNC mills. It has an HTML/CSS/JS front-end that communicates with the daemon via a custom Node.JS V8 add-on. The logic is entirely separate from the UI, which makes it trivial to swap out different implementaitons of the UI.

### Front-end (HTML/CSS/JS)
TODO - The front end is still being developed.

### Integration (Node.JS)
A Node.JS addon is provided to wrap DDCut2 library's daemon. This allows the front-end to simply import or 'require' the addon anywhere it needs to access the library.

The entire add-on consists of just one file, NodeWrapper.cpp, which wraps the daemon and contains a Node.JS API for each of the daemon's public functions. The add-on should contain no business logic, and should only unpack requests from the front-end, call the daemon, and translate the daemon's response to be returned to the front-end.

### Back-end/Daemon (C++)
**TODO: Re-evaluate all of this after phase 3 is complete**
The daemon is written in C++, and maintains the state of the application, contains all of the application's logic, and handles all communication with the Ghost Gunner CNC mill. A single entry-point is provided which allows the developer to easily include DDCut2 as a library in other applications.
The majority of the classes can be understood as being one of 5 different types:

1. Entry-points - Easy-to-use interfaces that provide entry into the library by consumers.
	* DDCutDaemon - Currently the only entry-point into the library. DDCutDaemon is a singleton, so there's no need for a consuming application to hold onto a copy of it. To get an instance of the daemon, simply call DDCutDaemon::GetInstance(), which will provide a reference to the singleton instance. You are then free to use any of its well-documented functions. NOTE: Initialization is done in a thread, so the first time an instance is retrieved, it is necessary for the consumer to call IsFullyInitialized() until it returns true before using the instance.
	
2. Managers - Singletons that maintain application state.
	* DDFileManager - Provides consumers access to the currently .dd file, if one has been selected.
	* JobManager - Manages the state of the current job being executed, and keeps track of which operation is in progress.
	* GhostGunnerManager - Provides a way to get a list of, and connect to, any Ghost Gunners that are plugged into the user's computer. After a Ghost Gunner has been found and selected, consumers must call InitializeConnection() before using the GhostConnection, and must call ShutdownGhostGunner() whenever the GhostConnection is no longer needed.
	* GhostDriverManager - Use this to install the arduino driver needed to communicate with the Ghost Gunner, or to load new firmware onto a Ghost Gunner. This maintains a cache of the currently installed firmware version for any connected Ghost Gunners.
	* SettingManager - On first use, loads settings from the 'ghost.conf' file in the same directory as the application's executable, if it exists. It maintains a cache of the settings, and keeps 'ghost.conf' in sync with the cache when updates are made. NOTE: Consumers attempting to update multiple settings at once are strongly encouraged to use UpdateSettings(), instead of individually updating each setting through the setter functions (eg. SetEnableSlider() or SetTimeout()).
	
3. Models - Containers that represent 'real-world' objects that any of the logic classes can read and/or manipulate.
	* Archive - Wrapper around Minizip’s unzip library to give OO access to a zip file.
	* Manifest - Represents a YAML manifest file as a vector of Jobs.
	* DDFile - Represents a .dd file. Wrapper around Manifest & Archive.
	* Coordinate - Represents a coordinate with an X, Y, and Z value.
	* GCodeLine - Represents a line of G-Code text.
	* GCodeFile - Represents a G-Code file, and contains a vector of GCodeLines.
	* Operation - Represents an operation from the manifest YAML file. Consists of a GCodeFile and image.
	* Job - Represents a set of steps/operations to perform a task. Includes a title, a prompt, a vector of Operations, a vector of strings that are filenames of guides, and a vector of strings that are filenames of models.
	* GhostConnection - Represents a connection to a specific Ghost Gunner CNC mill.

4. Utilities - Provide common, re-usable logic, often through static methods.
	* OSUtility - Wraps OS-specific calls (like GetExecPath) to hide cross-platform complexity from consumers.
	* FileUtility - Provides easy-to-use functions for working with file systems.
	* DDMath - TODO: This is more of a model, since it currently consists of a Point structure and a Matrix structure.
	* Logger - Wraps the logging library to provide an easy way to write to the log file.

5. Tasks - Perform a specific task, typically providing a single public method.
	* ConnectionInitializer - Given a reference to a GhostConnection, it handles the initial connection to the GhostGunner, and prepares it to be ready to handle commands.
	* M100 - Executes an M100 machine code on the Ghost Gunner. TODO: Define what M100 is.
	* M101 - Executes an M101 machine code on the Ghost Gunner. TODO: Define what M101 is.
