# GridSearchVisualizer updated: 12.2.2023

Main purpose of this program is to showcase the functionality of different 
pathfinding algorithms and the ability to compare them with one another.

How to run:
Either use the included installer and after installing run GridSearhVisualizer.exe
or if you would rather use the source code then you need to have Qt 5.12. installed.

How to operate:
First choose a grid size from the options tab.
After that you can move the start node (green) and goal node (red) by 
dragging them with your mouse. Also Obstacles can be drawn by dragging the mouse over
white nodes. Obstacles can be changed back to free nodes by dragging over them again.
Pathfinding algorithm can be selected from the algorithm combo box.
After you have done your selections you can start the operation by pressing the "Run" button.
After the search has concluded and if a path was found you can perform pathsmoothing.
To smooth the found path you must select first a version of pathsmoothing to use from the
correct radio buttons and then press the "Smooth" button.
If you wish to remove from the scene the resuling changes from the pathfinding operation
press the "Clean" button.
If you wish to remove the previous and also all obstacles press the "Clear" button.
