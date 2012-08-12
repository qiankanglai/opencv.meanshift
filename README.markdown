#1.Introduction

Hi, here is part of my current project and I hope this would be helpful. Some of the code is from opencv samples or other open source projects. 
I will try my best to include the origin source for every tiny tool and please contact me if you find something wrong.

Development Environment: [opencv 2.3](https://launchpad.net/~gijzelaar/+archive/opencv2.3), Ubuntu 11.10 amd64, gcc 4.6.1
Please refer to [here](http://opencv.willowgarage.com/wiki/CompileOpenCVUsingLinux) for details

More information can be found on my [website])http://qiankanglai.me/)

#2.Tool detials

This includes a filter and cluster, proposed in *D. Comaniciu, “Mean shift: A robust approach toward feature space analysis,” Analysis and Machine Intelligence,, vol. 24, no. 5, pp. 603-619, 2002. This code can be used as image segmentation*. 
The filtering part comes from [here](http://rsbweb.nih.gov/ij/plugins/download/Mean_Shift.java), because the build-in function ``PyrMeanShiftFiltering`` comes up with bad result!(You can refer to [my own question](http://stackoverflow.com/questions/9645713/whats-the-difference-between-edison-and-cvpyrmeanshiftfiltering))
The clustering part is mainly based on [EDISON system](http://coewww.rutgers.edu/riul/research/code/EDISON/doc/help.html)
Attention: In openCV, RGB2LUV is not exactly correct! One more map is used to make the data structure fit so I introduce a hack in the code.

#3.Lisence

You can use the code in the way whatever you like, but I will be very pleased if you can send me back your comments or include this github project in your work(Maybe in the code comments, aha~).



Author:
Kanglai Qian

#update

1. I upload a visual studio 2010 project setting for the project. Please modify your own system path for opencv 2.4

2. Replace Lab for Luv because of the color converation problem.
