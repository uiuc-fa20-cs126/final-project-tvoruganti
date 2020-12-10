<h1>AStar Path Finder App</h1>
	
<h3>Building the project</h3>
1. Make sure you have cinder installed.
2. Move this project into cinder.
3. Load the CMake File.
4. Edit settings in path_finding_app.cc
5. Run the app in cinder_app_main.cc

<h3>What does this app do?</h3>	
![](Images/pathfinder.png?raw=true)

<h5>Summary</h5>	

This Application allows the user to create a maze like graph with points
and obstacles. The user can place a start and end point and then draw walls/obstacles 
on the screen. The Application will find the shortest path from the start to the
end point while navigating around the obstacles using the A* path finding algorithm.
The user can also customize the dimensions of this graph to their will. 

<h5>Buttons</h5>	

A List of all the buttons the user can press. Selected buttons will be 
highlighted yellow.

- Start and End Point Buttons
    - Green Button for Start Point and Red Button for End Point
    - Can place start and end points by right-clicking on the graph
    - First select either the start or end button, then right click on the graph to move that specific button
    to the selected cell
- Clear Button
    - Removes all walls and resets the start point to the top left corner and
    the end point to the bottom right corner
- Show Path Button
    - Displays the shortest path from the start point to the end point.
    - Will display nothing if no path is found
    - Press button repeatedly to toggle showing the path or not
    - Path will change in real time as graph is changed
- Save Graph Button
    - Will save the current arrangement of points, walls, and dimensions to a file
    that can be loaded at a later point in time.
- Load Graph Button
    - Loads a graph from a file to the screen. 
    - You can edit anything after it is loaded.

<h5>Additional Instructions</h5>	

You can draw gray walls by left-clicking on an empty cell. Left-clicking on 
a wall will turn it back to an empty, white cell. Left-clicking a point will 
do nothing. 

	


