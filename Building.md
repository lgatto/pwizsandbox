Building `pwiz`
==============

For details, see
- https://svn.code.sf.net/p/proteowizard/code/trunk/pwiz/doc/technical/building.html
- https://svn.code.sf.net/p/proteowizard/code/trunk/pwiz/doc/docs.html

1. Install dependencies. On linux 
- [Boost](http://boost.org):  `sudo apt-get install libboost1.53-all-dev`
- [gd](http://www.libgd.org): `sudo apt-get install libgd2-xpm-dev` (possibly optional)
- [fftw](http://www.fftw.org): `sudo apt-get install libfftw3-dev`

2. Get the data `svn checkout https://proteowizard.svn.sourceforge.net/svnroot/proteowizard/trunk/pwiz <pwiz-root>`

3. Build with `quickbuild.sh`

4. Get some example code

``` sh
mkdir hello_pwiz
cp doc/technical/hello_pwiz/hello_pwiz.cpp hello_pwiz
cp doc/technical/hello_pwiz/Jamfile.jam hello_pwiz
```

5. Build example code `quickbuild.sh hello_pwiz`

6. Test example code `hello_pwiz/hello_pwiz example_data/tiny.pwiz.1.1.mzML`
