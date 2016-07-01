# Audio Synthesizer

## What is it?

The core of a programmable sound maker.

## What's special about it?

Its powerful, hardware-agnostic sound description language encourages massively-concurrent,
procedural waveform generation with minimal memory usage.
The language programs a simple virtual machine.
Many thousands of these programs can run in parallel
by employing many concurrent virtual machines and an efficient task-switching mechanism.

## What does it actually do?

The program in this repository, Synthesizer.exe, is just a simple test application of the engine.
Given a program file in the sound-description language, Synthesizer.exe will spontaneously
instantiate the program, associating the output of each with a random spatial location
within a small region of a 2D plane.
Those positions are used to alter the outputs via delays and modulation to simulate the sounds
at each of the two ears of a human in the center of that region.
The spatialized outputs of all running programs are mixed and finally sent to the default sound
output device, probably headphones or speakers.  
Synthesizer.exe uses several engines in parallel, on different CPU cores, to demonstrate that
in addition to concurrency within the sound description language, parallel engines add
a near-linear computation speedup when sufficient sound description language programs are instantiated
concurrently.

## Neat features of the sound description language:

* scalar math expressions include operators to specify random variable distribution parameters,
  which means that programs can be partially stochastic
* efficient composition of vector functions
* all synthesis statements are parameterized in the time by amplitude domain, which makes them oblivious to
  computer hardware details like sample rate and bit depth
* program instance state is small, enabling one engine to task-switch between many instances, and
  allowing instances to move among multiple engines during execution

## What can I use it for?

I use it to generate relaxing ambient sound at home, such as the gentle sound of running water,
the sound of heavy rain, or the sound of wind chimes.
You could use it to generate the sound track of an endless space battle (of the genre that have sound in space),
or if you're clever you might convince it to play beautiful music.

## What else could someone use it for?

The system is very efficient, and can easily handle thousands of different program instances simultaneously
in just a few megabytes of memory.
A person might use one or more engines to generate sounds in a virtual-reality environment prior to spatialization
and mixing, or they might connect it to a musical instrument like a digital keyboard to become the ultimate programmable
musical synthesizer.

## Can I use it?

Sure!  
My intended application of this engine needs me to solve a much-more difficult problem in
artificial intelligence, so until then these codes and this Synthesizer program are just sitting here.

