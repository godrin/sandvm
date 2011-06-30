== Architecture layout
At the base is a very simplistic virtual machine with either
(a configurable amount of) registers, stacks and queues.
The count of instructions is as low as possible.

The VM has no direct access to the local machine whatsoever.
The whole communication to the local computer goes by pipes.

=== Subsystems
There will be a pipe for either
* stdin/stdout/stderr

A function based 
  