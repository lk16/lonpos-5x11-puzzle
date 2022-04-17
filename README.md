
# Lonpos 5 x 11 Puzzle
This repo implements a fast brute-force search to find all 371,020 solutions of the [Lonpos 505 brick puzzle](https://www.lonpos.com.au/products/lonpos-505).

![](lonpos.jpeg)

## How to use
Compile with `gcc lonpos.c -Wall -Wextra -Ofast -o lonpos` and run with `./lonpos`.

## Solution files
Solution files were intentionally added to this repo, even though they are quite large. This is so other people can search through solutions without having to compile and run this code on their own machine.

The machine readable version can be used in combination with text search tools such as `grep` to find solutions for puzzle exercises. For example for the very hard puzzle below:
```
+-----------------------+
| A A A J J J J D D D D |
|     A             D   |
|                       |
|                       |
|                       |
+-----------------------+
```
We can use `grep '^AAAJJJJDDDD..A......D' solutions/machine_readable.txt` to find that there is only one solution: `AAAJJJJDDDDCCAHHLFFIDICGHHLLLFIIICGHEELBBBKK`, which looks like this:
```
+-----------------------+
| A A A J J J J D D D D |
| C C A H H L F F I D I |
| C G H H L L L F I I I |
| C G H E E L B B B K K |
| C G G G E E E B B K K |
+-----------------------+
```


## Performance
This program runs in about 16 seconds on my machine, trying 155,674,519 configurations and thus achieving a speed of about 9,400,000 configurations per second.
When redirecting output to `/dev/null` speeds up to 13,500,000 can be reached on my machine.

## My machine

```
$ neofetch
             ...-:::::-...                 luuk@argon
          .-MMMMMMMMMMMMMMM-.              ----------
      .-MMMM`..-:::::::-..`MMMM-.          OS: Linux Mint 20.3 x86_64
    .:MMMM.:MMMMMMMMMMMMMMM:.MMMM:.        Kernel: 5.4.0-107-generic
   -MMM-M---MMMMMMMMMMMMMMMMMMM.MMM-       Uptime: 7 hours, 47 mins
 `:MMM:MM`  :MMMM:....::-...-MMMM:MMM:`    Packages: 3311 (dpkg)
 :MMM:MMM`  :MM:`  ``    ``  `:MMM:MMM:    Shell: bash 5.0.17
.MMM.MMMM`  :MM.  -MM.  .MM-  `MMMM.MMM.   Resolution: 2560x1440, 1280x1024, 1280x1024
:MMM:MMMM`  :MM.  -MM-  .MM:  `MMMM-MMM:   DE: Xfce
:MMM:MMMM`  :MM.  -MM-  .MM:  `MMMM:MMM:   WM: Xfwm4
:MMM:MMMM`  :MM.  -MM-  .MM:  `MMMM-MMM:   WM Theme: Mint-Y-Dark
.MMM.MMMM`  :MM:--:MM:--:MM:  `MMMM.MMM.   Theme: Mint-Y-Dark [GTK2], Mint-Y [GTK3]
 :MMM:MMM-  `-MMMMMMMMMMMM-`  -MMM-MMM:    Icons: Mint-Y-Dark [GTK2], Mint-Y [GTK3]
  :MMM:MMM:`                `:MMM:MMM:     CPU: AMD Ryzen 9 3950X (32) @ 3.500GHz
   .MMM.MMMM:--------------:MMMM.MMM.      GPU: NVIDIA GeForce GTX 1060 6GB
     '-MMMM.-MMMMMMMMMMMMMMM-.MMMM-'       Memory: 2909MiB / 32081MiB
       '.-MMMM``--:::::--``MMMM-.'
            '-MMMMMMMMMMMMM-'
               ``-:::::-``

```
