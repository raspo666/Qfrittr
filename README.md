Credit for the Plotting Part must go to https://www.qcustomplot.com/


this really is my first attempt on doing something with Qt so it may look clumsy....
I thought about ksysguard, but don't expect worl&dog to have it installed, so I opted for Qcustomplot and "recycled"
their axis example.....

Anyway, Qfrittr [(Q)(fritzbox)(traffic)] tries to figure out where your box lives (ipv4) and gets some data from it once the test button is clicked 
Then monitoring starts.
Updates every 3 secs, vertical values are scaled as tradssic comes in....

build with qcreator, or:
``` 
$>qmake
$>make
```

   -rasp
