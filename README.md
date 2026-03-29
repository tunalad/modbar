# tunalad's EPIC modbar fork
Modbar is a modular status bar for dwm.

![preview](img/preview.png)

## Features
Each module is updated independently of the others based on a given time interval or by passing module name to a named pipe.

## Configuration
The program is configured via the config.h file. Modules are added to the modbar by editing the `modules` array.
- `FUNCTION`: this is a function that modbar runs and uses it's output. Can be an actual C function or a script that gets embedded in the binary itself (see `modules.h`).
- `INTERVAL`: defines how often a module should be refreshed (in seconds). `0` means no refresh.
- `SIGNAL`: defines the signal name that can interact with the pipe (eg.: `echo "!volume" > /var/run/user/1000/modbar.pipe`)

The `PIPE_PATH` directive tells the program where to create a named pipe that will be used to communicate with external programs. Modbar listens to the pipe in order to update a module on demand.

## Installation
Run `sudo make install` to install modbar.
