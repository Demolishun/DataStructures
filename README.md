# DataStructures
Various data structures for C++ to solve specific needs.

# CircularBuffer 
The CircularBuffer class is designed to push to the back and pop from the front.  The memory is fixed and is not allocated due to the pushing or popping.  The use case is for a realtime graphing application.  It provides a convenient way to feed data into the buffer and extract it out as needed.

Things to improve:
The ability to remove sections of buffer after using the begin and end iterators to find features in the data.  This would be good for searching for a trigger condition in an oscilloscope program.  Once the condition is detected in the data then the preceding data can be removed to start reading the data at the trigger point.  This would be a lossy operation on the data.
