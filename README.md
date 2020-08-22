## PS2Unit

PS2Unit is a script for compiling & installing CUnit for the Playstation 2 EE
core and IOP.

I decided to make it because CUnit doesn't exactly make itself easy to compile
in the first place, and it's a little extra tricky to get going on the EE, and
a lot harder to get going on the IOP.

It's not impossible and definitely not difficult for anyone who's used to PS2
programming, but I thought it'd be nice to help out newbies like me.

## Usage

You will need ps2dev installed with the PS2DEV environment variable set to the
location it was installed to - see https://github.com/ps2dev/ps2dev to ensure
you're set-up fully.

Run the following commands to download this repository and compile CUnit for EE
and IOP.

```console
git clone https://github.com/telyn/ps2-cunit-port.git
cd ps2unit-cunit-port
./install-cunit.sh
```

For an example of a CUnit program and its compilation for the host machine, EE,
and IOP, see the 'test' directory.

### IOP-specific notes

CUnit requires functions to be imported from the following IRX modules:

* alloc.irx
* stdio.irx
* sysclib.irx
* thbase.irx

Of those, all except alloc.irx are loaded by default by PS2Link (or already
loaded by the PS2 BIOS, I don't really know) - so you don't need to load them
prior to loading a program compiled with CUnit.

To load alloc.irx prior to loading your program:

```console
cd $PS2SDK/iop/irx
ps2client execiop host:alloc.irx
```
n.b. at least for me, `ps2client execiop` remains
