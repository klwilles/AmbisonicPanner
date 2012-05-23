AmbisonicPanner
===============

Ambisonic panner written in C++ and OpenFrameworks

The Ambisonic Panner is for panning sounds across 8 speakers. We used this custom panner for a large interactive wall. Sounds would move with the person as they walked across the screen. 

Looking at the wall from the front, you have the following speaker placement (X): 

```
-------X------------X------------X------------X-------
|                                                    |
|                                                    |
|                                                    |
|                   23' x 8' screen                  |
|                                                    |
|                                                    |
|                                                    |
-------X------------X------------X------------X-------
```

We used m-audio's Fast Track Ultra 8R sound interface (http://www.m-audio.com/products/en_us/FastTrackUltra8R.html).

There are two components to the software. 

1. The Ambisonic Panner (Sound Engine, Server)
2. The Ambisonic Client

The panner is what outputs the sound to the speakers and the client is what makes the request remotely. We used a mac to serve the sound and a PC to communicate which sounds it needed. 

The Panner has a graphical display (bare essentials) of where sounds are located and their intensities. There is an xml file that stores the locations of speaker configurations. 

You will need to put sounds in the bin/data/finalsounds directory in wav format. It will need to be in a format that OpenFramework supports. In addition to this, you will need to update the file names you will use in the Emitter.cpp file. 

I haven't tested this software apart from the project because of the complicated setup involved, but it should work. The original worked without a problem.  

Please make sure to go through all README files because there are other dependencies not included in the package that you will need to download. 