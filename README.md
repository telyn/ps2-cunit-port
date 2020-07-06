## PS2Unit

PS2Unit is a script for compiling & installing CUnit for the Playstation 2 EE
core (and eventually IOP).

I decided to make it because CUnit doesn't exactly make itself easy to compile
in the first place, and it's a little extra tricky to get going on the EE.

It's not impossible and definitely not difficult for anyone who's used to PS2
programming, but I thought it'd be nice to help out newbies like me.

## Usage

You will need ps2dev installed with the PS2DEV environment variable set to the
location it was installed to - see https://github.com/ps2dev/ps2dev to ensure
you're set-up fully.

```console
git clone https://github.com/telyn/ps2unit.git
cd ps2unit
./install-cunit.sh
```
