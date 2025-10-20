# (01) Analyzing the window gridsize

The method to identify the intersections of line segments uses smaller subwindows/grid cells of equal columns and rows count over the canvas window, of which intersections are detected only on subwindows/cells that have multiple line segments passing them.

Ideally speaking, the subwindow/cell size should be proportional on the number of segments possible for the case. Too large, and the algorithm will end up using a mostly brute-force/O(n^2) approach, since multiple segments will occur on the same subwindow. Too small, and phase done on each subwindow will take longer, since there are more subwindows to be processed.

# (02) Appropriate pattern for finding a segment.

For each (sub)window, appropriate patterns are identified by scanning parts of the pixels and match them according to a specific matrix representing a pixel pattern of intersections. Frankly speaking though, a major downside of identifying intersections this way (through checking the pixel patterns directly) is that the possibilities can become complex, and it's also computationally slow (especially without multithreading).