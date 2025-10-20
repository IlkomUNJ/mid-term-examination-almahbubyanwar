# (01) Analyzing the window size

In solving the line intersection problem this way, the appropriate window size depends on the pixel width of the line segments; it's also needed to take into account the possible patterns that may appear in intersections.

# (02) Appropriate pattern for finding a segment.

For each (sub)window, appropriate patterns are identified by scanning parts of the pixels and match them according to a specific matrix representing a pixel pattern of intersections. These patterns can be:

```
[[0, 1, 0, 0]
[1, 1, 1, 0]
[0, 1, 0, 0]
[0, 1, 0, 0]]

[[1, 0, 0, 1]
[0, 1, 1, 0]
[0, 1, 1, 0]
[1, 0, 0, 1]]
```
etc.

Frankly speaking though, a major downside of identifying intersections this way (through checking the pixel patterns directly) is that the possibilities of patterns can become complex and recognizing the patterns exclusively through it can be unreliable (since there are many possible patterns), and it's also computationally slow and inefficient. 

One other issue to be considered is that since anti-aliasing is originally applied, there are a lot of opaque pixels which aren't part of the actual line segment meant to hide the "jagged lines" on the canvas (this can be solved by only detecting pixels that have, in this case, the color pitch red/FF0000, and not just ones that aren't white/FFFFFF; but this doesn't solve the unreliability and inefficiency issue of using pixel pattern recognition for identifying intersections).